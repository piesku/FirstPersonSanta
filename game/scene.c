#include <cgltf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/entity.h"
#include "../common/matrix.h"
#include "com_collide.h"
#include "com_render.h"
#include "com_transform.h"
#include "index.h"
#include "world.h"

Entity blueprint_lamp(struct world* world);
Entity blueprint_furniture(struct world* world);
Entity blueprint_decoration(struct world* world);

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
		if (data->nodes[i].mesh == NULL) {
			// It's a collider object without a mesh.
			continue;
		}

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
			Entity entity = blueprint_lamp(world);

			Transform* transform = world->transform[entity];
			transform->translation = translation;
			transform->rotation = rotation;
			transform->scale = scale;

			if (data->nodes[i].children_count > 0) {
				// The node has a child collider.
				cgltf_node* child = data->nodes[i].children[0];

				Entity collider = transform->children.entities[0];
				world->transform[collider]->translation = (vec3){
						child->translation[0],
						child->translation[1],
						child->translation[2],
				};
				world->transform[collider]->scale = (vec3){
						child->scale[0],
						child->scale[1] * 20,
						child->scale[2],
				};
				world->collide[collider]->aabb.size = (vec3){
						child->scale[0],
						child->scale[1],
						child->scale[2],
				};
			} else {
				// Turn off the collider child.
				Entity collider = transform->children.entities[0];
				world->signature[collider] &= ~HAS_TRANSFORM;
			}

			continue;
		}

		Entity entity;
		Transform* transform;

		if (data->nodes[i].children_count > 0) {
			entity = blueprint_furniture(world);
			transform = world->transform[entity];

			// The node has a child collider.
			cgltf_node* child = data->nodes[i].children[0];

			Entity collider = transform->children.entities[0];
			world->transform[collider]->translation = (vec3){
					child->translation[0],
					child->translation[1],
					child->translation[2],
			};
			world->transform[collider]->scale = (vec3){
					child->scale[0],
					child->scale[1],
					child->scale[2],
			};
			world->collide[collider]->aabb.size = (vec3){
					child->scale[0],
					child->scale[1],
					child->scale[2],
			};
		} else {
			entity = blueprint_decoration(world);
			transform = world->transform[entity];
		}

		transform->translation = translation;
		transform->rotation = rotation;
		transform->scale = scale;

		if (starts_with(name, "bear")) {
			world->render[entity]->colored_unlit.mesh = MESH_BEAR;
			world->render[entity]->colored_unlit.color = (vec4){0.9f, 0.3f, 0.4f, 1.0f};
		} else if (starts_with(name, "bed_bunk")) {
			world->render[entity]->colored_unlit.mesh = MESH_BED_BUNK;
		} else if (starts_with(name, "bed_double")) {
			world->render[entity]->colored_unlit.mesh = MESH_BED_DOUBLE;
		} else if (starts_with(name, "bed_single")) {
			world->render[entity]->colored_unlit.mesh = MESH_BED_SINGLE;
		} else if (starts_with(name, "bench")) {
			world->render[entity]->colored_unlit.mesh = MESH_BENCH;
		} else if (starts_with(name, "bookcase_closed")) {
			world->render[entity]->colored_unlit.mesh = MESH_BOOKCASE_CLOSED;
		} else if (starts_with(name, "bookcase_closed_doors")) {
			world->render[entity]->colored_unlit.mesh = MESH_BOOKCASE_CLOSED_DOORS;
		} else if (starts_with(name, "bookcase_closed_wide")) {
			world->render[entity]->colored_unlit.mesh = MESH_BOOKCASE_CLOSED_WIDE;
		} else if (starts_with(name, "bookcase_open")) {
			world->render[entity]->colored_unlit.mesh = MESH_BOOKCASE_OPEN;
		} else if (starts_with(name, "books")) {
			world->render[entity]->colored_unlit.mesh = MESH_BOOKS;
			world->render[entity]->colored_unlit.color = (vec4){0.9f, 0.3f, 0.4f, 1.0f};
		} else if (starts_with(name, "cabinet_bed")) {
			world->render[entity]->colored_unlit.mesh = MESH_CABINET_BED;
		} else if (starts_with(name, "cabinet_bed_drawer")) {
			world->render[entity]->colored_unlit.mesh = MESH_CABINET_BED_DRAWER;
		} else if (starts_with(name, "cabinet_bed_drawer_table")) {
			world->render[entity]->colored_unlit.mesh = MESH_CABINET_BED_DRAWER_TABLE;
		} else if (starts_with(name, "cabinet_television")) {
			world->render[entity]->colored_unlit.mesh = MESH_CABINET_TELEVISION;
		} else if (starts_with(name, "cabinet_television_doors")) {
			world->render[entity]->colored_unlit.mesh = MESH_CABINET_TELEVISION_DOORS;
		} else if (starts_with(name, "cardboard_box_closed")) {
			world->render[entity]->colored_unlit.mesh = MESH_CARDBOARD_BOX_CLOSED;
		} else if (starts_with(name, "cardboard_box_open")) {
			world->render[entity]->colored_unlit.mesh = MESH_CARDBOARD_BOX_OPEN;
		} else if (starts_with(name, "chair")) {
			world->render[entity]->colored_unlit.mesh = MESH_CHAIR;
		} else if (starts_with(name, "chair_rounded")) {
			world->render[entity]->colored_unlit.mesh = MESH_CHAIR_ROUNDED;
		} else if (starts_with(name, "coat_rack_standing")) {
			world->render[entity]->colored_unlit.mesh = MESH_COAT_RACK_STANDING;
		} else if (starts_with(name, "coat_rack")) {
			world->render[entity]->colored_unlit.mesh = MESH_COAT_RACK;
		} else if (starts_with(name, "computer_screen")) {
			world->render[entity]->colored_unlit.mesh = MESH_COMPUTER_SCREEN;
		} else if (starts_with(name, "cube")) {
			world->render[entity]->colored_unlit.mesh = MESH_CUBE;
		} else if (starts_with(name, "desk")) {
			world->render[entity]->colored_unlit.mesh = MESH_DESK;
		} else if (starts_with(name, "gift")) {
			world->render[entity]->colored_unlit.mesh = MESH_GIFT;
		} else if (starts_with(name, "lamp_round_floor")) {
			world->render[entity]->colored_unlit.mesh = MESH_LAMP_ROUND_FLOOR;
		} else if (starts_with(name, "lamp_round_table")) {
			world->render[entity]->colored_unlit.mesh = MESH_LAMP_ROUND_TABLE;
		} else if (starts_with(name, "lounge_chair")) {
			world->render[entity]->colored_unlit.mesh = MESH_LOUNGE_CHAIR;
		} else if (starts_with(name, "lounge_sofa")) {
			world->render[entity]->colored_unlit.mesh = MESH_LOUNGE_SOFA;
		} else if (starts_with(name, "monkey")) {
			world->render[entity]->colored_unlit.mesh = MESH_MONKEY;
		} else if (starts_with(name, "plant_small_1")) {
			world->render[entity]->colored_unlit.mesh = MESH_PLANT_SMALL_1;
		} else if (starts_with(name, "plant_small_2")) {
			world->render[entity]->colored_unlit.mesh = MESH_PLANT_SMALL_2;
		} else if (starts_with(name, "plant_small_3")) {
			world->render[entity]->colored_unlit.mesh = MESH_PLANT_SMALL_3;
		} else if (starts_with(name, "potted_plant")) {
			world->render[entity]->colored_unlit.mesh = MESH_POTTED_PLANT;
		} else if (starts_with(name, "quad")) {
			world->render[entity]->colored_unlit.mesh = MESH_QUAD;
		} else if (starts_with(name, "radio")) {
			world->render[entity]->colored_unlit.mesh = MESH_RADIO;
			world->render[entity]->colored_unlit.color = (vec4){0.9f, 0.3f, 0.4f, 1.0f};
		} else if (starts_with(name, "side_table")) {
			world->render[entity]->colored_unlit.mesh = MESH_SIDE_TABLE;
		} else if (starts_with(name, "side_table_drawers")) {
			world->render[entity]->colored_unlit.mesh = MESH_SIDE_TABLE_DRAWERS;
		} else if (starts_with(name, "stool_bar_square")) {
			world->render[entity]->colored_unlit.mesh = MESH_STOOL_BAR_SQUARE;
		} else if (starts_with(name, "table_coffee")) {
			world->render[entity]->colored_unlit.mesh = MESH_TABLE_COFFEE;
		} else if (starts_with(name, "table_coffee_square")) {
			world->render[entity]->colored_unlit.mesh = MESH_TABLE_COFFEE_SQUARE;
		} else if (starts_with(name, "table_round")) {
			world->render[entity]->colored_unlit.mesh = MESH_TABLE_ROUND;
		} else if (starts_with(name, "table")) {
			world->render[entity]->colored_unlit.mesh = MESH_TABLE;
		} else if (starts_with(name, "television_modern")) {
			world->render[entity]->colored_unlit.mesh = MESH_TELEVISION_MODERN;
		} else if (starts_with(name, "television_vintage")) {
			world->render[entity]->colored_unlit.mesh = MESH_TELEVISION_VINTAGE;
		} else if (starts_with(name, "wall_doorway")) {
			world->render[entity]->colored_unlit.mesh = MESH_WALL_DOORWAY;
		} else if (starts_with(name, "wall_window")) {
			world->render[entity]->colored_unlit.mesh = MESH_WALL_WINDOW;
		} else if (starts_with(name, "wall")) {
			world->render[entity]->colored_unlit.mesh = MESH_WALL;
		}
	}

	cgltf_free(data);
}
