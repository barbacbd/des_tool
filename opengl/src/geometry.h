#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <string.h>
#include "Common.h"
#include <vector>
#include "Simulate.h"
#include "printStructs.h"
#include "utility.h"
#include "states.h"
#include "main.h"
#include <vector>


bool in_button(button b, int x, int y);
bool in_arrow(arrow a, int x, int y);
float area(int x1, int y1, int x2, int y2, int x3, int y3);

#endif
