#include "commonVariable.h"

static std::map<std::string, float> _float_vars;

void SetCommonFloat(std::string key, float value)
{
	_float_vars[key] = value;
}

float GetCommonFloat(std::string key)
{
	return _float_vars[key];
}