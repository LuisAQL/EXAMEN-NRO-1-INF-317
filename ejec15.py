import multiprocessing

def ejec15():
  print("Hola mundo")

if __name__ == "__main__":
  proceso = multiprocessing.Process(target=ejec15)

  proceso.start()

  proceso.join()
