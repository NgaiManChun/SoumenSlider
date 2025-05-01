#include "scene.h"
using namespace MG;

namespace SoumenTitleScene {
	// =======================================================
	// 定数
	// =======================================================
	constexpr const char* TEXTURE_TITLE = "asset\\texture\\soumen\\title.png";
	constexpr const char* TEXTURE_SUDARE = "asset\\texture\\soumen\\sudare.png";

	// =======================================================
	// クラス定義
	// =======================================================
	class SoumenTitleScene : public Scene {
	public:
		void Init() override;
		//void Uninit() override;
		void Update() override;
		//void Draw() override;
	};


	// =======================================================
	// シーン登録
	// =======================================================
	static SceneName sceneName = REGISTER_SCENE("soumen_title", SoumenTitleScene);


	// =======================================================
	// 初期化
	// =======================================================
	void SoumenTitleScene::Init()
	{
		Scene::Init();

		// スクリーンの中心座標を取得
		F2 screenCenter = GetScreenCenter();

		// スクリーンのサイズを取得
		F2 screenSize = GetScreenSize();

		AddGameObject(
			new GameObjectQuad(
				{ screenSize.x, screenSize.y, 0 },
				{ screenCenter.x,screenCenter.y,0 },
				LoadTexture(TEXTURE_SUDARE)
			)
		);

		AddGameObject(
			new GameObjectQuad(
				{ 391 *3, 42 * 3, 0 },
				{ screenCenter.x,screenCenter.y,0 },
				LoadTexture(TEXTURE_TITLE)
			)
		);

		F3 fontSize{ 80.0f, 80.0f, 0.0f };
		AddGameObject(
			new GameObjectText(
				"Press Enter",
				fontSize,
				{ screenCenter.x ,screenCenter.y + screenSize.y * 0.25f, 0.0f },
				CENTER
			)
		);
	}


	// =======================================================
	// 終了処理
	// =======================================================
	/*void SoumenTitleScene::Uninit()
	{
		Scene::Uninit();
	}*/


	// =======================================================
	// 更新
	// =======================================================
	void SoumenTitleScene::Update()
	{
		Scene::Update();
		if (Keyboard_IsKeyDownTrigger(KK_ENTER)) {
			SceneTransit("soumen", "sample_transition");
		}

	}


	// =======================================================
	// 描画
	// =======================================================
	/*void SoumenTitleScene::Draw()
	{
		Scene::Draw();
	}*/
}
