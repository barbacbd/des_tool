#include "stdafx.h"
#include "geometry.h"

/* get the area of the triangle */
float area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
}

/* check if the x-y combo is inside of the arrow */
bool in_arrow(arrow a, int x, int y) 
{
	float t = 0.0, t1 = 0.0, t2 = 0.0, t3 = 0.0;

	if (a.dir == 0) 
	{
		// area of triangle abc
		t = area(a.b.xmin, a.b.ymin, (a.b.xmax + a.b.xmin) / 2.0, a.b.ymax,
			a.b.xmax, a.b.ymin);
		// area of x-y bc
		t1 = area(x, y, (a.b.xmax + a.b.xmin) / 2.0, a.b.ymax,
			a.b.xmax, a.b.ymin);
		// area of x-y ac
		t2 = area(a.b.xmin, a.b.ymin, x, y, a.b.xmax, a.b.ymin);
		// area of x-y ab
		t3 = area(a.b.xmin, a.b.ymin, (a.b.xmax + a.b.xmin) / 2.0, a.b.ymax, x, y);

	}
	else 
	{ // face down

		   // area of triangle abc
		t = area(a.b.xmin, a.b.ymax, (a.b.xmax + a.b.xmin) / 2.0, a.b.ymin,
			a.b.xmax, a.b.ymax);
		// area of x-y bc
		t1 = area(x, y, (a.b.xmax + a.b.xmin) / 2.0, a.b.ymin,
			a.b.xmax, a.b.ymax);
		// area of x-y ac
		t2 = area(a.b.xmin, a.b.ymax, x, y, a.b.xmax, a.b.ymax);
		// area of x-y ab
		t3 = area(a.b.xmin, a.b.ymax, (a.b.xmax + a.b.xmin) / 2.0, a.b.ymin, x, y);
	}
	return (t == t1 + t2 + t3);
}

/* check if the x-y combo is inside of the button parameters */
bool in_button(button b, int x, int y)
{
	return (x >= b.xmin && x <= b.xmax && y >= b.ymin && y <= b.ymax);
}
