
#include "ServerPch.h"


//uncomment this when you begin working on the server

bool Server::StaticInit()
{
	sInstance.reset(new Server());

	return true;
}

Server::Server()
{

}


void Server::DoFrame()
{
}

int Server::Run()
{
	return Engine::Run();
}
