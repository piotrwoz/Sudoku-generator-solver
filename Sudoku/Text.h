#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Window.h"

class Text {
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* textTexture = nullptr;
	SDL_Rect textRect;
	std::string message;

	SDL_Texture* loadFont(const std::string& _fontPath, int _fontSize, const std::string& _message, const SDL_Color& _color);

public:
	Text(SDL_Renderer* _renderer, const std::string& _fontPath, int _fontSize, const std::string& _message, const SDL_Color& _color);
	~Text();
	void display(int x, int y);
	void changeText(std::string& newText);
};