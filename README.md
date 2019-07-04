# DES_TOOL

While I was learning about Discrete Event Simulation (DES), I was taught to manually simulate Discrete Event Systems. 
I noticed that these systems were thrown off easily, and many errors occurred with one minor mistake. I thought that
it could be useful for others (learning simulations), to see where they may have made a mistake or just to check 
their work. While the systems are easy for users to introduce errors, the systems are deterministic. The deterministic 
nature of these systems means that automating the work using a computer is much simpler.


## Qt

This project was built using Qt. Originally, the project consisted of opengl code. The Qt
version is quite a bit of a visual upgrade. 

> The system was tested with Qt 5.11 and Qt 5.9

## Simulation Files

These simulation files were created using the ConfigCreator tool. The files will be installed during a
local installation. The files will be placed into the same directory that the executable is created.

```
simulation/des.json
```

In the event that more simulation files should be added to this project the base CMakelists.txt file
should be altered to ensure the new simulation files are installed.

```
add_custom_command(
        TARGET des_tool POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/simulations/des.json
        ${CMAKE_CURRENT_BINARY_DIR}/des.json)
```

This snippet shows how the des.json file is copied to the local installation location.

## External dependencies

In python, the user has the ability to 
```python
import qdarkstyle
```

but C++ requires that the user include the project. There is a ```QDarkStyleSheet``` project that was pulled directly
from the hosted github. I followed the instructions to include the project as a part of mine.

## Build

```
mkdir build
cd build
cmake ..
make -j4
```

## Run

To run the example program, please build the project first. After building the project,
run the executable ```./des_tool```. Select ```file``` then ```open``` and pass the simulation file
that was described in the simulation files.