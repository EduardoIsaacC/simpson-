#include <stdio.h>
#include <math.h>

// Definición de la función a integrar
double f(double x) {
    return sin(x);
}

double simpson_1_3(double (*f)(double), double a, double b, int n) {
    if (n % 2 != 0) {
        printf("El número de subintervalos n debe ser par.\n");
        return -1;
    }

    double h = (b - a) / n;
    double sum_odd = 0.0, sum_even = 0.0;

    for (int i = 1; i < n; i += 2) {
        sum_odd += f(a + i * h);
    }

    for (int i = 2; i < n; i += 2) {
        sum_even += f(a + i * h);
    }

    double integral = (h / 3) * (f(a) + 4 * sum_odd + 2 * sum_even + f(b));
    return integral;
}

int main() {
    double a = 0;
    double b = M_PI;
    int n = 10; // Debe ser par

    double resultado = simpson_1_3(f, a, b, n);
    if (resultado != -1) {
        printf("La integral de f(x) de %f a %f es aproximadamente %f\n", a, b, resultado);
    }

    return 0;
}