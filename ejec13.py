import multiprocessing

def fibonacci(n):
    if n <= 1:
        return n
    else:
        a, b = 0, 1
        for _ in range(2, n + 1):
            a, b = b, a + b
        return b

def fibonacci_rango(start, end, resultados):
    for i in range(start, end):
        resultados[i] = fibonacci(i)

if __name__ == "__main__":
    num_procesadores = multiprocessing.cpu_count()
    num_terminos = 1000

    # Calcular la cantidad
    terminos_por_procesador = num_terminos // num_procesadores

    procesos = []
    resultados = multiprocessing.Array('i', num_terminos)
    for i in range(num_procesadores):
        start = i * terminos_por_procesador
        end = start + terminos_por_procesador if i < num_procesadores - 1 else num_terminos
        proceso = multiprocessing.Process(target=fibonacci_rango, args=(start, end, resultados))
        procesos.append(proceso)
        proceso.start()

    for proceso in procesos:
        proceso.join()

    # Print
    for i in range(num_terminos):
        print(resultados[i], end=" ")
    print()
