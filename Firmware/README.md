# Firmware

The `Firmware` folder contains precompiled binary files (.bin) for various example projects. These firmware files can be directly uploaded to the CH32V003 microcontroller using a WCH-LinkE or compatible debugger.

## Usage Instructions

1. Connect your CH32V003 board to your computer using the WCH-LinkE debugger.
2. Use MounRiver Studio or WCH tools to flash the .bin file to the microcontroller.
3. Refer to each example’s README to understand the expected behavior of the firmware.

### Firmware Files

- **blink.bin**: Basic LED blink firmware.
- **rgb_pwm_control.bin**: Controls PWM outputs.
- **adc_example.bin**: Reads and outputs ADC values.

Ensure you have the correct connections before flashing. Refer to the `Documentation` folder if you need help with wiring.
