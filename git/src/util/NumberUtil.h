#ifndef NUMBERUTIL_H_
#define NUMBERUTIL_H_

#include <cstdlib>
#include <sstream>
#include <string>

class NumberUtil {

public:
	int static getRandom(int rango);
	int static getRandom(int min, int max);
	void static getRandomString(std::string& str, const int len);

private:
	int static sequence;
};

#endif /* NUMBERUTIL_H_ */
