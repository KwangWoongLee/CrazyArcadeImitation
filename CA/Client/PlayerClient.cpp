#include <ClientPch.h>



PlayerClient::PlayerClient() :
	mTimeLocationBecameOutOfSync(0.f),
	mTimeVelocityBecameOutOfSync(0.f)
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("Player"));
	
}


void PlayerClient::Update()
{
	//for now, we don't simulate any movement on the client side
	//we only move when the server tells us to move
}

void PlayerClient::Read(InputMemoryBitStream& inInputStream)
{
	bool stateBit;

	uint32_t readState = 0;

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		uint32_t playerId;
		inInputStream.Read(playerId);
		SetPlayerId(playerId);
		readState |= ECRS_PlayerId;
	}

	float oldRotation = GetRotation();
	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetVelocity();

	float replicatedRotation;
	Vector3 replicatedLocation;
	Vector3 replicatedVelocity;
	uint32_t replicatedDirection;
	bool	replicatedBoolMove;

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		inInputStream.Read(replicatedVelocity.mX);
		inInputStream.Read(replicatedVelocity.mY);

		SetVelocity(replicatedVelocity);

		inInputStream.Read(replicatedLocation.mX);
		inInputStream.Read(replicatedLocation.mY);

		SetLocation(replicatedLocation);

		inInputStream.Read(replicatedRotation);
		SetRotation(replicatedRotation);

		inInputStream.Read(replicatedDirection);
		inInputStream.Read(replicatedBoolMove);
		
		switch (replicatedDirection)
			{
			case 0:
				mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("PlayerDown"));
				break;
			case 1:
				mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("PlayerUp"));
				break;
			case 2:
				mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("PlayerLeft"));
				break;
			case 3:mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("PlayerRight"));
				break;

			default:
				break;
			}


		SetMove(replicatedBoolMove);
		SetDirection(replicatedDirection);
		

		readState |= ECRS_Pose;
	}

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		inInputStream.Read(stateBit);
		mThrustDir = stateBit ? 1.f : -1.f;
	}
	else
	{
		mThrustDir = 0.f;

		switch (replicatedDirection)
		{
		case 0:
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("PlayerIdleDown"));
			break;
		case 1:
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("PlayerIdleUp"));
			break;
		case 2:
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("PlayerIdleLeft"));
			break;
		case 3:
			mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("PlayerIdleRight"));
			break;

		default:
			break;
		}

	}

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 color;
		inInputStream.Read(color);
		SetColor(color);
		readState |= ECRS_Color;
	}

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		mHealth = 0;
		inInputStream.Read(mHealth, 4);
		readState |= ECRS_Health;
	}

	if (GetPlayerId() == NetworkManagerClient::sInstance->GetPlayerId())
	{
		//did we get health? if so, tell the hud!
		if ((readState & ECRS_Health) != 0)
		{
			//HUD::sInstance->SetPlayerHealth(mHealth);
		}
	}

}
