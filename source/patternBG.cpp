#include "patternBG.h"

PatternBG::PatternBG(
	F3 size, F3 position,
	Texture* texture,
	F2 patternSize, F2 patternMargins, F2 patternOffset,
	F3 rotate, F4 color, F2 uvOffset, F2 uvRange
) : GameObjectQuad(size, position, texture, rotate, color, uvOffset, uvRange),
patternSize(patternSize), patternMargins(patternMargins), patternOffset(patternOffset) {}

void PatternBG::Draw()
{
	F2 leftTop = { position.x - size.x * 0.5f, position.y - size.y * 0.5f };
	leftTop.x += patternOffset.x;
	leftTop.y += patternOffset.y;
	F3 patternPosition = { leftTop.x, leftTop.y, 0.0f };
	F3 _patternSize = { patternSize.x, patternSize.y, 0.0f };
	patternPosition.x += patternSize.x * 0.5f;
	patternPosition.y += patternSize.y * 0.5f;
	float xMax = position.x + size.x + patternSize.x * 0.5f;
	float yMax = position.y + size.y + patternSize.y * 0.5f;
	while (patternPosition.x < xMax) {
		while (patternPosition.y < xMax) {
			DrawQuad(texture, patternPosition, _patternSize, rotate, color, uvOffset, uvRange);

			patternPosition.y += patternMargins.y;
			patternPosition.y += patternSize.y;
		}
		patternPosition.y = leftTop.y + patternSize.y * 0.5f;
		patternPosition.x += patternMargins.x;
		patternPosition.x += patternSize.x;
	}
}