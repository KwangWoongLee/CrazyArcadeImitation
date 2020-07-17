#pragma once

#include "resource.h"

class Server : public Engine
{
public:

	static bool StaticInit();


	virtual void DoFrame() override;

	virtual int Run();


private:
	Server();

	bool	InitNetworkManager();
	void	SetupWorld();

};