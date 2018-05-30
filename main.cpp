#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
using namespace std;
class Image
{
	private:
		int width;
		int height;
		int graylevels;
		int **pixels;
	public:
		Image()
		{
			int i, j;
			width = 0;
			height = 0;
			graylevels = 0;
		}
		~Image()
		{
			int i;
			for (i = 0; i < height; ++i)
				delete[] pixels[i];
			delete pixels;
		}
		void setter();
};
class Filter
{
	private:
		int width;
		int height;
		char **matrix;
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
				delete[] matrix[i];
			delete matrix;
		}
};
int main()
{
	Image haha;
	haha.setter();
	return 0;
}

void Image::setter()
{
	ifstream ifs;
	char buffer[10000];
	char *c;
	int i = 0, j, k;
	ifs.open("E:\\Personal\\HTG Locker\\Tai_lieu_hoc_tap\\Lap-trinh-huong-doi-tuong\\Bai-cuoi-ky\\feep.ascii.pgm", ios_base::in);
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
	graylevels = atoi(buffer);
	pixels = new int*[height];
	for(i = 0; i < height; ++i)	pixels[i] = new int[width];
	for(i = 0; i < height; ++i)
	{
		ifs.getline(buffer, 10000, '\n');
		c = &buffer[0];
		for(k = 0; k < width ; ++k)
		{
			pixels[i][k] = strtol(c, &c, 10);
			cout << setw(4) << pixels[i][k] << " ";
		}
		cout << endl;
	}
	ifs.close();
}
