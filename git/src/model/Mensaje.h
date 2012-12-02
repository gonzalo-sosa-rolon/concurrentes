#ifndef MENSAJE_H_

#define MENSAJE_H_

namespace Mensaje {

static const char* PATH_TOKEN_COLAS_ENTRADA = "/bin/ps";
static const char* PATH_TOKEN_COLAS_SALIDA = "/bin/cp";
static const char* PATH_TOKEN_COLA_SERVIDOR = "/bin/pwd";

const int TOMAR_PUERTA = 2;
const int LIBERAR_PUERTA = 3;

typedef struct mensaje {
	long mtype;
	int pid;
	int automovil;
	int plaza;
	int estacionamiento;
} Mensaje;

}



#endif /* MENSAJE_H_ */
