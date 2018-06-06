#pragma once
#include<iostream>
#include<cstring>
#include"class.h"
#define Round(a)  int(a+0.5)
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
		}
	}
	ifs.close();
}

void Image::outPutFile()
{
	ofstream ofs;
	int i, j;
	ofs.open("temp.ascii.pgm", ios_base::out);
	if (ofs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	ofs << "P2" << endl;
	ofs << "# temp.ascii.pgm" << endl;
	ofs << width << " " << height << endl;
	ofs << graylevel << endl;
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			ofs << getPixel(i,j) << " ";
		}
		ofs << endl;
	}
	ofs.close();
}

void Filter::negative(Image &pic)
{
	int i, j, w, h, g;
	w = pic.getterWidth();
	h = pic.getterHeight();
	g = pic.getterGrayLevel();
	int **matrix = pic.getterPixels();
	for(i = 0; i < h; ++i)
		for(j = 0; j < w; ++j)
			matrix[i][j] = g - matrix[i][j];
}

void Filter::logarite(Image &pic)
{
	int i, j, w, h, g;
	w = pic.getterWidth();
	h = pic.getterHeight();
	g = pic.getterGrayLevel();
	int **matrix = pic.getterPixels();
	for(i = 0; i < h; ++i)
		for(j = 0; j < w; ++j)
			matrix[i][j] = Round(log(1 + matrix[i][j]));
}

void Filter::histogram(Image &pic)
{
	int i, j, w, h, g, sumpixel;
	w = pic.getterWidth();
	h = pic.getterHeight();
	g = pic.getterGrayLevel();
	int **matrix = pic.getterPixels();
	float p[g+1] = {0};
	for(i = 0; i < h; ++i)
		for(j = 0; j < w; ++j)
			++p[matrix[i][j]];
	sumpixel = w * h;
	for(i = 0; i < g+1; ++i)
	{
		p[i] = p[i]*1.0/sumpixel;
		if(i != 0)
			p[i] += p[i-1];
	}
	for(i = 0; i < h; ++i)
		for(j = 0; j < w; ++j)
			matrix[i][j] = Round(p[matrix[i][j]] * g);
}

void Filter::smoothing(Image &pic)
{
	int i, j, w, h, g;
	w = pic.getterWidth();
	h = pic.getterHeight();
	g = pic.getterGrayLevel();
	width = w+2;
	height = h+2;
	pixels = new int*[height];
	for(i = 0; i < height; ++i)	pixels[i] = new int[width];
	int **matrix = pic.getterPixels();
	for(i = 0; i < h; ++i)
	{
		j = 0;
		pixels[i+1][j] = matrix[i][j];		//j = 0
		for(; j < w; ++j)
		{
			pixels[i+1][j+1] = matrix[i][j];
			if(i == 0)
				pixels[i][j+1] = matrix[i][j];
			else if(i == h - 1)
				pixels[i+2][j+1] = matrix[i][j];
		}
		pixels[i+1][j+1] = matrix[i][j-1]; //j = w
	}
	pixels[0][0] = matrix[0][0];
	pixels[0][width - 1] = matrix[0][w - 1];		
	pixels[height - 1][0] = matrix[h - 1][0];
	pixels[height - 1][width - 1] = matrix[h - 1][w - 1];
	for(i = 1; i < height - 1; ++i)
		for(j = 1; j < width - 1; ++j)
			matrix[i-1][j-1] = (pixels[i][j] + pixels[i-1][j] + pixels[i+1][j] + pixels[i][j+1] + 
			pixels[i][j+1] + pixels[i+1][j+1] + pixels[i-1][j+1] + pixels[i-1][j-1] + pixels[i+1][j-1])/9;
	Delete(pixels);
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

