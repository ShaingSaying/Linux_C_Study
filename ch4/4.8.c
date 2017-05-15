#include <stdio.h>
int main()
{
    const float PER_GALLON = 3.785;
    const float PER_MILE = 1.609;
    float miles = 0.0;
    float gallons = 0.0;

    printf("Please input the miles and gallons:");
    scanf("%f %f", &miles, &gallons);
    
    float miles_per_gallon = miles / gallons;
    printf("Miles per gallon: %.1f\n", miles_per_gallon);
    printf("Liters per 100 kilometers: %f\n", (100 / PER_MILE) * (gallons / miles) * PER_GALLON);

    return 0;
}
