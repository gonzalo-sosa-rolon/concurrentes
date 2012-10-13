#include "ProcesoConsulta.h"

ProcesoConsulta::ProcesoConsulta() {
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

		cout << "Opcion leida ";
		if (opcion == "a" || opcion == "b") {
			break;
		} else {
			cout << "Opcion invalida" << opcion << endl;
		}
	}

	return opcion;
}

void ProcesoConsulta::ejecutarOpcion(string opcion) {

}

void ProcesoConsulta::ejecutar() {

	string opcion;

	while (true) {
		this->imprimirOpciones();
		opcion = this->leerOpcion();
		this->ejecutarOpcion(opcion);
	}
}
