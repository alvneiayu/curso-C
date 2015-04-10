#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>

int append_nodo(json_t *array, json_t *value)
{
	if (json_array_append(array, value) < 0) {
		perror("Error add node: ");
		return -1;
	}

	return 0;
}

int establece_nodo(json_t *root, const char *key, json_t *value)
{
	if (json_object_set(root, key, value) < 0) {
		perror("Error set up node: ");
		return -1;
	}

	return 0;
}

int main (void)
{
	json_t *root, *persona, *carac;
	json_t *id, *dni, *carac1, *carac2;
	const char *salida;

	root = json_object();
	persona = json_object();
	if (root == NULL || persona == NULL) {
		perror("Error create node: ");
		return EXIT_FAILURE;
	}

	if (establece_nodo(root, "persona", persona) < 0)
		return EXIT_FAILURE;

	id = json_integer(0);
	if (id == NULL)
		return EXIT_FAILURE;

	if (establece_nodo(persona, "id", id) < 0)
		return EXIT_FAILURE;

	dni = json_string("523413443X");
	if (dni == NULL)
		return EXIT_FAILURE;

	if (establece_nodo(persona, "dni", dni) < 0)
		return EXIT_FAILURE;

	carac = json_array();
	if (carac == NULL) {
		perror("Error create array: ");
		return EXIT_FAILURE;
	}

	carac1 = json_string("alto");
	if (carac1 == NULL)
		return EXIT_FAILURE;

	if (append_nodo(carac, carac1) < 0)
		return EXIT_FAILURE;

	carac2 = json_string("delgado");
	if (carac2 == NULL)
		return EXIT_FAILURE;

	if (append_nodo(carac, carac2) < 0)
		return EXIT_FAILURE;

	if (establece_nodo(persona, "caracteristicas", carac) < 0)
		return EXIT_FAILURE;

	salida = json_dumps(root, JSON_INDENT(4));

	printf("salida :\n%s\n", salida);

	if (json_dump_file(root, "prueba.json", 0) < 0) {
		perror("Error export file: ");
		return EXIT_FAILURE;
	}

	free((void *)salida);
	json_decref(carac1);
	json_decref(carac2);
	json_decref(dni);
	json_decref(id);
	json_decref(carac);
	json_decref(persona);
	json_decref(root);
	return EXIT_SUCCESS;
}
