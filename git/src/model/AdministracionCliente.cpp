#include "AdministracionCliente.h"

const char* AdministracionCliente::PATH_TOKEN_MEMORIA_COMPARTIDA = "/bin/ls";

AdministracionCliente::AdministracionCliente(int tamanio, int cantidadEntradas, int cantidadSalidas)
		 {
	this->tamanio = tamanio;
	this->cantidadEntradas = cantidadEntradas;
	this->cantidadSalidas = cantidadSalidas;

	for (int i = 0; i < tamanio; i++) {
		Cola<Mensaje::Mensaje>* colaEntrada = new Cola<Mensaje::Mensaje>((char*)Mensaje::PATH_TOKEN_COLAS_ENTRADA, i);
		Cola<Mensaje::Mensaje>* colaSalida = new Cola<Mensaje::Mensaje>((char*)Mensaje::PATH_TOKEN_COLAS_SALIDA, i);

		this->colaEntrada.push_back(colaEntrada);
		this->colaSalida.push_back(colaSalida);
	}
}

AdministracionCliente::~AdministracionCliente() {

}

bool AdministracionCliente::solicitarLugar(int estacionamiento) {

	return true;
}

bool AdministracionCliente::solicitarEntrada(int estacionamiento) {
	pid_t pid = getpid();
	Mensaje::Mensaje mensaje;

	mensaje.mtype = Mensaje::TOMAR_PUERTA;
	mensaje.pid = pid;
	colaEntrada[estacionamiento]->escribir(mensaje);
	return colaEntrada[estacionamiento]->leer(pid, &mensaje);
}

bool AdministracionCliente::liberarEntrada(int estacionamiento) {
	Mensaje::Mensaje solicitud;

	solicitud.mtype = Mensaje::LIBERAR_PUERTA;
	solicitud.pid = getpid();

	return colaEntrada[estacionamiento]->escribir(solicitud);
}

bool AdministracionCliente::ocuparPlaza(int estacionamiento) {
	return true;
}

bool AdministracionCliente::solicitarSalida(int estacionamiento) {
	pid_t pid = getpid();
	Mensaje::Mensaje solicitud;

	solicitud.mtype = Mensaje::TOMAR_PUERTA;
	solicitud.pid = pid;
	colaSalida[estacionamiento]->escribir(solicitud);
	return colaSalida[estacionamiento]->leer(pid, &solicitud);
}

bool AdministracionCliente::liberarSalida(int estacionamiento) {
	Mensaje::Mensaje solicitud;
	solicitud.mtype = Mensaje::LIBERAR_PUERTA;
	solicitud.pid = getpid();
	return colaSalida[estacionamiento]->escribir(solicitud);
}

bool AdministracionCliente::salir(Auto* automovil) {
	return true;
}
