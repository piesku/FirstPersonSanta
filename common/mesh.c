#include "mesh.h"

#include <stdbool.h>
#include <string.h>

#include "entity.h"
#include "matrix.h"

#pragma warning(push)
#pragma warning(disable : 4996 26451)
#define CGLTF_IMPLEMENTATION
#include "cgltf.h"
#pragma warning(pop)

entity blueprint_lamp(struct world* world, vec3 translation, quat rotation);
entity blueprint_sofa(struct world* world, vec3 translation, quat rotation);

static inline bool starts_with(const char* name, const char* prefix)
{
	return strncmp(prefix, name, strlen(prefix)) == 0;
}

void load_scene_from_gltf(struct world* world, const char* file_location)
{
	cgltf_options options = {0};
	cgltf_data* data = NULL;
	cgltf_result result = cgltf_parse_file(&options, file_location, &data);
	if (result == cgltf_result_success) {
		for (cgltf_size i = 0; i < data->nodes_count; i++) {
			vec3 translation = {
					data->nodes[i].translation[0],
					0, //data->nodes[i].translation[1],
					data->nodes[i].translation[2],
			};
			quat rotation = {
					data->nodes[i].rotation[0],
					data->nodes[i].rotation[1],
					data->nodes[i].rotation[2],
					data->nodes[i].rotation[3],
			};

			char* name = data->nodes[i].name;

			if (starts_with(name, "lamp")) {
				blueprint_lamp(world, translation, rotation);
			} else if (starts_with(name, "sofa")) {
				blueprint_sofa(world, translation, rotation);
			}
		}
		cgltf_free(data);
	}
}
