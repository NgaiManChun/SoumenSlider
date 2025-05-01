#include "hurdle.h"

Hurdle::Hurdle(F3 size, F3 position,
	Texture* texture,
	bool canDestory,
	F3 rotate,
	F4 color,
	F2 uvOffset,
	F2 uvRange)
	: GameObjectQuad(size, position, texture, rotate, color, uvOffset, uvRange), canDestory(canDestory){}

void Hurdle::Update() {
	if (destory) {
		destoryProgress.IncreaseValue(GetDeltaTime());
		color.w = 0.5f * abs(cosf(destoryProgress * 2.0f * 3.14f * 2.0f));
		if (destoryProgress == 1.0f) {
			enable = false;
		}
	}
}

bool Hurdle::GetCanDestory()
{
	return canDestory;
}

bool Hurdle::GetDestory() 
{
	return destory;
}

void Hurdle::SetDestory(bool destory)
{
	this->destory = destory && canDestory;
}

std::string Hurdle::GetType()
{
	return "Hurdle";
}