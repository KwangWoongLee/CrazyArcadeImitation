#include "ClientPch.h"

std::unique_ptr< TextureManager >		TextureManager::sInstance;

void TextureManager::StaticInit()
{
	sInstance.reset(new TextureManager());
}

TextureManager::TextureManager()
{
	CacheTexture("CountDownBazzi", "./Resources/bazziBubble.bmp", 16, 1);
	CacheTexture("PlayerDown", "./Resources/bazziDown.bmp",7,1);
	CacheTexture("PlayerUp", "./Resources/bazziUp.bmp", 7, 1);
	CacheTexture("PlayerLeft", "./Resources/bazziLeft.bmp", 7, 1);
	CacheTexture("PlayerRight", "./Resources/bazziRight.bmp", 7, 1);
	CacheTexture("PlayerIdleDown", "./Resources/bazziIdleDown.bmp", 1, 1);
	CacheTexture("PlayerIdleUp", "./Resources/bazziIdleUp.bmp", 1, 1);
	CacheTexture("PlayerIdleLeft", "./Resources/bazziIdleLeft.bmp", 1, 1);
	CacheTexture("PlayerIdleRight", "./Resources/bazziIdleRight.bmp", 1, 1);
	CacheTexture("Bomb", "./Resources/bomb_already.bmp", 4, 1);
	CacheTexture("BoomCenter", "./Resources/boom_center.bmp", 14, 1);
	CacheTexture("BoomUp", "./Resources/boom_up.bmp", 9, 1);
	CacheTexture("BoomDown", "./Resources/boom_down.bmp", 9, 1);
	CacheTexture("BoomLeft", "./Resources/boom_left.bmp", 9, 1);
	CacheTexture("BoomRight", "./Resources/boom_right.bmp", 9, 1);
	CacheTexture("Block", "./Resources/tree.bmp", 1, 1);
}

TexturePtr	TextureManager::GetTexture(const string& inTextureName)
{
	return mNameToTextureMap[inTextureName];
}

bool TextureManager::CacheTexture(string inTextureName, const char* inFileName,uint32_t inDistX, uint32_t inDistY)
{
	SDL_Surface* image = SDL_LoadBMP(inFileName);
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 255, 0, 255));

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
	newTexture->SetDist(inDistX, inDistY);

	mNameToTextureMap[inTextureName] = newTexture;

	return true;

}