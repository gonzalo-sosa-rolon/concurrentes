#include "AdministracionCliente.h"
#include "Auto.h"

const char* AdministracionCliente::PATH_TOKEN_MEMORIA_COMPARTIDA = "/bin/ls";

AdministracionCliente::AdministracionCliente(int cantidadEstacionamientos,
		int tamanio, int precio, int cantidadEntradas, int cantidadSalidas) :
		colaServidor((char*) Mensaje::PATH_TOKEN_COLA_SERVIDOR, 3) {
	this->tamanio = tamanio;
	this->cantidadEntradas = cantidadEntradas;
	this->cantidadSalidas = cantidadSalidas;
	this->cantidadEstacionamientos = cantidadEstacionamientos;

	for (int i = 0; i < cantidadEstacionamientos; i++) {
		Cola<Mensaje::Mensaje>* colaEntrada = new Cola<Mensaje::Mensaje>(
				(char*) Mensaje::PATH_TOKEN_COLAS_ENTRADA, i);
		Cola<Mensaje::Mensaje>* colaSalida = new Cola<Mensaje::Mensaje>(
				(char*) Mensaje::PATH_TOKEN_COLAS_SALIDA, i);

		this->colasEntrada.push_back(colaEntrada);
		this->colasSalida.push_back(colaSalida);
	}
}

AdministracionCliente::~AdministracionCliente() {
	for (int i = 0; i < cantidadEstacionamientos; i++) {

		this->colasEntrada[i]->destruir();
		delete this->colasEntrada[i];

		this->colasSalida[i]->destruir();
		delete this->colasSalida[i];
		colaServidor.destruir();
	}
}

bool AdministracionCliente::solicitarLugar(Auto* automovil) {

	int estacionamiento = automovil->getEstacionamiento();
	pid_t pid = getpid();
	Mensaje::Mensaje mensaje = prepararMensajeServidor(estacionamiento);
	mensaje.tipo = Mensaje::TIPO_SOLICITAR_LUGAR;

	Mensaje::Mensaje respuesta;

	colaServidor.escribir(mensaje);
	colaServidor.leer(pid, &respuesta);

	return respuesta.resultado;
}

bool AdministracionCliente::solicitarEntrada(Auto* automovil) {
	int estacionamiento = automovil->getEstacionamiento();
	pid_t pid = getpid();
	Mensaje::Mensaje mensaje;

	mensaje.mtype = Mensaje::TOMAR_PUERTA;
	mensaje.pid = pid;
	colasEntrada[estacionamiento]->escribir(mensaje);
	return colasEntrada[estacionamiento]->leer(pid, &mensaje);
}

bool AdministracionCliente::liberarEntrada(Auto* automovil) {
	int estacionamiento = automovil->getEstacionamiento();
	Mensaje::Mensaje solicitud;

	solicitud.mtype = Mensaje::LIBERAR_PUERTA;
	solicitud.pid = getpid();

	return colasEntrada[estacionamiento]->escribir(solicitud);
}

bool AdministracionCliente::ocuparPlaza(Auto* automovil) {

	int estacionamiento = automovil->getEstacionamiento();

	pid_t pid = getpid();
	Mensaje::Mensaje mensaje = prepararMensajeServidor(estacionamiento);

	mensaje.tipo = Mensaje::TIPO_OCUPAR_PLAZA;
	mensaje.automovil = automovil->getId();
	mensaje.tiempo = automovil->getTiempo();

	colaServidor.escribir(mensaje);
	colaServidor.leer(pid, &mensaje);

	automovil->setNumeroPlaza(mensaje.resultado);
	return mensaje.resultado == -1 || mensaje.resultado == 0 ? false : true;
}

bool AdministracionCliente::solicitarSalida(Auto* automovil) {
	int estacionamiento = automovil->getEstacionamiento();
	pid_t pid = getpid();
	Mensaje::Mensaje solicitud;

	solicitud.mtype = Mensaje::TOMAR_PUERTA;
	solicitud.pid = pid;
	colasSalida[estacionamiento]->escribir(solicitud);
	return colasSalida[estacionamiento]->leer(pid, &solicitud);
}

bool AdministracionCliente::liberarSalida(Auto* automovil) {
	int estacionamiento = automovil->getEstacionamiento();
	Mensaje::Mensaje solicitud;
	solicitud.mtype = Mensaje::LIBERAR_PUERTA;
	solicitud.pid = getpid();
	return colasSalida[estacionamiento]->escribir(solicitud);
}

bool AdministracionCliente::descocuparLugar(Auto* automovil) {

	int estacionamiento = automovil->getEstacionamiento();
	Mensaje::Mensaje mensaje = prepararMensajeServidor(estacionamiento);

	mensaje.tipo = Mensaje::TIPO_LIBERAR_PLAZA;
	mensaje.plaza = automovil->getNumeroPlaza();

	colaServidor.escribir(mensaje);

	return true;
}

Mensaje::Mensaje AdministracionCliente::prepararMensajeServidor(
		int estacionamiento) {
	Mensaje::Mensaje resultado;
	pid_t pid = getpid();

	resultado.mtype = Mensaje::MENSAJE_SERVIDOR;
	resultado.pid = pid;
	resultado.estacionamiento = estacionamiento;

	return resultado;
}

int AdministracionCliente::consultarCantidadFacturado(int estacionamiento) {
	pid_t pid = getpid();

	Mensaje::Mensaje mensaje = prepararMensajeServidor(estacionamiento);
	Mensaje::Mensaje respuesta;
	mensaje.tipo = Mensaje::TIPO_MONTO_FACTURADO;

	colaServidor.escribir(mensaje);
	colaServidor.leer(pid, &respuesta);

	return respuesta.resultado;
}

int AdministracionCliente::getCantidadEstacionamientos() {
	return this->cantidadEstacionamientos;
}

int AdministracionCliente::consultarCantidadAutos(int estacionamiento) {
	pid_t pid = getpid();

	Mensaje::Mensaje mensaje = prepararMensajeServidor(estacionamiento);
	mensaje.tipo = Mensaje::TIPO_CANTIDAD_AUTOS;

	colaServidor.escribir(mensaje);
	colaServidor.leer(pid, &mensaje);

	return mensaje.resultado;
}

bool AdministracionCliente::salir(Auto* automovil) {
	return false; //TODO ver esto
}
