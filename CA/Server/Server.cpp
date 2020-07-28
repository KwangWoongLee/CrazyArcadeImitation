
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

}
