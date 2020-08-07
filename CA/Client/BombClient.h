class BombClient : public Bomb
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new BombClient()); }

	virtual void		Read(InputMemoryBitStream& inInputStream) override;

protected:
	BombClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};