class PlayerClient : public Player
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new PlayerClient()); }

	virtual void Update();

	virtual void	Read(InputMemoryBitStream& inInputStream) override;

protected:
	PlayerClient();


private:
	float				mTimeLocationBecameOutOfSync;
	float				mTimeVelocityBecameOutOfSync;

	SpriteComponentPtr	mSpriteComponent;
};