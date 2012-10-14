#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <string>
#include <sstream>

using namespace std;

class StringUtil {

public:
	int static stringToInt(string valor);
	static string intToString(int valor);
};

#endif /* STRINGUTIL_H_ */
