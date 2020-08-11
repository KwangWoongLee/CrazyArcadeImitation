#include "GamePch.h"

Boom::Boom() :
	mPlayerId(0),
	mLifeTime(1.f),
	mWidth(40),
	mHeight(40)
{
}



uint32_t Boom::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & EBRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);


		writtenState |= EBRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EBRS_Color)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(GetColor());

		writtenState |= EBRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EBRS_PlayerId)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(mPlayerId, 8);

		writtenState |= EBRS_PlayerId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EBRS_Animation)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(mAnimationVelocity);

		writtenState |= EBRS_Animation;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EBRS_State)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(mBoomState);

		writtenState |= EBRS_State;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	return writtenState;
}

bool Boom::HasCollisionWithPlayer(Player* inPlayer)
{
	(void)inPlayer;

	return false;
}



void Boom::HandleCollisionWithPlayer(Player* inPlayer)
{
	(void)inPlayer;
}


void Boom::InitFromBomb(Bomb* inBomb, int State)
{
	SetColor(inBomb->GetColor());
	SetPlayerId(inBomb->GetPlayerId());
	SetAnimationVelocity(0.05f);

	Vector3 location = inBomb->GetLocation();
	switch (State)
	{
	case 0:
		SetBoomState(0);
		SetAnimationVelocity(0.1f);
		break;
	case 1:
		location.mX -= mWidth* 0.01f ;
		SetBoomState(1);
		break;
	case 2:
		SetBoomState(2);
		location.mX += mWidth * 0.01f;
		break;
	case 3:
		SetBoomState(3);
		location.mY -= mHeight * 0.01f;
		break;
	case 4:
		SetBoomState(4);
		location.mY += mHeight * 0.01f;
		break;
	}
	SetLocation(location);

}

void Boom::Update()
{

	float deltaTime = Timing::sInstance.GetDeltaTime();

	SetLocation(GetLocation());


	//we'll let the cats handle the collisions
}
