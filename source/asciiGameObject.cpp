#include "asciiGameObject.h"

AsciiGameObject::AsciiGameObject(F3 size, F3 position, Texture* texture,
	F3 rotate,
	int row, int col, std::string value,
	float spacing,
	F4 color) :
	GameObjectQuad(size, position, texture, rotate, color), row(row), col(col), value(value.data()), spacing(spacing)
{}

void AsciiGameObject::SetValue(std::string value) {
	this->value = value.data();
}

void AsciiGameObject::Draw() {
	const char* chars = value.c_str();
	F2 uvRange = F2{ 1.0f / row, 1.0f / col };
	float width = value.size() * size.x + spacing * (value.size() - 1);
	float currX = position.x - width * 0.5f + size.x * 0.5f;
	int length = value.length();
	for (int i = 0; i < length; i++) {
		int index = chars[i] - 32;
		F2 uvOffset = F2{ uvRange.x * (index % col), uvRange.y * (index / col) };
		DrawQuad(texture, F3{ currX, position.y, position.z }, size, rotate, color, uvOffset, uvRange);
		currX += size.x + spacing;
	}
}