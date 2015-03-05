#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int *valor;

	valor = (int *)malloc(sizeof(int));
	printf("Valor del puntero después del malloc %p\n", &valor);

	printf("Valor de inicio del puntero %d\n", *valor);
	*valor = 5000;
	printf("Valor modificado del puntero %d\n", *valor);

	free(valor);
	return 0;
}
