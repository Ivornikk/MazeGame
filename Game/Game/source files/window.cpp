#include "../headers/window.h"
Window::Window(float marginX, float marginY, std::string heading) {
	buttons = {};
	title = heading;
	window = { marginX, marginY, GetScreenWidth() - 2 * marginX, GetScreenHeight() - 2 * marginY};
	backgroundColor = GRAY;
	outlineColor = DARKGRAY;
}

void Window::Draw() {
	DrawRectangleRec(window, backgroundColor);
	DrawTexture(backgroundTexture, window.x, window.y, LIGHTGRAY);
	DrawRectangleLinesEx(window, 3, outlineColor);
	float textWidth = MeasureText(title.c_str(), 50);
	DrawText(title.c_str(), GetScreenWidth() / 2 - textWidth / 2, window.y + 5, 50, WHITE);
	for (StateButton button : buttons) {
		button.button.Draw();
	}
}

void Window::Update(GAME_STATES* state) {
	for (StateButton button : buttons)
		if (button.button.isClicked()) {
			*state = button.state;
		}
}

void Window::setBackgroundColor(Color color) {
	backgroundColor = color;
}

void Window::setOutlineColor(Color color) {
	outlineColor = color;
}

void Window::addButton(Position pos, int margin, int width, int height, const char* text, GAME_STATES state, Color color, Color textColor, const char* imagePath) {
	
	if (pos == CENTER) {
		float buttonsHeight = 0;
		for (StateButton el : buttons)
			if (el.pos == CENTER) {
				buttonsHeight += el.button.getRect().height + el.borderMargin;
			}
		Button button = Button(
			GetScreenWidth() / 2 - width / 2,
			GetScreenHeight() / 2 - height / 2 + buttonsHeight + margin,
			width, height, text, color, textColor, imagePath
		);
		StateButton result = {
			button, state, pos, margin
		};
		buttons.push_back(result);
	}

	else if (pos == TOP_RIGHT) {
		float buttonsHeight = 0;
		for (StateButton el : buttons)
			if (el.pos == TOP_RIGHT) {
				buttonsHeight += el.button.getRect().height + el.borderMargin;
			}
		Button button = Button(
			window.x + window.width - width - margin,
			buttonsHeight + margin,
			width, height, text, color, textColor, imagePath
		);
		StateButton result = {
			button, state, pos, margin
		};
		buttons.push_back(result);
	}

	else if (pos == RIGHT) {
		float buttonsHeight = 0;
		for (StateButton el : buttons)
			if (el.pos == RIGHT) {
				buttonsHeight += el.button.getRect().height + el.borderMargin;
			}
		Button button = Button(
			window.x + window.width - width - margin,
			GetScreenHeight() / 2 - height / 2 + buttonsHeight + margin,
			width, height, text, color, textColor, imagePath
		);
		StateButton result = {
			button, state, pos, margin
		};
		buttons.push_back(result);
	}

	else if (pos == BOTTOM_RIGHT) {
		float buttonsHeight = 0;
		for (StateButton el : buttons)
			if (el.pos == BOTTOM_RIGHT) {
				buttonsHeight += el.button.getRect().height + 15;
			}
		Button button = Button(
			window.x + window.width - width - margin,
			window.y + window.height - height - buttonsHeight - margin,
			width, height, text, color, textColor, imagePath
		);
		StateButton result = {
			button, state, pos, margin
		};
		buttons.push_back(result);
	}

	else if (pos == BOTTOM) {
		float buttonsHeight = 0;
		for (StateButton el : buttons)
			if (el.pos == BOTTOM) {
				buttonsHeight += el.button.getRect().height + el.borderMargin;
			}
		Button button = Button(
			GetScreenWidth() / 2 - width / 2,
			window.y + window.height - height - buttonsHeight - margin,
			width, height, text, color, textColor, imagePath
		);
		StateButton result = {
			button, state, pos, margin
		};
		buttons.push_back(result);
	}

	else if (pos == BOTTOM_LEFT) {
		float buttonsHeight = 0;
		for (StateButton el : buttons)
			if (el.pos == BOTTOM_LEFT) {
				buttonsHeight += el.button.getRect().height + el.borderMargin;
			}
		Button button = Button(
			margin,
			window.y + window.height - height - buttonsHeight - margin,
			width, height, text, color, textColor, imagePath
		);
		StateButton result = {
			button, state, pos, margin
		};
		buttons.push_back(result);
	}

	else if (pos == LEFT) {
		float buttonsHeight = 0;
		for (StateButton el : buttons)
			if (el.pos == LEFT) {
				buttonsHeight += el.button.getRect().height + el.borderMargin;
			}
		Button button = Button(
			margin,
			GetScreenHeight() / 2 - height / 2 + buttonsHeight + margin,
			width, height, text, color, textColor, imagePath
		);
		StateButton result = {
			button, state, pos, margin
		};
		buttons.push_back(result);
	}

	else if (pos == TOP_LEFT) {
		float buttonsHeight = 0;
		for (StateButton el : buttons)
			if (el.pos == TOP_LEFT) {
				buttonsHeight += el.button.getRect().height + el.borderMargin;
			}
		Button button = Button(
			margin,
			buttonsHeight + margin,
			width, height, text, color, textColor, imagePath
		);
		StateButton result = {
			button, state, pos, margin
		};
		buttons.push_back(result);
	}
}

void Window::setBackgroundImage(const char* filePath) {
	Image backgroundImage = LoadImage(filePath);
	ImageResize(&backgroundImage, window.width, window.height);
	backgroundTexture = LoadTextureFromImage(backgroundImage);
	UnloadImage(backgroundImage);
}
