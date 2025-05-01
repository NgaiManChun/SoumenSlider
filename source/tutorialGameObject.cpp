#include "tutorialGameObject.h"

#ifdef NX64
#define TEXTURE_TITLE "rom:/title.tga"
#define TEXTURE_WHITE "rom:/white.tga"
#else
#define TEXTURE_TITLE "asset\\texture\\title.png"
#define TEXTURE_WHITE "asset\\texture\\white.png"
#endif

TutorialGameObject::TutorialGameObject(F3 size, F3 position, F3 rotate) : GameObject(size, position, rotate)
{
	// スクリーンの中心座標を取得
	F2 screenCenter = GetScreenCenter();

	// スクリーンのサイズを取得
	F2 screenSize = GetScreenSize();

	bgTexture = LoadTexture(TEXTURE_WHITE);

	F3 fontSize{ 40.0f, 40.0f, 0.0f };
	dot = new GameObjectText(
		"",
		fontSize,
		F3{ screenCenter.x, screenCenter.y + screenSize.y * 0.35f - 40.0f, 0.0f },
		CENTER
	);

	cursorDot = new GameObjectText(
		"",
		fontSize,
		F3{ screenCenter.x, screenCenter.y + screenSize.y * 0.35f - 40.0f, 0.0f },
		CENTER,
		0.0f,
		{},
		F4{ 245.0f / 255.0f, 244.0f / 255.0f, 14.0f / 255.0f, 1.0f }
	);
	labelNext = new GameObjectText(
		"",
		fontSize,
		F3{ screenCenter.x + screenSize.x * 0.35f - 40.0f, screenCenter.y + screenSize.y * 0.35f - 40.0f - 15.0f, 0.0f },
		RIGHT_TOP
	);

	labelSkip = new GameObjectText(
		"-：チュートリアルスキップ",
		fontSize,
		F3{ screenCenter.x - screenSize.x * 0.35f + 40.0f, screenCenter.y + screenSize.y * 0.35f - 40.0f - 15.0f, 0.0f },
		LEFT_TOP
	);

	UpdateDot();
}

TutorialGameObject::~TutorialGameObject()
{
	delete dot;
	delete cursorDot;
	delete labelNext;
	delete labelSkip;
	dot = nullptr;
	cursorDot = nullptr;
	labelNext = nullptr;
	labelSkip = nullptr;
}

void TutorialGameObject::Update()
{
	introductionFade.IncreaseValue(GetDeltaTime());
}

void TutorialGameObject::Draw()
{
	
	if (tutorialTextures.size() > 0) {

		// スクリーンの中心座標を取得
		F2 screenCenter = GetScreenCenter();

		// スクリーンのサイズを取得
		F2 screenSize = GetScreenSize();

		F3 size = F3{ screenSize.x * 0.7f, screenSize.y * 0.7f, 0.0f };
		F3 position = F3{ screenCenter.x, screenCenter.y, 0.0f };

		DrawQuad(
			bgTexture,
			position,
			size,
			F3{},
			F4{ 0.0f, 0.0f, 0.0f, 0.5f }
		);

		float padding = 40.0f;
		float bottomHeight = 50.0f;
		size = F3{ screenSize.x * 0.7f - padding * 2.0f, screenSize.y * 0.7f - padding * 2.0f - bottomHeight, 0.0f };
		position = F3{ screenCenter.x, screenCenter.y - bottomHeight * 0.5f, 0.0f };

		DrawQuad(
			tutorialTextures[currentPage],
			position,
			size,
			F3{},
			F4{ 1.0f, 1.0f, 1.0f, introductionFade }
		);

		dot->Draw();
		cursorDot->Draw();
		labelNext->Draw();
		labelSkip->Draw();
	}

	
}

void TutorialGameObject::AddPage(Texture* texture)
{
	tutorialTextures.push_back(texture);
	UpdateDot();
}

void TutorialGameObject::UpdateDot()
{
	string dotString = "";
	string cursorString = "";
	for (int i = 0; i < tutorialTextures.size(); i++) {
		dotString += "●";
		if (i == currentPage) {
			cursorString += "●";
		}
		else {
			cursorString += "　";
		}
	}
	string label = "";
	if (currentPage > 0) {
		label += " ←：前へ";
	}
	if (currentPage < tutorialTextures.size() - 1) {
		label += " →：次へ";
	}
	if (currentPage == tutorialTextures.size() - 1) {
		label += " ↓：開始";
	}
	labelNext->SetValue(label);
	dot->SetValue(dotString);
	cursorDot->SetValue(cursorString);
}

void TutorialGameObject::NextPage()
{
	if (currentPage < tutorialTextures.size() - 1) {
		ToPage(currentPage + 1);
	}
}

void TutorialGameObject::PreviousPage() 
{
	if (currentPage > 0) {
		ToPage(currentPage - 1);
	}
}

void TutorialGameObject::ToPage(int page)
{
	currentPage = page;
	UpdateDot();
	introductionFade.SetValue(0.0f);
}

int TutorialGameObject::GetTotalPage()
{
	return tutorialTextures.size();
}

int TutorialGameObject::GetCurrentPage()
{
	return currentPage;
}