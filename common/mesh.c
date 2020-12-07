#include "mesh.h"

#define CGLTF_IMPLEMENTATION
#include "cgltf.h"

void load_gltf_from_file(struct mesh* mesh, const char* file_location) {
	cgltf_options options = {0};
	cgltf_data* data = NULL;
	cgltf_result result = cgltf_parse_file(&options, file_location, &data);
	if (result == cgltf_result_success) {
		// XXX: Do stuff with `mesh` & `data` here
		cgltf_free(data);
	}
}
