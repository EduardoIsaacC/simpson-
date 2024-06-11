#include <stdio.h>
#include <math.h>

// Definir la función a integrar (polinomio)
double f(double x, double coef[], int degree) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += coef[i] * pow(x, i);
    }
    return result;
}

// Método de Simpson 1/3 para calcular el área bajo la curva
double simpson(double a, double b, int n, double coef[], int degree) {
    if (n % 2 != 0) {
        printf("El numero de intervalos n debe ser par.\n");
        return -1;
    }

    double h = (b - a) / n;
    double s1 = 0.0;
    double s2 = 0.0;

    for (int i = 1; i < n; i += 2) {
        s1 += f(a + i * h, coef, degree);
    }

    for (int i = 2; i < n; i += 2) {
        s2 += f(a + i * h, coef, degree);
    }

    double integral = (h / 3) * (f(a, coef, degree) + f(b, coef, degree) + 4 * s1 + 2 * s2);
    return integral;
}

int main() {
    double a, b;
    int n, degree;

    printf("Ingrese el limite inferior de la integral: ");
    scanf("%lf", &a);
    printf("Ingrese el limite superior de la integral: ");
    scanf("%lf", &b);
    printf("Ingrese el numero de intervalos (debe ser par): ");
    scanf("%d", &n);
    printf("Ingrese el grado del polinomio: ");
    scanf("%d", &degree);

    double coef[degree + 1];
    printf("Ingrese los coeficientes del polinomio (desde el coeficiente de mayor grado al menor):\n");
    for (int i = degree; i >= 0; i--) {
        printf("Coeficiente de x^%d: ", i);
        scanf("%lf", &coef[i]);
    }

    double area = simpson(a, b, n, coef, degree);
    if (area != -1) {
        printf("El area aproximada es: %10.5f\n", area);
    }

    return 0;
}