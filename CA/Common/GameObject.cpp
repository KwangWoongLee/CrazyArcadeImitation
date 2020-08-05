#include "GamePch.h"

GameObject::GameObject() :
	mIndexInWorld(-1),
	mCollisionRadius(0.5f),
	mDoesWantToDie(false),
	mRotation(0.f),
	mNetworkId(0),
	mColor(Colors::White),
	mScale(1.0f)
{
}

void GameObject::Update()
{
	//object don't do anything by default...	
}


Vector3 GameObject::GetForwardVector() const
{
	return Vector3();
}

void GameObject::SetNetworkId(int inNetworkId)
{
	//this doesn't put you in the map or remove you from it
	mNetworkId = inNetworkId;

}

void GameObject::SetRotation(float inRotation)
{
	//should we normalize using fmodf?
	mRotation = inRotation;
}

void GameObject::SetDirection(uint32_t inDirection)
{
	mDir = inDirection;
}

void GameObject::SetMove(bool inMove)
{
	mMove = inMove;
}