import multiprocessing

def generar(inicio, fin, paso, resultado):
    serie = []
    for i in range(inicio, fin, paso):
        serie.append(i)
    resultado.put(serie)

if __name__ == "__main__":
    N = 80  
    M = 5   
    paso = 2  
    terminos_por_procesador = N // M 
    
    resultados = multiprocessing.Queue()
    procesos = []
    
    for i in range(M):
        inicio = i * terminos_por_procesador * paso
        fin = inicio + terminos_por_procesador * paso
        proceso = multiprocessing.Process(target=generar, args=(inicio, fin, paso, resultados))
        procesos.append(proceso)
        proceso.start()
    
    for proceso in procesos:
        proceso.join()
    
    #print
    for i in range(M):
        print(f" {i+1}: {resultados.get()}")
