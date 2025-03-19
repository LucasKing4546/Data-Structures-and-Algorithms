#include "ExtendedTest.h"
#include "ShortTest.h"

#include "FixedCapBiMap.h"


#include <iostream>
using namespace std;


auto main() -> int {
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}