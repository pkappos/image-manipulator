#pragma once
#include "Filter.h"

namespace imaging {
	class FilterLinear :
		public Filter
	{
	private:
		Color a;
		Color c;
	public:
		FilterLinear(Color a, Color c);
		~FilterLinear();

		virtual Image operator << (imaging::Image& inpImage);
	};
}

