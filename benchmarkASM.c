#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <windows.h>

// external assembly function
extern void imgCvtGrayFloatToInt(float *inputImage, uint8_t *outputImage, int width, int height);

// function to generate random float values between 0.0 and 1.0
void generateRandomPixels(float *image, int size) {
    for (int i = 0; i < size; i++) {
        image[i] = (float)rand() / (float)RAND_MAX;
    }
}

// function to time the assembly function for a specific image size
double timeAssemblyFunction(int width, int height, int iterations) {
    int size = width * height;
    float *inputImage = (float *)malloc(sizeof(float) * size);
    uint8_t *outputImage = (uint8_t *)malloc(sizeof(uint8_t) * size);
    
    if (!inputImage || !outputImage) {
        printf("ERROR: Memory allocation failed for %dx%d image (%d pixels)\n", 
               width, height, size);
        free(inputImage);
        free(outputImage);
        return -1.0;
    }

    printf("\n--- Timing %dx%d image (%d pixels) ---\n", width, height, size);
    printf("Memory allocated: %.2f MB\n", (size * (sizeof(float) + sizeof(uint8_t))) / (1024.0 * 1024.0));

    // initialize random number generator
    srand((unsigned int)time(NULL) + width * height);

    // High-precision timing setup
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    
    double totalTime = 0.0;
    double minTime = 1e9; 
    double maxTime = 0.0;

    printf("Running %d iterations...\n", iterations);

    for (int i = 0; i < iterations; i++) {
        // Generate new random data for each iteration
        generateRandomPixels(inputImage, size);
        QueryPerformanceCounter(&start);
        imgCvtGrayFloatToInt(inputImage, outputImage, width, height);
        QueryPerformanceCounter(&end);
        
        double elapsed = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
        
        totalTime += elapsed;
        if (elapsed < minTime) minTime = elapsed;
        if (elapsed > maxTime) maxTime = elapsed;

        if (iterations >= 30 && (i + 1) % 10 == 0) {
            printf("  Completed %d/%d iterations\n", i + 1, iterations);
        }
    }

    double averageTime = totalTime / iterations;
    double pixelsPerSecond = size / averageTime;
    double megapixelsPerSecond = pixelsPerSecond / 1000000.0;

    printf("\n=== TIMING RESULTS ===\n");
    printf("Image Size: %dx%d (%d pixels)\n", width, height, size);
    printf("Iterations: %d\n", iterations);
    printf("Total Time: %.6f seconds\n", totalTime);
    printf("Average Time: %.9f seconds (%.6f ms)\n", averageTime, averageTime * 1000.0);
    printf("Min Time: %.9f seconds (%.6f ms)\n", minTime, minTime * 1000.0);
    printf("Max Time: %.9f seconds (%.6f ms)\n", maxTime, maxTime * 1000.0);
    printf("Time per pixel: %.3f nanoseconds\n", (averageTime * 1e9) / size);
    printf("Throughput: %.0f pixels/second\n", pixelsPerSecond);
    printf("Throughput: %.3f megapixels/second\n", megapixelsPerSecond);
    printf("======================\n");

    free(inputImage);
    free(outputImage);
    
    return averageTime;
}

int main() {
    printf("=== ASSEMBLY FUNCTION TIMING BENCHMARK ===\n");
    printf("Timing imgCvtGrayFloatToInt assembly function\n");
    printf("Random float input values: [0.0, 1.0]\n");
    printf("Output integer values: [0, 255]\n");
    
    // Test configurations
    const int testSizes[][2] = {
        {10, 10},       // 100 pixels
        {100, 100},     // 10,000 pixels  
        {1000, 1000}    // 1,000,000 pixels
    };
    const int numTests = 3;
    const int iterations = 30;  // As required: at least 30 times

    printf("Number of iterations per test: %d\n", iterations);
    printf("===========================================\n");

    // Store results for summary
    double results[3];
    int successful_tests = 0;

    // Run timing tests for each image size
    for (int i = 0; i < numTests; i++) {
        int width = testSizes[i][0];
        int height = testSizes[i][1];
        
        double avgTime = timeAssemblyFunction(width, height, iterations);
        
        if (avgTime > 0) {
            results[successful_tests] = avgTime;
            successful_tests++;
        } else {
            printf("FAILED: Could not complete timing for %dx%d image\n", width, height);
            printf("This might be due to insufficient memory.\n");
            printf("Consider reducing the image size or closing other applications.\n");
        }
        
        printf("\n");
    }

    // Summary report
    printf("=== SUMMARY REPORT ===\n");
    printf("Successfully tested %d out of %d image sizes\n", successful_tests, numTests);
    
    if (successful_tests > 0) {
        printf("\nPerformance Summary:\n");
        const char* sizeNames[] = {"10x10", "100x100", "1000x1000"};
        const int pixels[] = {100, 10000, 1000000};
        
        for (int i = 0; i < successful_tests; i++) {
            printf("- %s: %.6f ms (%.3f MP/s)\n", 
                   sizeNames[i], 
                   results[i] * 1000.0,
                   (pixels[i] / results[i]) / 1000000.0);
        }
        
        // Performance scaling analysis
        if (successful_tests >= 2) {
            double ratio = results[1] / results[0];
            printf("\nScaling Analysis:\n");
            printf("- 100x100 is %.1fx slower than 10x10\n", ratio);
            printf("- Expected ratio for linear scaling: 100x\n");
            printf("- Actual scaling efficiency: %.1f%%\n", (100.0 / ratio) * 100.0);
            
            if (successful_tests == 3) {
                double ratio2 = results[2] / results[1];
                printf("- 1000x1000 is %.1fx slower than 100x100\n", ratio2);
                printf("- Expected ratio for linear scaling: 100x\n");
                printf("- Actual scaling efficiency: %.1f%%\n", (100.0 / ratio2) * 100.0);
            }
        }
    }
    return 0;
}