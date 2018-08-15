#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

#include <iostream>

using namespace std;

namespace math {

	template <typename T>
	class Array {
	protected:
		std::vector<T> buffer;
		unsigned int width, height;
	public:
		unsigned int getWidth() const { return width; }
		unsigned int getHeight() const { return height; }

		T * getRawDataPtr() {
			return this->buffer.data();
		}

		T getElementByCoordinates(unsigned int x, unsigned int y) const {
			T returnColor;

			if ((x > width - 1) || (y > height - 1)) {
				return returnColor;
			}

			int pixel = (x + y * (width));

			returnColor = buffer[pixel];

			return returnColor;
		}


		void setElementByCoordinates(unsigned int x, unsigned int y, T & value) {
			if ((x > width - 1) || (y > height - 1)) {
				return;
			}
			else {
				int pixel = (x + y * (width));

				buffer[pixel] = value;
			}
		}

		void setData(const T *  & data_ptr) {

			if (buffer.size != 0) {
				for (int i = 0; i < width*height; i++) {
					buffer[i] = data_ptr[i];
				}
			}
		}

			//Constructors Area

			Array() : width(0), height(0) {}

			Array(unsigned int newWidth, unsigned int newHeight) {
				this->width = newWidth;
				this->height = newHeight;

				buffer.resize(newWidth*newHeight);
			}

			Array(unsigned int w, unsigned int h, std::vector<T> & data_ptr) : width(w), height(h) {
				this->buffer = data_ptr;
			}

			//Copy c-tor
			Array(const Array<T> & src) {
				this->width = src.width;
				this->height = src.height;
				buffer.resize(width * height);
				for (unsigned int i = 0; i < width * height; i++) {
					buffer[i] = src.buffer[i];
				}
			}

			//End of Constructors

			virtual ~Array() {

			}

			//Copy assignment operator
			Array<T> & operator=(const Array<T> & right) {

				if (this != &right)                                 
				{
					this->width = right.width;
					this->height = right.height;
					buffer.resize(right.width*right.height);
					for (unsigned int i = 0; i < width*height; i++) {
						buffer[i] = right.buffer[i];                    
					}
				}
				return *this;
			}

			T & operator()(unsigned int x, unsigned int y) //where x and y are the coordinates of the pixel
			{
				if (x >= width || y >= height) {
					cout << "Error x and y are coordinated out of bounds " << endl;
				}
				return buffer[y * width + x];
			}
		};
	}
#endif // !ARRAY_H