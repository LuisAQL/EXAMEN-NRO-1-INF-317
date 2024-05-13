#include <iostream>

// Funciones
int suma(int *a, int *b);
int resta(int *a, int *b);
int multiplicacion(int *a, int *b);
double division(int *a, int *b);

int main() {
    int num1, num2;
    std::cout << "Numero 1:";
    std::cin >> num1;
    std::cout << "Numero 2:";
    std::cin >> num2;
    
    //OPERACIONES
    std::cout << "Suma: " << suma(&num1, &num2) << std::endl;
    std::cout << "Resta: " << resta(&num1, &num2) << std::endl;
    std::cout << "Multiplicacion: " << multiplicacion(&num1, &num2) << std::endl;
    std::cout << "Division: " << division(&num1, &num2) << std::endl;
    
    return 0;
}
int suma(int *a, int *b) {
    return *a + *b;
}
int resta(int *a, int *b) {
    return *a - *b;
}
int multiplicacion(int *a, int *b) {
    int resultado = 0;
    for (int i = 0; i < *b; i++) {
        resultado = suma(&resultado, a);
    }
    return resultado;
}
double division(int *a, int *b) {
    double resultado = static_cast<double>(*a) / static_cast<double>(*b);
    return resultado;
}
