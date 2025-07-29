# Float-to-Integer Grayscale Image Conversion

## Project Overview

This project demonstrates the conversion of grayscale images represented as floating-point values (`float`, 0.0–1.0) into 8-bit unsigned integers (`uint8_t`, 0–255) using a combination of C and x86-64 assembly language.

The conversion is done using the formula: float / int = 1 / 255 → int = float * 255

## Features

- Input image dimensions and float-based pixel values manually
- Scalar SIMD conversion using `XMM` registers (`mulss`, `cvttss2si`)
- Automatic clamping to ensure values remain within `uint8_t` range
- Neatly formatted image output in the terminal
- Dynamically allocates memory for image storage
- Benchmarking-ready with `generateImage()` and timing support

# Requirements

## i. Execution Time and Short Analysis of the Performance
--- Timing 10x10 image (100 pixels) ---
Memory allocated: 0.00 MB
Ran 30 iterations.
Image Size: 10x10 (100 pixels)
Iterations: 30
Total Time: 0.000005 seconds
Average Time: 0.000000180 seconds (0.000180 ms)
Min Time: 0.000000100 seconds (0.000100 ms)
Max Time: 0.000000200 seconds (0.000200 ms)
Time per pixel: 1.800 nanoseconds
Throughput: 555555556 pixels/second
Throughput: 555.556 megapixels/second


--- Timing 100x100 image (10000 pixels) ---
Memory allocated: 0.05 MB
Ran 30 iterations
Image Size: 100x100 (10000 pixels)
Iterations: 30
Total Time: 0.000443 seconds
Average Time: 0.000014770 seconds (0.014770 ms)
Min Time: 0.000014300 seconds (0.014300 ms)
Max Time: 0.000021600 seconds (0.021600 ms)
Time per pixel: 1.477 nanoseconds
Throughput: 677048070 pixels/second
Throughput: 677.048 megapixels/second

--- Timing 1000x1000 image (1000000 pixels) ---
Memory allocated: 4.77 MB
Ran 30 iterations
Image Size: 1000x1000 (1000000 pixels)
Iterations: 30
Total Time: 0.054816 seconds
Average Time: 0.001827197 seconds (1.827197 ms)
Min Time: 0.001438600 seconds (1.438600 ms)
Max Time: 0.004272400 seconds (4.272400 ms)
Time per pixel: 1.827 nanoseconds
Throughput: 547286463 pixels/second
Throughput: 547.286 megapixels/second

**Analysis:**

Performance Summary:
- 10x10: 0.000180 ms (555.556 MP/s)
- 100x100: 0.014770 ms (677.048 MP/s)
- 1000x1000: 1.827197 ms (547.286 MP/s)

Scaling Analysis:
- 100x100 is 82.1x slower than 10x10
- Expected ratio for linear scaling: 100x
- Actual scaling efficiency: 121.9%
- 1000x1000 is 123.7x slower than 100x100
- Expected ratio for linear scaling: 100x
- Actual scaling efficiency: 80.8%

## ii. Screenshot of Program Output with Correctness Check

## iii. Short Video Demonstration (5–10 minutes)

[Watch Demo Video](https://insert link)

The video includes:
- Overview of the C and ASM source code
- Compilation steps (Visual Studio and NASM)
- Execution with sample input
- Correct output and timing demonstration

