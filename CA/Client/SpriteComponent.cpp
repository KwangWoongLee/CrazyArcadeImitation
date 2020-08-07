#include "ClientPch.h"

SpriteComponent::SpriteComponent(GameObject* inGameObject) :
	mGameObject(inGameObject)
{
	//hardcoded at the moment...
	float textureWidth = 128.f, textureHeight = 128.f;
	//origin should be half texture size, but we're not loading the actual size at the moment
	mOrigin = Vector3(textureWidth * 0.5f, textureHeight * 0.5f, 0.f);
	mIdx = 0;
	//and add yourself to the rendermanager...
	RenderManager::sInstance->AddComponent(this);
}

SpriteComponent::~SpriteComponent()
{
	//don't render me, I'm dead!
	RenderManager::sInstance->RemoveComponent(this);
}


void SpriteComponent::Draw(const SDL_Rect& inViewTransform)
{
	if (mTexture)
	{
		mfAnimationTime += Timing::sInstance.GetDeltaTime();
		if (mfAnimationTime > mGameObject->GetAnimationVelocity())
		{
			mfAnimationTime = 0.f;
			mIdx += 1;
		}
			
		if (mIdx >= mTexture->GetDistX())
			mIdx = 0;


		// Texture color multiplier
		Vector3 color = mGameObject->GetColor();
		Uint8 r = static_cast<Uint8>(color.mX * 255);
		Uint8 g = static_cast<Uint8>(color.mY * 255);
		Uint8 b = static_cast<Uint8>(color.mZ * 255);
		SDL_SetTextureColorMod(mTexture->GetData(), r, g, b);

		// Compute the destination rectangle
		Vector3 objLocation = mGameObject->GetLocation();
		float objScale = mGameObject->GetScale();
		

		SDL_Rect rcSprite = { mTexture->GetWidth() / mTexture->GetDistX() * mIdx,0,mTexture->GetWidth() / mTexture->GetDistX(),mTexture->GetHeight() };
		//�׸��� ���° �κ��̹������� x,y,w,h x,y�� �׸������� *idx�� ��ȭ��Ű�� �������ٲ�

		SDL_Rect dstRect; //�׸��� �׸� ��ġ�� ũ��
		dstRect.h = static_cast<int>(mTexture->GetHeight() * objScale);
		dstRect.w = static_cast<int>(mTexture->GetWidth() * objScale) / mTexture->GetDistX();
		dstRect.x = static_cast<int>(objLocation.mX * inViewTransform.w + inViewTransform.x - dstRect.w / 2);
		dstRect.y = static_cast<int>(objLocation.mY * inViewTransform.h + inViewTransform.y - dstRect.h / 2);

		SDL_RenderCopy(GraphicsDriver::sInstance->GetRenderer(), mTexture->GetData(), &rcSprite, &dstRect);
	}
}