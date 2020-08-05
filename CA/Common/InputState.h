
class InputState
{
public:

	InputState() :
		mDesiredRightAmount(0),
		mDesiredLeftAmount(0),
		mDesiredForwardAmount(0),
		mDesiredBackAmount(0),
		mDesiredDir(0),
		mMove(false),
		mIsShooting(false)
	{}

	float GetDesiredHorizontalDelta()	const { return mDesiredRightAmount - mDesiredLeftAmount; }
	float GetDesiredVerticalDelta()		const { return mDesiredForwardAmount - mDesiredBackAmount; }

	uint32_t GetDesiredDir() const { return mDesiredDir; }
	bool	GetDesiredMove()	const { return mMove; }

	bool  IsShooting()					const { return mIsShooting; }

	bool Write(OutputMemoryBitStream& inOutputStream) const;
	bool Read(InputMemoryBitStream& inInputStream);

private:
	friend class InputManager;

	float	mDesiredRightAmount, mDesiredLeftAmount;
	float	mDesiredForwardAmount, mDesiredBackAmount;
	uint32_t mDesiredDir;
	bool	mMove;
	bool	mIsShooting;

};