#include "mesh.h"

#include "entity.h"
#include "matrix.h"

#define CGLTF_IMPLEMENTATION
#include "cgltf.h"

entity blueprint_lamp(struct world* world, vec3 translation, quat rotation);
entity blueprint_sofa(struct world* world, vec3 translation, quat rotation);

void load_scene_from_gltf(struct world* world, const char* file_location)
{
	cgltf_options options = {0};
	cgltf_data* data = NULL;
	cgltf_result result = cgltf_parse_file(&options, file_location, &data);
	if (result == cgltf_result_success) {
		int nodes_count = data->nodes_count;
		for (int i = 0; i < nodes_count; i++) {
			char name[20] = {0};
			char* dot = strchr(data->nodes[i].name, '.');
			int name_length = strlen(data->nodes[i].name);

			if (dot) {
				strncpy(name, data->nodes[i].name, (int)(name_length - strlen(dot)));
			} else {
				strncpy(name, data->nodes[i].name, name_length);
			}

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

			if (strncmp(name, "lamp", 20) == 0) {
				blueprint_lamp(world, translation, rotation);
			} else if (strncmp(name, "sofa", 20) == 0) {
				blueprint_sofa(world, translation, rotation);
			}
		}
		cgltf_free(data);
	}
}
