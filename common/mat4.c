#include "matrix.h"

#include <math.h>

void mat4_identity(mat4 mat)
{
	mat4_set(mat,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
};

void mat4_set(mat4 out,
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
{
	out[0] = m00;
	out[1] = m01;
	out[2] = m02;
	out[3] = m03;
	out[4] = m10;
	out[5] = m11;
	out[6] = m12;
	out[7] = m13;
	out[8] = m20;
	out[9] = m21;
	out[10] = m22;
	out[11] = m23;
	out[12] = m30;
	out[13] = m31;
	out[14] = m32;
	out[15] = m33;
};

bool mat4_invert(mat4 out, const mat4 mat)
{
	float a00 = mat[0], a01 = mat[1], a02 = mat[2], a03 = mat[3];
	float a10 = mat[4], a11 = mat[5], a12 = mat[6], a13 = mat[7];
	float a20 = mat[8], a21 = mat[9], a22 = mat[10], a23 = mat[11];
	float a30 = mat[12], a31 = mat[13], a32 = mat[14], a33 = mat[15];

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
	out[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
	out[1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
	out[2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
	out[3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
	out[4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
	out[5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
	out[6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
	out[7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
	out[8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
	out[9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
	out[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
	out[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
	out[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
	out[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
	out[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
	out[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;

	return true;
}

void mat4_multiply(mat4 out, const mat4 a, const mat4 b)
{
	float a00 = a[0], a01 = a[1], a02 = a[2], a03 = a[3];
	float a10 = a[4], a11 = a[5], a12 = a[6], a13 = a[7];
	float a20 = a[8], a21 = a[9], a22 = a[10], a23 = a[11];
	float a30 = a[12], a31 = a[13], a32 = a[14], a33 = a[15];

	// Cache only the current line of the second matrix
	float b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3];
	out[0] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out[1] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out[2] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out[3] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

	b0 = b[4];
	b1 = b[5];
	b2 = b[6];
	b3 = b[7];
	out[4] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out[5] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out[6] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out[7] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

	b0 = b[8];
	b1 = b[9];
	b2 = b[10];
	b3 = b[11];
	out[8] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out[9] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out[10] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out[11] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;

	b0 = b[12];
	b1 = b[13];
	b2 = b[14];
	b3 = b[15];
	out[12] = b0 * a00 + b1 * a10 + b2 * a20 + b3 * a30;
	out[13] = b0 * a01 + b1 * a11 + b2 * a21 + b3 * a31;
	out[14] = b0 * a02 + b1 * a12 + b2 * a22 + b3 * a32;
	out[15] = b0 * a03 + b1 * a13 + b2 * a23 + b3 * a33;
};

void mat4_translate(mat4 out, const mat4 mat, const vec3 vec)
{
	float x = vec[0], y = vec[1], z = vec[2];
	float a00, a01, a02, a03;
	float a10, a11, a12, a13;
	float a20, a21, a22, a23;

	if (mat == out) {
		out[12] = mat[0] * x + mat[4] * y + mat[8] * z + mat[12];
		out[13] = mat[1] * x + mat[5] * y + mat[9] * z + mat[13];
		out[14] = mat[2] * x + mat[6] * y + mat[10] * z + mat[14];
		out[15] = mat[3] * x + mat[7] * y + mat[11] * z + mat[15];
	} else {
		a00 = mat[0];
		a01 = mat[1];
		a02 = mat[2];
		a03 = mat[3];
		a10 = mat[4];
		a11 = mat[5];
		a12 = mat[6];
		a13 = mat[7];
		a20 = mat[8];
		a21 = mat[9];
		a22 = mat[10];
		a23 = mat[11];

		out[0] = a00;
		out[1] = a01;
		out[2] = a02;
		out[3] = a03;
		out[4] = a10;
		out[5] = a11;
		out[6] = a12;
		out[7] = a13;
		out[8] = a20;
		out[9] = a21;
		out[10] = a22;
		out[11] = a23;

		out[12] = a00 * x + a10 * y + a20 * z + mat[12];
		out[13] = a01 * x + a11 * y + a21 * z + mat[13];
		out[14] = a02 * x + a12 * y + a22 * z + mat[14];
		out[15] = a03 * x + a13 * y + a23 * z + mat[15];
	}
}

bool mat4_rotate(mat4 out, const mat4 mat, float angle, const vec3 axis)
{
	float x = axis[0], y = axis[1], z = axis[2];
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

	a00 = mat[0];
	a01 = mat[1];
	a02 = mat[2];
	a03 = mat[3];
	a10 = mat[4];
	a11 = mat[5];
	a12 = mat[6];
	a13 = mat[7];
	a20 = mat[8];
	a21 = mat[9];
	a22 = mat[10];
	a23 = mat[11];

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
	out[0] = a00 * b00 + a10 * b01 + a20 * b02;
	out[1] = a01 * b00 + a11 * b01 + a21 * b02;
	out[2] = a02 * b00 + a12 * b01 + a22 * b02;
	out[3] = a03 * b00 + a13 * b01 + a23 * b02;

	out[4] = a00 * b10 + a10 * b11 + a20 * b12;
	out[5] = a01 * b10 + a11 * b11 + a21 * b12;
	out[6] = a02 * b10 + a12 * b11 + a22 * b12;
	out[7] = a03 * b10 + a13 * b11 + a23 * b12;

	out[8] = a00 * b20 + a10 * b21 + a20 * b22;
	out[9] = a01 * b20 + a11 * b21 + a21 * b22;
	out[10] = a02 * b20 + a12 * b21 + a22 * b22;
	out[11] = a03 * b20 + a13 * b21 + a23 * b22;

	return true;
}

void mat4_perspective(mat4 out, float fovy, float aspect, float near, float far)
{
	float f = 1.0f / tanf(fovy / 2.0f);
	float nf = 1.0f / (near - far);

	out[0] = f / aspect;
	out[1] = 0.0f;
	out[2] = 0.0f;
	out[3] = 0.0f;
	out[4] = 0.0f;
	out[5] = f;
	out[6] = 0.0f;
	out[7] = 0.0f;
	out[8] = 0.0f;
	out[9] = 0.0f;
	out[10] = (far + near) * nf;
	out[11] = -1.0f;
	out[12] = 0.0f;
	out[13] = 0.0f;
	out[14] = (2.0f * far * near) * nf;
	out[15] = 0.0f;
}

void mat4_compose(mat4 out, const vec3 v, const quat q, const vec3 s)
{
	// Quaternion math
	float x = q[0];
	float y = q[1];
	float z = q[2];
	float w = q[3];
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
	float sx = s[0];
	float sy = s[1];
	float sz = s[2];
	out[0] = (1.0f - (yy + zz)) * sx;
	out[1] = (xy + wz) * sx;
	out[2] = (xz - wy) * sx;
	out[3] = 0.0f;
	out[4] = (xy - wz) * sy;
	out[5] = (1.0f - (xx + zz)) * sy;
	out[6] = (yz + wx) * sy;
	out[7] = 0.0f;
	out[8] = (xz + wy) * sz;
	out[9] = (yz - wx) * sz;
	out[10] = (1.0f - (xx + yy)) * sz;
	out[11] = 0.0f;
	out[12] = v[0];
	out[13] = v[1];
	out[14] = v[2];
	out[15] = 1.0f;
}

void mat4_get_translation(vec3 out, const mat4 mat)
{
	out[0] = mat[12];
	out[1] = mat[13];
	out[2] = mat[14];
}
