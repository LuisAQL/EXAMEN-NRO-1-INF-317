#include <stdio.h>
#include <omp.h>

int multiplicar(int a, int b) {
  int c = 0;

  #pragma omp parallel for
  for (int i = 0; i < b; i++) {
    c += a;
  }
  return (int)c;
}

int dividir(int a, int b) {
  if (b == 0) {
    printf("Error: La división por cero no está permitida.\n");
    return 0;
  }
  int signo = 1;
  if (a < 0) {
    a = -a;
    signo = -signo;
  }
  if (b < 0) {
    b = -b;
    signo = -signo;
  }

  int c = a / b;
  return c * signo;
}

int main() {
  int a, b;
  printf("Ingrese el primer número: ");
  scanf("%d", &a);
  printf("Ingrese el segundo número: ");
  scanf("%d", &b);

  int resultadoMultiplicacion = multiplicar(a, b);
  printf("Multiplicacion: %d\n", resultadoMultiplicacion);

  int resultadoDivision = dividir(a, b);
  printf("Division: %d\n", resultadoDivision);

  return 0;
}

