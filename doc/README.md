# Structure
The program is organized based on two arrays:
  - the pre-included values, that is more simple to use
  - the instructions

 The pre-included values is a set of values that can be directly consumed.
 
 The instructions are codes that's executed by the machine.

 under the hood, it uses a stack to store the values and results, and a (experimental and basic) memory system.

When started, it traverse the instructions, and using a switch-case statement to determine the action to do.

1. When looping, first it checks if a error ocurred, if yes, it starts to ignore all of the next instructions until find a secure recovery point, the 32 instruction, if it found it, it stops and follows normally to the next instruction after 32.

2. otherwise, it follows to the switch-case, thats determines a action.

3. if a error occurs (such zero division, invalid memory access, etc.), it shows a error message, and enable the error flag.

4. otherwise, continue.

Its the basic functionality of the simple machine.

Other references:
1. [Installing](./installing.md)  
2. [Instructions](./instructions.md)

