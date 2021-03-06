class Player : public GameObject
{
public:
	CLASS_IDENTIFICATION('PLAY', GameObject)

		enum ECatReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_PlayerId = 1 << 2,
		ECRS_Health = 1 << 3,
		ECRS_Animation = 1<< 4,
		ECRS_Live = 1 << 5,


		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_PlayerId | ECRS_Health | ECRS_Animation | ECRS_Live
	};




	static	GameObject* StaticCreate() { return new Player(); }

	virtual uint32_t GetAllStateMask()	const override { return ECRS_AllState; }

	virtual	Player* GetAsCat() { return this; }

	virtual void Update()	override;

	void ProcessInput(float inDeltaTime, const InputState& inInputState);
	void SimulateMovement(float inDeltaTime);

	void SetTimeToDie(float		inTimeToDie) { mTimeToDie = inTimeToDie; }
	bool	GetTimeToDie()		const { return mTimeToDie; }

	void SetCountDown(bool inCountDown) { mbCountDown = inCountDown; }
	bool	GetCountDown()		const { return mbCountDown; }

	void ProcessCollisions();
	void ProcessCollisionsWithScreenWalls();

	void ProcessCollisionsWithBlocks();

	float GetWallRestitution()		const { return mWallRestitution; }

	void		SetWidth(int pWidth) { mWidth = pWidth; }
	uint32_t	GetWidth()						const { return mWidth; }

	void		SetHeight(int pHeight) { mHeight = pHeight; }
	uint32_t	GetHeight()						const { return mHeight; }

	void		SetPlayerId(uint32_t inPlayerId) { mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const { return mPlayerId; }

	void			SetVelocity(const Vector3& inVelocity) { mVelocity = inVelocity; }
	const Vector3& GetVelocity()						const { return mVelocity; }

	void		SetAnimationVelocity(const float inAnimationVelocity) { mAnimationVelocity = inAnimationVelocity; }
	const float GetAnimationVelocity()				const { return mAnimationVelocity; }


	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

protected:
	Player();

private:


	void	AdjustVelocityByThrust(float inDeltaTime);

	Vector3				mVelocity;

	
	float				mMaxLinearSpeed;
	float				mMaxRotationSpeed;

	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mCatRestitution;
	uint32_t			mPlayerId;

protected:

	///move down here for padding reasons...

	float				mLastMoveTimestamp;

	float				mThrustDir;
	uint32_t			mDir;
	bool				mMove;
	int					mHealth;
	int					mWidth;
	int					mHeight;
	bool				mbCountDown;
	float				mTimeToDie;

	//float				mAnimationVelocity;

	bool				mIsShooting;





};

typedef shared_ptr< Player >	PlayerPtr;