#include <iostream>
#include <muParser.h>
#include <cmath>

// Función para evaluar la expresión ingresada por el usuario
double evaluate_expression(mu::Parser &parser, double x) {
    parser.DefineVar("x", &x);
    try {
        return parser.Eval();
    } catch (mu::Parser::exception_type &e) {
        std::cerr << "Error de evaluación: " << e.GetMsg() << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Implementación del método de Simpson 1/3 ajustado
double simpson_1_3(mu::Parser &parser, double a, double b, int n) {
    if (n < 1) {
        std::cerr << "El número de subintervalos n debe ser al menos 1." << std::endl;
        return -1;
    }

    double h = (b - a) / n;
    double integral = 0.0;

    // Si n es impar, usar Simpson 1/3 en los primeros n-1 subintervalos y el método del trapecio en el último subintervalo
    if (n % 2 != 0) {
        double sum_odd = 0.0, sum_even = 0.0;
        
        for (int i = 1; i < n - 1; i += 2) {
            sum_odd += evaluate_expression(parser, a + i * h);
        }

        for (int i = 2; i < n - 1; i += 2) {
            sum_even += evaluate_expression(parser, a + i * h);
        }

        integral = (h / 3) * (evaluate_expression(parser, a) + 4 * sum_odd + 2 * sum_even + evaluate_expression(parser, a + (n - 1) * h));
        // Añadir el último subintervalo usando el método del trapecio
        integral += (h / 2) * (evaluate_expression(parser, a + (n - 1) * h) + evaluate_expression(parser, b));
    } else {
        // Si n es par, usar Simpson 1/3 en todos los subintervalos
        double sum_odd = 0.0, sum_even = 0.0;

        for (int i = 1; i < n; i += 2) {
            sum_odd += evaluate_expression(parser, a + i * h);
        }

        for (int i = 2; i < n; i += 2) {
            sum_even += evaluate_expression(parser, a + i * h);
        }

        integral = (h / 3) * (evaluate_expression(parser, a) + 4 * sum_odd + 2 * sum_even + evaluate_expression(parser, b));
    }

    return integral;
}

int main() {
    std::string expression;
    double a, b;
    int n;

    // Solicitar la entrada del usuario
    std::cout << "Ingrese la función a integrar (use 'x' como variable, por ejemplo 'sin(x) + x^2'): ";
    std::cin >> expression;
    std::cout << "Ingrese el límite inferior a: ";
    std::cin >> a;
    std::cout << "Ingrese el límite superior b: ";
    std::cin >> b;
    std::cout << "Ingrese el número de subintervalos n: ";
    std::cin >> n;

    // Crear un parser de muParser
    mu::Parser parser;
    try {
        parser.SetExpr(expression);
    } catch (mu::Parser::exception_type &e) {
        std::cerr << "Error al analizar la expresión: " << e.GetMsg() << std::endl;
        return EXIT_FAILURE;
    }

    // Calcular la integral
    double resultado = simpson_1_3(parser, a, b, n);
    if (resultado != -1) {
        std::cout << "La integral de f(x) de " << a << " a " << b << " es aproximadamente " << resultado << std::endl;
    }

    return 0;
}