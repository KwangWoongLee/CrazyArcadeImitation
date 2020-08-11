#include "GamePch.h"

//zoom hardcoded at 100...if we want to lock players on screen, this could be calculated from zoom
const float HALF_WORLD_HEIGHT = 4.0f;
const float HALF_WORLD_WIDTH = 6.8f;


Player::Player() :
	GameObject(),
	mMaxRotationSpeed(5.f),
	mMaxLinearSpeed(80.f),
	mVelocity(Vector3::Zero),
	mWallRestitution(0.1f),
	mCatRestitution(0.1f),
	mThrustDir(0.f),
	mDir(0),
	mMove(false),
	mPlayerId(0),
	mIsShooting(false),
	mHealth(10),
	mWidth(44),
	mHeight(60),
	mbCountDown(false),
	mTimeToDie(2.5f)
{
	SetCollisionRadius(0.5f);
}

void Player::ProcessInput(float inDeltaTime, const InputState& inInputState)
{
	//process our input....

	//turning...
	//float newRotation = GetRotation() + inInputState.GetDesiredHorizontalDelta() * mMaxRotationSpeed * inDeltaTime;
	//SetRotation(newRotation);

	//no moving
	mMove = inInputState.GetDesiredMove();

	//moving...
	
	mDir = inInputState.GetDesiredDir();
	float inputForwardDelta = inInputState.GetDesiredVerticalDelta();
	float inputSideDelta = inInputState.GetDesiredHorizontalDelta();

	switch (mDir)
	{
	case 0:
	case 1:
		mThrustDir = inputForwardDelta;
		break;
	case 2:
	case 3:
		mThrustDir = inputSideDelta;
		break;
	default:
		break;
	}
	
	mIsShooting = inInputState.IsShooting();
}

void Player::AdjustVelocityByThrust(float inDeltaTime)
{
	//just set the velocity based on the thrust direction -- no thrust will lead to 0 velocity
	//simulating acceleration makes the client prediction a bit more complex
	Vector3 DirVector = GetForwardVector();
	switch (mDir)
	{
	case 0:
	case 1:
		DirVector.mY = -1.f;
		break;
	case 2:
	case 3:
		DirVector.mX = 1.f;
		break;
	default:
		break;
	}
	
	mVelocity = DirVector * (mThrustDir * inDeltaTime * mMaxLinearSpeed);
	
}

void Player::SimulateMovement(float inDeltaTime)
{
	//simulate us...
	AdjustVelocityByThrust(inDeltaTime);


	SetLocation(GetLocation() + mVelocity * inDeltaTime);

	ProcessCollisions();
}

void Player::ProcessCollisions()
{
	ProcessCollisionsWithScreenWalls();

	Vector3 sourceLocation = GetLocation();


	for (auto goIt = World::sInstance->GetGameObjects().begin(), end = World::sInstance->GetGameObjects().end(); goIt != end; ++goIt)
	{
		GameObject* target = goIt->get();
		if (target != this && !target->DoesWantToDie())
		{
			if (target->HasCollisionWithPlayer(this))
			{
				target->HandleCollisionWithPlayer(this);
			}

		}
	}
}

void Player::ProcessCollisionsWithScreenWalls()
{
	Vector3 location = GetLocation();
	float x = location.mX;
	float y = location.mY;

	float vx = mVelocity.mX;
	float vy = mVelocity.mY;

	float radius = GetCollisionRadius();

	//if the cat collides against a wall, the quick solution is to push it off
	if ((y + radius) >= HALF_WORLD_HEIGHT && vy > 0)
	{
		mVelocity.mY = -vy * mWallRestitution;
		location.mY = HALF_WORLD_HEIGHT - radius;
		SetLocation(location);
	}
	else if (y <= (-HALF_WORLD_HEIGHT - radius) && vy < 0)
	{
		mVelocity.mY = -vy * mWallRestitution;
		location.mY = -HALF_WORLD_HEIGHT - radius;
		SetLocation(location);
	}

	if ((x + radius) >= HALF_WORLD_WIDTH && vx > 0)
	{
		mVelocity.mX = -vx * mWallRestitution;
		location.mX = HALF_WORLD_WIDTH - radius;
		SetLocation(location);
	}
	else if (x <= (-HALF_WORLD_WIDTH - radius) && vx < 0)
	{
		mVelocity.mX = -vx * mWallRestitution;
		location.mX = -HALF_WORLD_WIDTH - radius;
		SetLocation(location);
	}
}

void Player::Update()
{

}

uint32_t Player::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & ECRS_PlayerId)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetPlayerId());

		writtenState |= ECRS_PlayerId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	if (inDirtyState & ECRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 velocity = mVelocity;
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		inOutputStream.Write(GetRotation());

		inOutputStream.Write(mDir);

		inOutputStream.Write(mMove);


		writtenState |= ECRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	//always write mThrustDir- it's just two bits
	if (mThrustDir != 0.f)
	{
		inOutputStream.Write(true);
		inOutputStream.Write(mThrustDir > 0.f);
	}
	else
	{
		inOutputStream.Write(false);
	}

	if (inDirtyState & ECRS_Color)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetColor());

		writtenState |= ECRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ECRS_Health)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(mHealth, 4);

		writtenState |= ECRS_Health;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ECRS_Animation)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetAnimationVelocity());

		writtenState |= ECRS_Animation;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ECRS_Live)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetCountDown());

		writtenState |= ECRS_Live;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	return writtenState;


}


