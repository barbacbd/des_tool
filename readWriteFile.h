#ifndef _READ_WRITE_FILE_H
#define _READ_WRITE_FILE_H
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

void readFile(std::string fileName, struct System_Information *info);
void generate_reports(System_Information *info);

#endif