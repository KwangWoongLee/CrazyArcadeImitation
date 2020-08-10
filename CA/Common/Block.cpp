#include "GamePch.h"

Block::Block()
{
	SetAnimationVelocity(1.f);
}



uint32_t Block::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
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

	if (inDirtyState & EBRS_Animation)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(GetAnimationVelocity());

		writtenState |= EBRS_Animation;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	return writtenState;
}



bool Block::HandleCollisionWithBomb()
{
	return false;
}

bool Block::HasCollisionWithPlayer(Player* inPlayer)
{
	return true;
}

void Block::HandleCollisionWithPlayer(Player* inPlayer)
{
	Vector3 location = inPlayer->GetLocation();
	Vector3 velocity = inPlayer->GetVelocity();

	if (location.mX > this->GetLocation().mX && velocity.mX <= 0)
	{
		location.mX = location.mX;
		inPlayer->SetLocation(location);
	}
		
	else if (location.mX <= this->GetLocation().mX && velocity.mX > 0)
	{
		location.mX = location.mX ;
		inPlayer->SetLocation(location);
	}
}


void Block::Update()
{
	SetLocation(GetLocation());

}
