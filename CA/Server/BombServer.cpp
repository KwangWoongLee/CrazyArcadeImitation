#include "ServerPch.h"

BombServer::BombServer()
{
	//bomb lives a second...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 4.f;
}

void BombServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


void BombServer::Update()
{
	Bomb::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}

}

void BombServer::HandleCollisionWithPlayer(Player* inPlayer)
{
}


