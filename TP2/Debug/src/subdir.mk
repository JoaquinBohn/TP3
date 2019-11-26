################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EasyBMP.cpp \
../src/EasyBMP_Font.cpp \
../src/EasyBMP_Geometry.cpp \
../src/auxiliar.cpp \
../src/camino.cpp \
../src/coordenadas.cpp \
../src/estacion.cpp \
../src/main.cpp \
../src/menu.cpp \
../src/recorrido.cpp \
../src/transporte.cpp 

OBJS += \
./src/EasyBMP.o \
./src/EasyBMP_Font.o \
./src/EasyBMP_Geometry.o \
./src/auxiliar.o \
./src/camino.o \
./src/coordenadas.o \
./src/estacion.o \
./src/main.o \
./src/menu.o \
./src/recorrido.o \
./src/transporte.o 

CPP_DEPS += \
./src/EasyBMP.d \
./src/EasyBMP_Font.d \
./src/EasyBMP_Geometry.d \
./src/auxiliar.d \
./src/camino.d \
./src/coordenadas.d \
./src/estacion.d \
./src/main.d \
./src/menu.d \
./src/recorrido.d \
./src/transporte.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


