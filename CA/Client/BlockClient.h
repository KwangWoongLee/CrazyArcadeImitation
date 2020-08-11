class BlockClient : public Block
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new BlockClient()); }

	virtual void		Read(InputMemoryBitStream& inInputStream) override;
	virtual bool		HasCollisionWithPlayer(Player* inPlayer) override;
	virtual void		HandleCollisionWithPlayer(Player* inPlayer) override;

protected:
	BlockClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};