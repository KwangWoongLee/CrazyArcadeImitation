class Block : public GameObject
{
public:
	CLASS_IDENTIFICATION('BLCK', GameObject)

		enum ECatReplicationState
	{
		EBRS_Pose = 1 << 0,
		EBRS_Color = 1 << 1,
		EBRS_PlayerId = 1 << 2,
		EBRS_Animation = 1 << 3,

		EBRS_AllState = EBRS_Pose | EBRS_Color | EBRS_PlayerId | EBRS_Animation
	};




	static	GameObject* StaticCreate() { return new Block(); }

	virtual uint32_t GetAllStateMask()	const override { return EBRS_AllState; }

	void		SetAnimationVelocity(const float inAnimationVelocity) { mAnimationVelocity = inAnimationVelocity; }
	const float GetAnimationVelocity()				const { return 0.f; }


	virtual void Update()	override;

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

	virtual bool HasCollisionWithPlayer(Player* inPlayer) override;

	virtual void HandleCollisionWithPlayer(Player* inPlayer) override;

protected:
	Block();

	int					mWidth;
	int					mHeight;









};

typedef shared_ptr< Block >	BlockPtr;
