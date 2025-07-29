#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>

// assembly function
extern void imgCvtGrayFloatToInt(float *inputImage, uint8_t *outputImage, int width, int height);

// function to generate random float values (not yet used - for timing/benchamrkin)
static void generateImage(float *image, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        image[i] = (float)rand() / (float)RAND_MAX;
    }
}

// function to print image
static void printImage(uint8_t *image, int width, int height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%d", image[i * width + j]);
            if (j != width - 1) printf(", ");
        }
        printf("\n");
    }
}

int main() {
    int width = 0, height = 0;

    printf("Enter height and width: ");
    if (scanf_s("%d %d", &height, &width) != 2 || height <= 0 || width <= 0) {
        printf("Invalid height or width.\n");
        return 1;
    }

    int size = width * height;
    float *inputImage = (float *)malloc(sizeof(float) * size);
    uint8_t *outputImage = (uint8_t *)malloc(sizeof(uint8_t) * size);

    if (!inputImage || !outputImage) {
        printf("Memory allocation failed.\n");
        free(inputImage);
        free(outputImage);
        return 1;
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Enter %d rows of %d comma-separated float values (row per row):\n", height, width);

    char buffer[1024];
    int pixelCount = 0;

    for (int row = 0; row < height; ++row) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Error reading line %d.\n", row + 1);
            free(inputImage);
            free(outputImage);
            return 1;
        }

        char *tokenPosition = NULL;
        char *token = strtok_s(buffer, ", \n", &tokenPosition);
        int col = 0;

        while (token && col < width && pixelCount < size) {
            inputImage[pixelCount++] = strtof(token, NULL);
            token = strtok_s(NULL, ", \n", &tokenPosition);
            col++;
        }

        if (col != width) {
            printf("Row %d does not contain exactly %d values.\n", row + 1, width);
            free(inputImage);
            free(outputImage);
            return 1;
        }
    }

    if (pixelCount != size) {
        printf("Total pixel count mismatch: got %d, expected %d.\n", pixelCount, size);
        free(inputImage);
        free(outputImage);
        return 1;
    }

     // Benchmark timing using <windows.h>
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    // Call the assembly function to convert float to uint8_t
    imgCvtGrayFloatToInt(inputImage, outputImage, width, height);
    QueryPerformanceCounter(&end);  // end time

    double elapsed = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

    printf("Output Integer Values:\n");
    printImage(outputImage, width, height);
    printf("Benchmark: Conversion took %.6f seconds.\n", elapsed);

    free(inputImage);
    free(outputImage);
    return 0;
}

