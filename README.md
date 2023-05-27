# CSD
COMPUTER SYSTEM DESIGN


In the ASIM folder, it is treated development of assembly programs. 
In this case the processor in question is the 68k.
Configuration and use of various Serial, PIA peripherals.
Programming of multicomputer systems with a single core. 
I'm going to use bare systems, which I'm going to program. We will have two to three nodes 
that will communicate with each other. Therefore, I'm going to implement some ISR (interrupt service routine) 
managed via hardware through the use of prioritization or via software using the TAS opcode.
Typically, we have a master node which will present two ISRs which must be suitably managed, 
in order to communicate with the other slave nodes.
The latter will also be interrupted or will be added in polling.
