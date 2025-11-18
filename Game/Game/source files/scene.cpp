#include "../headers/scene.h"
void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color)
{
    float x = position.x;
    float y = position.y;
    float z = position.z;

    // Set desired texture to be enabled while drawing following vertex data
    rlSetTexture(texture.id);

    // Vertex data transformation can be defined with the commented lines,
    // but in this example we calculate the transformed vertex data directly when calling rlVertex3f()
    //rlPushMatrix();
        // NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
        //rlTranslatef(2.0f, 0.0f, 0.0f);
        //rlRotatef(45, 0, 1, 0);
        //rlScalef(2.0f, 2.0f, 2.0f);

    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    // Front Face
    rlNormal3f(0.0f, 0.0f, 1.0f);       // Normal Pointing Towards Viewer
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
    // Back Face
    rlNormal3f(0.0f, 0.0f, -1.0f);     // Normal Pointing Away From Viewer
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
    // Top Face
    rlNormal3f(0.0f, 1.0f, 0.0f);       // Normal Pointing Up
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    // Bottom Face
    rlNormal3f(0.0f, -1.0f, 0.0f);     // Normal Pointing Down
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    // Right face
    rlNormal3f(1.0f, 0.0f, 0.0f);       // Normal Pointing Right
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
    // Left Face
    rlNormal3f(-1.0f, 0.0f, 0.0f);    // Normal Pointing Left
    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
    rlEnd();
    //rlPopMatrix();

    rlSetTexture(0);
}

void DrawPlaneTexture(Texture2D texture, Vector3 center, Vector2 size, Color color) {
	float x = center.x;
	float y = center.y;
	float z = center.z;

	float width = size.x;
	float height = 0;
	float length = size.y;

	rlSetTexture(texture.id);
	rlBegin(RL_QUADS);
	rlColor4ub(color.r, color.g, color.b, color.a);

	//Top Face
	rlNormal3f(0.0f, 1.0f, 0.0f);       // Normal Pointing Up
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
	//Bottom Face
	rlNormal3f(0.0f, -1.0f, 0.0f);     // Normal Pointing Down
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Top Left Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad

	rlSetTexture(0);
}

Scene::Scene(int** mazeTemp, int widthTemp, int heightTemp, ResourceManager* resourceManager) {
	rm = resourceManager;
	camera = { 0 };
	camera.position = { 1.0f, 1.0f, 1.0f };
	camera.target = { 0.0f, 0.5f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 60.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	mazeArray = mazeTemp;
	mazeWidth = widthTemp;
	mazeHeight = heightTemp;

	finishCell = { (float)mazeWidth - 1, (float)mazeHeight - 1 };
	finishCell = GetCellCenter(finishCell);

	minEnemies = 3;
	maxEnemies = 6;
	srand(time(0));
	int npcsNum = rand() % (maxEnemies - minEnemies + 1) + minEnemies;

	for (int i = 0; i < npcsNum; i++) {
		npcs.push_back(new NPC({ 0 }, mazeArray, 100, 10, 4, 4, widthTemp, heightTemp, resourceManager));
	}
	npcs[0]->setKey(true);
	npcs[1]->setKey(true);
	npcs[2]->setKey(true);
}
void Scene::Display(Player* player, GAME_STATES* gameState) {

	if (IsKeyPressed(KEY_R)) {
		*gameState = GAME_PAUSE;
		EnableCursor();
	}

	if (*gameState != GAME_PAUSE)
		Update(player, gameState);

	BeginMode3D(camera);
	Draw();
	for (NPC* npc : npcs)
		npc->Display({ ceil(camera.position.x / 2.f), ceil(camera.position.z / 2.f) }, player, camera, npcs.size());
	handleGameFinish(gameState, player);
	EndMode3D();
	drawCrossbar();
	// Displays player's current position
	std::string pos = "X: " + std::to_string(camera.position.x) + " Z: " + std::to_string(camera.position.z);
	DrawText(pos.c_str(), GetScreenWidth() / 2.f, 5, 25, WHITE);
}

void Scene::Update(Player* player, GAME_STATES* gameState) {
	handleCameraCollision();
	handlePlayerAttack(player);
	if (*gameState != GAME_WON)
		DisableCursor();
	updateItems(player);
}

void Scene::Draw() {
	float playerX = camera.position.x;
	float playerZ = camera.position.z;

	for (int i = 0; i < mazeHeight; i++) {
		for (int j = 0; j < mazeWidth; j++) {
			Vector3 pos = { 2.f * j - 1.f, 1.f, 2.f * i - 1.f };
			DrawPlaneTexture(floorTexture, { pos.x, 0, pos.z }, { 2, 2 }, DARKGRAY);
			DrawCubeTexture(ceilingTexture, { pos.x, 2.5, pos.z }, 2, 0.1, 2, DARKGRAY);
			if (mazeArray[i][j] == 0) {

				float distance = Vector3Distance(pos, { playerX, 1.f, playerZ });
				float brightness = Clamp(1.f - distance * 0.1f, 0.3f, 1.f);

				Color resultColor = {
					(unsigned int)(WHITE.r * brightness),
					(unsigned int)(WHITE.g * brightness),
					(unsigned int)(WHITE.b * brightness),
					255
				};

                DrawCubeTexture(texture, pos, 2, 3, 2, resultColor);
			}
		}
	}
	drawItems();
}

void Scene::drawCrossbar() {
	float radius = 20;
	Vector2 pos = GetWorldToScreen(camera.target, camera);
	DrawRectangle(pos.x - radius , pos.y, radius * 2, 1, { 255,255,255,100 });
	DrawRectangle(pos.x, pos.y - radius, 1, radius * 2, { 255,255,255,100 });
}

Vector2 Scene::getPlayerMazePosition() {
	// The coordinates are divided by 2 because in the scene every cell is actually 2 units of measure
	Vector2 pos = { camera.position.x / 2.f, camera.position.z / 2.f };
	return pos;
}

void Scene::handleCameraCollision() {
	Vector3 oldPos = camera.position;
	Vector3 oldTarget = camera.target;
	UpdateCamera(&camera, CAMERA_FIRST_PERSON);

	if (isWallAtPosition(camera.position) && camera.position.y <= 4.f) {
		camera.position = oldPos;
		camera.target = oldTarget;
	}
}

bool CheckCollisionPointBox(Vector3 point, BoundingBox box) {
	return (
		point.x >= box.min.x &&
		point.x <= box.max.x &&
		point.z >= box.min.z &&
		point.z <= box.max.z &&
		point.y >= box.min.y &&
		point.y <= box.max.y
		);
}

void Scene::handlePlayerAttack(Player* player) {
	rm->setNpcsCount(npcs.size());
	for (int i = 0; i < npcs.size(); i++) {
		NPC* npc = npcs[i];
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
			Vector3Distance(camera.position, npc->getPosition()) <= player->getRange() &&
			player->isReloaded()) {
			npc->takeDamage(player->getDamage());
		}
		if (npc->getIsDead()) {
			if (npc->checkIfHasKey())
				droppedItems.push_back(new Key(rm, npc->getPosition()));
			npc->~NPC();
			npcs.erase(npcs.begin() + i);
		}
	}
}

void Scene::reset() {
	for (int i = 0; i < npcs.size(); i++) {
		npcs[i]->~NPC();
		npcs.erase(npcs.begin() + i);
	}

	for (int i = 0; i < droppedItems.size(); i++) {
		droppedItems.erase(droppedItems.begin() + i);
	}

	srand(time(0));
	int npcsNum = rand() % (maxEnemies - minEnemies + 1) + minEnemies;

	for (int i = 0; i < npcsNum; i++)
		npcs.push_back(new NPC(camera, mazeArray, 100, 10, 4, 4, mazeWidth, mazeHeight, rm));
	npcs[0]->setKey(true);
	npcs[1]->setKey(true);
	npcs[2]->setKey(true);

	camera.position = { 1.0f, 1.0f, 1.0f };
	camera.target = { 0.0f, 0.5f, 0.0f };
}

void Scene::drawItems() {
	for (int i = 0; i < droppedItems.size(); i++)
		droppedItems[i]->Draw();
}

void Scene::updateItems(Player* player) {
	for (int i = 0; i < droppedItems.size(); i++) {
		droppedItems[i]->Update();
		if (CheckCollisionPointBox(camera.position, droppedItems[i]->getHitbox())) {
			droppedItems.erase(droppedItems.begin() + i);
			player->pickUpItem(new Key(rm, { 0, 0, 0 }));
		}
	}
}

bool Scene::isWallAtPosition(Vector3 pos) {
	int cellX = ceil(pos.x / 2.f);
	int cellY = ceil(pos.z / 2.f);
	
	if (mazeArray[cellY][cellX] == 0 || pos.x <= 0 || pos.z <= 0)
		return true;
	return false;
}

Vector3 Scene::getCameraTarget() {
	return camera.target;
}

void Scene::handleGameFinish(GAME_STATES* gameState, Player* player) {
	BoundingBox finishCellHitbox = {
		{finishCell.x - 2, 0, finishCell.y - 2},
		{finishCell.x + 2, 2, finishCell.y + 2}
	};
	DrawBoundingBox(finishCellHitbox, GREEN);
	if (CheckCollisionPointBox(camera.position, finishCellHitbox)) {
		if (player->getKeysCount() >= 3) {
			*gameState = GAME_WON;
			EnableCursor;
		}
	}
}

Vector3 Scene::getCameraPos() {
	return camera.position;
}

Camera3D Scene::getCamera()
{
	return camera;
}
