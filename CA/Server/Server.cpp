﻿#include <ServerPch.h>


bool Server::StaticInit()
{
	sInstance.reset(new Server());

	return true;
}

Server::Server()
{
#ifdef _DEBUG
	//콘솔창 생성함수.
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif  
	GameObjectRegistry::sInstance->RegisterCreationFunction('PLAY', PlayerServer::StaticCreate);

	InitNetworkManager();

	float latency = 0.0f;

	NetworkManagerServer::sInstance->SetSimulatedLatency(latency);
}

void Server::SetupWorld()
{
}

int Server::Run()
{
	SetupWorld();

	return Engine::Run();
}

bool Server::InitNetworkManager()
{
	//string portString = StringUtils::GetCommandLineArg( 1 );
	string portString = "45000";
	uint16_t port = stoi(portString);

	return NetworkManagerServer::StaticInit(port);
}

void Server::DoFrame()
{
	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();
	
	Engine::DoFrame();

	NetworkManagerServer::sInstance->SendOutgoingPackets();
}


void Server::HandleNewClient(ClientProxyPtr inClientProxy)
{

	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->AddEntry(playerId, inClientProxy->GetName());
	SpawnPlayer(playerId);

}

void Server::SpawnPlayer(int inPlayerId)
{
	Vector3 mColor;
	mColor.mX = 100.f;
	mColor.mY = 127.f;
	mColor.mZ = 146.f;



	PlayerPtr cat = std::static_pointer_cast<Player>(GameObjectRegistry::sInstance->CreateGameObject('PLAY'));
	cat->SetColor(mColor);
	cat->SetPlayerId(inPlayerId);
	//gotta pick a better spawn location than this...
	cat->SetLocation(Vector3(1.f - static_cast<float>(inPlayerId), 0.f, 0.f));

}

void Server::HandleLostClient(ClientProxyPtr inClientProxy)
{
	//kill client's cat
	//remove client from scoreboard
	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->RemoveEntry(playerId);
	PlayerPtr cat = GetCatForPlayer(playerId);
	if (cat)
	{
		cat->SetDoesWantToDie(true);
	}
}

PlayerPtr Server::GetCatForPlayer(int inPlayerId)
{
	//run through the objects till we find the cat...
	//it would be nice if we kept a pointer to the cat on the clientproxy
	//but then we'd have to clean it up when the cat died, etc.
	//this will work for now until it's a perf issue
	const auto& gameObjects = World::sInstance->GetGameObjects();
	for (int i = 0, c = gameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = gameObjects[i];
		Player* cat = go->GetAsCat();
		if (cat && cat->GetPlayerId() == inPlayerId)
		{
			return std::static_pointer_cast<Player>(go);
		}
	}

	return nullptr;

}