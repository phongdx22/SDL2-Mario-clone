#include "TextRenderer.h"

TextRenderer::TextRenderer(int fontSize)
{
	font = TTF_OpenFont("SuperMarioBros.ttf", fontSize);
	color = { 0,0,0,255 };
}

TextRenderer::~TextRenderer()
{
	text = NULL;
}

void TextRenderer::Render(SDL_Renderer* renderer, const char* message, int x, int y)
{
	if (text != NULL)
	{
		SDL_DestroyTexture(text);
	}

	textSurface = TTF_RenderText_Solid(font, message, color);
	text = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_FreeSurface(textSurface);
	textSurface = nullptr;

	textRect.x = x;
	textRect.y = y;

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_RenderCopy(renderer, text, NULL, &textRect);
}

void TextRenderer::Render(SDL_Renderer* renderer, int score, int x, int y)
{
	if (text != NULL)
	{
		SDL_DestroyTexture(text);
	}

	char Buffer[256];

	sprintf_s(Buffer, "%i", score);

	textSurface = TTF_RenderText_Solid(font, Buffer, color);
	text = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_FreeSurface(textSurface);
	textSurface = nullptr;

	textRect.x = x;
	textRect.y = y;

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_RenderCopy(renderer, text, NULL, &textRect);
}


