#include "Image.h"
#include "ppm.h"
#include "Color.h"
#include <string>
#include <iostream>

using namespace std;
using namespace math;

#include "Array.h"

namespace imaging {

	//Constructors inhereted by Array class

	Image::Image()  {

	}


	Image::Image(unsigned int w, unsigned int h) : Array<Color>(w, h) {
		
	}

	

	Image::Image(unsigned int w, unsigned int h, std::vector<Color> & data_ptr) : Array<Color>(w, h, data_ptr)  {

	}

	Image::Image(const Image &src) : Array(src) {
		
	}

	

	bool Image::load(const std::string & filename, const std::string & format) {
		int w, h;
		const char * input = filename.c_str();
		float * floatbuffer = ReadPPM(input, &w, &h); //Calling ReadPPM
		float * p = floatbuffer;

		bool loaddone = true;

		cout << "#####" << endl;
		cout << "w= " << w << endl;
		cout << "h= " << h << endl;

		if (floatbuffer == NULL) {
			loaddone = false;
		}

		if (loaddone == true) {
			
			buffer.resize(w*h);

			Color * colorBuffer = new Color();

			for (unsigned int i = 0; i < buffer.size(); i++) {
				colorBuffer->r = *p;
				p++;
				colorBuffer->g = *p;
				p++;
				colorBuffer->b = *p;
				p++;				
				
				buffer[i] = *colorBuffer;
			}

			delete colorBuffer;

			width = w;
			height = h;

			delete[] floatbuffer;
		}

		return loaddone;
	}

	bool Image::save(const std::string & filename, const std::string & format) {
		int w = width, h = height;
		const char * output = filename.c_str();

		const Color * data_ptr = getRawDataPtr();
		Color * colorBuffer = getRawDataPtr();

		float * floatbuffer = new float[3 * w*h];
		float * p = floatbuffer;



		for (int i = 0; i < w*h; i++) {
			*p = colorBuffer->r;
			p++;
			*p = colorBuffer->g;
			p++;
			*p = colorBuffer->b;
			p++;
		}

		bool writedone = WritePPM(floatbuffer, w, h, output);

		delete[] floatbuffer;

		return writedone;
	}
}