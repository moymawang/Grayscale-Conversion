/*
    This file initializes a grayscale image from float values,
    calls an assembly function to convert it to 8-bit integer values,
    and prints the resulting image to the console.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// assembly function
extern void imgCvtGrayFloatToInt(float* inputImage, uint8_t* outputImage, int width, int height);

// function to generate a random values for the image
static void generateImage(float* image, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        image[i] = (float)rand() / (float)RAND_MAX;
    }
}

// function to print image
static void printImage(uint8_t* image, int width, int height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%d", image[i * width + j]);
            if (j != width - 1) printf(", ");
        }
        printf("\n");
    }
}

int main() {
    int width, height;

    printf("Enter height and width: ");
    if (scanf("%d %d", &height, &width) != 2) {
        printf("Invalid input for height and width.\n");
        return 1;
    }

    int size = width * height;

    float* inputImage = (float*)malloc(sizeof(float) * size);
    uint8_t* outputImage = (uint8_t*)malloc(sizeof(uint8_t) * size);

    if (inputImage == NULL || outputImage == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d float pixel values:\n", size);
    for (int i = 0; i < size; i++) {
        if (scanf("%f", &inputImage[i]) != 1) {
            printf("Invalid float input.\n");
            free(inputImage);
            free(outputImage);
            return 1;
        }
    }

    imgCvtGrayFloatToInt(inputImage, outputImage, width, height);

    printf("Converted uint8 pixel values:\n");
    printImage(outputImage, width, height);

    free(inputImage);
    free(outputImage);

    return 0;
}
