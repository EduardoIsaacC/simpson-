def simpson_1_3(f, a, b, n):
    """
    Implementación del método de Simpson 1/3.

    Parámetros:
    f (función): La función a integrar.
    a (float): Límite inferior de integración.
    b (float): Límite superior de integración.
    n (int): Número de subintervalos (debe ser par).

    Retorna:
    float: Aproximación de la integral de f desde a hasta b usando el método de Simpson 1/3.
    """
    if n % 2 != 0:
        print("El número de subintervalos n debe ser par. Ajustando n a n+1.")
        n += 1
    
    h = (b - a) / n
    sum_odd = sum(f(a + i * h) for i in range(1, n, 2))
    sum_even = sum(f(a + i * h) for i in range(2, n, 2))
    
    integral = (h / 3) * (f(a) + 4 * sum_odd + 2 * sum_even + f(b))
    return integral

def main():
    import math
    
    # Solicitar al usuario la entrada de la función, los límites de integración y el número de subintervalos
    function_str = input("Ingrese la función a integrar (use 'x' como variable, por ejemplo 'sin(x) + x**2'): ")
    a = float(input("Ingrese el límite inferior a: "))
    b = float(input("Ingrese el límite superior b: "))
    n = int(input("Ingrese el número de subintervalos n: "))
    
    # Convertir la cadena de la función a una función utilizable
    def f(x):
        return eval(function_str)
    
    # Calcular la integral
    resultado = simpson_1_3(f, a, b, n)
    print(f"La integral de f(x) de {a} a {b} es aproximadamente {resultado:.6f}")

if __name__ == "__main__":
    main()