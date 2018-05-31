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
void Delete(int **&ptr);
void Image::setter()
{
	ifstream ifs;
	char buffer[10000];
	char *c;
	int i = 0, j;
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
		for(j = 0; j < width ; ++j)
		{
			pixels[i][j] = strtol(c, &c, 10);
//			cout << setw(4) << pixels[i][j] << " ";
		}
//		cout << endl;
	}
	ifs.close();
}

void Image::outPutFile()
{
//		cout << pixel[0] << endl;
	ofstream ofs;
//	char buffer[100];
//	char *c;
	int i, j;
//	for(i = 0; i < height; ++i)
//		cout << *pixels[i] << endl;
	ofs.open("temp.ascii.pgm", ios_base::out);
	if (ofs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	ofs << "P2" << endl;
	ofs << "# temp.ascii.pgm" << endl;
	ofs << width << " " << height << endl;
//	cout<<width<<height;
	ofs << graylevel << endl;
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			ofs << getPixel(i,j) << " ";
//			cout<<getPixel(i,j)<<" ";
		}
//		cout<<endl;
		ofs << endl;
	}
	ofs.close();
}

void Image::negative()
{
	int i, j;
//	int **matrix = pic.getterPixels();
//	cout << matrix << endl;
//	cout << pic.getterPixels() << endl;
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			pixels[i][j] = graylevel - pixels[i][j];
////			matrix[i][j] = graylevel - matrix[i][j];
////			pic.setPixel(graylevel-pic.getPixel(i,j),i,j);
//			cout << setw(4) << pixels[i][j];
		}
//		cout << endl;
	}
//	pic.setPixels(matrix);
//	cout << matrix << endl;
//	Delete(matrix);
}

void Image::setPixels(int **matrix)
{
	int i, j;
	for(i = 0; i < height; ++i)
		for(j = 0; j < width; ++j)
			pixels[i][j] = matrix[i][j];
}

void Delete(int **&ptr)			
{
	int i;
	for (i = 0; i < 3; ++i)
		delete[] ptr[i];
	delete ptr;
}

