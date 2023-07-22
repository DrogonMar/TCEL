#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct dyn_array dyn_array;

dyn_array* dyn_array_create(bool free_data_self);
void dyn_array_free(dyn_array *array);

bool dyn_array_push(dyn_array *array, void *data);
bool dyn_array_remove(dyn_array *array, size_t idx);
bool dyn_array_find(dyn_array *array, void *data, size_t *out_idx);
size_t dyn_array_count(dyn_array *array);

#define DYN_ARR_GET(array, idx, out_data) dyn_array_get(array, idx, (void**)out_data)
bool dyn_array_get(dyn_array *array, size_t idx, void **out_data);