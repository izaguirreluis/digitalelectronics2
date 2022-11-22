# Lab 8: LUIS IZAGUIRRE IMAZ

### Instruction set

1. Complete the conversion table with selected instructions:

   | **Instruction** | **Binary opcode** | **Hex opcode** | **Compiler Hex opcode** |
   | :-- | :-: | :-: | :-: |
   | `add r24, r0` | ` 0000_1101_1000_0000`| `D80` |  |
   | `com r26` | ` 1001_0101_1010_0000` |  `95A0` |  |
   | `eor r26, r27` | ` 0010_0111_1011_1010` | ` 27BA ` |  |
   | `mul r22, r20` | ` 1001_1111_0110_0100` | ` 9F64` |  |
   | `ret` | `1001_0101_0000_1000` | `9508` |  |

    Firts example:
      D= 24 in decimal, 1 1000 in binary
      r= 0 in decimal, 0 0000 in binary

      So, 0000 11.1000 ...., 0000 1101 1000 0000 in binary
### 4-bit LFSR

2. Complete table with 4-bit LFSR values for different Tap positions:

   | **Tap position** | **Generated values** | **Length** |
   | :-: | :-- | :-: |
   | 4, 3 | 0, 1, 3, 7,15, 30, 29, 27, 14, 28, 25, 19, 6, 13, 26, 21, 10, 20, 8, 16 | 20 |
   | 4, 2 | 0 1 3 7 14 28 25 18 4 8 17 2 5 10 21 11 23 15 30 29 27 22 13 26 20 9 19 6 12 24 16 | 30 |
   | 4, 1 | 0 1 3 6 12 25 18 5 11 22 13 27 23 15 30 29 26 21 10 20 8 17 2 4 9 19 7 14 28 24  16 | 30 |

### Variable number of short pulses

3. Draw a flowchart of function `void burst_c(uint8_t number)` which generates a variable number of short pulses at output pin. Let the pulse width be the shortest one. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![your figure]()
