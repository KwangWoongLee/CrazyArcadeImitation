#include <ServerPch.h>


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
	SpawnPlayer(playerId);

}

void Server::SpawnPlayer(int inPlayerId)
{
	PlayerPtr cat = std::static_pointer_cast<Player>(GameObjectRegistry::sInstance->CreateGameObject('PLAY'));
	cat->SetPlayerId(inPlayerId);
	//gotta pick a better spawn location than this...
	cat->SetLocation(Vector3(1.f - static_cast<float>(inPlayerId), 0.f, 0.f));

}