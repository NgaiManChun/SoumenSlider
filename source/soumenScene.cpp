#include "scene.h"
#include "progress.h"
#include <vector>
#include <random>

using namespace MG;


namespace SoumenScene {
	// =======================================================
	// 定数
	// =======================================================
	constexpr const char* TEXTURE_SOUMEN = "asset\\texture\\soumen\\soumen.png";
	constexpr const char* TEXTURE_SPLASH = "asset\\texture\\soumen\\splash.png";
	constexpr const char* TEXTURE_HASHI = "asset\\texture\\soumen\\hashi.png";
	constexpr const char* TEXTURE_HASHI_SPLASH = "asset\\texture\\soumen\\hashi_splash.png";
	constexpr const char* TEXTURE_BULLET = "asset\\texture\\white_bullet.png";
	constexpr const char* TEXTURE_BAMBOO = "asset\\texture\\soumen\\take.png";
	constexpr const char* TEXTURE_WATER = "asset\\texture\\soumen\\water.png";
	constexpr const char* TEXTURE_SUDARE = "asset\\texture\\soumen\\sudare.png";
	
	float position_x[3];
	float flowingSpeed = 10.0f;
	float magnification = 1.0f;
	

	class Soumen : public GameObjectQuad {
	private:
		Texture* splashTexture;
		Progress splashProgress = Progress(700.0f, false);
		int splash_col = 2;
		int splash_row = 1;
		int splash_index = 0;
		int score = 0;
	public:

		Soumen(
			F3 size, F3 position,
			Texture* texture,
			Texture* splashTexture,
			F3 rotate = F3{ 0.0f, 0.0f, 0.0f },
			F4 color = F4{ 1.0f, 1.0f, 1.0f, 1.0f },
			F2 uvOffset = F2{ 0.0f, 0.0f },
			F2 uvRange = F2{ 1.0f, 1.0f }
		) : GameObjectQuad(size, position, texture, rotate, color, uvOffset, uvRange), splashTexture(splashTexture) {}

		void Update() override {
			GameObjectQuad::Update();

			if (splashProgress == 1.0f) {
				splash_index = (splash_index + 1) % (splash_col * splash_row);
				splashProgress.SetValue(0.0f);
			}

			splashProgress.IncreaseValue(GetDeltaTime());
		}

		void Draw() override {
			GameObjectQuad::Draw();

			F2 uvRange = { 1.0f / splash_col, 1.0f / splash_row };
			F2 uvOffset = { (splash_index % splash_col) * uvRange.x,  (splash_index / splash_col) * uvRange.y };
			DrawQuad(
				splashTexture,
				{
					position.x,
					position.y - size.y * 0.5f,
					0.0f
				},
				{
					size.x,
					size.y * 136.0f / 364.0f,
					0.0f
				},
				rotate,
				color,
				uvOffset,
				uvRange
			);
		}
	};

	class Hashi : public GameObjectQuad {
	private:
		Texture* splashTexture;
		Progress splashProgress = Progress(700.0f, false);
		int splash_col = 2;
		int splash_row = 1;
		int splash_index = 0;
	public:

		Hashi(
			F3 size, F3 position,
			Texture* texture,
			Texture* splashTexture,
			F3 rotate = F3{ 0.0f, 0.0f, 0.0f },
			F4 color = F4{ 1.0f, 1.0f, 1.0f, 1.0f },
			F2 uvOffset = F2{ 0.0f, 0.0f },
			F2 uvRange = F2{ 1.0f, 1.0f }
		) : GameObjectQuad(size, position, texture, rotate, color, uvOffset, uvRange), splashTexture(splashTexture) {}

		void Update() override {
			GameObjectQuad::Update();

			if (splashProgress == 1.0f) {
				splash_index = (splash_index + 1) % (splash_col * splash_row);
				splashProgress.SetValue(0.0f);
			}

			splashProgress.IncreaseValue(GetDeltaTime());
		}

		void Draw() override {
			//GameObjectQuad::Draw();
			F3 __position = {
				position.x + size.x * 0.25f,
				position.y,
				0.0f
			};
			DrawQuad(texture, __position, size, rotate, color, uvOffset, uvRange);


			F3 _size = { size.x * 218.0f / 473.0f, size.y * 123.0f / 570.0f, 0.0f };
			F3 _position = {
				__position.x - size.x * 0.5f + _size.x * 0.25f,
				__position.y + size.y * 0.5f - _size.y * 0.25f,
				0.0f
			};
			F2 uvRange = { 1.0f / splash_col, 1.0f / splash_row };
			F2 uvOffset = { (splash_index % splash_col) * uvRange.x,  (splash_index / splash_col) * uvRange.y };
			DrawQuad(
				splashTexture,
				_position,
				_size,
				rotate,
				color,
				uvOffset,
				uvRange
			);
		}
	};

	// =======================================================
	// クラス定義
	// =======================================================
	class SoumenScene : public Scene {
	private:
		GameObjectQuad* player;
		GameObjectQuad* bamboo;
		GameObjectQuad* water;
		GameObjectQuad* sudare;
		GameObjectText* scoreLabel;
		int score = 0;
		list<GameObjectQuad*> obstrcles;
		int state;
		int o_state;
		Progress moveProgress = Progress(100.0f, false);
		Progress obstacleInterval = Progress(1000, false);
		bool ended = false;
	public:
		void Init() override;
		void Uninit() override;
		void Update() override;
		//void Draw() override;
	};

	

	

	// =======================================================
	// シーン登録
	// =======================================================
	static SceneName sceneName = REGISTER_SCENE("soumen", SoumenScene);


	// =======================================================
	// 初期化
	// =======================================================
	void SoumenScene::Init()
	{
		Scene::Init();

		// スクリーンの中心座標を取得
		F2 screenCenter = GetScreenCenter();

		// スクリーンのサイズを取得
		F2 screenSize = GetScreenSize();

		position_x[0] = screenCenter.x - 300.0f;
		position_x[1] = screenCenter.x;
		position_x[2] = screenCenter.x + 300.0f;

		state = 1;//中央に位置

		

		sudare = (GameObjectQuad*)AddGameObject(
			new GameObjectQuad(
				{ screenSize.x, screenSize.y, 0 },
				{ screenCenter.x,screenCenter.y,0 },
				LoadTexture(TEXTURE_SUDARE)
			)
		);

		bamboo = (GameObjectQuad*)AddGameObject(
			new GameObjectQuad(
				{ 1000, 1080, 0 },
				{ screenCenter.x,screenCenter.y,0 },
				LoadTexture(TEXTURE_BAMBOO)
			)
		);

		player = (GameObjectQuad*)AddGameObject(
			new Soumen(
				{ 200, 200, 0 },
				{ screenCenter.x,screenCenter.y + 270,0 },
				LoadTexture(TEXTURE_SOUMEN),
				LoadTexture(TEXTURE_SPLASH)
			)
		);

		water = (GameObjectQuad*)AddGameObject(
			new GameObjectQuad(
				{ 1000, 1080, 0 },
				{ screenCenter.x,screenCenter.y,0 },
				LoadTexture(TEXTURE_WATER)
			)
		);
		F3 fontSize{ 80.0f, 80.0f, 0.0f };
		scoreLabel = (GameObjectText*) AddGameObject(
			new GameObjectText(
				std::to_string(score).data(),
				fontSize,
				{ screenCenter.x - screenSize.x * 0.5f + 40.0f ,screenCenter.y - screenSize.y * 0.5f + 40.0f, 0.0f }
			)
		);
		scoreLabel->color = { 0, 0, 0, 1 };

		/*resultLabel = (GameObjectText*)AddGameObject(
			new GameObjectText(
				"ENTER: もう一回遊ぶ",
				fontSize,
				{ screenCenter.x, screenCenter.y, 0.0f },
				CENTER
			)
		);
		resultLabel->color = { 1, 1, 1, 0 };*/

		o_state = 1;
		state = 1;
		score = 0;
		magnification = 1.0f;
		ended = false;
	}


	// =======================================================
	// 終了処理
	// =======================================================
	void SoumenScene::Uninit()
	{
		Scene::Uninit();
		obstrcles.clear();
		player = nullptr;
		bamboo = nullptr;
		water = nullptr;
		sudare = nullptr;
		scoreLabel = nullptr;
	}


	// =======================================================
	// 更新
	// =======================================================
	void SoumenScene::Update()
	{
		Scene::Update();

		// スクリーンの中心座標を取得
		F2 screenCenter = GetScreenCenter();

		// スクリーンのサイズを取得
		F2 screenSize = GetScreenSize();

		
		if (!ended) {
			if (moveProgress == 1.0f) {
				if (state > 0 && Keyboard_IsKeyDownTrigger(KK_LEFT)) {
					o_state = state;
					state--;
					moveProgress.SetValue(0.0f);
				}
				else if (state < 2 && Keyboard_IsKeyDownTrigger(KK_RIGHT))
				{
					o_state = state;
					state++;
					moveProgress.SetValue(0.0f);
				}

			}

			player->position.x = (1.0f - moveProgress) * position_x[o_state] + moveProgress * position_x[state];
			moveProgress.IncreaseValue(GetDeltaTime() * magnification);

			//障害物発生カウント
			if (obstacleInterval == 1.0f) {
				std::vector<int>  laneNumbers = { 0, 1, 2 };
				std::random_device rd;
				std::mt19937 g(rd());
				std::shuffle(laneNumbers.begin(), laneNumbers.end(), g);

				int first = laneNumbers[0];
				int second = laneNumbers[1];

				float pos[2];

				if (first == 0) {
					pos[0] = position_x[0];
				}
				else if (first == 1) {
					pos[0] = position_x[1];
				}
				else {
					pos[0] = position_x[2];
				}

				if (second == 0) {
					pos[1] = position_x[0];
				}
				else if (second == 1) {
					pos[1] = position_x[1];
				}
				else {
					pos[1] = position_x[2];
				}

				obstrcles.push_back(
					(GameObjectQuad*)AddGameObject(
						new Hashi(
							{ 200, 200, 0 },
							{ pos[0], screenCenter.y - screenSize.y * 0.5f - 200.0f,0 },
							LoadTexture(TEXTURE_HASHI),
							LoadTexture(TEXTURE_HASHI_SPLASH)
						)
					)
				);

				obstrcles.push_back(
					(GameObjectQuad*)AddGameObject(
						new Hashi(
							{ 200, 200, 0 },
							{ pos[1], screenCenter.y - screenSize.y * 0.5f - 200.0f,0 },
							LoadTexture(TEXTURE_HASHI),
							LoadTexture(TEXTURE_HASHI_SPLASH)
						)
					)
				);

				obstacleInterval.SetValue(0.0f);
			}

			F4 playerArea = { 
				player->position.y - player->size.y * 0.4f,
				player->position.y,
				player->position.x - player->size.x * 0.4f,
				player->position.x + player->size.x * 0.4f
			};

			// コピーを取る、リスト変動防止
			list<GameObjectQuad*> _obstrcles(obstrcles);
			for (auto itr = _obstrcles.begin(); itr != _obstrcles.end(); itr++) {
				GameObjectQuad* gameObject = *itr;
				gameObject->position.y += flowingSpeed * magnification;

				F4 hashiArea = {
					gameObject->position.y + gameObject->size.y * 0.25f,
					gameObject->position.y + gameObject->size.y * 0.5f,
					gameObject->position.x - gameObject->size.x * 0.25f,
					gameObject->position.x + gameObject->size.x * 0.25f
				};

				bool colision =
				playerArea.x < hashiArea.y &&
				playerArea.y > hashiArea.x &&
				playerArea.z < hashiArea.w &&
				playerArea.w > hashiArea.z;

				if (colision) {
					ended = true;
					AddGameObject(
						new GameObjectText(
							"ENTER: もう一回遊ぶ",
							{ 80.0f, 80.0f, 0.0f },
							{ screenCenter.x, screenCenter.y, 0.0f },
							CENTER
						)
					);
				}

				if (gameObject->position.y > screenCenter.y + screenSize.y * 0.5f + gameObject->size.y) {
					DeleteGameObject(gameObject);
					obstrcles.remove(gameObject);
				}
			}

			water->uvOffset.y -= flowingSpeed / screenSize.y * magnification * 1.2f;
			bamboo->uvOffset.y -= flowingSpeed / screenSize.y * magnification * 1.1f;
			sudare->uvOffset.y -= flowingSpeed / screenSize.y * magnification * 0.5f;

			obstacleInterval.IncreaseValue(GetDeltaTime() * magnification);
			score += 1 * magnification;
			scoreLabel->SetValue(std::to_string(score));
			magnification += 0.0002f;
		}

		if (ended) {
			if (Keyboard_IsKeyDownTrigger(KK_ENTER)) {
				Uninit();
				Init();
			}
			
		}
		
	}


	// =======================================================
	// 描画
	// =======================================================
	/*void SoumenScene::Draw()
	{
		Scene::Draw();
	}*/
}
