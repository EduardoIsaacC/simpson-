#include <iostream>
#include <string>
#include "muParser.h"

float simpson(float a, float b, int n, const std::string& expr) {
    mu::Parser parser;
    double var = 0.0;
    parser.DefineVar("x", &var);
    
    try {
        parser.SetExpr(expr);
    } catch (mu::ParserError &e) {
        std::cout << "Error en la configuración de la expresión: " << e.GetMsg() << std::endl;
        return 0.0;
    }

    float h = (b - a) / n;
    float sum = 0.0;

    std::cout << "Pasos del método de Simpson 1/3:" << std::endl;
    std::cout << "1. Se divide el intervalo [" << a << ", " << b << "] en " << n << " subintervalos." << std::endl;
    std::cout << "2. Se calcula la anchura de cada subintervalo: h = (" << b << " - " << a << ") / " << n << " = " << h << std::endl;

    for (int i = 0; i <= n; ++i) {
        float x = a + i * h;
        var = x;
        double y = 0.0;
        try {
            y = parser.Eval();
        } catch (mu::ParserError &e) {
            std::cout << "Error en la evaluación de la función: " << e.GetMsg() << std::endl;
            return 0.0;
        }

        std::cout << "x[" << i << "] = " << x << ", f(x[" << i << "]) = " << y << std::endl;

        if (i == 0 || i == n) {
            sum += y;
            std::cout << "sum += f(x[" << i << "]) = " << y << std::endl;
        } else if (i % 2 == 0) {
            sum += 2 * y;
            std::cout << "sum += 2 * f(x[" << i << "]) = " << 2 * y << std::endl;
        } else {
            sum += 4 * y;
            std::cout << "sum += 4 * f(x[" << i << "]) = " << 4 * y << std::endl;
        }
    }

    float result = sum * h / 3.0;
    std::cout << "5. Se aplica la fórmula de Simpson 1/3:" << std::endl;
    std::cout << "Resultado = sum * h / 3 = " << sum << " * " << h << " / 3 = " << result << std::endl;

    return result;
}

int main() {
    float a, b;
    int n;
    std::string expr;

    std::cout << "Ingrese la función (por ejemplo, sin(x) o cos(x) o exp(x)): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar cualquier entrada pendiente
    std::getline(std::cin, expr);

    if (expr.empty()) {
        std::cout << "La expresión no puede estar vacía." << std::endl;
        return 1;
    }

    std::cout << "Ingrese el límite inferior a: ";
    std::cin >> a;
    std::cout << "Ingrese el límite superior b: ";
    std::cin >> b;
    std::cout << "Ingrese el número de intervalos n (debe ser par): ";
    std::cin >> n;

    if (n % 2 == 0) {
        float result = simpson(a, b, n, expr);
        std::cout << "El resultado de la integral es: " << result << std::endl;
    } else {
        std::cout << "n debe ser un número par." << std::endl;
    }

    return 0;
}