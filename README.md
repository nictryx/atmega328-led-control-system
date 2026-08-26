# ATmega328 LED Control System

An embedded systems project built around the **ATmega328P microcontroller** to demonstrate the interaction between digital inputs, analog inputs, interrupts, ADC conversion, PWM, and LED outputs.

The system uses **three push switches** and a **potentiometer** to control the behavior and brightness of three LEDs.

## Features

* Three LED outputs
* Three digital push-button inputs
* Potentiometer-based analog input
* ADC conversion
* PWM brightness control
* External interrupts
* Timer-based PWM generation
* Digital input/output control
* Simulated embedded system testing

## How It Works

* Switch 1 controls LED 1.
* Switch 2 controls LED 2.
* Switch 3 affects the brightness of LED 1 and LED 2.
* The potentiometer controls the brightness of LED 3 through ADC and PWM.
* External interrupts are used to trigger LED behavior from switch inputs.
* Timer1 is configured for PWM output.

## Main Components

* ATmega328P Microcontroller
* 3 Push Switches
* 3 LEDs
* Potentiometer
* Resistors
* Power Supply

## Tech Stack

* Embedded C
* AVR
* ATmega328P
* ADC
* PWM
* External Interrupts
* Timers
* Microchip Studio
* SimulIDE

## Testing

The project was tested virtually using:

* Functional testing
* Boundary testing
* Combination testing

SimulIDE was used to simulate the circuit and Microchip Studio was used to write, test, and debug the code.

## Project Goal

The goal of this project is to demonstrate how digital and analog inputs can be combined with embedded control logic to manage multiple outputs and explore the interaction between switches, sensors, PWM, and microcontroller peripherals.

