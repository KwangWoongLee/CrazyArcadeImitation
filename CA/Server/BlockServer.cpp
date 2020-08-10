#include "ServerPch.h"

BlockServer::BlockServer()
{
}

void BlockServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


void BlockServer::Update()
{
	Block::Update();


}

bool BlockServer::HandleCollisionWithBomb()
{	
	SetDoesWantToDie(true);

	return false;
}


