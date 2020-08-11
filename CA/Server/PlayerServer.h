enum ECatControlType
{
	ESCT_Human,
	ESCT_AI
};

class PlayerServer : public Player
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new PlayerServer()); }

	virtual void Update() override;


protected:
	PlayerServer();

	void HandleDying();


private:
	void HandleShooting();
	void HandleCountDown();


	float		mTimeOfNextShot;
	float		mTimeBetweenShots;

};