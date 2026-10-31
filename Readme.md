# Auto-Aligning Solar Tracker Using Dual LDRs

A low-cost, single-axis solar-tracking system built using an **Arduino
Nano**, **two Light Dependent Resistors (LDRs)**, and a **geared DC
motor**. The system detects differences in light intensity and
automatically adjusts the solar panel's orientation toward the brighter
side.

## Project Overview

This project demonstrates the use of semiconductor photoconductivity,
voltage dividers, feedback control, and motor-driven solar-panel
alignment.

Two LDRs are mounted on opposite sides of an opaque divider. When the
light source is centred, both sensors receive approximately equal
illumination. If the light shifts to one side, the divider shades one
LDR more than the other. The Arduino compares the sensor readings and
briefly drives the motor to correct the panel's alignment.

## Aim

To construct and evaluate a low-cost, single-axis solar tracker using
dual LDR sensing and Arduino-based motor control.

## How It Works

1.  Each LDR is connected with a fixed resistor to form a voltage
    divider.
2.  The Arduino Nano reads the two divider voltages through analog pins
    **A0** and **A1**.
3.  It calculates the difference between the readings: `D = |L - R|`.
4.  A potentiometer connected to **A2** sets the correction threshold
    (deadband).
5.  If the difference exceeds the threshold, the Arduino sends a short
    control pulse through **D5** and **D6** to the L9110S motor driver.
6.  The motor turns the panel mount toward the brighter side. If the
    readings are sufficiently close, the motor remains stopped.

The deadband helps prevent unnecessary movement due to small sensor
fluctuations.

## Components Required

  ------------------------------------------------------------------------
  Component                                 Quantity Purpose
  --------------------- ---------------------------- ---------------------
  Arduino                                          1 Reads sensors and
  Nano-compatible board                              controls the motor
  (ATmega328P)                                       driver

  GL5528 or similar LDR                            2 Detects light
                                                     intensity

  10 kΩ resistor, ¼ W                              2 Forms a voltage
                                                     divider with each LDR

  Mini solar panel                                 1 Test panel; output
  (5--6 V, 1--2 W)                                   voltage is measured
                                                     separately

  Low-speed geared DC                              1 Rotates the panel
  motor (3--6 V)                                     mount

  L9110S motor-driver                              1 Controls motor
  module                                             direction

  10 kΩ potentiometer                              1 Optional threshold
                                                     adjustment through A2

  Breadboard                                       1 Temporary circuit
                                                     assembly

  Male-to-male jumper                          1 set Electrical
  wires                                              connections

  Regulated DC supply                              1 Powers the motor and
  suitable for the                                   driver
  motor                                              

  USB cable for Nano                               1 Programming and board
                                                     power during testing

  100 nF ceramic                                   1 Optional supply
  capacitor                                          decoupling

  10 μF electrolytic                               1 Optional supply
  capacitor                                          smoothing

  SPST switch                                      1 Manual power
                                                     isolation

  Base board and                               1 set Supports the panel
  lightweight panel                                  and pivot
  bracket                                            

  Pivot, coupler,                              1 set Transfers motor
  screws, nuts and                                   motion to the mount
  washers                                            

  Opaque black divider                             1 Separates the LDRs'
                                                     fields of view

  Cable ties/tape                              1 set Keeps wiring
                                                     organised

  Digital multimeter                               1 Measures panel
                                                     voltage and checks
                                                     continuity

  Lamp, protractor and                         1 set Provides a controlled
  ruler                                              light source and
                                                     measurement setup
  ------------------------------------------------------------------------

## Experimental Setup and Connections

-   **LDR sensors:** Each LDR forms a voltage divider with a 10 kΩ
    resistor. The two divider junctions connect to Arduino analog inputs
    **A0** and **A1**.
-   **Threshold control:** The potentiometer connects to **A2** to
    adjust the threshold.
-   **Motor driver:** The L9110S motor driver is controlled by Arduino
    pins **D5** and **D6** and drives the geared DC motor.
-   **Solar panel:** The panel is mounted on a pivot and its output
    voltage is measured separately using a multimeter.

Check the pin labels on the specific Nano and L9110S modules before
wiring, as board layouts can vary.

## Physics Concepts

### 1. LDR and Photoconductivity

An LDR is a semiconductor component whose resistance generally decreases
as incident light intensity increases. Absorbed photons create
additional mobile charge carriers, increasing conductivity.

The energy of a photon is:

`E = hν`

where: - `E` = photon energy - `h` = Planck's constant - `ν` = frequency
of incident light

The tracker does not directly measure photon energy; it uses the
resulting change in LDR resistance.

### 2. LDR vs. Solar Cell

  -----------------------------------------------------------------------
  Feature                 LDR                     Solar cell
  ----------------------- ----------------------- -----------------------
  Device type             Photoresistor           Photovoltaic device

  Main effect             Photoconductive effect  Photovoltaic effect

  Output                  Change in resistance    Voltage/current when
                                                  connected to a load

  Role in this project    Light-intensity sensor  Panel being aligned
                                                  toward the light
  -----------------------------------------------------------------------

An LDR detects light through a change in resistance. A solar cell uses a
semiconductor junction to separate light-generated charge carriers and
produce electrical output.

### 3. Voltage Divider

The Arduino cannot directly measure resistance through an analog input.
A voltage divider converts the LDR's resistance change into a changing
voltage that the Arduino can read. The reading's direction depends on
whether the LDR is connected toward 5 V or GND, so the wiring and
control logic must be consistent.

### 4. Directional Sensing

The two LDRs are placed on opposite sides of an opaque partition. When
the light source is off-centre, the partition shades one sensor more
than the other. The difference between their readings indicates the
direction of misalignment.

### 5. Feedback Control and Deadband

The Arduino compares the absolute difference between the two sensor
readings with a selected threshold:

-   **Difference above threshold:** The motor receives a short
    correction pulse.
-   **Difference within threshold:** The motor stops.

The deadband reduces constant movement caused by minor fluctuations in
sensor readings. The threshold and motor pulse duration can be adjusted
experimentally.

## Applications

-   Demonstration of semiconductor photoconductivity.
-   Basic light-seeking and solar-tracking systems.
-   Learning analog sensing, voltage dividers, embedded control, and
    motor drivers.
-   Experimental study of solar-panel orientation and electrical output.

## Precautions

1.  Verify the pin labels on the exact Nano and L9110S modules; clone
    boards may have different layouts.
2.  Never connect a motor directly to an Arduino GPIO pin.
3.  Observe the polarity of the electrolytic capacitor.
4.  Keep the pivot movement within its mechanical limits and prevent
    wires from wrapping around the shaft.
5.  Keep lamp distance and brightness constant during comparative
    measurements.
6.  Disconnect the power supply before changing any wiring.

## Learning Outcomes

Through this project, we learned:

-   How an LDR's resistance changes with light intensity and why its
    response is not linear.
-   The difference between the photoconductive effect in an LDR and the
    photovoltaic effect in a solar cell.
-   How a voltage divider converts resistance changes into analog
    voltages.
-   How a threshold or deadband can control motor movement and prevent
    constant hunting.
-   How to assemble and test a system using an Arduino Nano and L9110S
    motor driver.
-   How to measure panel voltage at different angles under a fixed light
    source.
-   Practical limitations such as sensor mismatch, ambient light, motor
    backlash, and overshoot.

## Team

  Name               Enrolment Number Batch
  ---------------- ------------------ -------
  Anubhav Tiwari           2601020008 A1
  Mudit Jindal             2601020021 A1
  Yanik Kumar              2601020023 A1
  Aariti Arora             2601020024 A1

**Submitted to:** Dr. Manoj Tripathi\
**Department:** Department of Physics and Material Sciences\
**Course:** Physics Lab -- 1 (15B17PH171)\
**Institution:** Jaypee Institute of Information Technology\
**Date:** 4 November 2026

## References

1.  Beiser, A. (2003). *Concepts of Modern Physics* (6th ed.).
    McGraw-Hill Education.
2.  Arduino Language Reference:
    https://docs.arduino.cc/language-reference/
3.  Arduino Nano Documentation: https://docs.arduino.cc/hardware/nano/
4.  Diodes Incorporated. *L9110 / L9110S Motor Driver Documentation.*
