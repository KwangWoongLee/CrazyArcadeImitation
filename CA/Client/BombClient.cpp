#include "ClientPch.h"

BombClient::BombClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("Bomb"));
}


void BombClient::Read(InputMemoryBitStream& inInputStream)
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
}
