SET C51INC=E:\Keil\C51\Inc;E:\Keil\C51\Inc\Atmel
SET C51LIB=E:\Keil\C51\Lib
SET CPU_TYPE=AT89C52
SET CPU_VENDOR=Atmel
SET UV2_TARGET=Target 1
SET CPU_XTAL=0x016E3600
"E:\Keil\C51\BIN\C51.EXE" @.\out\main.__i
"E:\Keil\C51\BIN\C51.EXE" @.\out\MyDemo.__i
"E:\Keil\C51\BIN\BL51.EXE" @.\out\rtos.lnp
"E:\Keil\C51\BIN\OH51.EXE" ".\out\rtos" 
