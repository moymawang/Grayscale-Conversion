# Float-to-Integer Grayscale Image Conversion (C + x86-64 ASM)

## Project Overview

This project demonstrates the conversion of grayscale images represented as floating-point values (`float`, 0.0–1.0) into 8-bit unsigned integers (`uint8_t`, 0–255) using a combination of C and x86-64 assembly language.

The conversion is done using the formula: float / int = 1 / 255 → int = float * 255

---

Assembly SIMD scalar instructions are used to efficiently convert pixel values, clamp them between 0 and 255, and store the result.

## Features

- Input image dimensions and float-based pixel values manually
- Scalar SIMD conversion using `XMM` registers (`mulss`, `cvtss2si`)
- Automatic clamping to ensure values remain within `uint8_t` range
- Neatly formatted image output in the terminal
- Dynamically allocates memory for image storage
- Benchmarking-ready with `generateImage()` and timing support

# Requirements

## i. Execution Time and Short Analysis of the Performance

**Analysis:**

## ii. Screenshot of Program Output with Correctness Check

## iii. Short Video Demonstration (5–10 minutes)

[Watch Demo Video](https://insert link)

The video includes:
- Overview of the C and ASM source code
- Compilation steps (Visual Studio and NASM)
- Execution with sample input
- Correct output and timing demonstration

