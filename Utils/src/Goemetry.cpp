#include "Goemetry.h"

#include "Utils.h"

/////////////////////////////////////////////////////////
// PointF
/////////////////////////////////////////////////////////
PointF::PointF(float _x, float _y) : x(_x), y(_y) 
{
}

# if defined(WINDOWS_PLATFORM)
PointF::PointF(POINT point) :  x((float)point.x), y((float)point.y)
{
}
# endif

void PointF::display(std::string name)
{
	Utils::getLogger()->debug("Displaying " + name);
	Utils::getLogger()->debug("(" + std::to_string(x) + "; " + std::to_string(y) + ")");
}

/////////////////////////////////////////////////////////
// Rect
/////////////////////////////////////////////////////////
Rect::Rect(int _left, int _top, int _right, int _bottom) : left(_left), top(_top), right(_right), bottom(_bottom)
{
}

# if defined(WINDOWS_PLATFORM)
Rect::Rect(RECT rect) : left(rect.left), top(rect.top), right(rect.right), bottom(rect.bottom)
{
}
# endif

void Rect::display(std::string name)
{
	Utils::getLogger()->debug("Displaying " + name);
	Utils::getLogger()->debug(" - Position : "
		+ std::to_string(left) + ", "
		+ std::to_string(top) + ", "
		+ std::to_string(right) + ", "
		+ std::to_string(bottom));
	Utils::getLogger()->debug(" - Dimensions : " + std::to_string(getWidth()) + "x" + std::to_string(getHeight()));
}

int Rect::getWidth()
{
	return right - left;
}

void Rect::setWidth(int width)
{
	right = left + width;
}

int Rect::getHeight()
{
	return bottom - top;
}

void Rect::setHeight(int height)
{
	bottom = top + height;
}
