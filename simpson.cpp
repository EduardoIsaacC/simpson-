include <muparser/muparser.h>

float simpson(float a, float b, int n, const std::string& expr) {
    MuParser parser;
    parser.SetExpr(expr);
    parser.DefineVar("x", 0.0);

    float h = (b - a) / n;
    float sum = 0.0;

    for (int i = 0; i <= n; i++) {
        float x = a + i * h;
        parser.SetVar("x", x);
        float y = parser.Eval();
        if (i == 0 || i == n) {
            sum += y;
        } else if (i % 2 == 0) {
            sum += 2 * y;
        } else {
            sum += 4 * y;
        }
    }

    return sum * h / 3.0;
}

int main() {
    float a, b;
    int n;
    std::string expr;

    std::cout << "Ingrese la función (por ejemplo, x*sin(x) o x*cos(x)): ";
    std::getline(std::cin, expr);
    std::cout << "Ingrese el límite inferior a: ";
    std::cin >> a;
    std::cout << "Ingrese el límite superior b: ";
    std::cin >> b;
    std::cout << "Ingrese el número de intervalos n: ";
    std::cin >> n;

    if (n % 2 == 0) {
        std::cout << "El resultado de la integral es: " << simpson(a, b, n, expr) << std::endl;
    } else {
        std::cout << "n debe ser un número par." << std::endl;
    }

    return 0;
}