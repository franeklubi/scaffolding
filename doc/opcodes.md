# opcodes

### Note:

Every character that does not qualify as an opcode will be loaded into **current head**'s **mod** field.

Characters that represent digits (between 48 and 57 inclusive) will be loaded into the **mod** field after subtraction of `0x30` to make operating on numbers possible.



## Available opcodes:

- `w`:
    Switches **current head** to the **Write Head**.

- `r`:
    Switches **current head** to the **Read Head**.

- `<`:
    Moves **current head** left **mod** amount of times.

- `>`:
    Moves **current head** right **mod** amount of times.

- `/`:
    Moves **current head** up **mod** amount of times.

- `\`:
    Moves **current head** down **mod** amount of times.

- `y`:
    Moves **current head** to line **mod**.

- `x`:
    Moves **current head** to column **mod**.

- `.`:
    Writes **Write Head**'s **mod** the the buffer at **Write Head**'s position, then it increments it's x position.

- `,`:
    Escapes the next character. Allows for opcodes, as well as chars representing numbers, to be loaded into the **mod** field.

- `-`:
    Subtracts value of the character after it from **current head**'s **mod**.

- `+`:
    Adds value of the character after it to **current head**'s **mod**.

- `=`:
    Adds `0x30` to **Write Head**'s **mod**, then performs the action of opcode `.`.

- `?`:
    Allows for conditional execution.

    If the field before it is not equal to `0` or `'0'` - it moves the **Read Head** right by 3 and decrements the checked field.


For usage examples check out [sample programs](../sample_programs).
