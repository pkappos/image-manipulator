#pragma once
#include "Filter.h"

namespace imaging
{
	class FilterGamma :
		public Filter
	{
	private:
		float g;
	public:
		FilterGamma(float g);
		~FilterGamma();

		virtual Image operator << (imaging::Image& inpImage);
	};
}