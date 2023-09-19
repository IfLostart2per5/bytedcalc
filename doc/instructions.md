# Instructions

The current instructions that the machine understands.

  - 0: Marks the end of the program. The program can finish normally without this, but ia recommended for readability.

  - 1: consumes a value from the pre-included values and add it into the stack. If the automatic control of the values index is enabled, its increased automatically.

  - 2: "unconsumes" a value from stack, decreasing the values index (the same thing of the above instruction).

  - 3: sum the values in the current "stack focus". It optimize certain expressions, and erase the right operand.

  - 4: multiply the values in the current "stack focus". like the 3 instruction, it optimize certain expressions, and erase the right operand.

  - 5: subtract the values in the current "stack focus". like all aritmetic operations here, it optimize certain expressions, and erase the right operand.

  - 6: divide the values in the current "stack focus". the same thing of others.

  - 7: moves the "stack focus" to right.

  - 8: moves the "stack focus" to right, ensuring that its not crossing the stack start.

  - 9: do a bitwise "AND" in the current "stack focus". not optimized yet, but erase the right operand.

  - 10: do a bitwise "OR" in the current "stack focus". the same thing of the 9 instruction.

  - 11: do a bitwise complement in the top of the stack. the same thing of 9 and 10 instructions.

  - 12: manually increases the values index, verifying if its inside of the values size.

  - 13: manually decreases the values index, verifying if its greater than 0.

  - (compound) 14: write a value in the given index on the memory, verifying if the given index not exceeds the memory size, in the format "14 index value".

  - (compound) 15: reedem a value from memory with the given index on the stack, verifying the same condition of the 14 instruction, in the format "15 index".

  - (compound) 16: deletes a value from the memory with the given index, verifying ... the same thing of 14 and 15 instructions, in the format "16 index".

  - (special) 32: serves as a recovery-point from errors.

* "stack focus" means the indexes that points to a operand, and other operand, like this, you can choose a specific point of the stack to apply operations.
