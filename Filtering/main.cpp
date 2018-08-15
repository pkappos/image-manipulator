#include <iostream>
#include <string>
#include "Filter.h"
#include "FilterLinear.h"
#include "FilterGamma.h"
#include "Image.h"

using namespace imaging;
using namespace std;

int main(int argc, char* argv[]) {
	const char* file;
	char * outputfile;
	char * p;
	string input;

	int i = 1;

	if (argc == 1)
	{
		cerr << "Low number of input, try again" << endl;
		exit(1);
	}

	file = argv[argc - 1];

	
	std::cout << "Initializing image ... " << endl;

	Image* img = new Image();
	Image tempImage;

	if (img != nullptr) {
		std::cout << "Loading ppm ... " << endl;

		img->load(file, "ppm");

		std::cout << "Image dimensions are: " << img->getWidth() << " X " << img->getHeight() << endl;

		tempImage = *img;
		cout << "Temp img width : " << tempImage.getWidth() << " and height : " << tempImage.getHeight() <<  endl; 


		while (i < argc) {
			if (strcmp(argv[i], "-f") == 0) {
				i++;

				if (strcmp(argv[i], "gamma") == 0) {
					i++;
					float gamma = (float) atof(argv[i]);

					FilterGamma f(gamma);

					std::cout << "Applying gamma " << gamma << endl;
					tempImage = f << tempImage;
				}

				if (strcmp(argv[i], "linear") == 0) {
					Color a;
					Color c;

					i++;
					a.r = (float) atof(argv[i]);
					i++;
					a.g = (float)atof(argv[i]);
					i++;
					a.b = (float)atof(argv[i]);
					i++;
					c.r = (float)atof(argv[i]);
					i++;
					c.g = (float)atof(argv[i]);
					i++;
					c.b = (float)atof(argv[i]);

					FilterLinear f(a, c);

					std::cout << "Applying linear " << endl;
					tempImage = f << tempImage;
				}

			}
			else {
				i++;
			}
		}

		// create output filename
		outputfile = new char[5000];
		strcpy_s(outputfile, strlen(file) + 4 + 1, file);
		p = outputfile;

		while (*p != '.') {
			p++;
		}

		*p = '\0';
		
		strcat_s(outputfile, 5000, "_filtered.ppm");

		std::cout << "Saving ppm ... " << endl;

		tempImage.save(outputfile, "ppm");

		delete img;
	}
	else {
		std::cout << "out of memory" << endl;
	}



	return 0;
}