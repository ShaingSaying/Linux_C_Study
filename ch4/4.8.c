#include <stdio.h>

int main(void)
{
    const float PER_GALLON = 3.785f;
    const float PER_MILE = 1.609f;
    float miles = 0.0f;
    float gallons = 0.0f;

    printf("Please input the miles and gallons:\n");
    scanf("%f %f", &miles, &gallons);
    
    float miles_per_gallon = miles / gallons;
    printf("Miles per gallon: %.1f\n", miles_per_gallon);
    printf("Liters per 100 kilometers: %f\n", (100 / PER_MILE) * (gallons / miles) * PER_GALLON);

    return 0;
}
