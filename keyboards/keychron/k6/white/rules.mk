# project specific files

# MCU name
MCU = SN32F268

# BOOTLOADER = flash
# SN32_BOOTLOADER_ADDRESS = 0x1FFF0009

OPT_DEFS = -O2

# Build Options
#   comment out to disable the options.
#
LTO_ENABLE = no # linker optimization

BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = software

MAGIC_ENABLE = yes
BOOTMAGIC_ENABLE = no # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no    # Mouse keys
EXTRAKEY_ENABLE = no    # Audio control and System control
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
NKRO_ENABLE = no        # USB Nkey Rollover
SERIAL_LINK_ENABLE = no
WAIT_FOR_USB = no
CUSTOM_MATRIX = no

# some options to reduce ram usage
LDFLAGS += --specs=nano.specs
# process stack size of 0x1c0 crashes during SEND_STRING
USE_EXCEPTIONS_STACKSIZE = 0x180
USE_PROCESS_STACKSIZE = 0x210


# LED_MATRIX_ENABLE = yes
# LED_MATRIX_DRIVER = SN32F260