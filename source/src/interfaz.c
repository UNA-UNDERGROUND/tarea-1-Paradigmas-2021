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
void mostrarPersonasAlojadas();
void mostrarEstadosDeLasHabitaciones();
void administrarReportes();
void administrarReservaciones();
void agregarReservaciones();
void verReservaciones();
void administrarHabitaciones();
void verEstadoDeLasHabitaciones();
void ponerHabitacionEnMantenimiento();
void ponerHabitacionEnHabitaciones();

void inicializarMemoria();
void liberarMemoria();

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

	limpiarPantalla();
	bool opcionWhile = 1;
	int opcionMenu = 0;
	while (opcionWhile) {
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

		switch (opcionMenu) {
		case 1:

			limpiarPantalla();
			administrarReservaciones();
			break;
		case 2:

			limpiarPantalla();
			administrarHabitaciones();
			break;
		case 3:

			limpiarPantalla();
			administrarReportes();
			break;
		case 4:

			limpiarPantalla();
			verClientesRegistrados();
			break;

		case 5:

			limpiarPantalla();
			opcionWhile = 0;
			break;

		default:
			break;
		}
	}
	liberarMemoria();
}

void administrarReservaciones() {
	limpiarPantalla();
	bool opcionWhile = 1;
	int opcionMenu = 0;

	while (opcionWhile) {
		printf("             Sub-Menu  Reservaciones");
		printf("\n   -------------------------------------");
		printf("\n   | 1- Agregar reservaciones          |");
		printf("\n   | 2- Ver reservaciones              |");
		printf("\n   | 3- Volver al menu principal       |");
		printf("\n   -------------------------------------");

		printf("\n   Digite una opcion: ");
		scanf("%d", &opcionMenu);

		switch (opcionMenu) {
		case 1:

			limpiarPantalla();
			agregarReservaciones();
			break;
		case 2:

			limpiarPantalla();
			verReservaciones();
			break;

		case 3:

			limpiarPantalla();
			opcionWhile = 0;
			break;

		default:
			break;
		}
	}
}

void agregarReservaciones() {
	Habitacion habitacion;
	reservarHabitacion(&habitacion);
}

void verReservaciones() {}

void administrarHabitaciones() {
	limpiarPantalla();
	bool opcionWhile = 1;
	int opcionMenu = 0;

	while (opcionWhile) {
		printf("           Sub-Menu Habitaciones");
		printf("\n   ------------------------------------------");
		printf("\n   | 1- Ver estado de las habitaciones      |");
		printf("\n   | 2- Poner habitacion en mantenimiento   |");
		printf("\n   | 3- Salir                               |");
		printf("\n   ------------------------------------------");

		printf("\n   Digite una opcion: ");
		scanf("%d", &opcionMenu);

		switch (opcionMenu) {
		case 1:

			limpiarPantalla();
			verEstadoDeLasHabitaciones();
			break;
		case 2:

			limpiarPantalla();
			ponerHabitacionEnMantenimiento();
			break;

		case 3:

			limpiarPantalla();
			opcionWhile = 0;
			break;

		default:
			break;
		}
	}
}

// TODO: por implementar
void verEstadoDeLasHabitaciones() {}

// TODO: por implementar
void ponerHabitacionEnMantenimiento() {}

// TODO: por implementar
void mostrarRecaudacionDeClientesTodoIncluido() {}

// TODO: por implementar
void mostrarRecaudacionDeClientesSinTodoIncluido() {}

// TODO: por implementar
void mostrarRecaudacionDeTodosLosClientes() {}

// TODO: por implementar
void verClientesRegistrados() {}

void administrarReportesDeRecaudacion() {
	limpiarPantalla();
	bool opcionWhile = 1;
	int opcionMenu = 0;

	while (opcionWhile) {
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

			limpiarPantalla();
			mostrarRecaudacionDeClientesTodoIncluido();
			break;
		case 2:

			limpiarPantalla();
			mostrarRecaudacionDeClientesSinTodoIncluido();
			break;
		case 3:

			limpiarPantalla();
			mostrarRecaudacionDeTodosLosClientes();
			break;
		case 4:

			limpiarPantalla();
			opcionWhile = 0;

			break;

		default:
			break;
		}
	}
}

void mostrarPersonasAlojadas() {}

void mostrarEstadosDeLasHabitaciones() {}

void administrarReportes() {
	limpiarPantalla();
	bool opcionWhile = 1;
	int opcionMenu = 0;

	while (opcionWhile) {
		printf("               sub-Menu Reportes");
		printf("\n   -------------------------------------");
		printf("\n   | 1- Personas alojadas en el hotel  |");
		printf("\n   | 2- Estado de las habitaciones     |");
		printf("\n   | 3- Reportes de recaudaciones      |");
		printf("\n   | 4- Ver clientes registrados       |");
		printf("\n   | 5- Salir                          |");
		printf("\n   -------------------------------------");

		printf("\n   Digite una opcion: ");
		scanf("%d", &opcionMenu);

		switch (opcionMenu) {
		case 1:

			limpiarPantalla();
			mostrarPersonasAlojadas();
			break;
		case 2:

			limpiarPantalla();
			mostrarEstadosDeLasHabitaciones();
			break;
		case 3:

			limpiarPantalla();
			administrarReportesDeRecaudacion();
			break;
		case 4:

			limpiarPantalla();
			verClientesRegistrados();
			break;

		case 5:

			limpiarPantalla();
			opcionWhile = 0;
			break;

		default:
			break;
		}
	}
}
