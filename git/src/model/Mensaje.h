#ifndef MENSAJE_H_

#define MENSAJE_H_


namespace Mensaje {

static const char* PATH_TOKEN_COLAS_ENTRADA = "/bin/ps";
static const char* PATH_TOKEN_COLAS_SALIDA = "/bin/cp";
static const char* PATH_TOKEN_COLA_SERVIDOR = "/bin/pwd";

const int TOMAR_PUERTA = 2;
const int LIBERAR_PUERTA = 3;
const int MENSAJE_SERVIDOR = 4;

const int TIPO_SOLICITAR_LUGAR = 5;
const int TIPO_OCUPAR_PLAZA = 6;
const int TIPO_LIBERAR_PLAZA = 7;
const int TIPO_SALIR = 8;

typedef struct mensaje {
	long mtype;
	int pid;
	int automovil;
	int plaza;
	int estacionamiento;
	int tipo;
	int resultado;
	int tiempo;
} Mensaje;

}



#endif /* MENSAJE_H_ */
