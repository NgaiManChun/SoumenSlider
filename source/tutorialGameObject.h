#ifndef _TUTORIAL_GAME_OBJECT_H
#define _TUTORIAL_GAME_OBJECT_H

#include "gameObject.h"
#include "progress.h"
#include <vector>
using namespace MG;

class TutorialGameObject : public GameObject {
protected:
	std::vector<Texture*> tutorialTextures;
	GameObjectText* dot;
	GameObjectText* cursorDot;
	GameObjectText* labelNext;
	GameObjectText* labelSkip;
	Texture* bgTexture;
	Progress introductionFade = Progress(300.0f, false);
	int currentPage = 0;
public:
	TutorialGameObject(F3 size, F3 position, F3 rotate);
	~TutorialGameObject();
	void Update() override;
	void Draw() override;
	void AddPage(Texture* texture);
	void UpdateDot();
	void NextPage();
	void PreviousPage();
	void ToPage(int page);
	int GetTotalPage();
	int GetCurrentPage();
};

#endif
