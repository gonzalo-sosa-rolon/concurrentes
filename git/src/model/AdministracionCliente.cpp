#include "AdministracionCliente.h"
#include "Auto.h"

const char* AdministracionCliente::PATH_TOKEN_MEMORIA_COMPARTIDA = "/bin/ls";

AdministracionCliente::AdministracionCliente(int cantidadEstacionamientos, int tamanio, int precio, int cantidadEntradas, int cantidadSalidas) :
		colaServidor((char*)Mensaje::PATH_TOKEN_COLA_SERVIDOR, 3)
		 {
	this->tamanio = tamanio;
	this->cantidadEntradas = cantidadEntradas;
	this->cantidadSalidas = cantidadSalidas;
	this->cantidadEstacionamientos = cantidadEstacionamientos;

	for (int i = 0; i < cantidadEstacionamientos; i++) {
		Cola<Mensaje::Mensaje>* colaEntrada = new Cola<Mensaje::Mensaje>((char*)Mensaje::PATH_TOKEN_COLAS_ENTRADA, i);
		Cola<Mensaje::Mensaje>* colaSalida = new Cola<Mensaje::Mensaje>((char*)Mensaje::PATH_TOKEN_COLAS_SALIDA, i);
		Estacionamiento* estacionamiento = new Estacionamiento(tamanio, precio);

		this->estacionamientos.push_back(estacionamiento);
		this->colasEntrada.push_back(colaEntrada);
		this->colasSalida.push_back(colaSalida);
	}
}

AdministracionCliente::~AdministracionCliente() {
	for (int i = 0; i < cantidadEstacionamientos; i++) {
		delete this->estacionamientos[i];

		this->colasEntrada[i]->destruir();
		delete this->colasEntrada[i];

		this->colasSalida[i]->destruir();
		delete this->colasSalida[i];
		colaServidor.destruir();
	}
}

bool AdministracionCliente::solicitarLugar(int estacionamiento) {
	Mensaje::Mensaje mensaje;
	mensaje.mtype = Mensaje::MENSAJE_SERVIDOR;
	mensaje.automovil = 334;

	colaServidor.escribir(mensaje);

	return this->estacionamientos[estacionamiento]->solicitarLugar();
}

bool AdministracionCliente::solicitarEntrada(int estacionamiento) {
	pid_t pid = getpid();
	Mensaje::Mensaje mensaje;

	mensaje.mtype = Mensaje::TOMAR_PUERTA;
	mensaje.pid = pid;
	colasEntrada[estacionamiento]->escribir(mensaje);
	return colasEntrada[estacionamiento]->leer(pid, &mensaje);
}

bool AdministracionCliente::liberarEntrada(int estacionamiento) {
	Mensaje::Mensaje solicitud;

	solicitud.mtype = Mensaje::LIBERAR_PUERTA;
	solicitud.pid = getpid();

	return colasEntrada[estacionamiento]->escribir(solicitud);
}

bool AdministracionCliente::ocuparPlaza(Auto* automovil) {
	return this->estacionamientos[automovil->getEstacionamiento()]->ocuparPlaza(automovil);
}

bool AdministracionCliente::solicitarSalida(int estacionamiento) {
	pid_t pid = getpid();
	Mensaje::Mensaje solicitud;

	solicitud.mtype = Mensaje::TOMAR_PUERTA;
	solicitud.pid = pid;
	colasSalida[estacionamiento]->escribir(solicitud);
	return colasSalida[estacionamiento]->leer(pid, &solicitud);
}

bool AdministracionCliente::liberarSalida(int estacionamiento) {
	Mensaje::Mensaje solicitud;
	solicitud.mtype = Mensaje::LIBERAR_PUERTA;
	solicitud.pid = getpid();
	return colasSalida[estacionamiento]->escribir(solicitud);
}

bool AdministracionCliente::descocuparLugar(Auto* automovil) {
	return this->estacionamientos[automovil->getEstacionamiento()]->desocuparLugar(automovil->getNumeroPlaza());
}

bool AdministracionCliente::salir(Auto* automovil) {
	return false; //TODO ver esto
}