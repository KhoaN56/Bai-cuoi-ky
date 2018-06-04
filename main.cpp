#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include<cmath>
#include"class.h"
#include"functions.h"
using namespace std;
int main()
{
	Image haha;
	Filter f;
	haha.setter();
//	haha.negative();
	f.logarite(haha);
	haha.outPutFile();
	return 0;
}
