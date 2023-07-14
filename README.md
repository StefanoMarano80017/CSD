# CSD
COMPUTER SYSTEM DESIGN


The ASIM folder deals with the development of assembly programs. 
In this case the processor in question is the 68k. Configuration and use of Serial and Parallel peripherals. 
Programming multi-computer systems with a single core. Naked systems, which are programmed, 
are simulated via ASIM. We will have two to three nodes communicating with each other. Therefore, 
I implement hardware-managed interrupt service routines (ISRs) using priority or software-managed using the TAS opcode. 
Typically, we have a master node which will have two ISRs which must be suitably managed in order
to communicate with the other slave nodes. 
The latter will also act either under interruption or polling.
In the stm32 folder, there are a series of small projects, to familiarize yourself with the ARM processor, and the final project, ProgettoCSD folder, which provide for a master, which receives the temperature and humidity parameters from two slaves, located in two different points . Based on the pid or fuzzy mode, the master adjusts the intensity of the air flow and plots everything on the pc, using an interface written in py.
In the MIPS folder, there are some simple programs to understand the functioning of the MIPS processor.
