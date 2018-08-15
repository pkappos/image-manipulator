#include "FilterLinear.h"

using namespace math;

namespace imaging
{
	FilterLinear::FilterLinear(Color a, Color c) : a(a), c(c)
	{

	}


	FilterLinear::~FilterLinear()
	{
	}

	Image FilterLinear::operator << (imaging::Image& inpImage) {
		Image im(inpImage.getWidth(), inpImage.getHeight());

		for (unsigned int i = 0; i < inpImage.getWidth(); i++) {
			for (unsigned int j = 0; j < inpImage.getHeight(); j++) {
				im(i, j).r = a.r * inpImage(i, j).r + c.r;
				im(i, j).g = a.g * inpImage(i, j).g + c.g;
				im(i, j).b = a.b * inpImage(i, j).b + c.b;
			}
		}
		return im;
	}
}