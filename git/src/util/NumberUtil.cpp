#include "NumberUtil.h"

int NumberUtil::sequence= 0;

int NumberUtil::getRandom(int rango) {
	return getRandom(0, rango);
}

int NumberUtil::getRandom(int min, int max) {
	return rand() % (max - min) + min;
}

void NumberUtil::getRandomString(std::string& str, const int len) {
	std::stringstream stream(std::stringstream::in | std::stringstream::out);
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    char s[len];
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    stream << s;

    str = stream.str();
}
