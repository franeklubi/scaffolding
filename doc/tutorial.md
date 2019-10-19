# tutorial

Alright, You decided to embark on the adventure of learning how to use **scaffolding**!

I couldn't be more sorry for You!


# Introduction

I recommend opening the [list of opcodes](./opcodes.md), You'll need it for reference.

In this tutorial I'll analyse and explain a couple of programs written in scaf.

Before that, let's lay down some fundamentals first:
- The **Read Head** (blue) and the **Write Head** (red) both initially start at position (0, 0).
- The **Read Head** advances automatically until it reaches an illegal position (outside the buffer).
- **Current Head** points to the **Write Head** by default.


# [absolute.scaf](../sample_programs/absolute.scaf)

```scaf
9y9+9xY.O. .D.U.D.E.
```

This short script does two things:
1. Positions the **Write Head** on the 9th line and 18 column:
    1. Loads `9` into the **Write Head**'s **mod**.
    2. Executes opcode `y`.
    3. Loads `9`, then adds another `9` to **mod**.
    4. Executes opcode `x`.

2. Loads 7 chars and prints them, sequentially until it reaches the end of the buffer:
    1. Loads a char into the **Write Head**'s **mod**.
    2. Executes opcode `.`.
    3. Repeats that 7 times.

Output of [franeklubi/scaf-visualizer](https://github.com/franeklubi/scaf-visualizer):
![absolute.scaf](./assets/absolute.gif)


# [loop.scaf](../sample_programs/loop.scaf)

```scaf
a.b.07<
```
