#include "NumberUtil.h"

int NumberUtil::getRandom(int rango) {
	return getRandom(0, rango);
}

int NumberUtil::getRandom(int min, int max) {
	return rand() % (max - min) + min;
}
