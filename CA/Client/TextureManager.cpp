#include "ClientPch.h"

std::unique_ptr< TextureManager >		TextureManager::sInstance;

void TextureManager::StaticInit()
{
	sInstance.reset(new TextureManager());
}

TextureManager::TextureManager()
{
	CacheTexture("Player", "./Resources/bazziReadyCharacter.bmp");

}

TexturePtr	TextureManager::GetTexture(const string& inTextureName)
{
	return mNameToTextureMap[inTextureName];
}

bool TextureManager::CacheTexture(string inTextureName, const char* inFileName)
{
	SDL_Surface* image = SDL_LoadBMP(inFileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(GraphicsDriver::sInstance->GetRenderer(), image);

	if (texture == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load texture: %s", inFileName);
		return false;
	}

	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

	// Set the blend mode up so we can apply our colors
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	TexturePtr newTexture(new Texture(w, h, texture));

	mNameToTextureMap[inTextureName] = newTexture;

	return true;

}