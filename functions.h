#pragma once
#include<iostream>
#include<cstring>
#include"class.h"
#include"config.h"
#define Round(a)  int(a+0.5)
using namespace std;
int c_a_r(char td [][50])
{
	int i;
	for(i = 0; td[i][0] != NULL; ++i);
	return i;
}

void Normal () {
	SetColor(WHITE);
	SetBGColor(0);
}

void HighLight () {
	SetColor(15);
	SetBGColor(1);
}

int MenuDong(char td [][50]) {
	Normal();
	system("cls");
	cout << "\t\t==============Image proccessing==============";
	int chon =0, so_item;
	int i;
	so_item = c_a_r(td);
	for ( i=0; i< so_item ; i++) {
		gotoxy(cot, dong +i);
		cout << td[i];
	}
	HighLight();
	gotoxy(cot,dong+chon);
	cout << td[chon];
	char kytu;
	do {
		kytu = getch();
		if (kytu == 0) kytu = getch();
		switch (kytu) {
			case Up :
				if (chon+1 >1) {
					Normal();
					gotoxy(cot,dong+chon);
					cout << td[chon];
					chon --;
					HighLight();
					gotoxy(cot,dong+chon);
					cout << td[chon];

				}
				break;
			case Down :
				if (chon + 1 <so_item) {
					Normal();
					gotoxy(cot,dong+chon);
					cout << td[chon];
					chon ++;
					HighLight();
					gotoxy(cot,dong+chon);
					cout << td[chon];
				}
				break;
			case 13 :
				return chon+1;
			case 27:
				system("cls");
				return 0;
		}  // end switch
	} while (1);
}
void Delete(int **&ptr);
void Image::setter(char *filename)
{
	ifstream ifs;
	char buffer[100];
	char *c;
	int i = 0, j;
	ifs.open(filename, ios_base::in);
	if (ifs.fail()==true)
	{
		cout << "Failed to open this file" << endl;
		Sleep(1500);
		return;
	}
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
		for(j = 0; j < width ; ++j)
		{
			ifs >> pixels[i][j];
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
			pixels[i][j-1] + pixels[i+1][j+1] + pixels[i-1][j+1] + pixels[i-1][j-1] + pixels[i+1][j-1])/9;
//	Delete(pixels);
}

void Filter::laplacian(Image &pic)
{
	int i, j, w, h, g, **matrix, filter[3][3] = {0};
	w = pic.getterWidth();
	h = pic.getterHeight();
	g = pic.getterGrayLevel();
	width = w+2;
	height = h+2;
	pixels = new int*[height];
	for(i = 0; i < height; ++i)	pixels[i] = new int[width];
	matrix = pic.getterPixels();
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
	filter[0][1] = -1;	filter[1][0] = -1;	filter[1][2] = -1;	filter[2][1] = -1;
	filter[1][1] = 4;
	for(i = 1; i < height - 1; ++i)
		for(j = 1; j < width - 1; ++j)
		{
			matrix[i-1][j-1] = pixels[i][j]*filter[1][1] + pixels[i-1][j]*filter[0][1] + pixels[i+1][j]*filter[2][1] + pixels[i][j+1]*filter[1][2] + 
			pixels[i][j-1]*filter[1][0] + pixels[i+1][j+1]*filter[2][2] + pixels[i-1][j+1]*filter[0][2] + pixels[i-1][j-1]*filter[0][0] + pixels[i+1][j-1]*filter[2][0];
			if(matrix[i-1][j-1] < 0)
				matrix[i-1][j-1] = pixels[i][j] - matrix[i-1][j-1];
			else
				matrix[i-1][j-1] += pixels[i][j];
		}
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

