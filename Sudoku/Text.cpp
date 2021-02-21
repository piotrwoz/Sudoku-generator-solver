#include "Text.h"

Text::Text(SDL_Renderer* _renderer, const std::string& _fontPath, int _fontSize, const std::string& _message, const SDL_Color& _color) {
	this->renderer = _renderer;
	this->textTexture = this->loadFont(_fontPath, _fontSize, _message, _color);
	SDL_QueryTexture(this->textTexture, nullptr, nullptr, &this->textRect.w, &this->textRect.h);
}

Text::~Text() {

}

SDL_Texture* Text::loadFont(const std::string& fontPath, int fontSize, const std::string& message, const SDL_Color& color ) {
	auto font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font) {
		std::cout << "Failed to load font" << std::endl;
		return nullptr;
	}

	auto textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
	if (!textSurface) {
		std::cout << "Failed to create text surface" << std::endl;
		return nullptr;
	}

	auto textTexture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
	if (!textTexture) {
		std::cout << "Failed to create text texture" << std::endl;
		return nullptr;
	}

	SDL_FreeSurface(textSurface);

	return textTexture;
}

void Text::display(int _x, int _y) {
	this->textRect.x = _x;
	this->textRect.y = _y;
	SDL_RenderCopy(this->renderer, this->textTexture, nullptr, &this->textRect);
}

void Text::changeText(std::string& newText) {
	this->message = newText;
}