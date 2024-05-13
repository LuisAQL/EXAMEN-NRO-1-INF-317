#include <stdio.h>

int suma(int *a, int *b);
int resta(int *a, int *b);
int multiplicacion(int *a, int *b);
double division(int *a, int *b);

int main() {
    int num1, num2;
    
    printf("Numero 1: ");
    scanf("%d", &num1);
    printf("Numero 2: ");
    scanf("%d", &num2);
    
    //OPERACIONES
    printf("Suma: %d\n", suma(&num1, &num2));
    printf("Resta: %d\n", resta(&num1, &num2));
    printf("Multiplicacion: %d\n", multiplicacion(&num1, &num2));
    printf("Division: %.2f\n", division(&num1, &num2));
    
    //system("pause");
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
    double resultado = (double)(*a) / (double)(*b);
    return resultado;
}
