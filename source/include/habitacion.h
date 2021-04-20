#pragma once
#include <cliente.h>
#include <informacion.h>

typedef struct Habitacion {
	String *id;
	char estado;
	Cliente *cliente;
	Informacion *informacion;
	int cantCamas;
	String *clasificacion;
} Habitacion;