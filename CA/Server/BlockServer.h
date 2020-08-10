class BlockServer : public Block
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new BlockServer()); }
	void HandleDying() override;

	virtual bool		HandleCollisionWithBomb() override;

	virtual void Update() override;

protected:
	BlockServer();

private:
	float mTimeToDie;

};