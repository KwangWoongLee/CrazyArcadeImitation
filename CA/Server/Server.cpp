
#include "ServerPch.h"



//uncomment this when you begin working on the server

bool Server::StaticInit()
{
	return true;
}

Server::Server()
{


	//NetworkManagerServer::sInstance->SetDropPacketChance( 0.8f );
	//NetworkManagerServer::sInstance->SetSimulatedLatency( 0.25f );
	//NetworkManagerServer::sInstance->SetSimulatedLatency( 0.5f );
	//NetworkManagerServer::sInstance->SetSimulatedLatency( 0.1f );

}


int Server::Run()
{
	return 1;
}
