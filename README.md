# Examensarbete-meditationshandskar
Arduino-based vibrotactile glove prototype for guiding box breathing through sequential vibration patterns. 

# Vibrotactile Breathing Glove

Arduino-based vibrotactile glove prototype developed as part of the bachelor thesis project **DM128X Examensarbete inom Medieteknik, grundnivå** at KTH Royal Institute of Technology.

The prototype explores how vibrotactile feedback can be used to guide box breathing without relying on visual or auditory instructions. Six vibration motors are placed across two gloves and controlled through an Arduino-based system. The motors create sequential vibration patterns intended to guide inhalation and exhalation through touch.

## Project Context

This repository contains the Arduino code used in a bachelor thesis project by:

- Anna Sköld  
- Refia Sargin  
- Elin Ståler  

KTH Royal Institute of Technology, Sweden, 2026.

The study investigates whether a vibrotactile interface can support correct execution of box breathing in a similar way to visual and auditory breathing guidance.

## Prototype Overview

The system consists of:

- 1 Arduino / Elegoo Uno
- 6 ERM vibration motors
- MOSFET-based motor control circuit
- Touch input using conductive copper tape
- Two wearable gloves
- Breadboard and wiring
- Flyback diodes for motor protection

The interaction is based on touch input:

- Touch input on pin 2 starts or stops a four-cycle breathing sequence.
- Touch input on pin 8 starts or stops a single breathing cycle.

## Breathing Pattern

One full breathing cycle lasts 16 seconds:

1. Inhale guidance through sequential vibration
2. Transition phase
3. Exhale guidance through sequential vibration
4. End of cycle

The code uses PWM signals and a sinusoidal smoothing function to create softer vibration pulses.

## Code Structure

The Arduino code includes:

- Motor pin configuration
- Touch input handling
- State machine for idle, single-cycle and multi-cycle modes
- Smooth vibration pulse generation
- Sequential wave pattern for breathing guidance
- End feedback signal after completed cycles
