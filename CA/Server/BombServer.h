class BombServer : public Bomb
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new BombServer()); }
	void HandleDying() override;

	virtual void	HandleCollisionWithPlayer(Player* inPlayer) override;

	virtual void Update() override;

protected:
	BombServer();

private:
	float mTimeToDie;

};