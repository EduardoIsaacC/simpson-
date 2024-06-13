#include <iostream>
#include <string>
#include <sstream>
#include "muParser.h"

float simpson(float a, float b, int n, const std::string& expr) {
    mu::Parser parser;
    double var = 0.0;
    parser.DefineVar("x", &var);
    
    // Reemplazar "x^n" con "pow(x,n)" en la expresión
    std::string expression = expr;
    size_t pos = 0;
    while ((pos = expression.find("^", pos)) != std::string::npos) {
        if (pos > 0 && std::isdigit(expression[pos - 1])) {
            // Encontrar la parte izquierda del ^
            size_t left_pos = expression.find_last_of("0123456789x", pos - 1);
            if (left_pos != std::string::npos) {
                // Encontrar la parte derecha del ^
                size_t right_pos = expression.find_first_not_of("0123456789./", pos + 1);
                if (right_pos == std::string::npos) {
                    right_pos = expression.length();
                }
                // Extraer la base y el exponente
                std::string base = expression.substr(left_pos, pos - left_pos);
                std::string exponent = expression.substr(pos + 1, right_pos - pos - 1);
                // Construir la nueva expresión
                std::stringstream ss;
                ss << "pow(" << base << "," << exponent << ")";
                expression.replace(left_pos, right_pos - left_pos, ss.str());
                // Mover pos al final del reemplazo
                pos = left_pos + ss.str().length();
                continue;
            }
        }
        ++pos;
    }

    try {
        parser.SetExpr(expression);
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

    std::cout << "Ingrese la función (por ejemplo, sin(x), cos(x), exp(x) o x^2, x^3, x^(1/2)): ";
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