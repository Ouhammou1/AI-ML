#include <stdio.h>
#include <math.h>

int main() {
    double a = 3.1;
    double b = -2.1;
    double c = 5.0;

    printf("floor(%.1f) = %.1f\n", a, floor(a)); // floor(3.7) = 3.0
    printf("floor(%.1f) = %.1f\n", b, floor(b)); // floor(-2.3) = -3.0
    printf("floor(%.1f) = %.1f\n", c, floor(c)); // floor(5.0) = 5.0

    return 0;
}
