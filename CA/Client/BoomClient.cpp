#include "ClientPch.h"

BoomClient::BoomClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("BoomCenter"));
	mWidth = TextureManager::sInstance->GetTexture("BoomCenter")->GetWidth();
	mHeight = TextureManager::sInstance->GetTexture("BoomCenter")->GetHeight();
}


void BoomClient::Read(InputMemoryBitStream& inInputStream)
{
	bool stateBit;

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 location;
		inInputStream.Read(location.mX);
		inInputStream.Read(location.mY);
		SetLocation(location);
	}


	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 color;
		inInputStream.Read(color);
		SetColor(color);
	}

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		inInputStream.Read(mPlayerId, 8);
	}

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		mAnimationVelocity = 0.f;
		inInputStream.Read(mAnimationVelocity);
		SetAnimationVelocity(mAnimationVelocity);

	}

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		mBoomState = 0;
		inInputStream.Read(mBoomState); 
		SetBoomState(mBoomState);

		switch (mBoomState)
		{
		case 0:
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("BoomCenter"));
			break;
		case 1:
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("BoomLeft"));
			break;
		case 2:
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("BoomRight"));
			break;
		case 3:
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("BoomUp"));
			break;
		case 4:
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("BoomDown"));
			break;
		}
	}
}
