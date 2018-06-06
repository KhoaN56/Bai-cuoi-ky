#pragma once
#include<iostream>
class Matrix
{
	protected:
		int width;
		int height;
		int **pixels;
	public:
		void setter(int , int);
};
class Image : Matrix
{
	private:
		int graylevel;
	public:
		Image()
		{
			width = 0;
			height = 0;
			graylevel = 0;
		}
		~Image()
		{
			int i;
			for (i = 0; i < height; ++i)
				delete[] pixels[i];
			delete pixels;
		}
		void setter();
		void setPixels(int **matrix);
		void setPixel(int value, int x, int y)	{pixels[x][y] = value;}
		int getPixel(int x, int y)	{return this->pixels[x][y];}
		void outPutFile();
//		int getPixel()	{return pixels[0][0];}
		int getterWidth() {return width;}
		int getterHeight()	{return height;}
		int getterGrayLevel()	{return graylevel;}
		int **getterPixels()	{return pixels;}
};
class Filter : Matrix
{
	public:
		Filter()
		{
			width = 0;
			height = 0;
		}
		~Filter()
		{
			int i;
			for (i = 0; i < height; ++i)
				delete[] pixels[i];
			delete pixels;
		}
		void negative(Image&);
		void logarite(Image&);
		void histogram(Image&);
};
