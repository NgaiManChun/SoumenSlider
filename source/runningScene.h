#ifndef _RUNNING_SCENE_H
#define _RUNNING_SCENE_H

#include "scene.h"
#include "progress.h"
using namespace MG;

#ifdef NX64
#define TEXTURE_YUBI "rom:/yubi.tga"
#define TEXTURE_WHITE "rom:/white.tga"
#define TEXTURE_PATTERN "rom:/pattern.tga"
#define TEXTURE_ASCII "rom:/ascii.tga"
#define TEXTURE_PAUSE "rom:/pause.tga"
#define TEXTURE_FENCE "rom:/fence.tga"
#define TEXTURE_HURDLE "rom:/hurdle.tga"
#else
#define TEXTURE_YUBI "asset\\texture\\yubi.png"
#define TEXTURE_WHITE "asset\\texture\\white.png"
#define TEXTURE_PATTERN "asset\\texture\\pattern.jpg"
#define TEXTURE_ASCII "asset\\texture\\ascii.png"
#define TEXTURE_PAUSE "asset\\texture\\pause.png"
#define TEXTURE_FENCE "asset\\texture\\fence.png"
#define TEXTURE_HURDLE "asset\\texture\\hurdle.png"
#endif

#define YUBI_WIDTH (567.0f * 0.5f)
#define YUBI_HEIGHT (807.0f * 0.5f)

#define COUNTER_WIDTH (64.0f * 3.0f)
#define COUNTER_HEIGHT (64.0f * 3.0f)

#define PAUSE_WIDTH (672.0f)
#define PAUSE_HEIGHT (448.0f)

#define TRACK_WIDTH (1456.0f)
#define TRACK_LINE_WIDTH (1456.0f + 120.0f)
#define TRACK_V_HEIGHT (498.0f)
#define TRACK_RATE (480.0f / TRACK_WIDTH)

#define SPEED_MATER_WIDTH (200.0f)
#define SPEED_MATER_HEIGHT (50.0f)

#define COURSE_LENGTH (60.0f) // メートル
#define MAX_SPEED (3.0f) // メートル／秒
#define ACCELERATION (MAX_SPEED / 8.0f) // １歩の移動量
#define HORIZONTAL_MAX_SPEED (10.0f)
#define ACC_ACCEPTABLE (20.0f)
#define ON_TABLE_INTENSITY (160.0f)

namespace RunningScene {

	struct CAMERA {
		float nearZ = -10.0f;
		float nearWidth = 0;
		float nearHeight = 0;

		float farZ = 290.0f;
		float farWidth = 0 * 5.0f;
		float farHeight = 0 * 5.0f;
	};

	struct INPUT_RESULT {
		float horizonFactor = 0.0f;
		bool acc = false;
		bool jump = false;
	};

	// =======================================================
	// クラス定義
	// =======================================================
	class RunningScene : public Scene {
	protected:
		std::list<GameObject*> UIGameObjects;
		std::list<GameObject*> projectGameObjects;
		GameObjectQuad* player;
		Progress playerSplit = Progress(1.0f, false);
		Progress jumpFrames = Progress(6.0f, false);
		float playerVelocity;
		float jumpVelocity;
		CAMERA camera;
		F4 skyColor = F4{ 75.0f / 255.0f, 180.0f / 255.0f, 240.0f / 255.0f, 1.0f };
		F4 grassColor = F4{ 180.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 1.0f };//F4{ 180.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 1.0f };
		F4 trackColor = F4{ 0.0f / 255.0f, 148.0f / 255.0f, 206.0f / 255.0f, 1.0f };//F4{ 202.0f / 255.0f, 102.0f / 255.0f, 79.0f / 255.0f, 1.0f };

		Texture* pattern_tex;
		Texture* white_tex;
		Texture* pause_tex;

		Progress fade = Progress(1000.0f, false);
		Progress fadeOut = Progress(1000.0f, false);
		
		bool pause = false;
		bool goingTitle = false;
		bool onTable = false;
		float accIntensitys[2] = {
			240.0f,
			200.0f
		};
		int accIntensityIndex = 0;
		int accIntensitySize = 2;
		float endPoint = 0.0f;
		bool started = false;
		bool ended = false;
	public:
		void Init() override;
		void Uninit() override;
		void Update() override;
		void Draw() override;
		virtual void DrawUI();
		INPUT_RESULT GetInput();
	};
}

#endif




