#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include<cmath>
#include<mylib.h>
#include"class.h"
#include"functions.h"
#include"config.h"
using namespace std;
int main()
{
	int choice, choice1, choice2;
	Image picture;
	Filter f;
//	picture.setter("mona_lisa.ascii.pgm");
//	f.logarite(picture);
//	picture.outPutFile();
	char *filename = new char[100];
	do
	{
		choice = MenuDong(menu);
		Normal();
		system("cls");
		switch(choice)
		{
			case 1:					//Choose image to proccess
				choice1 = MenuDong(pic);
				Normal();
				system("cls");
				switch(choice1)
				{
					case 1:
						filename = {"mona_lisa.ascii.pgm"};
						picture.setter(filename);
						break;
					case 2:
						filename = {"venus2.ascii.pgm"};
						picture.setter(filename);
						break;
					case 3:
						filename = {"balloons.ascii.pgm"};
						picture.setter(filename);
						break;
					case 4:
						filename = {"brain_604.ascii.pgm"};
						picture.setter(filename);
						break;
					case 5:
						filename = {"casablanca.ascii.pgm"};
						picture.setter(filename);
						break;
					case 6:
						break;
					default:
						break;
				}
				break;
			case 2:					//Choose filters
				if(picture.getterGrayLevel() == 0)
				{
					cout << "Image not found.." << endl;
					Sleep(1500);
					break;
				}
				choice2 = MenuDong(filters);
				Normal();
				system("cls");
				switch(choice2)
				{
					case 1:			//Choose Negative transformation
						f.negative(picture);
						break;
					case 2:			//Choose Logarite transformation
						f.logarite(picture);
						break;
					case 3:			//Choose Histogram equalization
						f.histogram(picture);
						break;
					case 4:			//Choose Smoothing Linear filter
						f.smoothing(picture);
						break;
					case 5:			//Choose Laplacian filter
						f.laplacian(picture);
						break;
					case 6:			//Choose back to menu
						break;
					default:		//choice2 == 0 --> ESC = Back to menu
						break;
				}
				break;
			case 3:					//Choose Save Image
				picture.outPutFile();
				break;
			case 4:
				break;
			default:
				break;
		}
	}while(choice != 0 && choice != 4);
	cout << "Thank you!!" << endl;
	delete filename;
	return 0;
}
