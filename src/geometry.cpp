#include "goemetry.h"

#include "logger/console_logger.h"

auto logger = ConsoleLogger(DEBUG);

/////////////////////////////////////////////////////////
// pointf
/////////////////////////////////////////////////////////
pointf::pointf(float _x, float _y)
	: x(_x), y(_y) { }

# if defined(WINDOWS_PLATFORM)
pointf::pointf(POINT point)
	: x((float)point.x), y((float)point.y) { }
# endif

void pointf::display(std::string name)
{
	logger.Debug("Displaying " + name);
	logger.Debug("(" + std::to_string(x) + "; " + std::to_string(y) + ")");
}

/////////////////////////////////////////////////////////
// Rect
/////////////////////////////////////////////////////////
rect::rect(int _left, int _top, int _right, int _bottom)
	: left(_left), top(_top), right(_right),  bottom(_bottom) { }

# if defined(WINDOWS_PLATFORM)
rect::rect(RECT rect)
	: left(rect.left), top(rect.top), right(rect.right),  bottom(rect.bottom) { }
# endif

void rect::display(std::string name)
{
	logger.Debug("Displaying " + name);
	logger.Debug(" - Position : "
		+ std::to_string(left) + ", "
		+ std::to_string(top) + ", "
		+ std::to_string(right) + ", "
		+ std::to_string(bottom));
	logger.Debug(" - Dimensions : " + std::to_string(get_width()) + "x" + std::to_string(get_height()));
}

int rect::get_width() const
{
	return right - left;
}

void rect::set_width(int width)
{
	right = left + width;
}

int rect::get_height() const
{
	return bottom - top;
}

void rect::set_height(int height)
{
	bottom = top + height;
}
