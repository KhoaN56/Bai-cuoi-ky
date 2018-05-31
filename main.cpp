#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include"class.h"
#include"functions.h"
using namespace std;
int main()
{
	Image haha;
	Negative filter;
	haha.setter();
	haha.negative();
//	filter.transform(haha);
	haha.outPutFile();
		cout << "adsafdsf" << endl;
		cout << "adsafdsf" << endl;
	return 0;
}
