################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/GB_Diagnostics/GB_Diag.c 

OBJS += \
./Drivers/GB_Diagnostics/GB_Diag.o 

C_DEPS += \
./Drivers/GB_Diagnostics/GB_Diag.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/GB_Diagnostics/%.o Drivers/GB_Diagnostics/%.su: ../Drivers/GB_Diagnostics/%.c Drivers/GB_Diagnostics/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/SerialLogging" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/MachineSensors" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/MachineErrors" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/SysObserver" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/GB_Diagnostics" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/userButtons" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/MotorComms" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/MachineSettings" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/FDCAN/MotherBoard" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/FDCAN" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/Eeprom" -I"/home/harsha/STM32CubeIDE/workspace_1.10.0/MainBoard_RD/Drivers/MCP23017" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-GB_Diagnostics

clean-Drivers-2f-GB_Diagnostics:
	-$(RM) ./Drivers/GB_Diagnostics/GB_Diag.d ./Drivers/GB_Diagnostics/GB_Diag.o ./Drivers/GB_Diagnostics/GB_Diag.su

.PHONY: clean-Drivers-2f-GB_Diagnostics

