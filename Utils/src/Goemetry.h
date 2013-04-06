#pragma once

#include <string>

#include "platform_config.h"
# if defined(WINDOWS_PLATFORM)
#	include <windows.h>
# endif

class pointf
{
public:
	pointf(float x = 0, float y = 0);
# if defined(WINDOWS_PLATFORM)
	pointf(POINT point);
# endif

	void display(std::string name);

	float x;
	float y;
};

class rect
{
public:
	rect(int left = 0, int top = 0, int right = 0, int bottom = 0);
# if defined(WINDOWS_PLATFORM)
	rect(RECT rect);
# endif

	void display(std::string name);
	int get_width() const;
	void set_width(int width);
	int get_height() const;
	void set_height(int height);

	int left;
	int top;
	int right;
	int bottom;
};