# project specific files
SRC = ../../../../drivers/sn32/matrix_sn32f24xx.c
SRC += config_led.c

# MCU name
MCU = SN32F248B

# BOOTLOADER = flash
SN32_BOOTLOADER_ADDRESS = 0x1FFF0301

OPT_DEFS = -O2

# Custom RGB matrix handling
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = SN32F248B
