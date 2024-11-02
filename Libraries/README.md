# Libraries

**Description:**  
The `Libraries` folder contains essential library files that facilitate working with the CH32V003 microcontroller by providing access to hardware features and simplifying code development.

**Folder Contents:**  
- `Peripheral Drivers`: Library files for controlling peripherals like GPIO, ADC, PWM, I2C, SPI, and USART.
- `Core Files`: Core functionality for system operations, including clock setup, interrupt management, and memory control.
- `Utility Functions`: Additional functions for common tasks, such as timing, delays, and debugging.

**How to Use:**  
1. **Add Required Libraries**:  
   - Identify which peripherals your project requires (e.g., GPIO, ADC).
   - Locate the necessary library files within this folder and add them to your project’s `include` path in MounRiver Studio.

2. **Include Library Files in Code**:  
   - For each peripheral or functionality, include the corresponding library header in your code. For example:
     ```c
     #include "gpio.h"  // For GPIO control
     #include "adc.h"   // For ADC configuration
     ```

3. **Initialize Peripherals**:  
   - Follow the initialization steps provided in each library’s documentation or comments to set up and configure peripherals (e.g., enabling clocks, setting modes).
   - For instance, if using GPIO, ensure you initialize the GPIO clock before setting pin modes.

4. **Compile and Debug**:  
   - Ensure all added library files compile without errors by building the project.
   - Use MounRiver Studio’s debug tools to check functionality and troubleshoot if necessary.

**Notes:**  
These libraries are regularly maintained to support the CH32V003’s core features. Check for updates to keep your project compatible with the latest peripheral support.
