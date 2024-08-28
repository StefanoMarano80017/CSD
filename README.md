# CSD
This folder contains material for the Computer System Design (CSD) course at Federico II University. 
Each folder contains material produced for a specific course topic:
- The ASIM folder deals with the development of assembly programs, in this case the processor is the 68k, generaly programming multi-computer systems with a single core with configuration and use of Serial and Parallel peripherals. 
These systems are simulated via ASIM. 
We will have two to three nodes communicating with each other. Therefore, there are implemented hardware-managed interrupt service routines (ISRs) using priority or software-managed using the TAS opcode. 
Typically, we have a master node which will have two ISRs which must be suitably managed in order to communicate with the other slave nodes. 
- In the MIPS folder, there are some simple programs to understand the functioning of the MIPS processor.
- In the stm32 folder, in addition to a number of small projects to familiarize with the ARM processor, is my final project for the course (in the ProjectCSD folder), which consisted of a climate control management system using an actuator made with a Stm32f3discovery board, such allows for temperature management in two different modes in the N desired rooms. 

The system involves a master, which receives temperature and humidity parameters from N - slaves, such are made again with the Stm32f3discovery board and a Bluetooth module for communication. 

The user can choose to run the air conditioning in ECO mode or by setting the temperature he or she wants, then the master uses pid or fuzzy logic to adjust the airflow intensity.  
In addition, there is a simple tool in py that, via COM port, allows the user to track and monitor the progress of the system.
