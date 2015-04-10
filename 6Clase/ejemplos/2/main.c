#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	json_t *root, *value, *persona;
	json_error_t err;
	const char *key;
	void *iter;

	root = json_load_file("prueba.json", 0, &err);
	if (root == NULL) {
		perror("Error: ");
		fprintf(stderr, "Jansson error: %s %d %d\n", err.text,
			err.column, err.line);
		return EXIT_FAILURE;
	}

	persona = json_object_get(root, "persona");
	if (persona == NULL)
		return EXIT_FAILURE;

	iter = json_object_iter(persona);
	while (iter) {
		key = json_object_iter_key(iter);
		value = json_object_iter_value(iter);
		printf ("key del objeto %s\n", key);
		iter = json_object_iter_next(persona, iter);
	}

	json_decref(root);
	return EXIT_SUCCESS;
}
