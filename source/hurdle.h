#ifndef _HURDLE_H
#define _HURDLE_H

#include "gameObject.h"
#include "progress.h"
using namespace MG;

class Hurdle : public GameObjectQuad {
protected:
	Progress destoryProgress = Progress(500.0f, false);
	bool canDestory = false;
	bool destory = false;
public:
	Hurdle(F3 size, F3 position,
		Texture* texture,
		bool canDestory,
		F3 rotate = F3{ 0.0f, 0.0f, 0.0f },
		F4 color = F4{ 1.0f, 1.0f, 1.0f, 1.0f },
		F2 uvOffset = F2{ 0.0f, 0.0f },
		F2 uvRange = F2{ 1.0f, 1.0f });
	void Update() override;
	std::string GetType() override;
	bool GetCanDestory();
	bool GetDestory();
	void SetDestory(bool destory);
};

#endif
