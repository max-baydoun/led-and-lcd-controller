# LCD/LED Controller
This small Arduino program controls both an LCD via I2C, and a led (or can be a strip of LED's). It requires a HM-10 bluetooth module, an Arduino Nano, a 2 X 16 LCD display module with I2C interface, and any LED of your choice.

## Schematic
![image](https://github.com/max-baydoun/led-and-lcd-controller/assets/144291500/40e1431a-0473-4615-a83d-e6a54d18bbf3)

## Design choice
I decided to connect the ground pin of the led to a digital pin, as there weren't enough ground pins on the nano, and I didn't want to use a breadboard, as the entire circuit wouldn't fit in a case I printed. This resulted in the brightness of the LED to be dimmer than usual.

