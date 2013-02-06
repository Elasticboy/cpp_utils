#include "Goemetry.h"

#include <iostream>

using namespace std;

/////////////////////////////////////////////////////////
// PointF
/////////////////////////////////////////////////////////
PointF::PointF(float _x, float _y) : x(_x), y(_y) 
{
}

PointF::PointF(POINT point) :  x((float)point.x), y((float)point.y)
{
}

void PointF::display(string _name)
{
	cout << "Displaying " << _name.c_str() << endl;
	cout << "(" << x << "; " << y	<< ")" << endl << endl;
}

/////////////////////////////////////////////////////////
// Rect
/////////////////////////////////////////////////////////
Rect::Rect(int _left, int _top, int _right, int _bottom) : left(_left), top(_top), right(_right), bottom(_bottom)
{
}

Rect::Rect(RECT rect) : left(rect.left), top(rect.top), right(rect.right), bottom(rect.bottom)
{
}

void Rect::display(string _name)
{
	cout << "Displaying " << _name.c_str() << endl;
	cout << " - Position : "	<< left	<< ", "	<< top << ", ";
	cout << right << ", "	<< bottom << endl;
	cout << " - Dimensions : "	<< getWidth() << "x" << getHeight() << endl << endl;
}

int Rect::getWidth()
{
	return right - left;
}

void Rect::setWidth(int _width)
{
	right = left + _width;
}

int Rect::getHeight()
{
	return bottom - top;
}

void Rect::setHeight(int _height)
{
	bottom = top + _height;
}
