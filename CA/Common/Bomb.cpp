#include "GamePch.h"

Bomb::Bomb() :
	mPlayerId(0),
	mLifeTime(1.f)
{
}



uint32_t Bomb::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
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


	return writtenState;
}



bool Bomb::HandleCollisionWithPlayer(Player* inPlayer)
{
	(void)inPlayer;

	//you hit a cat, so look like you hit a cat

	return false;
}


void Bomb::InitFromPutter(Player* inPutter)
{
	SetColor(inPutter->GetColor());
	SetPlayerId(inPutter->GetPlayerId());
	SetAnimationVelocity(0.2f);
	Vector3 forward = inPutter->GetForwardVector();
	SetLocation(inPutter->GetLocation() /* + forward * 0.55f */);

}

void Bomb::Update()
{

	float deltaTime = Timing::sInstance.GetDeltaTime();

	SetLocation(GetLocation());


	//we'll let the cats handle the collisions
}
