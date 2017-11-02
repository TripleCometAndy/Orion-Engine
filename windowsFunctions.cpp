#include "windowsFunctions.h"


void setScreenDimension(int * screenWidth, int * screenHeight) {

	*screenWidth = GetSystemMetrics(SM_CXSCREEN);
	*screenHeight = GetSystemMetrics(SM_CYSCREEN);



}