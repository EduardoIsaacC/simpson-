#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <muParser.h>

// Función de envoltura para evaluar expresiones matemáticas usando muParser
double evaluateFunction(mu::Parser* parser, double x) {
    parser->DefineVar("x", &x);
    try {
        return parser->Eval();
    } catch (mu::Parser::exception_type &e) {
        printf("Error: %s\n", e.GetMsg());
        exit(EXIT_FAILURE);
    }
}

// Método de Simpson 1/3 para calcular el área bajo la curva
double simpson(mu::Parser* parser, double a, double b, int n) {
    if (n % 2 != 0) {
        printf("El numero de intervalos n debe ser par.\n");
        return -1;
    }

    double h = (b - a) / n;
    double s1 = 0.0;
    double s2 = 0.0;

    for (int i = 1; i < n; i += 2) {
        s1 += evaluateFunction(parser, a + i * h);
    }

    for (int i = 2; i < n; i += 2) {
        s2 += evaluateFunction(parser, a + i * h);
    }

    double integral = (h / 3) * (evaluateFunction(parser, a) + evaluateFunction(parser, b) + 4 * s1 + 2 * s2);
    return integral;
}

int main() {
    double a, b;
    int n;
    char func[256];

    printf("Ingrese la funcion f(x): ");
    scanf("%255s", func);
    printf("Ingrese el limite inferior de la integral: ");
    scanf("%lf", &a);
    printf("Ingrese el limite superior de la integral: ");
    scanf("%lf", &b);
    printf("Ingrese el numero de intervalos (debe ser par): ");
    scanf("%d", &n);

    mu::Parser parser;
    parser.SetExpr(func);

    double area = simpson(&parser, a, b, n);
    if (area != -1) {
        printf("El area aproximada es: %10.5f\n", area);
    }

    return 0;
}