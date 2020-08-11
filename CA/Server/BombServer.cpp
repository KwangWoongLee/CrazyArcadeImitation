#include "ServerPch.h"

BombServer::BombServer()
{
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 1.f;
}

void BombServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
	BoomPtr boom_center = std::static_pointer_cast<Boom>(GameObjectRegistry::sInstance->CreateGameObject('BOOM'));
	boom_center->InitFromBomb(this,0);
	BoomPtr boom_left = std::static_pointer_cast<Boom>(GameObjectRegistry::sInstance->CreateGameObject('BMLT'));
	boom_left->InitFromBomb(this,1);
	BoomPtr boom_right = std::static_pointer_cast<Boom>(GameObjectRegistry::sInstance->CreateGameObject('BMRT'));
	boom_right->InitFromBomb(this,2);
	BoomPtr boom_up = std::static_pointer_cast<Boom>(GameObjectRegistry::sInstance->CreateGameObject('BMUP'));
	boom_up->InitFromBomb(this,3);
	BoomPtr boom_down = std::static_pointer_cast<Boom>(GameObjectRegistry::sInstance->CreateGameObject('BMDW'));
	boom_down->InitFromBomb(this,4);

}

bool BombServer::HasCollisionWithPlayer(Player* inPlayer)
{
	return true;
}


void BombServer::Update()
{
	Bomb::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);

	}

}

void BombServer::HandleCollisionWithPlayer(Player* inPlayer)
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


	//충돌하지 않은 경우
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



	if (l < r2 && velocity.mX < 0)
	{
		velocity.mX = -velocity.mX * 0.2f;
		location.mX = r2 + mWidth * 0.01f * 0.1f;
		inPlayer->SetLocation(location);
	}
	else if (r > l2 && velocity.mX > 0)
	{
		velocity.mX = -velocity.mX * 0.2f;
		location.mX = l2 - mWidth * 0.01f * 0.1f;
		inPlayer->SetLocation(location);
	}

	if (b >= t2 && velocity.mY > 0)
	{
		velocity.mY = -velocity.mY * 0.2f;
		location.mY = t2 + mWidth * 0.01f * 0.1f;
		inPlayer->SetLocation(location);
	}
	else if (t <= b2 && velocity.mY < 0)
	{
		velocity.mY = -velocity.mY * 0.2f;
		location.mY = b2 - mWidth * 0.01f * 0.1f;
		inPlayer->SetLocation(location);
	}
}


