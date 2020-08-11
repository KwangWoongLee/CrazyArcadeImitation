class Boom : public GameObject
{
public:
	CLASS_IDENTIFICATION('BOOM', GameObject)

		enum ECatReplicationState
	{
		EBRS_Pose = 1 << 0,
		EBRS_Color = 1 << 1,
		EBRS_PlayerId = 1 << 2,
		EBRS_Animation = 1 << 3,
		EBRS_State = 1 << 4,

		EBRS_AllState = EBRS_Pose | EBRS_Color | EBRS_PlayerId | EBRS_Animation | EBRS_State
	};




	static	GameObject* StaticCreate() { return new Boom(); }

	virtual uint32_t GetAllStateMask()	const { return EBRS_AllState; }

	virtual void Update()	override;



	void		SetPlayerId(uint32_t inPlayerId) { mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const { return mPlayerId; }

	void		SetAnimationVelocity(const float inAnimationVelocity) { mAnimationVelocity = inAnimationVelocity; }
	const float GetAnimationVelocity()				const { return mAnimationVelocity; }

	void		InitFromBomb(Bomb* inBomb,int inState);

	void		SetBoomState(int inBoomState) { mBoomState = inBoomState; }
	int			GetBoomState()				const { return mBoomState; }
	
	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

	virtual bool HasCollisionWithPlayer(Player* inPlayer);

	virtual void HandleCollisionWithPlayer(Player* inPlayer);
protected:
	Boom();

	float				mLifeTime;
	uint32_t			mPlayerId;
	int					mWidth;
	int					mHeight;
	int					mBoomState;









};

typedef shared_ptr< Boom >	BoomPtr;