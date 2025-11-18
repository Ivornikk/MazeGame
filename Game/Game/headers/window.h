#pragma once

#include <raylib.h>
#include "button.h"
#include "../utils.h"
#include <vector>
#include <string>

enum Position {
	CENTER,
	TOP,
	TOP_RIGHT,
	RIGHT,
	BOTTOM_RIGHT,
	BOTTOM,
	BOTTOM_LEFT,
	LEFT,
	TOP_LEFT
};

struct StateButton {
	Button button;
	GAME_STATES state;
	Position pos;
	int borderMargin;
};

struct Text {
	const char* text;
	Position pos;
	int borderMargin;
	int fontSize;
};

class Window {
	std::vector<StateButton> buttons;
	std::vector<Text> paragraphs;
	std::string title;
	Rectangle window;
	Color backgroundColor;
	Color outlineColor;
	Texture2D backgroundTexture;
public:
	Window(float marginX = 0, float marginY = 0, std::string heading = "");
	void Draw();
	void Update(GAME_STATES* state);
	void setBackgroundColor(Color color);
	void setOutlineColor(Color color);
	void addButton(Position pos, int margin, int width, int height, const char* text, GAME_STATES state, Color color=GREEN, Color textColor=BLACK, const char* imagePath=nullptr);
	void setBackgroundImage(const char* filePath);
};