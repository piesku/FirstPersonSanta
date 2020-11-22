#include "../common/mesh.h"

struct mesh mesh_cube(void)
{
	struct mesh mesh = {0};

	GLfloat vertex_positions[] = {
			-0.5, -0.5, 0.5,
			-0.5, 0.5, 0.5,
			-0.5, 0.5, -0.5,
			-0.5, -0.5, -0.5,
			-0.5, -0.5, -0.5,
			-0.5, 0.5, -0.5,
			0.5, 0.5, -0.5,
			0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			0.5, 0.5, -0.5,
			0.5, 0.5, 0.5,
			0.5, -0.5, 0.5,
			0.5, -0.5, 0.5,
			0.5, 0.5, 0.5,
			-0.5, 0.5, 0.5,
			-0.5, -0.5, 0.5,
			-0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			0.5, -0.5, 0.5,
			-0.5, -0.5, 0.5,
			0.5, 0.5, -0.5,
			-0.5, 0.5, -0.5,
			-0.5, 0.5, 0.5,
			0.5, 0.5, 0.5};

	glGenBuffers(1, &mesh.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

	GLfloat vertex_normals[] = {
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0};

	glGenBuffers(1, &mesh.normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_normals), vertex_normals, GL_STATIC_DRAW);

	GLfloat vertex_texcoords[] = {
			0.666667, 0.333333,
			0.333333, 0.333333,
			0.333333, 0,
			0.666667, 0,
			0.333333, 0.666667,
			0, 0.666667,
			0, 0.333333,
			0.333333, 0.333333,
			0.333333, 0.333333,
			0, 0.333333,
			0, 0,
			0.333333, 0,
			0.333333, 0.666667,
			0.333333, 0.333333,
			0.666667, 0.333333,
			0.666667, 0.666667,
			1, 0.333333,
			0.666667, 0.333333,
			0.666667, 0,
			1, 0,
			0.333333, 0.666667,
			0.333333, 1,
			0, 1,
			0, 0.666667};

	glGenBuffers(1, &mesh.texcoord_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.texcoord_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_texcoords), vertex_texcoords, GL_STATIC_DRAW);

	GLushort indices[] = {
			23, 22, 20,
			22, 21, 20,
			19, 18, 16,
			18, 17, 16,
			15, 14, 12,
			14, 13, 12,
			11, 10, 8,
			10, 9, 8,
			7, 6, 4,
			6, 5, 4,
			3, 2, 0,
			2, 1, 0};

	glGenBuffers(1, &mesh.index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	mesh.index_count = sizeof(indices) / sizeof(GLushort);
	return mesh;
}