class BlockClient : public Block
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new BlockClient()); }

	virtual void		Read(InputMemoryBitStream& inInputStream) override;

protected:
	BlockClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};