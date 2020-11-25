#include "matrix.h"

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
	float halfToRad = (0.5f * PI) / 180.0f;
	x *= halfToRad;
	y *= halfToRad;
	z *= halfToRad;

	float sx = sinf(x);
	float cx = cosf(x);
	float sy = sinf(y);
	float cy = cosf(y);
	float sz = sinf(z);
	float cz = cosf(z);

	out[0] = sx * cy * cz - cx * sy * sz;
	out[1] = cx * sy * cz + sx * cy * sz;
	out[2] = cx * cy * sz - sx * sy * cz;
	out[3] = cx * cy * cz + sx * sy * sz;
}

void quat_from_axis(quat out, vec3 axis, float angle)
{
	float half = angle / 2.0f;
	out[0] = sinf(half) * axis[0];
	out[1] = sinf(half) * axis[1];
	out[2] = sinf(half) * axis[2];
	out[3] = cosf(half);
}

void quat_lerp(quat out, quat a, quat b, float t)
{
	float ax = a[0];
	float ay = a[1];
	float az = a[2];
	float aw = a[3];
	out[0] = ax + t * (b[0] - ax);
	out[1] = ay + t * (b[1] - ay);
	out[2] = az + t * (b[2] - az);
	out[3] = aw + t * (b[3] - aw);
	return out;
}

void quat_slerp(quat out, quat a, quat b, float t)
{
	float ax = a[0];
	float ay = a[1];
	float az = a[2];
	float aw = a[3];
	float bx = b[0];
	float by = b[1];
	float bz = b[2];
	float bw = b[3];

	float omega, cosom, sinom, scale0, scale1;

	// calc cosine
	cosom = ax * bx + ay * by + az * bz + aw * bw;
	// adjust signs (if necessary)
	if (cosom < 0.0f) {
		cosom = -cosom;
		bx = -bx;
		by = -by;
		bz = -bz;
		bw = -bw;
	}
	// calculate coefficients
	if (1.0 - cosom > EPSILON) {
		// standard case (slerp)
		omega = acosf(cosom);
		sinom = sinf(omega);
		scale0 = sinf((1.0f - t) * omega) / sinom;
		scale1 = sinf(t * omega) / sinom;
	} else {
		// "from" and "to" quaternions are very close
		//  ... so we can do a linear interpolation
		scale0 = 1.0f - t;
		scale1 = t;
	}
	// calculate final values
	out[0] = scale0 * ax + scale1 * bx;
	out[1] = scale0 * ay + scale1 * by;
	out[2] = scale0 * az + scale1 * bz;
	out[3] = scale0 * aw + scale1 * bw;

	return out;
}
