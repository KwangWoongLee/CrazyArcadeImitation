class BoomServer : public Boom
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new BoomServer()); }
	void HandleDying() override;

	virtual bool	HasCollisionWithPlayer(Player* inPlayer) override;

	virtual void	HandleCollisionWithPlayer(Player* inPlayer) override;

	virtual void Update() override;

protected:
	BoomServer();

private:
	float mTimeToDie;

};