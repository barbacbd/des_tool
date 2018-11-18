#ifndef _BUTTON_H
#define _BUTTON_H

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
#include "states.h"
#include "main.h"
#include <vector>


void button_pos_setup(button &b, char *text, float xmin,
	float xmax, float ymin, float ymax);
void set_colors();
void button_setup();

#endif