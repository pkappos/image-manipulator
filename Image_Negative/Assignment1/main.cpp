#include <iostream>
#include <string>

#include "Image.h"

using namespace imaging;
using namespace std;

int main(int argc, char* argv[]) {
	const char* file;
	char * outputfile;
	char * p;
	string input;

	if (argc <= 1) {
		cout << "File name of the image to load : ";
		cin >> input;
		file = input.c_str();
		
	} else {
		file = argv[1];
	}

	Image* img = new Image();

	if (img != nullptr) {
		img->load(file, "ppm");

		cout << "Image dimensions are: " << img->getWidth() << " X " << img->getHeight() << endl;
		
		Color * buffer = img->getRawDataPtr();
		
		int size = img->getHeight()*img->getWidth();
		
		for (int i = 0; i < size; i++) {
			float r = buffer[i].r;
			float g = buffer[i].g;
			float b = buffer[i].b;

			buffer[i].r = 1.0f - r;
			buffer[i].g = 1.0f - g;
			buffer[i].b = 1.0f - b;
		}

		outputfile = new char[strlen(file) + 4 + 1];
		strncpy_s(outputfile, strlen(file) + 4 + 1, file, strlen(file));
		p = outputfile;

		while (*p != '.') {
			p++;
		}

		*p = '\0';
		strcat_s(outputfile, strlen(file) + 4 + 1,  "_neg.ppm");

		img->save(outputfile, "ppm");
	} else {
		cout << "out of memory" << endl;
	}

	system("pause");

	return 0;
}