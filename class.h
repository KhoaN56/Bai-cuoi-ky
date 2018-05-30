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
};
class Negative : Filter
{
	public:
		void transform(Image);
};
