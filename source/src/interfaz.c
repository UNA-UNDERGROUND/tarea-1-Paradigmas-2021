#include "utils.h"
#include <contenedora.h>
#include <habitacion.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void mostrarRecaudacionDeClientesTodoIncluido();
void mostrarRecaudacionDeClientesSinTodoIncluido();
void mostrarRecaudacionDeTodosLosClientes();
void verClientesRegistrados();
void administrarReportesDeRecaudacion();

void administrarReportes();
void administrarReservaciones();
void agregarReservaciones();
void verReservaciones();
void administrarHabitaciones();
void verEstadoDeLasHabitaciones();
void cambiarEstadoHabitaciones();
void ponerHabitacionEnHabitaciones();
void pagarReservacion();
void inicializarMemoria();
void liberarMemoria();
void imprimirMatriz(Contenedora *);
void pause();
void imprimirMatrizId(Contenedora *);
void guardarCadena(String *);
void reservarHabitacion(Habitacion *);
void cambiarEstadoDelaHabitacion(Contenedora *, String *, String *);
int RecaudacionDeTodosLosClientes(Contenedora *);
int RecaudacionDeClientesTodoIncluido(Contenedora *);
int RecaudacionDeClientesSinTodoIncluido(Contenedora *);
int cancelarHabitacionPorId(Contenedora *, String *);
int cantDeCamasDesocupadasSegunAux(Contenedora *, int);
int cantHabitacionesLibres(Contenedora *);
int cantHabitacionesEnMantenimiento(Contenedora *);
int cantHabitacionesOcupadas(Contenedora *);
int cantDePersonasAdultas(Contenedora *);
int cantDeNinnos(Contenedora *);

void llenarMatriz(Contenedora *);

void llenarMatriz();

void limpiarPantalla() {
// aunque esto se considera inseguro
// el proyecto solo es con fines de demostracion
#ifdef WIN32
	system("cls");
#else
	system("clear");
#endif
}

extern Contenedora contenedor;

void mainMenu() {
	inicializarMemoria();
	llenarMatriz(&contenedor);

	bool opcionWhile = 1;
	int opcionMenu = 0;
	while (opcionWhile) {
		limpiarPantalla();

		printf("               Menu Principal");
		printf("\n   -------------------------------------");
		printf("\n   | 1- Administrar reservaciones      |");
		printf("\n   | 2- Administrar habitaciones       |");
		printf("\n   | 3- Administrar reportes           |");
		printf("\n   | 4- Ver clientes registrados       |");
		printf("\n   | 5- Salir                          |");
		printf("\n   -------------------------------------");

		printf("\n   Digite una opcion: ");
		scanf("%d", &opcionMenu);

		limpiarPantalla();

		switch (opcionMenu) {
		case 1:

			administrarReservaciones();
			break;
		case 2:

			administrarHabitaciones();
			break;
		case 3:

			administrarReportes();
			break;
		case 4:

			verClientesRegistrados();
			break;

		case 5:

			opcionWhile = 0;
			break;

		default:
			break;
		}
	}
	liberarMemoria();
}

void pagarReservacion() {

	String *idCliente = NULL;

	printf("Ingrese el id del cliente");
	idCliente = readString();
	printf("Debe de cancelar: %d",
	       cancelarHabitacionPorId(&contenedor, idCliente));
	pause();
}

void administrarReservaciones() {
	bool opcionWhile = 1;
	int opcionMenu = 0;

	while (opcionWhile) {
		limpiarPantalla();
		printf("             Sub-Menu  Reservaciones");
		printf("\n   -------------------------------------");
		printf("\n   | 1- Agregar reservaciones          |");
		printf("\n   | 2- Pagar reservaciones            |");
		printf("\n   | 3- Ver reservaciones              |");
		printf("\n   | 4- Volver al menu principal       |");
		printf("\n   -------------------------------------");

		printf("\n   Digite una opcion: ");
		scanf("%d", &opcionMenu);
		limpiarPantalla();
		switch (opcionMenu) {
		case 1:

			agregarReservaciones();
			break;
		case 2:

			pagarReservacion();
			break;

		case 3:

			verReservaciones();
			break;

		case 4:

			opcionWhile = 0;
			break;

		default:
			break;
		}
	}
}

void agregarReservaciones() {

	String *idHabitacion = NULL;

	imprimirMatrizId(&contenedor);
	printf("Ingrese el id de la habitacion");
	idHabitacion = readString();

	for (int i = 0; i < contenedor.habitaciones; i++) {
		for (int j = 0; j < contenedor.pisos; j++) {

			if (cmpString(idHabitacion, contenedor.vec[i][j].id)) {

				reservarHabitacion(&contenedor.vec[i][j]);
				return;
			}
		}
	}
}

void verReservaciones() {
	imprimirMatriz(&contenedor);
	pause();
}

void administrarHabitaciones() {
	bool opcionWhile = 1;
	int opcionMenu = 0;

	while (opcionWhile) {
		limpiarPantalla();
		printf("           Sub-Menu Habitaciones");
		printf("\n   ------------------------------------------");
		printf("\n   | 1- Ver estado de las habitaciones      |");
		printf("\n   | 2- Cambiar estado de las habitaciones  |");
		printf("\n   | 3- Salir                               |");
		printf("\n   ------------------------------------------");

		printf("\n   Digite una opcion: ");
		scanf("%d", &opcionMenu);
		limpiarPantalla();

		switch (opcionMenu) {
		case 1:

			verEstadoDeLasHabitaciones();
			break;
		case 2:

			cambiarEstadoHabitaciones();
			break;

		case 3:

			opcionWhile = 0;
			break;

		default:
			break;
		}
	}
}

// TODO: por implementar
void verEstadoDeLasHabitaciones() {
	imprimirMatriz(&contenedor);
	pause();
}

// TODO: por implementar
void cambiarEstadoHabitaciones() {

	String *idHabitacion = NULL;
	char estado;

	printf("Ingrese el id de la habitacion");
	idHabitacion = readString();
	printf("Ingrese el nuevo estado de la habitacion");
	scanf("  %c", &estado);

	cambiarEstadoDelaHabitacion(&contenedor, idHabitacion, estado);
	pause();
}

// TODO: por implementar
void mostrarRecaudacionDeClientesTodoIncluido() {
	printf("%d", RecaudacionDeTodosLosClientes(&contenedor));
	pause();
}

// TODO: por implementar
void mostrarRecaudacionDeClientesSinTodoIncluido() {
	printf("%d", RecaudacionDeClientesTodoIncluido(&contenedor));
	pause();
}

// TODO: por implementar
void mostrarRecaudacionDeTodosLosClientes() {
	printf("%d", RecaudacionDeClientesSinTodoIncluido(&contenedor));
	pause();
}

// TODO: por implementar
void verClientesRegistrados() {
	imprimirMatriz(&contenedor);
	pause();
}

void administrarReportesDeRecaudacion() {

	bool opcionWhile = 1;
	int opcionMenu = 0;

	while (opcionWhile) {
		limpiarPantalla();
		printf("                  sub-Menu Reportes de recaudaciones");

		printf(
		    "\n   ---------------------------------------------------------");
		printf(
		    "\n   | 1- Mostrar recaudacion de clientes todo incluido      |");
		printf(
		    "\n   | 2- Mostrar recaudacion de clientes sin todo incluido  |");
		printf(
		    "\n   | 3- Mostrar recaudacion de todos los clientes          |");
		printf(
		    "\n   | 4- Salir                                              |");
		printf(
		    "\n   ---------------------------------------------------------");

		printf("\n   Digite una opcion: ");
		scanf("%d", &opcionMenu);

		switch (opcionMenu) {
		case 1:

			mostrarRecaudacionDeClientesTodoIncluido();
			break;
		case 2:

			mostrarRecaudacionDeClientesSinTodoIncluido();
			break;
		case 3:

			mostrarRecaudacionDeTodosLosClientes();
			break;
		case 4:

			opcionWhile = 0;

			break;

		default:
			break;
		}
	}
}

void mostrarPersonasAlojadas() {}

void cantCamasDesocupadas() {

	printf("\nCantidad de habitaciones libres con 2 camas: %d",
	       cantDeCamasDesocupadasSegunAux(&contenedor, 2));
	printf("\nCantidad de habitaciones libres con 3 camas: %d",
	       cantDeCamasDesocupadasSegunAux(&contenedor, 3));
	printf("\nCantidad de habitaciones libres con 4 camas: %d",
	       cantDeCamasDesocupadasSegunAux(&contenedor, 4));
	printf("\nCantidad de habitaciones libres con 5 camas: %d",
	       cantDeCamasDesocupadasSegunAux(&contenedor, 5));
}

void administrarReportes() {

	bool opcionWhile = 1;
	int opcionMenu = 0;

	while (opcionWhile) {
		limpiarPantalla();

		printf("               sub-Menu Reportes");
		printf(
		    "\n   "
		    "---------------------------------------------------------------");
		printf("\n   | 1- Cuantas habitaciones estan libres                    "
		       "     |");
		printf("\n   | 2- Cuantas estan en mantenimiento                       "
		       "     |");
		printf("\n   | 3- Cuantas habitaciones ocupadas                        "
		       "     |");
		printf("\n   | 4- Cuantas hay desocupadas por cantidad de camas        "
		       "     |");
		printf("\n   | 5- Cuantas personas adultas hay el dia de hoy en el "
		       "hotel   |");
		printf("\n   | 6- Cuantos ninnos existen al dia de hoy en el hotel     "
		       "    |");
		printf("\n   | 7- Submenu-Reportes De Recaudacion                      "
		       "     |");
		printf("\n   | 8- Salir                                                "
		       "     |");
		printf(
		    "\n   "
		    "---------------------------------------------------------------");

		printf("\n   Digite una opcion: ");
		scanf("%d", &opcionMenu);
		limpiarPantalla();
		switch (opcionMenu) {
		case 1:

			printf("%d ", cantHabitacionesLibres(&contenedor));
			pause();
			break;
		case 2:

			printf("%d ", cantHabitacionesEnMantenimiento(&contenedor));
			pause();
			break;
		case 3:

			printf("%d ", cantHabitacionesOcupadas(&contenedor));
			pause();
			break;
		case 4:
			cantCamasDesocupadas();
			pause();
			break;

		case 5:
			printf("%d ", cantDePersonasAdultas(&contenedor));
			pause();
			break;

		case 6:

			printf("%d ", cantDeNinnos(&contenedor));
			pause();
			break;

		case 7:
			administrarReportesDeRecaudacion();
			break;

		case 8:

			opcionWhile = 0;
			break;

		default:
			break;
		}
	}
}
