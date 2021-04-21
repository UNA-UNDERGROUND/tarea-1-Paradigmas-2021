#include <contenedora.h>
#include <habitacion.h>
#include <stdlib.h>

const int max_pisos = 5;
const int max_habitaciones = 5;

Contenedora contenedor;

void inicializarMemoria() {
	contenedor.pisos = max_pisos;
	contenedor.habitaciones = max_habitaciones;
	contenedor.vec = malloc(sizeof(Habitacion *) * max_pisos);
	for (size_t i = 0; i < contenedor.pisos; i++) {
		contenedor.vec[i] =
		    malloc(sizeof(Habitacion) * contenedor.habitaciones);
	}
}

void liberarMemoria() {
	for (size_t i = 0; i < contenedor.pisos; i++) {
		free(contenedor.vec[i]);
	}
	free(contenedor.vec);
}