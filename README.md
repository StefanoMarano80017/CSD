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
