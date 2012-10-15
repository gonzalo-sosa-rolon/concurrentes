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

	cout << "Opcion: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> opcion;

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
		break;
	}
}

void ProcesoConsulta::consultarCantidadDeAutos() {
	cout << "Cantidad actual de autos : " << this->estacionamiento->getCantidadDeAutos() << endl;
	cout.flush();
}

void ProcesoConsulta::consultarMontoFacturado() {
	cout << "Monto facturado : " << this->estacionamiento->getCantidadFacturado() << endl;
	cout.flush();
}

void ProcesoConsulta::ejecutar() {

	string opcion;

	while (!this->sigint_handler.getGracefulQuit()) {
		this->imprimirOpciones();
		opcion = this->leerOpcion();
		this->ejecutarOpcion(opcion);
	}
}
