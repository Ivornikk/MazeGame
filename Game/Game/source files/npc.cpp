#include "../headers/npc.h"

// Returns normalized vector of the npc's +Z axis.
Vector3 getForward(Matrix matrix) {
    Vector3 res = Vector3Normalize({ matrix.m8, matrix.m9, matrix.m10 });
    return res;
}

// Returns coordinates of the center of a cell in the 3D space.
Vector3 getCellCenter(Vector2 cell) {
    float x = cell.x * 2.f - 1.f;
    float z = cell.y * 2.f - 1.f;

    return { x, 1.f, z };
}


ModelAnimation NPC::getAnimationByName(std::string name, ModelAnimation* animations, int animationsCount) {
    for (int i = 0; i < animationsCount; i++) {
        if (animations[i].name == name) return animations[i];
    }
    return animations[0];
}

NPC::NPC(Camera3D camera, int** maze, float healthTemp, float damageTemp, float speedTemp, float rangeTemp, int mazeWidthTemp, int mazeHeightTemp, ResourceManager* resourceManager) {
    mazeArray = maze;
	path = {};
	health = healthTemp;
	damage = damageTemp;
	speed = speedTemp;
	range = rangeTemp;
	mazeWidth = mazeWidthTemp;
	mazeHeight = mazeHeightTemp;
	
    // Cooldown for hits of 2 seconds
    cooldown = 2.f;
    timePassedAfterHit = 0.f;

	emptyCellsNum = 0;
	initializeEmptyCells();
	// npcMap is passed because the function has to modify the value of the original variable, too.
	spawnCell = chooseSpawnCell(maze);
    currentCell = spawnCell;
	pos = { spawnCell.x * 2 - 1, 1.f, spawnCell.y * 2 - 1};

    rm = resourceManager;
    rm->loadNpcModel(id, "models/glb/firecrab.glb");
    rm->loadNpcAnimations(id, "models/glb/firecrab.glb", &animationsCount);

    model = rm->getNpcModel(id);

    animCurrentFrame = 0;

    animationsCount = rm->getNpcAnimationsCount(id);
    animations = rm->getNpcAnimations(id);
    model.transform = MatrixMultiply(model.transform, MatrixTranslate(0, -50, 0));
    //model.transform = MatrixMultiply(model.transform, MatrixRotate({ 1, 0, 0 }, 90 * DEG2RAD));

    healthBar = new NpcHealthBar(health, pos, camera);
    isDead = false;
}

NPC::~NPC() {
    rm->unloadNpc(id);
}

void NPC::Display(Vector2 newPlayerPos, Player* player, Camera3D newCamera, int npcsLasted) {
    Update(newPlayerPos, player, newCamera, npcsLasted);
    Draw();
}

void NPC::Draw() {
    if (!isDeathFinished) {
        DrawModel(model, pos, 0.02f, WHITE);
    }
    handleHealthBarDrawing();
}

void NPC::Update(Vector2 newPlayerPos, Player* player, Camera3D newCamera, int npcsLasted) {
    if (playerPos.x != newPlayerPos.x || playerPos.y != newPlayerPos.y) {
        playerPos = newPlayerPos;
        path = bfsShortestPath();
    }
    if (!isDead && isStunFinished)
        followPlayer();
    handleAnimation();
    if (!isDead) {
        damagePlayer(player);
    }
    healthBar->Update(newCamera, pos, health);
    npcsCount = npcsLasted;
}

void NPC::updateCooldown() {
    if (timePassedAfterHit < cooldown && isStunFinished)
        timePassedAfterHit += GetFrameTime();
}


void NPC::damagePlayer(Player* player) {
    updateCooldown();
    if (path.size() <= 2 && !attackAnimFinished) {
        if (timePassedAfterHit >= cooldown) {
            player->takeDamage(damage);
            timePassedAfterHit = 0.f;
        }
    }
}

void NPC::takeDamage(float damage) {
    health -= damage;
    if (health <= 0)
        isDead = true;
    else
        isStunFinished = false;
    animCurrentFrame = 0;
}

float NPC::getHealth() {
    return health;
}

// Takes coordinates of a point in the 3D scene and returns coordinates of the cell in which that point lies.
Vector2 getCellBy3DPos(Vector3 pos, int mazeWidth, int mazeHeight) {
    Vector2 result = {};

    for (int i = 1; i < mazeHeight; i++) {
        for (int j = 1; j < mazeWidth; j++) {
            Vector3 maxPos = { j * 2 + 1.f, 1.f, i * 2 + 1.f };
            Vector3 minPos = { j * 2 - 1.f, 1.f, i * 2 - 1.f };

            if (pos.x > minPos.x && pos.x < maxPos.x && pos.z > minPos.z && pos.z < maxPos.z)
                result = { pos.x, pos.z };
        }
    }
    return result;
}

// Updates the npc position to follow the player
void NPC::followPlayer() {
    if (path.size() >= 2) {
        mazeArray[(int)currentCell.y][(int)currentCell.x] = 1;

        float step = speed * GetFrameTime();

        Vector2 targetCell = path[1];
        Vector2 targetPos = GetCellCenter(targetCell);

        if (path.size() <= range) isTriggered = true;

        if (isTriggered) {
            // Moving to the target
            if (pos.x < targetPos.x) pos.x = std::min(pos.x + step, targetPos.x);
            if (pos.x > targetPos.x) pos.x = std::max(pos.x - step, targetPos.x);

            if (pos.z < targetPos.y) pos.z = std::min(pos.z + step, targetPos.y);
            if (pos.z > targetPos.y) pos.z = std::max(pos.z - step, targetPos.y);

            // Checking if npc reached target cell
            if (abs(pos.x - targetPos.x) < 0.01f && abs(pos.z - targetPos.y) < 0.01f)
            {
                pos.x = targetPos.x;
                pos.z = targetPos.y;

                currentCell = targetCell;
                path = bfsShortestPath();
            }
            handleOrientation();
        }
        // Updates npc's position in the maze array so that it can be read by the minimap
        mazeArray[(int)currentCell.y][(int)currentCell.x] = 2;
    }
}

void NPC::handleOrientation() {
    Ray faceDirection = { pos, getForward(model.transform) };

    Vector3 cellPos = getCellCenter(path[1]);
    BoundingBox cellBox = { {cellPos.x-1, 0, cellPos.z-1}, {cellPos.x+1, 4, cellPos.z+1} };

    while (!GetRayCollisionBox(faceDirection, cellBox).hit) {
        model.transform = MatrixMultiply(model.transform, MatrixRotateXYZ({ 0.f, 90.f * DEG2RAD, 0.f }));
        faceDirection = { pos, getForward(model.transform) };
    }
}

void NPC::handleAnimation() {
    ModelAnimation idleAnim = getAnimationByName("Idle", animations, animationsCount);
    ModelAnimation walkAnim = getAnimationByName("Walk_forward", animations, animationsCount);
    ModelAnimation attackAnim = getAnimationByName("Attack", animations, animationsCount);
    ModelAnimation damagedAnim = getAnimationByName("Damage", animations, animationsCount);
    ModelAnimation deathAnim = getAnimationByName("Death", animations, animationsCount);

    animCurrentFrame++;

    if (path.size() <= 2 && timePassedAfterHit >= cooldown && attackAnimFinished) {
        animCurrentFrame = 0;
        attackAnimFinished = false;
    }
    if (isDead && !isDeathFinished) {
        if (animCurrentFrame >= deathAnim.frameCount) {
            isDeathFinished = true;
            mazeArray[(int)currentCell.y][(int)currentCell.x] = 1;
            return;
        }
        UpdateModelAnimation(model, deathAnim, animCurrentFrame);
    }
    else if (!isStunFinished) {
        if (animCurrentFrame >= damagedAnim.frameCount) {
            animCurrentFrame = 0;
            isStunFinished = true;
            return;
        }
        UpdateModelAnimation(model, damagedAnim, animCurrentFrame);
    }
    else if (!attackAnimFinished) {
        if (animCurrentFrame >= attackAnim.frameCount) {
            animCurrentFrame = 0;
            attackAnimFinished = true;
            return;
        }
        UpdateModelAnimation(model, attackAnim, animCurrentFrame);
    }
    else {
        if (path.size() <= 2 || !isTriggered) {
            if (animCurrentFrame == idleAnim.frameCount) animCurrentFrame = 0;
            UpdateModelAnimation(model, idleAnim, animCurrentFrame);
        }
        else {
            if (animCurrentFrame == idleAnim.frameCount) animCurrentFrame = 0;
            UpdateModelAnimation(model, walkAnim, animCurrentFrame);
        }
    }
}

void NPC::initializeEmptyCells() {
	for (int i = 0; i < mazeHeight; i++) {
		for (int j = 0; j < mazeWidth; j++) {
			if (mazeArray[i][j] == 1) {
				emptyCells.push_back({ (float)j, (float)i });
				emptyCellsNum++;
			}
		}
	}
}

void NPC::setPlayerPos(Vector2 pos) {
    playerPos = pos;
}

// Makes sure the health bar is drawn only when the player sees the npc.
void NPC::handleHealthBarDrawing() {

    Ray faceDirection = { pos, getForward(model.transform) };

    Vector3 cellPos = getCellCenter(playerPos);
    BoundingBox cellBox = { {cellPos.x - 1, 0, cellPos.z - 1}, {cellPos.x + 1, 4, cellPos.z + 1} };

    RayCollision collision = GetRayCollisionBox(faceDirection, cellBox);

    if (collision.hit && collision.distance <= 4)
        healthBar->Draw();
}

void NPC::setKey(bool val) {
    hasKey = val;
}

bool NPC::checkIfHasKey() {
    return hasKey;
}

Vector2 NPC::chooseSpawnCell(int** npcMapTemp) {
	srand(time(0));

	int randomEmptyCell = rand() % emptyCellsNum;

    while (emptyCells[randomEmptyCell].x <= 5 || emptyCells[randomEmptyCell].y <= 5) {
        randomEmptyCell = rand() % emptyCellsNum;
    }

    int x = emptyCells[randomEmptyCell].x;
    int y = emptyCells[randomEmptyCell].y;
	npcMapTemp[y][x] = 2;

	return emptyCells[randomEmptyCell];
}

Vector3 NPC::getPosition() {
    return pos;
}

BoundingBox NPC::getHitbox() {
    BoundingBox hitbox = { {pos.x - 1, 0, pos.z - 1}, {pos.x + 1, 1, pos.z + 1} };

    return hitbox;
}

// checks if a cell can be in the path to the player
bool NPC::isCellValid(int x, int y) {
	return x > 0 && y > 0 && x < mazeHeight && y < mazeWidth && (mazeArray[y][x] == 1 || mazeArray[y][x] == 2);
}

bool NPC::getIsDead() {
    return isDeathFinished;
}

// finds the shortest route to the player
std::vector<Vector2> NPC::bfsShortestPath() {

    if (currentCell.x == playerPos.x && currentCell.y == playerPos.y) {
        return {
            currentCell,
            currentCell
        };
    }

    const int dx[4] = { -1, 1, 0, 0 };
    const int dy[4] = { 0, 0, -1, 1 };


    Vector2 startCell = { std::ceil(pos.x / 2.f), std::ceil(pos.z / 2.f) };
    Vector2 endCell = playerPos;

    std::vector<std::vector<bool>> visited(mazeHeight, std::vector<bool>(mazeWidth, false));
    std::vector<std::vector<Vector2>> parent(mazeHeight, std::vector<Vector2>(mazeWidth, { -1, -1 }));

    std::queue<Vector2> queue;
    queue.push(startCell);
    visited[startCell.y][startCell.x] = true;

    while (!queue.empty()) {
        Vector2 cell = queue.front();
        queue.pop();

        int x = cell.x;
        int y = cell.y;

        if (x == endCell.x && y == endCell.y) {

            std::vector<Vector2> path;
            Vector2 cur = endCell;

            while (!(cur.x == startCell.x && cur.y == startCell.y)) {
                path.push_back(cur);
                Vector2 p = parent[cur.y][cur.x];
                cur = p;
            }
            path.push_back(startCell);
            reverse(path.begin(), path.end());
            path.erase(path.end() - 1);
            path.push_back(currentCell);
            return path;
        }

        for (int dir = 0; dir < 4; dir++) {
            int newX = x + dx[dir];
            int newY = y + dy[dir];

            if (isCellValid(newX, newY) && !visited[newY][newX]) {
                visited[newY][newX] = true;
                parent[newY][newX] = { (float)x, (float)y };
                queue.push({ (float)newX, (float)newY });
            }
        }
    }

    return {};
}
