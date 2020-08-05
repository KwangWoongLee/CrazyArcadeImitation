#include "GamePch.h"

namespace
{
	void WriteDirection(OutputMemoryBitStream& inOutputStream, uint32_t inDirValue)
	{
		inOutputStream.Write(inDirValue,32);
	}

	void ReadDirection(InputMemoryBitStream& inOutputStream, uint32_t& outDirValue)
	{
		inOutputStream.Read(outDirValue,32);
	}

	void WriteSignedBinaryValue(OutputMemoryBitStream& inOutputStream, float inValue)
	{
		bool isNonZero = (inValue != 0.f);
		inOutputStream.Write(isNonZero);
		if (isNonZero)
		{
			inOutputStream.Write(inValue > 0.f);
		}
	}

	void ReadSignedBinaryValue(InputMemoryBitStream& inInputStream, float& outValue)
	{
		bool isNonZero;
		inInputStream.Read(isNonZero);
		if (isNonZero)
		{
			bool isPositive;
			inInputStream.Read(isPositive);
			outValue = isPositive ? 1.f : -1.f;
		}
		else
		{
			outValue = 0.f;
		}
	}
}

bool InputState::Write(OutputMemoryBitStream& inOutputStream) const
{
	WriteDirection(inOutputStream, GetDesiredDir());
	WriteSignedBinaryValue(inOutputStream, GetDesiredHorizontalDelta());
	WriteSignedBinaryValue(inOutputStream, GetDesiredVerticalDelta());
	inOutputStream.Write(mMove);
	inOutputStream.Write(mIsShooting);

	return false;
}

bool InputState::Read(InputMemoryBitStream& inInputStream)
{
	ReadDirection(inInputStream, mDesiredDir);
	ReadSignedBinaryValue(inInputStream, mDesiredRightAmount);
	ReadSignedBinaryValue(inInputStream, mDesiredForwardAmount);
	inInputStream.Read(mMove);
	inInputStream.Read(mIsShooting);

	return true;
}