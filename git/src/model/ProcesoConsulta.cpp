#include "ProcesoConsulta.h"

ProcesoConsulta::ProcesoConsulta(Estacionamiento* estacionamiento) {
	this->estacionamiento = estacionamiento;

	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);
}

ProcesoConsulta::~ProcesoConsulta() {
}

void ProcesoConsulta::imprimirOpciones() {

	cout << "Opciones:" << endl;
	cout << "a) Consultar cantidad de vehiculos" << endl;
	cout << "b) Consultar monto facturado" << endl;
}

string ProcesoConsulta::leerOpcion() {

	string opcion;

	while (true) {

		cout << "Opcion: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());

		cin >> opcion;

		this->ejecutarOpcion(opcion);
	}

	return opcion;
}

void ProcesoConsulta::ejecutarOpcion(string opcion) {

	char opcionElegida = opcion[0];

	switch (opcionElegida) {
	case 'a':
		this->consultarCantidadDeAutos();
		break;
	case 'b':
		this->consultarMontoFacturado();
		break;
	default:
		cout << "Opcion incorrecta" << endl;
	}
}

void ProcesoConsulta::consultarCantidadDeAutos() {
	cout << "Cantidad actual de autos : " << this->estacionamiento->getCantidadDeAutos() << endl;
}

void ProcesoConsulta::consultarMontoFacturado() {
	cout << "Monto facturado : " << this->estacionamiento->getCantidadFacturado() << endl;
}

void ProcesoConsulta::ejecutar() {

	string opcion;

	while (!this->sigint_handler.getGracefulQuit()) {
		this->imprimirOpciones();
		opcion = this->leerOpcion();

		if (!this->sigint_handler.getGracefulQuit()) {
			this->ejecutarOpcion(opcion);
		} else {
			cout << "La aplicacion ya no se encuentra en funcionamiento" << endl;
		}
	}
}
