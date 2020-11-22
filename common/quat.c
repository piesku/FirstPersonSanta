#include "matrix.h"

#define _USE_MATH_DEFINES
#include <math.h>

void quat_multiply(quat out, quat a, quat b)
{
	float ax = a[0];
	float ay = a[1];
	float az = a[2];
	float aw = a[3];
	float bx = b[0];
	float by = b[1];
	float bz = b[2];
	float bw = b[3];

	out[0] = ax * bw + aw * bx + ay * bz - az * by;
	out[1] = ay * bw + aw * by + az * bx - ax * bz;
	out[2] = az * bw + aw * bz + ax * by - ay * bx;
	out[3] = aw * bw - ax * bx - ay * by - az * bz;
}

void quat_from_euler(quat out, float x, float y, float z)
{
	float halfToRad = (0.5 * M_PI) / 180.0;
	x *= halfToRad;
	y *= halfToRad;
	z *= halfToRad;

	float sx = sin(x);
	float cx = cos(x);
	float sy = sin(y);
	float cy = cos(y);
	float sz = sin(z);
	float cz = cos(z);

	out[0] = sx * cy * cz - cx * sy * sz;
	out[1] = cx * sy * cz + sx * cy * sz;
	out[2] = cx * cy * sz - sx * sy * cz;
	out[3] = cx * cy * cz + sx * sy * sz;
}

void quat_from_axis(quat out, vec3 axis, float angle)
{
	float half = angle / 2.0;
	out[0] = sin(half) * axis[0];
	out[1] = sin(half) * axis[1];
	out[2] = sin(half) * axis[2];
	out[3] = cos(half);
}
