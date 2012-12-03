#include "ProcesoConsulta.h"
#include "Mensaje.h"

ProcesoConsulta::ProcesoConsulta(int cantidadEstacionamientos) {
	this->cantidadEstacionamientos = cantidadEstacionamientos;
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

int ProcesoConsulta::leerEstacionamiento() {

	string estacionamiento;
	int resultado;

	cout << "Ingrese el estacionamiento: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> estacionamiento;
	stringstream ss(estacionamiento);

	ss >> resultado;

	return resultado;
}

void ProcesoConsulta::ejecutarOpcion(string opcion) {

	char opcionElegida = opcion[0];
	int estacionamiento = leerEstacionamiento();

	switch (opcionElegida) {
	case 'a':
		this->consultarCantidadDeAutos(estacionamiento);
		break;
	case 'b':
		this->consultarMontoFacturado(estacionamiento);
		break;
	default:
		cout << "Opcion incorrecta" << endl;
		break;
	}
}

void ProcesoConsulta::consultarCantidadDeAutos(int estacionamiento) {

	if (estacionamiento >= cantidadEstacionamientos) {
		cout << "Estacionamiento invalido (" << estacionamiento <<") Rango  [0," << cantidadEstacionamientos - 1<<"]" << endl;
	}

	cout << "Cantidad actual de autos : " << endl;//TODO this->estacionamiento->getCantidadDeAutos() << endl;
	cout.flush();
}

void ProcesoConsulta::consultarMontoFacturado(int estacionamiento) {

	if (estacionamiento >= cantidadEstacionamientos) {
		cout << "Estacionamiento invalido (" << estacionamiento <<") Rango [0," << cantidadEstacionamientos - 1<<"]" << endl;
	}
	cout << "Monto facturado : " << endl; //TODO this->estacionamiento->getCantidadFacturado() << endl;
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
