#pragma once
#include<iostream>
#include<cstring>
#include"class.h"
using namespace std;
//void Matrix::setter(Image pic)
//{
//	int i, j;
//	width = w;
//	height = h;
//	pixels = new int*[height];
//	for(i = 0; i < height; ++i)	pixels[i] = new int[width];
//	
//}
void Image::setter()
{
	ifstream ifs;
	char buffer[10000];
	char *c;
	int i = 0, j, k;
	ifs.open("mona_lisa.ascii.pgm", ios_base::in);
	if (ifs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	ifs.getline(buffer, 100, '\n');
	if(buffer[0] != 'P' || buffer[1] != '2')
	{
		cout << "Format error!!";
		ifs.close();
		return;
	}
	do
	{
		ifs.getline(buffer, 100, '\n');
	}while(buffer[0] == '#');
	width = strtol(buffer, &c, 10);
	height = atoi(c);
	ifs.getline(buffer, 100, '\n');
	graylevel = atoi(buffer);
	pixels = new int*[height];
	for(i = 0; i < height; ++i)	pixels[i] = new int[width];
	for(i = 0; i < height; ++i)
	{
		ifs.getline(buffer, 10000, '\n');
		c = &buffer[0];
		for(k = 0; k < width ; ++k)
		{
			pixels[i][k] = strtol(c, &c, 10);
//			cout << setw(4) << pixels[i][k] << " ";
		}
//		cout << endl;
	}
	ifs.close();
}
void Negative::transform(Image pic)
{
	int i, j, width, height, graylevel;
	graylevel = pic.getterGrayLevel();
	width = pic.getterWidth();
	height = pic.getterHeight();
	int **matrix = pic.getterPixels();
	for(i = 0; i < height; ++i)
		for(j = 0; j < width; ++j)
			matrix[i][j] = graylevel - matrix[i][j];
}

