#pragma once
#include <stdint.h>
#include <stddef.h>
/*
 * Goes without saying, but dont switch malloc/free functions in the middle of a program.
 */

typedef struct tcel_settings {
#ifdef TCEL_ALLOW_CUSTOM_MALLOC
	void* (*malloc_func)(size_t);
	void (*free_func)(void*);
#endif
} tcel_settings_t;

tcel_settings_t* tcel_settings_get();

#ifdef TCEL_ALLOW_CUSTOM_MALLOC
#define TCEL_MALLOC(size) tcel_settings_get()->malloc_func(size)
#define TCEL_FREE(ptr) tcel_settings_get()->free_func(ptr)
#else
#define TCEL_MALLOC(size) malloc(size)
#define TCEL_FREE(ptr) free(ptr)
#endif