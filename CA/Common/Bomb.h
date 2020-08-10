class Bomb : public GameObject
{
public:
	CLASS_IDENTIFICATION('BOMB', GameObject)

		enum ECatReplicationState
	{
		EBRS_Pose = 1 << 0,
		EBRS_Color = 1 << 1,
		EBRS_PlayerId = 1 << 2,
		EBRS_Animation = 1 << 3 ,

		EBRS_AllState = EBRS_Pose | EBRS_Color | EBRS_PlayerId | EBRS_Animation
	};




	static	GameObject* StaticCreate() { return new Bomb(); }

	virtual uint32_t GetAllStateMask()	const override { return EBRS_AllState; }

	virtual void Update()	override;



	void		SetPlayerId(uint32_t inPlayerId) { mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const { return mPlayerId; }

	void		SetAnimationVelocity(const float inAnimationVelocity) { mAnimationVelocity = inAnimationVelocity; }
	const float GetAnimationVelocity()				const { return mAnimationVelocity; }

	void		InitFromPutter(Player* inPutter);

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

	virtual bool HasCollisionWithPlayer (Player* inPlayer) override;

	virtual void HandleCollisionWithPlayer(Player* inPlayer);
protected:
	Bomb();
	
	float				mLifeTime;
	uint32_t			mPlayerId;









};

typedef shared_ptr< Bomb >	BombPtr;