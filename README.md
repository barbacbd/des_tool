# DES_TOOL

While I was learning about Discrete Event Simultion (DES), I was taught to manually simulate Discrete Event Systems. 
I noticed that these systems were thrown off easily, and many errors occured with one minor mistake. I though that 
it could be useful for others (learning simulations), to see where they may have made a mistake or just to check 
their work. While the systems are easy for users to introduce errors, the systems are deterministic. The deterministic 
nature of these systems means that automating the work using a computer is much simpler.


## Opengl

The opengl subdirectory contains a makefile to make the opengl gui version of the project. The opengl version 
of the project was the prototype, but a newer version has been constructed using Qt. 

> The user will be required to install OpenGL on their system.

### Simulation Files

```
opengl/test.txt
```

## Qt

The src subdirectory contains the newer version of the code. The new code is based off of Qt. 

In order to build this version of the code

```mkdir build; cd build; cmake ..; make;```

> This is not a library so there is no need to install any of the files sudo a make install.

The name of the executable is des_tool. 

### Simulation Files

```
simulations/des.json
```

## Future Work

- Search the json file for objects where the name is not case sensitive
- Run the Simulation
- Create a record for each discrete time event and what happened and the state of all parts of the simulation
- Output a statistical record for the simulation
