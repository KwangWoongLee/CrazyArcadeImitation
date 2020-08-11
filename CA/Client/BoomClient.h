class BoomClient : public Boom
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new BoomClient()); }

	virtual void		Read(InputMemoryBitStream& inInputStream) override;

protected:
	BoomClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};