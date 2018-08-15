#ifndef _FILTER
#define _FILTER

#include "Image.h"
#include <string>

namespace imaging
{
	
class Filter
{
public:

	Filter ();
	virtual ~Filter();

	// Apply the filter
	virtual Image operator << (imaging::Image& inpImage) = 0;
};

}
#endif