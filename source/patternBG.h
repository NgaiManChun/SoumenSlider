#include "gameObject.h"
using namespace MG;

#ifndef _PATTERN_BG_H
#define _PATTERN_BG_H

class PatternBG : public GameObjectQuad {
protected:
	F2 patternSize;
	F2 patternMargins;
public:
	F2 patternOffset;
	PatternBG(
		F3 size, F3 position,
		Texture* texture,
		F2 patternSize, F2 patternMargins, F2 patternOffset,
		F3 rotate = F3{ 0.0f, 0.0f, 0.0f },
		F4 color = F4{ 1.0f, 1.0f, 1.0f, 1.0f },
		F2 uvOffset = F2{ 0.0f, 0.0f },
		F2 uvRange = F2{ 1.0f, 1.0f }
	);

	void Draw() override;
};

#endif



