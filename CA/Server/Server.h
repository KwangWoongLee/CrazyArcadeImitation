
class Server : public Engine
{
public:

	static bool StaticInit();

	virtual void DoFrame() override;

	virtual int Run();

	void HandleNewClient(ClientProxyPtr inClientProxy);
private:
	Server();
	bool	InitNetworkManager();
	void	SetupWorld();

};