#include "matrix.h"

float signf(float x)
{
	if (x > 0.0f) {
		return 1.0f;
	} else if (x < 0.0f) {
		return -1.0f;
	} else {
		return 0.0f;
	}
}

float absf(float x)
{
	if (x < 0.0f) {
		return -x;
	} else {
		return x;
	}
}

float minf(float a, float b)
{
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

float maxf(float a, float b)
{
	if (a < b) {
		return b;
	} else {
		return a;
	}
}

float lerp(float from, float to, float progress)
{
	return from + progress * (to - from);
}

float clamp(float mini, float maxi, float num)
{
	return maxf(mini, minf(maxi, num));
}