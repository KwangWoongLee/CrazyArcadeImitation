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


private:
	void HandleShooting();


	float		mTimeOfNextShot;
	float		mTimeBetweenShots;

};