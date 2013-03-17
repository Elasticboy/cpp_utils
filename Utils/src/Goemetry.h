#pragma once

#include <string>

#include "platform_config.h"
# if defined(WINDOWS_PLATFORM)
#	include <windows.h>
# endif

class PointF
{
public:
	PointF(float x = 0, float y = 0);
# if defined(WINDOWS_PLATFORM)
	PointF(POINT point);
# endif
	void display(std::string name);

	float x;
	float y;
};

class Rect
{
public:
	Rect(int left = 0, int top = 0, int right = 0, int bottom = 0);
# if defined(WINDOWS_PLATFORM)
	Rect(RECT rect);
# endif
	void display(std::string name);
	int getWidth();
	void setWidth(int width);
	int getHeight();
	void setHeight(int height);

	int left;
	int top;
	int right;
	int bottom;
};