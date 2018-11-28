CC = gcc
LDLIBS = -lglut -lGL -lGLU -lglut -lm


des_tool: button.cpp draw.cpp geometry.cpp main.cpp printStructs.cpp readWriteFile.cpp Simulate.cpp statistics.cpp utility.cpp
	$(CC) -std=c++11 -o des_tool button.cpp draw.cpp geometry.cpp main.cpp printStructs.cpp readWriteFile.cpp Simulate.cpp statistics.cpp utility.cpp $(LDLIBS) -lstdc++
