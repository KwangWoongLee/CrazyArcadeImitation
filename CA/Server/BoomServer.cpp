#include "ServerPch.h"

BoomServer::BoomServer()
{
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 0.5f;
}

void BoomServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

bool BoomServer::HasCollisionWithPlayer(Player* inPlayer)
{
	return true;
}


void BoomServer::Update()
{
	Boom::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}

}

void BoomServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	Vector3 location = inPlayer->GetLocation();
	Vector3 velocity = inPlayer->GetVelocity();
	float l, r, b, t;
	l = location.mX - inPlayer->GetWidth() / 100;
	r = location.mX + inPlayer->GetWidth() / 100;
	b = location.mY - inPlayer->GetHeight() / 100;
	t = location.mY + inPlayer->GetHeight() / 100;

	float l2, r2, b2, t2;
	l2 = GetLocation().mX - mWidth / 100.f;
	r2 = GetLocation().mX + mWidth / 100.f;
	b2 = GetLocation().mY + mHeight / 100.f;
	t2 = GetLocation().mY - mHeight / 100.f;


	//�浹���� ���� ���
	if (l > r2)
	{
		return;
	}
	else if (r < l2)
	{
		return;
	}
	else if (t > b2 - 0.041f)
	{
		return;

	}
	else if (b < t2 + 0.041f)
	{
		return;
	}


	if (inPlayer->GetPlayerId() == GetPlayerId())
	{
		inPlayer->SetCountDown(true);
		inPlayer->SetTimeToDie(Timing::sInstance.GetFrameStartTime() + 2.5f);
	}
}


