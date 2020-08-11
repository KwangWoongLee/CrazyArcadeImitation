class BombServer : public Bomb
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new BombServer()); }
	void HandleDying() override;

	virtual bool		HasCollisionWithPlayer(Player* inPlayer) override;

	virtual void		HandleCollisionWithPlayer(Player* inPlayer) override;

	virtual void Update() override;

protected:
	BombServer();

private:
	float mTimeToDie;

};