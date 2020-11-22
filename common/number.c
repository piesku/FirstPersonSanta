#include "matrix.h"

inline float sign(float x)
{
	if (x > 0) {
		return 1.f;
	} else if (x < 0) {
		return -1.f;
	} else {
		return 0.f;
	}
}

inline float absf(float x)
{
	if (x < 0) {
		return -x;
	} else {
		return x;
	}
}

inline float minf(float a, float b)
{
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

inline float maxf(float a, float b)
{
	if (a < b) {
		return b;
	} else {
		return a;
	}
}

inline float lerp(float from, float to, float progress)
{
	return from + progress * (to - from);
}

inline float clamp(float mini, float maxi, float num)
{
	return maxf(mini, minf(maxi, num));
}