## Multi-Slot Bootloader for STM32
This is a bootloader project for STM32 microcontrollers, demonstrating a multi-slot architecture. The bootloader can jump to different applications stored at separate memory locations, making it a reusable template for more advanced bootloader work.

## Key features:
- Jumps to multiple apps based on button press or UART command
- Uses custom linker scripts and memory sections for precise control

## Tools Used
- Stm32F407 Discovery Board
- USB to TTL converter
- STM32Cubeide, Stm32Programmer, RealTerm
