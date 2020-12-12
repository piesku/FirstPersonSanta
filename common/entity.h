#pragma once
#include <stddef.h>
#include <stdint.h>

typedef size_t entity;
typedef int32_t signature;

// A specialized vector for storing entities.
struct entity_list {
	entity* entities;
	size_t capacity;
	size_t size;
};

struct entity_list entity_list_create(size_t capacity);
void entity_list_destroy(struct entity_list* list);
void entity_list_push(struct entity_list* list, entity element);
