#include "../ppm/ppm.h"
#include "Image.h"
#include <iostream>


using namespace std;

namespace imaging {

	//Creates 2 ptrs and copy to buffer
	void Image::setData(const Color * & data_ptr) {
		std::memcpy(buffer, data_ptr, ((sizeof Color)*width*height));
	}

	//thisImg = otherImg
	Image & Image:: operator = (const Image & right) {
		if (buffer != nullptr) {
			delete[] buffer;
		}
		height = right.height;
		width = right.width;

		const Color * data_ptr = right.buffer;
		buffer = new Color[height*width];
		setData(data_ptr);

		return *this;
	}

	//returns buffer img
	Color * Image::getRawDataPtr() {
		return buffer;
	}


	Color Image::getPixel(unsigned int x, unsigned int y) const {
		Color returnColor;

		if ((x > width - 1) || (y > height - 1)) {
			returnColor.r = 0;
			returnColor.g = 0;
			returnColor.b = 0;
			return returnColor;
		}

		int pixel = (x + y*(width));
		float r = buffer[pixel].r;
		float g = buffer[pixel].g;
		float b = buffer[pixel].b;

		returnColor.r = r;
		returnColor.g = g;
		returnColor.b = b;

		return returnColor;
	}

	void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
		if ((x > width - 1) || (y > height - 1)) {
			return;
		} else {		
			int pixel = (x + y*(width));

			buffer[pixel].r = value.r;
			buffer[pixel].g = value.g;
			buffer[pixel].b = value.b;						
		}
	}

	Image::Image() : width(0), height(0), buffer(nullptr) {
	
	}

	Image::Image(unsigned int width, unsigned int height) : width(width), height(height), buffer(new Color[width*height]) {
	}

	Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) : width(width), height(height) {
		buffer = new Color[width * height];
		setData(data_ptr); //ask nikos
	}

	Image::Image(const Image &src) : width(src.width), height(src.height) {
		const Color * data_ptr = src.buffer;
		buffer = new Color[width * height];
		setData(data_ptr);		
	}

	Image::~Image() {
		if (buffer == nullptr) {
			delete[] buffer;
		}
	}

	bool Image::load(const std::string & filename, const std::string & format) {
		int w, h;
		const char * input = filename.c_str();
		float * floatbuffer = ReadPPM(input, &w, &h);
		float * p = floatbuffer;

		bool loaddone = true;

		if (floatbuffer == NULL) {
			loaddone = false;
		}

		if (loaddone == true) {
			if (buffer != nullptr) {
				delete[] buffer;
			}

			Color * colorBuffer = new Color[w*h];
			Color * data_ptr = colorBuffer;

			for (int i = 0; i < w*h; i++) {
				colorBuffer->r = *p;
				p++;
				colorBuffer->g = *p;
				p++;
				colorBuffer->b = *p;
				p++;
				colorBuffer++;
			}
			
			width = w;
			height = h;
			buffer = data_ptr;

			delete [] floatbuffer;
		}

		return loaddone;
	}

	bool Image::save(const std::string & filename, const std::string & format) {
		int w = width, h = height;
		const char * output = filename.c_str();

		const Color * data_ptr = buffer;
		Color * colorBuffer = buffer;

		float * floatbuffer = new float[3 * w*h];
		float * p = floatbuffer;

		

		for (int i = 0; i < w*h; i++) {
			*p = colorBuffer->r;
			p++;
			*p = colorBuffer->g;
			p++;
			*p = colorBuffer->b;
			p++;
			colorBuffer++;
		}
		
		bool writedone = WritePPM(floatbuffer, w, h, output);

		delete[] floatbuffer;

		return writedone;
	}

}