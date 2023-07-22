#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dyn_array.h"
#include "tcel_settings.h"

//region Internal structs
typedef struct dyn_array_node {
	struct dyn_array_node *prev, *next;
	void *data;
} dyn_array_node_t;

struct dyn_array {
	dyn_array_node_t *start, *end;
	size_t count;
	bool free_data_self;
};
//endregion

//region Internal functions
dyn_array_node_t* internal_seek_start(dyn_array_node_t *node)
{
	while (node && node->prev) {
		node = node->prev;
	}
	return node;
}

dyn_array_node_t* internal_seek_end(dyn_array_node_t *node)
{
	while (node && node->next) {
		node = node->next;
	}
	return node;
}

dyn_array_node_t* internal_seek_idx(dyn_array *array, size_t idx)
{
	assert(array != NULL);
	dyn_array_node_t *node = internal_seek_start(array->start);
	while (node && idx > 0) {
		node = node->next;
		idx--;
	}
	return node;
}
//endregion

dyn_array* dyn_array_create(bool free_data_self){
	dyn_array *array = TCEL_MALLOC(sizeof(dyn_array));
	if(!array){
		return NULL;
	}
	array->free_data_self = free_data_self;
	array->count = 0;
	array->start = NULL;
	array->end = NULL;

	return array;
}

void dyn_array_free(dyn_array *array)
{
	assert(array != NULL);
	dyn_array_node_t *node = array->start;
	while (node) {
		dyn_array_node_t *next = node->next;
		if (array->free_data_self) {
			TCEL_FREE(node->data);
		}
		TCEL_FREE(node);
		node = next;
	}
	TCEL_FREE(array);
}

bool dyn_array_push(dyn_array *array, void *data)
{
	assert(array != NULL);
	//push is adding to the end of the list, so the array->end should be the new node

	dyn_array_node_t *node = TCEL_MALLOC(sizeof(dyn_array_node_t));
	if (!node) {
		return false;
	}

	node->prev = array->end;
	node->data = data;
	node->next = NULL;

	if (array->end) {
		array->end->next = node;
	}
	array->end = node;

	if (!array->start) {
		//If there is no start, then this is the first node
		array->start = node;
	}

	array->count++;
	return true;
}

bool dyn_array_remove(dyn_array *array, size_t idx)
{
	assert(array != NULL);
	dyn_array_node_t *node = internal_seek_idx(array, idx);
	if (!node) {
		return false;
	}

	if (node->prev) {
		node->prev->next = node->next;
	}
	if (node->next) {
		node->next->prev = node->prev;
	}

	if (node == array->start) {
		array->start = node->next;
	}
	if (node == array->end) {
		array->end = node->prev;
	}

	if (array->free_data_self) {
		TCEL_FREE(node->data);
	}
	TCEL_FREE(node);

	array->count--;
	return true;
}

bool dyn_array_find(dyn_array *array, void *data, size_t *out_idx)
{
	assert(array != NULL);
	dyn_array_node_t *node = array->start;
	size_t idx = 0;
	while (node) {
		if (node->data == data) {
			*out_idx = idx;
			return true;
		}
		node = node->next;
		idx++;
	}

	return false;
}

size_t dyn_array_count(dyn_array *array)
{
	assert(array != NULL);
	return array->count;
}

bool dyn_array_get(dyn_array *array, size_t idx, void **out_data)
{
	assert(array != NULL);
	dyn_array_node_t *node = internal_seek_idx(array, idx);
	if (!node) {
		return false;
	}
	*out_data = node->data;
	return true;
}
