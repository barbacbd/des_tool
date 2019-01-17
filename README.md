# DES_TOOL

While I was learning about Discrete Event Simultion (DES), I was taught to manually simulate Discrete Event Systems. 
I noticed that these systems were thrown off easily, and many errors occured with one minor mistake. I thought that
it could be useful for others (learning simulations), to see where they may have made a mistake or just to check 
their work. While the systems are easy for users to introduce errors, the systems are deterministic. The deterministic 
nature of these systems means that automating the work using a computer is much simpler.


## Opengl

The opengl subdirectory contains a makefile to make the opengl gui version of the project. The opengl version 
of the project was the prototype, but a newer version has been constructed using Qt. 

> The user will be required to install OpenGL on their system.

### Simulation Files

```
simulation/des.txt
```


## Build

```
mkdir build
cd build
cmake ..
make -j4
```

## Run

```
./des_tool des.txt
```