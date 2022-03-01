
#include <iostream>

#include "House.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

House::House(const std::array<char, width_h * height_h>& look) {
	std::copy_n(look.begin(), look.size(), static_cast<char*>(*this->look));
}

bool House::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}


void House::Draw() const
{
	MyTools::SetColor(CC_Yellow);
	int value = 6;
	GotoXY(x, y - value);
	for (int i = 0; i < height_h; i++) {
		for (int j = 0; j < width_h; j++)
		{
			cout << look[i][j];
		}
		value--;
		GotoXY(x, y - value);

	}
}

