#include <ServerPch.h>

PlayerServer::PlayerServer()	:
	mTimeOfNextShot(0.f),
	mTimeBetweenShots(0.2f)
{

}

void PlayerServer::Update()
{
	Player::Update();

	Vector3 oldLocation = GetLocation();
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
		}

		moveList.Clear();
	}

	HandleShooting();

	if (!ServerMath::Is2DVectorEqual(oldLocation, GetLocation()) ||
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
