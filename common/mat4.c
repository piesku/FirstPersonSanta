#include "matrix.h"

#include <math.h>

void mat4_identity(mat4* mat)
{
	mat4_set(mat,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
}

void mat4_set(mat4* out,
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
{
	out->m00 = m00;
	out->m01 = m01;
	out->m02 = m02;
	out->m03 = m03;
	out->m10 = m10;
	out->m11 = m11;
	out->m12 = m12;
	out->m13 = m13;
	out->m20 = m20;
	out->m21 = m21;
	out->m22 = m22;
	out->m23 = m23;
	out->m30 = m30;
	out->m31 = m31;
	out->m32 = m32;
	out->m33 = m33;
}

void mat4_copy(mat4* out, const mat4* a)
{
	out->m00 = a->m00;
	out->m01 = a->m01;
	out->m02 = a->m02;
	out->m03 = a->m03;
	out->m10 = a->m10;
	out->m11 = a->m11;
	out->m12 = a->m12;
	out->m13 = a->m13;
	out->m20 = a->m20;
	out->m21 = a->m21;
	out->m22 = a->m22;
	out->m23 = a->m23;
	out->m30 = a->m30;
	out->m31 = a->m31;
	out->m32 = a->m32;
	out->m33 = a->m33;
}

bool mat4_invert(mat4* out, const mat4* mat)
{
	float a00 = mat->m00, a01 = mat->m01, a02 = mat->m02, a03 = mat->m03;
	float a10 = mat->m10, a11 = mat->m11, a12 = mat->m12, a13 = mat->m13;
	float a20 = mat->m20, a21 = mat->m21, a22 = mat->m22, a23 = mat->m23;
	float a30 = mat->m30, a31 = mat->m31, a32 = mat->m32, a33 = mat->m33;

	float b00 = a00 * a11 - a01 * a10;
	float b01 = a00 * a12 - a02 * a10;
	float b02 = a00 * a13 - a03 * a10;
	float b03 = a01 * a12 - a02 * a11;
	float b04 = a01 * a13 - a03 * a11;
	float b05 = a02 * a13 - a03 * a12;
	float b06 = a20 * a31 - a21 * a30;
	float b07 = a20 * a32 - a22 * a30;
	float b08 = a20 * a33 - a23 * a30;
	float b09 = a21 * a32 - a22 * a31;
	float b10 = a21 * a33 - a23 * a31;
	float b11 = a22 * a33 - a23 * a32;

	// Calculate the determinant
	float det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

	if (!det) {
		return false;
	}

	det = 1.0f / det;
	out->m00 = (a11 * b11 - a12 * b10 + a13 * b09) * det;
	out->m01 = (a02 * b10 - a01 * b11 - a03 * b09) * det;
	out->m02 = (a31 * b05 - a32 * b04 + a33 * b03) * det;
	out->m03 = (a22 * b04 - a21 * b05 - a23 * b03) * det;
	out->m10 = (a12 * b08 - a10 * b11 - a13 * b07) * det;
	out->m11 = (a00 * b11 - a02 * b08 + a03 * b07) * det;
	out->m12 = (a32 * b02 - a30 * b05 - a33 * b01) * det;
	out->m13 = (a20 * b05 - a22 * b02 + a23 * b01) * det;
	out->m20 = (a10 * b10 - a11 * b08 + a13 * b06) * det;
	out->m21 = (a01 * b08 - a00 * b10 - a03 * b06) * det;
	out->m22 = (a30 * b04 - a31 * b02 + a33 * b00) * det;
	out->m23 = (a21 * b02 - a20 * b04 - a23 * b00) * det;
	out->m30 = (a11 * b07 - a10 * b09 - a12 * b06) * det;
	out->m31 = (a00 * b09 - a01 * b07 + a02 * b06) * det;
	out->m32 = (a31 * b01 - a30 * b03 - a32 * b00) * det;
	out->m33 = (a20 * b03 - a21 * b01 + a22 * b00) * det;

	return true;
}

void mat4_multiply(mat4* out, const mat4* a, const mat4* b)
{
	float a00 = a->m00, a01 = a->m01, a02 = a->m02, a03 = a->m03;
	float a10 = a->m10, a11 = a->m11, a12 = a->m12, a13 = a->m13;
	float a20 = a->m20, a21 = a->m21, a22 = a->m22, a23 = a->m23;
	float a30 = a->m30, a31 = a->m31, a32 = a->m32, a33 = a->m33;

	// Cache only the current line of the second matrix
	float b0 = b->m00, b1 = b->m01, b2 = b->m02, b3 = b->m03;
	out->m00 = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out->m01 = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out->m02 = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out->m03 = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

	b0 = b->m10;
	b1 = b->m11;
	b2 = b->m12;
	b3 = b->m13;
	out->m10 = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out->m11 = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out->m12 = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out->m13 = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

	b0 = b->m20;
	b1 = b->m21;
	b2 = b->m22;
	b3 = b->m23;
	out->m20 = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out->m21 = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out->m22 = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out->m23 = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

	b0 = b->m30;
	b1 = b->m31;
	b2 = b->m32;
	b3 = b->m33;
	out->m30 = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out->m31 = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out->m32 = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out->m33 = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
}

void mat4_translate(mat4* out, const mat4* mat, const vec3* vec)
{
	float x = vec->x, y = vec->y, z = vec->z;
	float a00, a01, a02, a03;
	float a10, a11, a12, a13;
	float a20, a21, a22, a23;

	if (mat == out) {
		out->m30 = mat->m00 * x + mat->m10 * y + mat->m20 * z + mat->m30;
		out->m31 = mat->m01 * x + mat->m11 * y + mat->m21 * z + mat->m31;
		out->m32 = mat->m02 * x + mat->m12 * y + mat->m22 * z + mat->m32;
		out->m33 = mat->m03 * x + mat->m13 * y + mat->m23 * z + mat->m33;
	} else {
		a00 = mat->m00;
		a01 = mat->m01;
		a02 = mat->m02;
		a03 = mat->m03;
		a10 = mat->m10;
		a11 = mat->m11;
		a12 = mat->m12;
		a13 = mat->m13;
		a20 = mat->m20;
		a21 = mat->m21;
		a22 = mat->m22;
		a23 = mat->m23;

		out->m00 = a00;
		out->m01 = a01;
		out->m02 = a02;
		out->m03 = a03;
		out->m10 = a10;
		out->m11 = a11;
		out->m12 = a12;
		out->m13 = a13;
		out->m20 = a20;
		out->m21 = a21;
		out->m22 = a22;
		out->m23 = a23;

		out->m30 = a00 * x + a10 * y + a20 * z + mat->m30;
		out->m31 = a01 * x + a11 * y + a21 * z + mat->m31;
		out->m32 = a02 * x + a12 * y + a22 * z + mat->m32;
		out->m33 = a03 * x + a13 * y + a23 * z + mat->m33;
	}
}

bool mat4_rotate(mat4* out, const mat4* mat, float angle, const vec3* axis)
{
	float x = axis->x, y = axis->y, z = axis->z;
	float len = sqrtf(x * x + y * y + z * z);
	float s, c, t;
	float a00, a01, a02, a03;
	float a10, a11, a12, a13;
	float a20, a21, a22, a23;
	float b00, b01, b02;
	float b10, b11, b12;
	float b20, b21, b22;

	if (len < EPSILON) {
		return false;
	}

	len = 1.0f / len;
	x *= len;
	y *= len;
	z *= len;

	s = sinf(angle);
	c = cosf(angle);
	t = 1.0f - c;

	a00 = mat->m00;
	a01 = mat->m01;
	a02 = mat->m02;
	a03 = mat->m03;
	a10 = mat->m10;
	a11 = mat->m11;
	a12 = mat->m12;
	a13 = mat->m13;
	a20 = mat->m20;
	a21 = mat->m21;
	a22 = mat->m22;
	a23 = mat->m23;

	// Construct the elements of the rotation matrix
	b00 = x * x * t + c;
	b01 = y * x * t + z * s;
	b02 = z * x * t - y * s;
	b10 = x * y * t - z * s;
	b11 = y * y * t + c;
	b12 = z * y * t + x * s;
	b20 = x * z * t + y * s;
	b21 = y * z * t - x * s;
	b22 = z * z * t + c;

	// Perform rotation-specific matrix multiplication
	out->m00 = a00 * b00 + a10 * b01 + a20 * b02;
	out->m01 = a01 * b00 + a11 * b01 + a21 * b02;
	out->m02 = a02 * b00 + a12 * b01 + a22 * b02;
	out->m03 = a03 * b00 + a13 * b01 + a23 * b02;

	out->m10 = a00 * b10 + a10 * b11 + a20 * b12;
	out->m11 = a01 * b10 + a11 * b11 + a21 * b12;
	out->m12 = a02 * b10 + a12 * b11 + a22 * b12;
	out->m13 = a03 * b10 + a13 * b11 + a23 * b12;

	out->m20 = a00 * b20 + a10 * b21 + a20 * b22;
	out->m21 = a01 * b20 + a11 * b21 + a21 * b22;
	out->m22 = a02 * b20 + a12 * b21 + a22 * b22;
	out->m23 = a03 * b20 + a13 * b21 + a23 * b22;

	return true;
}

void mat4_perspective(mat4* out, float fovy, float aspect, float near, float far)
{
	float f = 1.0f / tanf(fovy / 2.0f);
	float nf = 1.0f / (near - far);

	out->m00 = f / aspect;
	out->m01 = 0.0f;
	out->m02 = 0.0f;
	out->m03 = 0.0f;
	out->m10 = 0.0f;
	out->m11 = f;
	out->m12 = 0.0f;
	out->m13 = 0.0f;
	out->m20 = 0.0f;
	out->m21 = 0.0f;
	out->m22 = (far + near) * nf;
	out->m23 = -1.0f;
	out->m30 = 0.0f;
	out->m31 = 0.0f;
	out->m32 = (2.0f * far * near) * nf;
	out->m33 = 0.0f;
}

void mat4_compose(mat4* out, const vec3* v, const quat* q, const vec3* s)
{
	// Quaternion math
	float x = q->x;
	float y = q->y;
	float z = q->z;
	float w = q->w;
	float x2 = x + x;
	float y2 = y + y;
	float z2 = z + z;
	float xx = x * x2;
	float xy = x * y2;
	float xz = x * z2;
	float yy = y * y2;
	float yz = y * z2;
	float zz = z * z2;
	float wx = w * x2;
	float wy = w * y2;
	float wz = w * z2;
	float sx = s->x;
	float sy = s->y;
	float sz = s->z;
	out->m00 = (1.0f - (yy + zz)) * sx;
	out->m01 = (xy + wz) * sx;
	out->m02 = (xz - wy) * sx;
	out->m03 = 0.0f;
	out->m10 = (xy - wz) * sy;
	out->m11 = (1.0f - (xx + zz)) * sy;
	out->m12 = (yz + wx) * sy;
	out->m13 = 0.0f;
	out->m20 = (xz + wy) * sz;
	out->m21 = (yz - wx) * sz;
	out->m22 = (1.0f - (xx + yy)) * sz;
	out->m23 = 0.0f;
	out->m30 = v->x;
	out->m31 = v->y;
	out->m32 = v->z;
	out->m33 = 1.0f;
}

void mat4_get_translation(vec3* out, const mat4* mat)
{
	out->x = mat->m30;
	out->y = mat->m31;
	out->z = mat->m32;
}

static inline float hypotf3(float x, float y, float z)
{
	return sqrtf(x * x + y * y + z * z);
}

void mat4_get_scaling(vec3* out, const mat4* mat)
{
	out->x = hypotf3(mat->m00, mat->m01, mat->m02);
	out->y = hypotf3(mat->m10, mat->m11, mat->m12);
	out->z = hypotf3(mat->m20, mat->m21, mat->m22);
}

void mat4_get_rotation(quat* out, const mat4* mat)
{
	vec3 scaling;
	mat4_get_scaling(&scaling, mat);

	float isx = 1.0f / scaling.x;
	float isy = 1.0f / scaling.y;
	float isz = 1.0f / scaling.z;

	float sm00 = mat->m00 * isx;
	float sm01 = mat->m01 * isy;
	float sm02 = mat->m02 * isz;
	float sm10 = mat->m10 * isx;
	float sm11 = mat->m11 * isy;
	float sm12 = mat->m12 * isz;
	float sm20 = mat->m20 * isx;
	float sm21 = mat->m21 * isy;
	float sm22 = mat->m22 * isz;

	float trace = sm00 + sm11 + sm22;
	float S = 0.0f;

	if (trace > 0) {
		S = sqrtf(trace + 1.0f) * 2.0f;
		out->w = 0.25f * S;
		out->x = (sm12 - sm21) / S;
		out->y = (sm20 - sm02) / S;
		out->z = (sm01 - sm10) / S;
	} else if (sm00 > sm11 && sm00 > sm22) {
		S = sqrtf(1.0f + sm00 - sm11 - sm22) * 2.0f;
		out->w = (sm12 - sm21) / S;
		out->x = 0.25f * S;
		out->y = (sm01 + sm10) / S;
		out->z = (sm20 + sm02) / S;
	} else if (sm11 > sm22) {
		S = sqrtf(1.0f + sm11 - sm00 - sm22) * 2.0f;
		out->w = (sm20 - sm02) / S;
		out->x = (sm01 + sm10) / S;
		out->y = 0.25f * S;
		out->z = (sm12 + sm21) / S;
	} else {
		S = sqrtf(1.0f + sm22 - sm00 - sm11) * 2.0f;
		out->w = (sm01 - sm10) / S;
		out->x = (sm20 + sm02) / S;
		out->y = (sm12 + sm21) / S;
		out->z = 0.25f * S;
	}
}

void mat4_get_forward(vec3* out, const mat4* mat)
{
	out->x = mat->m20;
	out->y = mat->m21;
	out->z = mat->m22;

	vec3_normalize(out, out);
}

void mat4_get_up(vec3* out, const mat4* mat)
{
	out->x = mat->m10;
	out->y = mat->m11;
	out->z = mat->m12;

	vec3_normalize(out, out);
}

void mat4_get_left(vec3* out, const mat4* mat)
{
	out->x = mat->m00;
	out->y = mat->m01;
	out->z = mat->m02;

	vec3_normalize(out, out);
}
