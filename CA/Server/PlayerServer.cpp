#include <ServerPch.h>

PlayerServer::PlayerServer()	:
	mTimeOfNextShot(0.f),
	mTimeBetweenShots(0.2f)
{
}

void PlayerServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


void PlayerServer::Update()
{
	Player::Update();

	HandleCountDown();

	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();

	ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy(GetPlayerId());
	if (client)
	{
		MoveList& moveList = client->GetUnprocessedMoveList();
		for (const Move& unprocessedMove : moveList)
		{
			const InputState& currentState = unprocessedMove.GetInputState();
			float deltaTime = unprocessedMove.GetDeltaTime();
			ProcessInput(deltaTime, currentState);
			SimulateMovement(deltaTime);

			LOG( "Server Move Time: %3.4f deltaTime: %3.4f left rot at %3.4f", unprocessedMove.GetTimestamp(), deltaTime, GetRotation() );

		}

		moveList.Clear();
	}

	HandleShooting();

	if (!ServerMath::Is2DVectorEqual(oldLocation, GetLocation()) ||
		!ServerMath::Is2DVectorEqual(oldVelocity, GetVelocity()) ||
		oldRotation != GetRotation())
	{
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Pose);
	}

}

void PlayerServer::HandleShooting()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if (mIsShooting && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot)
	{
		//not exact, but okay
		mTimeOfNextShot = time + mTimeBetweenShots;

		//fire!
		
		BombPtr bomb = std::static_pointer_cast<Bomb>(GameObjectRegistry::sInstance->CreateGameObject('BOMB'));
		bomb->InitFromPutter(this);
	}
}

void PlayerServer::HandleCountDown()
{
	if(mbCountDown)
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Live);

	if (mbCountDown && Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
	
}

