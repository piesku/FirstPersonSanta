#include "../common/mesh.h"

struct mesh mesh_sofa(void)
{
	struct mesh mesh = {0};

#pragma warning(suppress : 4305)
	GLfloat vertex_positions[] = {
			-0.889829, 0.23, 0.02,
			-0.889829, 0.33, 0.02,
			-0.889829, 0.37, 0.06,
			-0.889829, 0.23, 0.319829,
			-0.889829, 0.37, 0.319829,
			-0.0550857, 0.37, 0.319829,
			-0.0550857, 0.42, 0.319829,
			-0.0550857, 0.42, 0.41,
			-0.0550857, 0.37, 0.41,
			-0.884914, 0.46, 0.319829,
			-0.924914, 0.42, 0.319829,
			-0.924914, 0.42, 0.41,
			-0.884914, 0.46, 0.41,
			-0.889829, 0.37, 0.319829,
			-0.889829, 0.37, 0.06,
			-0.98, 0.37, 0.06,
			-0.924914, 0.37, 0.319829,
			-0.924914, 0.37, 0.41,
			-0.98, 0.37, 0.41,
			-0.889829, 0.33, 0.02,
			-0.98, 0.33, 0.02,
			-0.98, 0.37, 0.06,
			-0.889829, 0.37, 0.06,
			-0.0950857, 0.46, 0.41,
			-0.0950857, 0.46, 0.319829,
			-0.884914, 0.46, 0.319829,
			-0.884914, 0.46, 0.41,
			-0.98, 0.33, 0.02,
			-0.98, 0.05, 0.02,
			-0.98, 0.05, 0.06,
			-0.98, 0.37, 0.06,
			-0.98, 0.05, 0.37,
			-0.98, 0.37, 0.41,
			-0.98, 0.05, 0.41,
			0, 0.05, 0.02,
			0, 0.33, 0.02,
			0, 0.37, 0.06,
			0, 0.05, 0.06,
			0, 0.37, 0.41,
			-9.02389e-16, 0.05, 0.37,
			-9.02389e-16, 0.05, 0.41,
			-0.04, 0.05, 0.41,
			-9.02389e-16, 0.05, 0.41,
			0, 0.37, 0.41,
			-0.94, 0.05, 0.41,
			-0.0550857, 0.37, 0.41,
			-0.98, 0.37, 0.41,
			-0.98, 0.05, 0.41,
			-0.0550857, 0.37, 0.41,
			-0.924914, 0.37, 0.41,
			-0.98, 0.37, 0.41,
			-0.924914, 0.37, 0.41,
			-0.0550857, 0.42, 0.41,
			-0.924914, 0.42, 0.41,
			-0.0950857, 0.46, 0.41,
			-0.884914, 0.46, 0.41,
			-0.04, 0.05, 0.37,
			-0.04, 0.05, 0.41,
			-0.94, 0.05, 0.41,
			-0.94, 0.05, 0.06,
			-0.94, 0.05, 0.41,
			-0.94, 0.05, 0.37,
			-0.94, 0.05, 0.06,
			-0.94, 0.05, 0.37,
			-0.98, 0.05, 0.06,
			-0.98, 0.05, 0.37,
			-0.94, 0.05, 0.02,
			-0.04, 0.05, 0.02,
			-0.04, 0.05, 0.37,
			-0.04, 0.05, 0.02,
			-0.04, 0.05, 0.06,
			-9.02389e-16, 0.05, 0.37,
			-0.04, 0.05, 0.06,
			0, 0.05, 0.06,
			-0.0901714, 0.23, 0.02,
			-0.0901714, 0.23, 0,
			-0.889829, 0.23, 0,
			-0.0901714, 0.23, 0.319829,
			-0.889829, 0.23, 0.319829,
			-0.889829, 0.23, 0,
			-0.889829, 0.23, 0.02,
			-0.889829, 0.23, 0.319829,
			-0.0901714, 0.144814, 0,
			-0.889829, 0.144814, 0,
			-0.889829, 0.23, 0,
			-0.0901714, 0.23, 0,
			-0.0901714, 0.144814, 0,
			-0.0901714, 0.144814, 0.02,
			-0.889829, 0.144814, 0.02,
			-0.889829, 0.144814, 0,
			-0.889829, 0.23, 0,
			-0.889829, 0.144814, 0,
			-0.889829, 0.144814, 0.02,
			-0.889829, 0.23, 0.02,
			-0.0901714, 0.144814, 0,
			-0.0901714, 0.23, 0,
			-0.0901714, 0.23, 0.02,
			-0.0901714, 0.144814, 0.02,
			-0.94, 0.05, 0.02,
			-0.98, 0.05, 0.02,
			-0.98, 0.33, 0.02,
			-0.889829, 0.144814, 0.02,
			-0.889829, 0.23, 0.02,
			-0.889829, 0.33, 0.02,
			-0.0901714, 0.144814, 0.02,
			0, 0.05, 0.02,
			0, 0.05, 0.02,
			-0.04, 0.05, 0.02,
			-0.94, 0.05, 0.02,
			0, 0.33, 0.02,
			-0.0901714, 0.23, 0.02,
			-0.0901714, 0.33, 0.02,
			0, 0.37, 0.41,
			0, 0.37, 0.06,
			-0.0901714, 0.37, 0.06,
			-0.0550857, 0.37, 0.319829,
			-0.0901714, 0.37, 0.319829,
			-0.0550857, 0.37, 0.41,
			0, 0.33, 0.02,
			-0.0901714, 0.33, 0.02,
			-0.0901714, 0.37, 0.06,
			0, 0.37, 0.06,
			-0.0901714, 0.33, 0.02,
			-0.0901714, 0.23, 0.02,
			-0.0901714, 0.23, 0.319829,
			-0.0901714, 0.37, 0.06,
			-0.0901714, 0.37, 0.319829,
			-0.0550857, 0.42, 0.319829,
			-0.0950857, 0.46, 0.319829,
			-0.0950857, 0.46, 0.41,
			-0.0550857, 0.42, 0.41,
			-0.889829, 0.37, 0.319829,
			-0.924914, 0.37, 0.319829,
			-0.924914, 0.42, 0.319829,
			-0.0901714, 0.37, 0.319829,
			-0.0550857, 0.37, 0.319829,
			-0.0550857, 0.42, 0.319829,
			-0.884914, 0.46, 0.319829,
			-0.0950857, 0.46, 0.319829,
			-0.0901714, 0.23, 0.319829,
			-0.889829, 0.23, 0.319829,
			-0.924914, 0.42, 0.319829,
			-0.924914, 0.37, 0.319829,
			-0.924914, 0.37, 0.41,
			-0.924914, 0.42, 0.41};

	glGenBuffers(1, &mesh.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

#pragma warning(suppress : 4305)
	GLfloat vertex_normals[] = {
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			-0.707107, 0.707107, 0,
			-0.707107, 0.707107, 0,
			-0.707107, 0.707107, 0,
			-0.707107, 0.707107, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 0.707107, -0.707107,
			0, 0.707107, -0.707107,
			0, 0.707107, -0.707107,
			0, 0.707107, -0.707107,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 0.707107, -0.707107,
			0, 0.707107, -0.707107,
			0, 0.707107, -0.707107,
			0, 0.707107, -0.707107,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			0.707107, 0.707107, 0,
			0.707107, 0.707107, 0,
			0.707107, 0.707107, 0,
			0.707107, 0.707107, 0,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0};

	glGenBuffers(1, &mesh.normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_normals), vertex_normals, GL_STATIC_DRAW);

#pragma warning(suppress : 4305)
	GLfloat vertex_texcoords[] = {
			-0.787402, 9.05512,
			-0.787402, 12.9921,
			-2.36221, 14.5669,
			-12.5917, 9.05512,
			-12.5917, 14.5669,
			-12.5917, 14.5669,
			-12.5917, 16.5354,
			-16.1417, 16.5354,
			-16.1417, 14.5669,
			12.5917, -11.8291,
			12.5917, -14.0562,
			16.1417, -14.0562,
			16.1417, -11.8291,
			35.0326, 12.5917,
			35.0326, 2.36221,
			38.5827, 2.36221,
			36.414, 12.5917,
			36.414, 16.1417,
			38.5827, 16.1417,
			35.0326, 9.7436,
			38.5827, 9.7436,
			38.5827, 11.9707,
			35.0326, 11.9707,
			3.74353, 16.1417,
			3.74353, 12.5917,
			34.8391, 12.5917,
			34.8391, 16.1417,
			0.787402, 12.9921,
			0.787402, 1.9685,
			2.36221, 1.9685,
			2.36221, 14.5669,
			14.5669, 1.9685,
			16.1417, 14.5669,
			16.1417, 1.9685,
			-0.787402, 1.9685,
			-0.787402, 12.9921,
			-2.36221, 14.5669,
			-2.36221, 1.9685,
			-16.1417, 14.5669,
			-14.5669, 1.9685,
			-16.1417, 1.9685,
			-1.5748, 1.9685,
			-3.78731e-14, 1.9685,
			-2.34598e-15, 14.5669,
			-37.0079, 1.9685,
			-2.16873, 14.5669,
			-38.5827, 14.5669,
			-38.5827, 1.9685,
			-2.16873, 14.5669,
			-36.414, 14.5669,
			-38.5827, 14.5669,
			-36.414, 14.5669,
			-2.16873, 16.5354,
			-36.414, 16.5354,
			-3.74353, 18.1102,
			-34.8391, 18.1102,
			-1.5748, 14.5669,
			-1.5748, 16.1417,
			-37.0079, 16.1417,
			-37.0079, 2.36221,
			-37.0079, 16.1417,
			-37.0079, 14.5669,
			-37.0079, 2.36221,
			-37.0079, 14.5669,
			-38.5827, 2.36221,
			-38.5827, 14.5669,
			-37.0079, 0.787402,
			-1.5748, 0.787402,
			-1.5748, 14.5669,
			-1.5748, 0.787402,
			-1.5748, 2.36221,
			-3.55391e-14, 14.5669,
			-1.5748, 2.36221,
			-1.1961e-17, 2.36221,
			3.55006, 0.787402,
			3.55006, 0,
			35.0326, 0,
			3.55006, 12.5917,
			35.0326, 12.5917,
			35.0326, 0,
			35.0326, 0.787402,
			35.0326, 12.5917,
			3.55006, 5.70135,
			35.0326, 5.70135,
			35.0326, 9.05512,
			3.55006, 9.05512,
			-3.55006, 0,
			-3.55006, 0.787402,
			-35.0326, 0.787402,
			-35.0326, 0,
			0, 9.05512,
			0, 5.70135,
			0.787402, 5.70135,
			0.787402, 9.05512,
			0, 5.70135,
			0, 9.05512,
			-0.787402, 9.05512,
			-0.787402, 5.70135,
			37.0079, 1.9685,
			38.5827, 1.9685,
			38.5827, 12.9921,
			35.0326, 5.70135,
			35.0326, 9.05512,
			35.0326, 12.9921,
			3.55006, 5.70135,
			0, 1.9685,
			0, 1.9685,
			1.5748, 1.9685,
			37.0079, 1.9685,
			0, 12.9921,
			3.55006, 9.05512,
			3.55006, 12.9921,
			-9.5957e-15, 16.1417,
			-9.5957e-15, 2.36221,
			3.55006, 2.36221,
			2.16873, 12.5917,
			3.55006, 12.5917,
			2.16873, 16.1417,
			0, 9.7436,
			3.55006, 9.7436,
			3.55006, 11.9707,
			0, 11.9707,
			0.787402, 12.9921,
			0.787402, 9.05512,
			12.5917, 9.05512,
			2.36221, 14.5669,
			12.5917, 14.5669,
			-12.5917, 13.2258,
			-12.5917, 15.4529,
			-16.1417, 15.4529,
			-16.1417, 13.2258,
			35.0326, 14.5669,
			36.414, 14.5669,
			36.414, 16.5354,
			3.55006, 14.5669,
			2.16873, 14.5669,
			2.16873, 16.5354,
			34.8391, 18.1102,
			3.74353, 18.1102,
			3.55006, 9.05512,
			35.0326, 9.05512,
			12.5917, 16.5354,
			12.5917, 14.5669,
			16.1417, 14.5669,
			16.1417, 16.5354};

	glGenBuffers(1, &mesh.texcoord_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.texcoord_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_texcoords), vertex_texcoords, GL_STATIC_DRAW);

	GLushort indices[] = {
			141, 144, 143,
			143, 142, 141,
			136, 138, 137,
			136, 137, 133,
			135, 136, 133,
			134, 135, 133,
			131, 140, 139,
			139, 134, 131,
			131, 134, 133,
			133, 132, 131,
			127, 130, 129,
			129, 128, 127,
			125, 126, 124,
			122, 125, 124,
			124, 123, 122,
			118, 121, 120,
			120, 119, 118,
			115, 116, 114,
			117, 115, 112,
			112, 115, 114,
			114, 113, 112,
			108, 107, 106,
			109, 111, 110,
			109, 110, 104,
			105, 109, 104,
			102, 103, 100,
			101, 102, 100,
			105, 104, 98,
			104, 101, 98,
			98, 101, 100,
			100, 99, 98,
			94, 97, 96,
			96, 95, 94,
			90, 93, 92,
			92, 91, 90,
			86, 89, 88,
			88, 87, 86,
			82, 85, 84,
			84, 83, 82,
			81, 80, 79,
			77, 78, 76,
			74, 77, 76,
			76, 75, 74,
			70, 69, 68,
			62, 61, 60,
			71, 73, 72,
			64, 65, 63,
			59, 64, 63,
			72, 56, 71,
			67, 66, 56,
			66, 59, 56,
			56, 59, 58,
			58, 57, 56,
			50, 49, 48,
			53, 55, 54,
			53, 54, 52,
			51, 53, 52,
			52, 45, 51,
			44, 47, 46,
			46, 45, 44,
			44, 45, 43,
			41, 44, 43,
			43, 42, 41,
			39, 40, 38,
			37, 39, 38,
			37, 38, 36,
			34, 37, 36,
			36, 35, 34,
			32, 33, 31,
			30, 32, 31,
			30, 31, 29,
			27, 30, 29,
			29, 28, 27,
			23, 26, 25,
			25, 24, 23,
			19, 22, 21,
			21, 20, 19,
			17, 18, 15,
			16, 17, 15,
			13, 16, 15,
			15, 14, 13,
			9, 12, 11,
			11, 10, 9,
			5, 8, 7,
			7, 6, 5,
			3, 4, 2,
			0, 3, 2,
			2, 1, 0};

	glGenBuffers(1, &mesh.index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	mesh.index_count = sizeof(indices) / sizeof(GLushort);
	return mesh;
}
