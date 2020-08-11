#include "ClientPch.h"

BlockClient::BlockClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("Block"));
	mWidth = TextureManager::sInstance->GetTexture("Block")->GetWidth();
	mHeight = TextureManager::sInstance->GetTexture("Block")->GetHeight();
}


void BlockClient::Read(InputMemoryBitStream& inInputStream)
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
		mAnimationVelocity = 0.f;
		inInputStream.Read(mAnimationVelocity);
		SetAnimationVelocity(mAnimationVelocity);
	}

}

bool BlockClient::HasCollisionWithPlayer(Player* inPlayer)
{
	return false;
}

void BlockClient::HandleCollisionWithPlayer(Player* inPlayer)
{

}
