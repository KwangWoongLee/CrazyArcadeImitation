﻿
#include <ClientPch.h>

bool Client::StaticInit()
{
	// Create the Client pointer first because it initializes SDL
	Client* client = new Client();

	if (WindowManager::StaticInit() == false)
	{
		return false;
	}

	if (GraphicsDriver::StaticInit(WindowManager::sInstance->GetMainWindow()) == false)
	{
		return false;
	}

	TextureManager::StaticInit();
	RenderManager::StaticInit();
	InputManager::StaticInit();

	//HUD::StaticInit();

	sInstance.reset(client);

	return true;
}

Client::Client()
{
	GameObjectRegistry::sInstance->RegisterCreationFunction('PLAY', PlayerClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BOMB', BombClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BOOM', BoomClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BMLT', BoomClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BMRT', BoomClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BMUP', BoomClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BMDW', BoomClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BLCK', BlockClient::StaticCreate);

	string destination = StringUtils::GetCommandLineArg(1);
	string name = StringUtils::GetCommandLineArg(2);
	//string destination = "127.0.0.1:45000";
	//string name = "A";

	SocketAddressPtr serverAddress = SocketAddressFactory::CreateIPv4FromString(destination);

	NetworkManagerClient::StaticInit(*serverAddress, name);

	NetworkManagerClient::sInstance->SetSimulatedLatency(0.0f);
}



void Client::DoFrame()
{
	InputManager::sInstance->Update();

	Engine::DoFrame();

	NetworkManagerClient::sInstance->ProcessIncomingPackets();

	RenderManager::sInstance->Render();

	NetworkManagerClient::sInstance->SendOutgoingPackets();
}

void Client::HandleEvent(SDL_Event* inEvent)
{
	switch (inEvent->type)
	{
	case SDL_KEYDOWN:
		InputManager::sInstance->HandleInput(EIA_Pressed, inEvent->key.keysym.sym);
		break;
	case SDL_KEYUP:
		InputManager::sInstance->HandleInput(EIA_Released, inEvent->key.keysym.sym);
		break;
	default:
		break;
	}
}

