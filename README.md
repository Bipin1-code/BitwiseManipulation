# 🧮 Bitwise Manipulation in C

A compact and educational collection of **C programs** demonstrating the power of **bitwise operations** — from the basics to practical problem-solving.  
This repository is ideal for learners exploring low-level programming or developers sharpening their C and bit manipulation skills.

---

## 📘 Overview

This repo contains small, self-contained C programs that demonstrate:

- Fundamental **bitwise operators** (`&`, `|`, `^`, `~`, `<<`, `>>`)
- **Bit masking**, **setting**, **clearing**, and **toggling** bits
- Common **bit tricks** used in interviews and embedded systems
- Example problems such as **finding a unique element** using XOR

Each file focuses on a single concept, so you can learn by experimenting with one at a time.

---

## 📂 Repository Structure

| File | Description |
|------|--------------|
| `BasicOfBitwiseOperation.c` | Explains and demonstrates core bitwise operators. |
| `BitwiseQuestionNSolution.c` | Contains example problems and solutions using bit manipulation. |
| `bitMani.c` | Utility snippets and custom bit-level operations. |
| `fUniqItemInArr.c` | Finds the unique element in an array using XOR logic. |

---

## ⚙️ How to Build and Run

You can compile any file directly using `gcc` or `clang`:

```bash
# Example: build and run the basics demo
gcc -std=c11 -Wall -Wextra BasicOfBitwiseOperation.c -o bitwise_basic
./bitwise_basic

# Build and run problem examples
gcc -std=c11 -Wall -Wextra BitwiseQuestionNSolution.c -o bitwise_qns
./bitwise_qns

---

## Goal:
 This repository is still on progess mode, helping all new programmer to get familiar with bit manipulation and their implementation.
