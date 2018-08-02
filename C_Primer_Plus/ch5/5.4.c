#include <stdio.h>

int main()
{
    const float CM_PER_INCH = 2.54;
    const int INCHES_PER_FOOT = 12;
    float centimeters = 0.0f;

    printf("Enter a height in centimeters: ");
    scanf("%f", &centimeters);
    while (centimeters > 0)
    {
        float inches = centimeters / CM_PER_INCH;
        int feet = (int) inches / INCHES_PER_FOOT;
        printf("%.1f cm = %d feet, %.1f inches\n", centimeters, feet, inches - (feet * INCHES_PER_FOOT));
        printf("Enter a height in centimeters: ");
        scanf("%f", &centimeters);
    }
    printf("bye\n");

    return 0;
}
