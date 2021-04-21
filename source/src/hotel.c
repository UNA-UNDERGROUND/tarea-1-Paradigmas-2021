#include "informacion.h"
#include <cliente.h>
#include <contenedora.h>
#include <habitacion.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void pause() {
	/*  Procedimiento tomado de: https://stackoverrun.com/es/q/3397614  */

	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
	if (c == EOF) {
	} else {
		printf("\n\n Presione enter para continuar...");
		getchar();
	}
}

void guardarCadena(String *cadena) {
	char *buffer = malloc(sizeof(char) * 100);
	scanf("%s", buffer);
	setString(cadena, buffer);
}

void imprimirCadena(String *cadena) {
	char *tex = getString(cadena);
	printf("%s", tex);
}

void crearCliente(Cliente *cliente) {
	String *id = createString("a");
	String *nombre = createString("a");
	String *telefono = createString("a");

	int hw = 1;
	while (hw) {
		printf("\nIngrese los datos del cliente:");
		printf("\nID:");
		guardarCadena(id);
		cliente->id = id;
		printf("\n Edad:");
		scanf("%d", &cliente->edad);

		if (cliente->edad < 18) {
			printf("Un menor de edad no puede solicitar una habitacion\n");
			printf("Vuelva a ingresar los datos");
		} else {
			printf("\nNombre: ");
			guardarCadena(nombre);
			cliente->nombreCliente = nombre;
			printf("\nTelefono: ");
			guardarCadena(telefono);
			cliente->telefono = nombre;
			printf("\nMetodo de pago: ");
			cliente->metodoPago = efectivo;
			hw = 0;
		}
	}
}

void llenarInformacion(Informacion *informacion) {

	printf("\nReservacion todo incluido? ");
	printf("\n 1.Si \n 0.No \n(Ingrese el numero de la respuesta  )");
	scanf("%d", &informacion->todoIncluido);

	printf("\nNumero de adultos: ");
	scanf("%d", &informacion->numeroAdultos);

	printf("\nNumero de infantes: ");
	scanf("%d", &informacion->numeroInfante);

	printf("\nNumero de dias: ");
	scanf("%d", &informacion->numeroDias);

	printf("\nIngrese la hora en la que esta reservando(formato 24 horas): ");
	scanf("%d", &informacion->hora);
}

void reservarHabitacion(Habitacion *habitacion) {
	Cliente *cliente = malloc(sizeof(Cliente));
	Informacion *informacion = malloc(sizeof(Informacion));

	habitacion->estado = 'O';
	crearCliente(cliente);

	llenarInformacion(informacion);

	habitacion->cliente = cliente;
	habitacion->informacion = informacion;
}

void imprimirMatriz(Contenedora *cont) {

	Habitacion **matriz = cont->vec;
	Habitacion habitacion;
	printf("Estados de las habitaciones \n Ocupadas: O \n Disponibles: poseen "
	       "un numero \n En mantenimiento: M");
	printf("\n\n");

	for (int i = 0; i < cont->habitaciones; i++) {
		for (int j = 0; j < cont->pisos; j++) {
			habitacion = matriz[i][j];
			printf("%c ", habitacion.estado);
		}
		printf("\n");
	}
}

void llenarMatriz(Contenedora *cont) {

	for (int i = 0; i < cont->habitaciones; i++) {
		for (int j = 0; j < cont->pisos; j++) {
			cont->vec[i][j].id = createString("-");
			cont->vec[i][j].estado = 'L';
			cont->vec[i][j].cliente = NULL;
			cont->vec[i][j].informacion = NULL;
			cont->vec[i][j].camas = 3;
			cont->vec[i][j].clasificacion = NULL;
		}
	}
}

int cantHabitacionesLibres(Contenedora *cont) {
	Habitacion **matriz = cont->vec;
	Habitacion habitacion;

	int contador = 0;

	for (int i = 0; i < cont->habitaciones; i++) {
		for (int j = 0; j < cont->pisos; j++) {
			habitacion = matriz[i][j];
			if (habitacion.estado == 'L') {
				contador++;
			}
		}
	}

	return contador;
}

int cantHabitacionesEnMantenimiento(Contenedora *cont) {
	Habitacion **matriz = cont->vec;
	Habitacion habitacion;

	int contador = 0;

	for (int i = 0; i < cont->habitaciones; i++) {
		for (int j = 0; j < cont->pisos; j++) {
			habitacion = matriz[i][j];
			if (habitacion.estado == 'M') {
				contador++;
			}
		}
	}

	return contador;
}

int cantHabitacionesOcupadas(Contenedora *cont) {
	Habitacion **matriz = cont->vec;
	Habitacion habitacion;

	int contador = 0;

	for (int i = 0; i < cont->habitaciones; i++) {
		for (int j = 0; j < cont->pisos; j++) {
			habitacion = matriz[i][j];
			if (habitacion.estado == 'O') {
				contador++;
			}
		}
	}

	return contador;
}

int cantDeCamasDesocupadasSegunAux(Contenedora *cont, int aux) {
	Habitacion **matriz = cont->vec;
	Habitacion habitacion;

	int contador = 0;

	for (int i = 0; i < cont->habitaciones; i++) {
		for (int j = 0; j < cont->pisos; j++) {
			habitacion = matriz[i][j];
			if (habitacion.camas == aux) {
				contador++;
			}
		}
	}

	return contador;
}

Habitacion *obtenerHabitacionPorIdCliente(String *id, Contenedora *cont) {

	Habitacion **matriz = cont->vec;
	Habitacion habitacion;

	for (int i = 0; i < cont->habitaciones; i++) {
		for (int j = 0; j < cont->pisos; j++) {
			habitacion = matriz[i][j];
			if (cmpString(id, habitacion.cliente->id)) {
				return &matriz[i][j];
				;
			}
		}
	}

	return NULL;
}

void liberarhabitacionPorIdCliente(String *id, Contenedora *cont) {
	Habitacion *hab = obtenerHabitacionPorIdCliente(id, cont);

	if (hab != NULL) {
		hab->id = createString("-");
		hab->estado = 'L';
		hab->cliente = NULL;
		hab->informacion = NULL;
		hab->camas = 3;
		hab->clasificacion = NULL;
	}
}

int cantDePersonasAdultas(Contenedora *cont) {
	Habitacion **matriz = cont->vec;
	Habitacion habitacion;
	Informacion *info;

	int contador = 0;

	for (int i = 0; i < cont->habitaciones; i++) {
		for (int j = 0; j < cont->pisos; j++) {
			habitacion = matriz[i][j];
			info = matriz[i][j].informacion;
			if (info != NULL) {
				contador += info->numeroAdultos;
			}
		}
	}

	return contador;
}

int cantDeNinnos(Contenedora *cont) {
	Habitacion **matriz = cont->vec;
	Habitacion habitacion;
	Informacion *info;

	int contador = 0;

	for (int i = 0; i < cont->habitaciones; i++) {
		for (int j = 0; j < cont->pisos; j++) {
			habitacion = matriz[i][j];
			info = matriz[i][j].informacion;
			if (info != NULL) {
				contador += info->numeroInfante;
			}
		}
	}

	return contador;
}

void cambiarEstadoDelaHabitacion(Contenedora *cont, String *id, char estado) {

	for (int i = 0; i < cont->habitaciones; i++) {
		for (int j = 0; j < cont->pisos; j++) {

			if (cmpString(id, cont->vec[i][j].id)) {

				cont->vec[i][j].estado = estado;
				return;
			}
		}
	}
}

/*void obtenerHabitacionPorIdhabitacion(String *id, Contenedora *cont) {

    for (int i = 0; i < cont->habitaciones; i++) {
        for (int j = 0; j < cont->pisos; j++) {

            if (cmpString(id, cont->vec[i][j].id)) {

                cont->vec[i][j];

            }
        }
    }


}*/