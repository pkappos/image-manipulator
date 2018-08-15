#include "FilterGamma.h"
#include <math.h>

using namespace std;

namespace imaging {
	FilterGamma::FilterGamma(float g) : g(g)
	{

	}


	FilterGamma::~FilterGamma()
	{
	}

	Image FilterGamma::operator << (imaging::Image& inpImage) {
		Image im(inpImage.getWidth(), inpImage.getHeight());

		for (unsigned int i = 0; i < inpImage.getWidth(); i++) {
			for (unsigned int j = 0; j < inpImage.getHeight(); j++) {
				im(i, j).r = pow(im(i, j).r, g);
				im(i, j).g = pow(im(i, j).g, g);
				im(i, j).b = pow(im(i, j).b, g); 
			}
		}
		return im;
	}
}