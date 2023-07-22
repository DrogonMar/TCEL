#include <malloc.h>
#include "tcel_settings.h"

static tcel_settings_t* tcel_settings = NULL;

tcel_settings_t *tcel_settings_get()
{
	if (tcel_settings == NULL) {
		tcel_settings = malloc(sizeof(tcel_settings_t));
#ifdef TCEL_ALLOW_CUSTOM_MALLOC
		tcel_settings->malloc_func = malloc;
		tcel_settings->free_func = free;
#endif
	}
	return tcel_settings;
}
