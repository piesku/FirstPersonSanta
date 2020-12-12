#include "entity.h"

#include <stdio.h>
#include <stdlib.h>

#include "malloc.h"

struct entity_list entity_list_create(size_t capacity)
{
	struct entity_list list = {
			.entities = xmalloc(capacity * sizeof(entity)),
			.capacity = capacity,
			.size = 0,
	};

	return list;
}

void entity_list_destroy(struct entity_list* list)
{
	free(list->entities);
}

void entity_list_push(struct entity_list* list, entity element)
{
	if (list->size == list->capacity) {
		size_t new_capacity = list->capacity * 2;
		entity* new_entities = realloc(list->entities, new_capacity);
		if (new_entities == NULL) {
			printf("Out of memory, realloc failed.");
			abort();
		}
		list->capacity = new_capacity;
		list->entities = new_entities;
	}

	list->entities[list->size] = element;
	list->size++;
}
