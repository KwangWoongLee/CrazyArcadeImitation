#include "GamePch.h"
#include <time.h>
#include <SDL.h>

std::unique_ptr< Engine >	Engine::sInstance;


Engine::Engine() :
	mShouldKeepRunning(true)
{
	//SocketUtil::StaticInit();

	srand(static_cast<uint32_t>(time(nullptr)));

	//GameObjectRegistry::StaticInit();


	//World::StaticInit();

	//ScoreBoardManager::StaticInit();

	//SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}

Engine::~Engine()
{
	//SocketUtil::CleanUp();

	//SDL_Quit();
}




int Engine::Run()
{
	return DoRunLoop();
}

int Engine::DoRunLoop()
{
	DoFrame();
	return 1;
}

void Engine::DoFrame()
{
}


