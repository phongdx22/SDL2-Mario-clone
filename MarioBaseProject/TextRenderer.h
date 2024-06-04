#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <String>

class TextRenderer
{
public:
	TextRenderer(int fontSize);
	~TextRenderer();
	void Render(SDL_Renderer* renderer, const char* message, int x, int y);
	void Render(SDL_Renderer* renderer, int score, int x, int y);

private:
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* textSurface;
	SDL_Texture* text;
	SDL_Rect textRect;
};

