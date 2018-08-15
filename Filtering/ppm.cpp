#include "ppm.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


using namespace std;

namespace imaging {

	float * ReadPPM(const char * filename, int * w, int *h) {

		ifstream iFile(filename, ios::binary);
		string imgFormat;
		unsigned int max;
		unsigned int W = *w;
		unsigned int H = *h;

		bool proceed = true;
		if (!iFile.is_open()) {
			cerr << "Error opening the file.. Maybe file missing or name of file is wrong" << endl;
			return nullptr;
		}

		iFile >> imgFormat >> W >> H >> max;

		if (imgFormat.compare("P6") != 0) {
			cout << "This is our known ppm format";
			proceed = false;
		}
		if (max != 255) {
			cerr << "Error at maximum range of colors " << endl;
			proceed = false;
		}

		if (proceed == true) {
			iFile.get(); // skip blank after max

			int size = W * H * 3;
			float * flBuffer = new float[size]; //need a buffer for components
			unsigned char * temp = new unsigned char[size]; //need a temp buffer 
			iFile.read((char*)temp, size);

			for (int i = 0; i < size; i++) {
				flBuffer[i] = temp[i] / 255.0f;
			}

			iFile.close();

			delete[] temp;

			*w = W;
			*h = H;

			return flBuffer;
		}
		else {
			return nullptr;
		}
	}

	bool WritePPM(const float * data, int w, int h, const char * filename) {
		string imgFormat = "P6";
		ofstream output;
		output.open(filename, ios::binary | ios::out);
		bool write = true;

		if (!output.is_open()) {
			cerr << "Error opening img file to write...." << endl;
			write = false;
		}

		if (write) {

			unsigned int size = w * h * 3;

			unsigned char * temp = new unsigned char[size]; //need a temp buffer 

			for (unsigned int i = 0; i < size; i++) {
				temp[i] = (unsigned char)(data[i] * 255.0f);
			}

			output << imgFormat << "\n" << w << "\n" << h << "\n" << 255 << "\n";

			output.write((char*)temp, size);

			output.close();
		}

		return write;

	}
}