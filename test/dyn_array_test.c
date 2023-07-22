#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include "tests.h"
#include "dyn_array.h"
#include "tcel_settings.h"

void internal_simple_test(){
	printf("Testing dyn_array simple.\n");
	dyn_array *array = dyn_array_create(false);
	assert(array != NULL);
	assert(dyn_array_count(array) == 0);

	char *data = "Hello World!";
	assert(dyn_array_push(array, data));
	assert(dyn_array_count(array) == 1);

	//make sure we can't find something that isn't there
	size_t idx;
	assert(!dyn_array_find(array, "Hello Earth!", &idx));

	//remove the data
	assert(dyn_array_remove(array, 0));
	assert(dyn_array_count(array) == 0);

	dyn_array_free(array);
	printf("dyn_array simple test passed.\n");
}

void internal_self_free(){
	dyn_array *array = dyn_array_create(true);
	assert(array != NULL);
	assert(dyn_array_count(array) == 0);

	for (int i = 0; i < 10; ++i) {
		char *data = TCEL_MALLOC(100);
		sprintf(data, "Hello World! %d", i);
		assert(dyn_array_push(array, data));
	}

	assert(dyn_array_count(array) == 10);
	//make sure get works
	char *data;
	assert(DYN_ARR_GET(array, 5, &data));
	assert(strcmp(data, "Hello World! 5") == 0);

	dyn_array_free(array);
}

void test_dyn_array()
{
	printf("Testing dyn_array...\n");

	internal_simple_test();
	internal_self_free();


	printf("Success!\n");
}