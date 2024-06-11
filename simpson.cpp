#include<iostream>
#include<cmath>
#include<string>
#include<functional>
#include<sstream>
#include<limits>

using namespace std;

// Función que evalúa la expresión ingresada por el usuario
float evalExpr(string expr, float x) {
    istringstream iss(expr);
    string token;
    float result = 0.0;
    while (iss >> token) {
        if (token == "x") {
            result = x;
        } else if (token == "sin") {
            iss >> token;
            result = sin(stof(token));
        } else if (token == "cos") {
            iss >> token;
            result = cos(stof(token));
        } else if (token == "exp") {
            iss >> token;
            result = exp(stof(token));
        } else if (token == "e") {
            result = exp(1.0);
        } else if (token == "log") {
            iss >> token;
            result = log(stof(token));
        } else if (token == "sqrt") {
            iss >> token;
            result = sqrt(stof(token));
        } else {
            result = stof(token);
        }
    }
    return result;
}

float simpson(float a, float b, int n, function<float(float)> func) {
    try {
        float h, x[n+1], sum = 0;
        int j;
        h = (b-a)/n;
        
        x[0] = a;
        
        cout << "Pasos del método de Simpson 1/3:" << endl;
        cout << "1. Se divide el intervalo [" << a << ", " << b << "] en " << n << " subintervalos." << endl;
        cout << "2. Se calcula la anchura de cada subintervalo: h = (" << b << " - " << a << ") / " << n << " = " << h << endl;
        
        for(j=1; j<=n; j++)
        {
            x[j] = a + h*j;
            cout << "3. Se calcula el valor de x en cada subintervalo: x[" << j << "] = " << a << " + " << h << " * " << j << " = " << x[j] << endl;
        }
        
        cout << "4. Se aplica la fórmula de Simpson 1/3:" << endl;
        sum = func(x[0]) + func(x[n]);
        for(j=1; j<n; j++)
        {
            if (j % 2 == 0)
                sum += 2*func(x[j]);
            else
                sum += 4*func(x[j]);
            cout << "   sum += " << (j % 2 == 0? "2*" : "4*") << "f(x[" << j << "])" << endl;
        }
        
        cout << "5. Se devuelve el resultado final: sum * h / 3 = " << sum << " * " << h << " / 3 = " << sum*h/3 << endl;
        
        return sum*h/3;
    } catch (std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 0.0;
    }
}

int main()
{
    float a,b;
    int n;
    string funcStr;
    cout << "Ingrese la función (por ejemplo, x*sin(x) o x*cos(x)): ";
    getline(cin, funcStr);
    cout << "Ingrese el límite inferior a: ";
    while (!(cin >> a)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    cout << "Ingrese el límite superior b: ";
    while (!(cin >> b)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    cout << "Ingrese el número de intervalos n: ";
    while (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    
    auto func = [&funcStr](float x) {
        return evalExpr(funcStr, x);
    };
    
    if (n%2 == 0)
        cout << "El resultado de la integral es: " << simpson(a,b,n,func) << endl;
    else
        cout << "n debe ser un número par." << endl;
    
    return 0;
}