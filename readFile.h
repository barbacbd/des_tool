#ifndef _READ_FILE_H
#define _READ_FILE_H
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Common.h"
#include <algorithm>
#include <limits>
#include <vector>

#include "printStructs.h"

#ifdef _DEBUG_PRG
std::string type_toString(struct Event e);
#endif

void readFile(std::string fileName, struct System_Information *info);


#endif