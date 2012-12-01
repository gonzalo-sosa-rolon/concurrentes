#include "AdministracionCliente.h"

const char* AdministracionCliente::PATH_TOKEN_MEMORIA_COMPARTIDA = "/bin/ls";
const char* AdministracionCliente::PATH_TOKEN_COLAS = "/bin/ps";

AdministracionCliente::AdministracionCliente() :
		colaEntrada((char*) PATH_TOKEN_COLAS, 'E'), colaSalida(
				(char*) PATH_TOKEN_COLAS, 'S') {

}

AdministracionCliente::~AdministracionCliente() {

}

bool AdministracionCliente::solicitarLugar(int estacionamiento) {

	return true;
}

bool AdministracionCliente::solicitarEntrada(int estacionamiento) {
	pid_t pid = getpid();
	Mensaje mensaje;

	mensaje.mtype = 2; //TODO cambiar por path
	mensaje.pid = pid;
	colaEntrada.escribir(mensaje);
	return colaEntrada.leer(pid, &mensaje);
}

bool AdministracionCliente::liberarEntrada(int estacionamiento) {
	Mensaje solicitud;

	solicitud.mtype = 3; //TODO remover constantes
	solicitud.pid = getpid();

	return colaEntrada.escribir(solicitud);
}

bool AdministracionCliente::ocuparPlaza(int estacionamiento) {
	return true;
}

bool AdministracionCliente::solicitarSalida(int estacionamiento) {
	pid_t pid = getpid();
	Mensaje solicitud;

	solicitud.mtype = 2;
	solicitud.pid = pid;
	colaSalida.escribir(solicitud);
	return colaSalida.leer(pid, &solicitud);
}

bool AdministracionCliente::liberarSalida(int estacionamiento) {
	Mensaje solicitud;
	solicitud.mtype = 3;
	solicitud.pid = getpid();
	return colaSalida.escribir(solicitud);
}

bool AdministracionCliente::salir(Auto* automovil) {
	return true;
}
