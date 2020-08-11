#include <ServerPch.h>


bool Server::StaticInit()
{
	sInstance.reset(new Server());

	return true;
}

Server::Server()
{
	GameObjectRegistry::sInstance->RegisterCreationFunction('PLAY', PlayerServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BOMB', BombServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BOOM', BoomServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BMLT', BoomServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BMRT', BoomServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BMDW', BoomServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BMUP', BoomServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BLCK', BlockServer::StaticCreate);
	InitNetworkManager();

	float latency = 0.0f;

	NetworkManagerServer::sInstance->SetSimulatedLatency(latency);
}



int Server::Run()
{
	SetupWorld();

	return Engine::Run();
}

bool Server::InitNetworkManager()
{
	string portString = StringUtils::GetCommandLineArg( 1 );
	//string portString = "45000";
	uint16_t port = stoi(portString);

	return NetworkManagerServer::StaticInit(port);
}

void Server::SetupWorld()
{
	ReadyBlockForMap();
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
	PlayerPtr player = std::static_pointer_cast<Player>(GameObjectRegistry::sInstance->CreateGameObject('PLAY'));
	player->SetVelocity(Vector3(1.f, 1.f, 0.f));
	player->SetPlayerId(inPlayerId);
	player->SetAnimationVelocity(0.07f);
	//gotta pick a better spawn location than this...
	player->SetLocation(Vector3(1.f - static_cast<float>(inPlayerId), 0.f, 0.f));

}

void Server::ReadyBlockForMap()
{
	//일단 하드코딩으로 맵을 만든다.
	BlockPtr block = std::static_pointer_cast<Block>(GameObjectRegistry::sInstance->CreateGameObject('BLCK'));
	block->SetAnimationVelocity(1.f);
	//gotta pick a better spawn location than this...
	block->SetLocation(Vector3(1.f, 0.f, 0.f));

	block = std::static_pointer_cast<Block>(GameObjectRegistry::sInstance->CreateGameObject('BLCK'));
	block->SetAnimationVelocity(1.f);
	//gotta pick a better spawn location than this...
	block->SetLocation(Vector3(0.1f, 0.f, 0.f));

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
		Player* player = go->GetAsCat();
		if (player && player->GetPlayerId() == inPlayerId)
		{
			return std::static_pointer_cast<Player>(go);
		}
	}

	return nullptr;

}
