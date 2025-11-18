#include "../headers/button.h"

Button::Button(float x, float y, float width, float height, const char* textTemp, Color colorTemp, Color textColorTemp, const char* imagePath )
{
	button = { x, y , width, height };
	text = textTemp;
	fontSize = findPerfectFontSize(button, text, 30);
	color = colorTemp;
	textColor = textColorTemp;
	hasTexture = false;	
	// Only load texture if an image path is provided
	if (imagePath != nullptr) {
		Image img = LoadImage(imagePath);
		ImageResize(&img, width, height);
		texture = LoadTextureFromImage(img);
		
		if (texture.id != 0) {
			hasTexture = true;
		}
		
	}

}
void Button::Draw()
{
	if (hasTexture) {
		DrawTexture(texture, button.x, button.y, WHITE);
		DrawTextEx(font, text, findPerfectTextPos(), fontSize, 1.f, WHITE);
	}
	else {
		DrawRectangleRec(button, color);
		DrawTextEx(font, text, findPerfectTextPos(), fontSize, 1.f, textColor);
	}
}
void Button::Unload()
{
	if (hasTexture) {
		UnloadTexture(texture);
		hasTexture = false;
	}
}

Rectangle Button::getRect() {
	return button;
}


bool Button::isClicked()
{
	if (CheckCollisionPointRec(GetMousePosition(), button))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return true;
		}
	}
	return false;
}

float Button::findPerfectFontSize(Rectangle container, const char* text, int textPadding) {
		// Start with a font size as large as the container width.
	float fontSize = container.width;
	Vector2 textSize = MeasureTextEx(font, text, fontSize, 5.f);

	for (int i = fontSize; i >= 1; i--) {
		textSize = MeasureTextEx(font, text, i, 5.f);
		if (textSize.x < container.width - textPadding && textSize.y < container.height) {
			return (float)i;
		}
	}
	return 0.f;
}

Vector2 Button::findPerfectTextPos() {
	Vector2 textSize = MeasureTextEx(font, text, fontSize, 1.f);
	Vector2 textPos = { button.x + ((button.width - textSize.x) / 2),
						button.y + ((button.height - textSize.y) / 2) };
	return textPos;
}
