
class Server : public Engine
{
public:

	static bool StaticInit();

	virtual void DoFrame() override;

	virtual int Run();

	void HandleNewClient(ClientProxyPtr inClientProxy);
	void SpawnPlayer(int inPlayerId);
	void HandleLostClient(ClientProxyPtr inClientProxy);
	PlayerPtr GetCatForPlayer(int inPlayerId);
private:
	Server();
	bool	InitNetworkManager();
	void	SetupWorld();

};