#include "matrix.h"

#include <math.h>

void quat_multiply(quat* out, const quat a, const quat b)
{
	float ax = a.x;
	float ay = a.y;
	float az = a.z;
	float aw = a.w;
	float bx = b.x;
	float by = b.y;
	float bz = b.z;
	float bw = b.w;

	out->x = ax * bw + aw * bx + ay * bz - az * by;
	out->y = ay * bw + aw * by + az * bx - ax * bz;
	out->z = az * bw + aw * bz + ax * by - ay * bx;
	out->w = aw * bw - ax * bx - ay * by - az * bz;
}

// Compute a quaternion out of three Euler angles given in degrees.
// The order of rotation is YXZ.
void quat_from_euler(quat* out, float x, float y, float z)
{
	float half_to_rad = 0.5f * DEG_TO_RAD;
	x *= half_to_rad;
	y *= half_to_rad;
	z *= half_to_rad;

	float sx = sinf(x);
	float cx = cosf(x);
	float sy = sinf(y);
	float cy = cosf(y);
	float sz = sinf(z);
	float cz = cosf(z);

	out->x = sx * cy * cz + cx * sy * sz;
	out->y = cx * sy * cz - sx * cy * sz;
	out->z = cx * cy * sz - sx * sy * cz;
	out->w = cx * cy * cz + sx * sy * sz;
}

void quat_from_axis(quat* out, const vec3 axis, float angle)
{
	float half = angle / 2.0f;
	out->x = sinf(half) * axis.x;
	out->y = sinf(half) * axis.y;
	out->z = sinf(half) * axis.z;
	out->w = cosf(half);
}

void quat_lerp(quat* out, const quat a, const quat b, float t)
{
	float ax = a.x;
	float ay = a.y;
	float az = a.z;
	float aw = a.w;
	out->x = ax + t * (b.x - ax);
	out->y = ay + t * (b.y - ay);
	out->z = az + t * (b.z - az);
	out->w = aw + t * (b.w - aw);
}

void quat_slerp(quat* out, const quat a, const quat b, float t)
{
	float ax = a.x;
	float ay = a.y;
	float az = a.z;
	float aw = a.w;
	float bx = b.x;
	float by = b.y;
	float bz = b.z;
	float bw = b.w;

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
	out->x = scale0 * ax + scale1 * bx;
	out->y = scale0 * ay + scale1 * by;
	out->z = scale0 * az + scale1 * bz;
	out->w = scale0 * aw + scale1 * bw;
}
