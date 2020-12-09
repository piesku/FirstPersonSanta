#include "mesh.h"

#define CGLTF_IMPLEMENTATION
#include "cgltf.h"

void load_scene_from_gltf(struct mesh* mesh, const char* file_location) {
	(void)mesh;

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

			printf("%s\n", name);
		}

		// XXX: Do stuff with `mesh` & `data` here
		cgltf_free(data);
	}
}
