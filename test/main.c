#include "tests.h"
#include <tcel_settings.h>
#include <malloc.h>

static size_t alloc_count = 0;

void* test_malloc(size_t size)
{
	alloc_count++;
	return malloc(size);
}

void test_free(void* ptr)
{
	alloc_count--;
	free(ptr);
}

int main(int argc, char** argv)
{
	tcel_settings_t* settings = tcel_settings_get();
	settings->malloc_func = test_malloc;
	settings->free_func = test_free;

	test_dyn_array();

	if (alloc_count != 0) {
		printf("Memory leak detected!\n");
		return 1;
	}
    return 0;
}
