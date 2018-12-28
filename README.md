# DES_TOOL

The project that was originally created in Visual Studio as a tool for DES Simulations. While I was learning
about Discrete Event Simultion, I was taught to manually simulate Discrete Event Systems. I noticed that these
systems were thrown off and many errors occured with one minor mistake. I decided that it could be useful for
others learning in this field, to see where they may have made a mistake or just to check their work. While the
systems are easy for users to introduce errors, the systems are deterministic. The deterministic nature of these
systems means that automating the work using a computer is much simpler.

> The user will be required to install OpenGL on their system.

## Opengl

The opengl subdirectory contains a makefile to make the opengl gui version of the project. The opengl version 
of the project was the prototype, but a newer version has been constructed using Qt. 

## Qt

The src subdirectory contains the newer version of the code. The new code is based off of Qt. 

In order to build this version of the code

- mkdir build;
- cd build;
- cmake ..;
- make;

The name of the executable is des_tool. 

This is not a library so there is no need to install any of the files sudo a make install.

## Future Work

- read in JSON files
- convert all structs to objects