#include <cgltf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_transform.h"
#include "world.h"

entity blueprint_lamp(struct world* world);
entity blueprint_sofa(struct world* world);

static inline bool starts_with(const char* name, const char* prefix)
{
	return strncmp(prefix, name, strlen(prefix)) == 0;
}

void load_scene_from_gltf(struct world* world, const char* path)
{
	cgltf_options options = {0};
	cgltf_data* data = NULL;

	cgltf_result result = cgltf_parse_file(&options, path, &data);
	if (result != cgltf_result_success) {
		printf("Failed to load model %s (error %d)", path, result);
		exit(1);
	}

	for (cgltf_size i = 0; i < data->nodes_count; i++) {
		vec3 translation = {
				data->nodes[i].translation[0],
				data->nodes[i].translation[1],
				data->nodes[i].translation[2],
		};
		quat rotation = {
				data->nodes[i].rotation[0],
				data->nodes[i].rotation[1],
				data->nodes[i].rotation[2],
				data->nodes[i].rotation[3],
		};
		vec3 scale = {
				data->nodes[i].scale[0],
				data->nodes[i].scale[1],
				data->nodes[i].scale[2],
		};

		char* name = data->nodes[i].name;

		if (starts_with(name, "lamp")) {
			entity entity = blueprint_lamp(world);
			world->transform[entity]->translation = translation;
			world->transform[entity]->rotation = rotation;
			world->transform[entity]->scale = scale;
			continue;
		}

		if (starts_with(name, "sofa")) {
			entity entity = blueprint_sofa(world);
			world->transform[entity]->translation = translation;
			world->transform[entity]->rotation = rotation;
			world->transform[entity]->scale = scale;
			continue;
		}
	}

	cgltf_free(data);
}
