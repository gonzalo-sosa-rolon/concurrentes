#include "StringUtil.h"

int StringUtil::stringToInt(string valor) {

	stringstream ss(valor);
	int resultado;

	ss >> resultado;

	return resultado;

}

string StringUtil::intToString(int valor) {

	stringstream ss;

	ss << valor;

	return ss.str();
}
