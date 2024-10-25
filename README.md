# Arduino Sensor Monitoring and Control System with GSM Module

## Project Overview
This project involves designing a system that uses an **Arduino** to monitor various sensors, display sensor data on an **LCD screen**, and transmit this information to a mobile device via **SMS** using the **SIM800L GSM/GPRS modem**. Additionally, the system allows for remote control of a **stepper motor** by receiving SMS commands from a predefined mobile number. All functionality is implemented and simulated in **Proteus**.

## System Operation
1. **Sensor Data Collection and Transmission**:  
   - Arduino collects data from all connected sensors.
   - The sensor data is displayed on an **LCD screen** connected to the Arduino.
   - The collected data is sent as an SMS message to a predefined mobile phone number via the **SIM800L GSM/GPRS modem**.

2. **Remote Control via SMS Commands**:  
   - Arduino is set up to receive SMS messages.
   - Upon receiving an SMS, Arduino checks if the sender's number matches the predefined number.
   - If verified, the Arduino interprets the message to extract commands for controlling the stepper motor.
   - Commands allow control of the stepper motor to rotate either clockwise or counterclockwise for a specified number of cycles.

3. **Command Customization**:  
   - The user can define commands for the stepper motor, specifying the number of cycles and the direction (clockwise or counterclockwise).

## Requirements and Tools
- **Arduino**: Central control unit for processing sensor data and sending/receiving SMS.
- **SIM800L GSM/GPRS Modem**: Used for sending and receiving SMS messages.
- **LCD Display**: Displays real-time sensor data.
- **Stepper Motor**: Controlled remotely via SMS commands.
- **Proteus Simulator**: All functionalities and components are simulated using Proteus.

## Example Commands
You can customize SMS commands for motor control. For example:
- `CW5` - Rotate motor **clockwise** for **5 cycles**.
- `CCW3` - Rotate motor **counterclockwise** for **3 cycles**.

## Simulation Setup
This project is fully implemented in **Proteus**. Ensure the following are configured in the simulation:
- Proper connections for the Arduino, sensors, SIM800L modem, LCD, and stepper motor.
- Predefined commands for motor control and a valid mobile number for SMS verification.

---

This project demonstrates a simple yet powerful way to remotely monitor sensor data and control hardware via SMS, using only the Proteus simulator.
