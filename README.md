# Homework 6.1 NARELI (@INTRO TO CRYPTOGRAPHY)

The source code only «calculates a elliptic curve coordinates over Galois finite field based on p». By default the parameters defined by the equation are:

* a = 3
* b = 8
* p = 13

## gcc compilation

To  compile, please use any suite of 'The GNU Compiler Collection' compilers xD:

### On windows

Assuming your PATH is correctly configured:

```bat ('*.bat', '*.cmd')
rm bin\leo.hw6.1.finite.field.over.elliptic.curve.exe & cls & D:\mingw\bin\g++.exe -g -o bin/leo.hw6.1.finite.field.over.elliptic.curve.exe finite.field.over.ec.c & bin\leo.hw6.1.finite.field.over.elliptic.curve.exe
```

### On unix

Assuming your ENV variables are set:

```shell ('*.sh', '*.bash')
g++ -g -o leo.hw6.1.finite.field.over.elliptic.curve.exe finite.field.over.ec.c
./leo.hw6.1.finite.field.over.elliptic.curve.exe
```

## Overriding explicit ELLIPTIC CURVE parameters

To execute it with explicit parameters over the curve, e.g.:

* a = 4
* b = 5
* p = 11

Just `leo.hw6.1.finite.field.over.elliptic.curve.exe 4 5 11`

## Docker image

If you are on a OS with difficulties or limitations installing the dependencies, please feel free to build the «The GNU Compiler Collection» image as follows:

```bat ('*.bat', '*.cmd')
docker build -t my-gcc-app .
docker run -it --rm --name hw6.1_crypto my-gcc-app
```