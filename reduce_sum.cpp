#include <iostream>
#include <fstream>
#include <mpi.h>

#define SIZE 1000

using namespace std;

int main(int argc, char** argv){

  int numProcessadores, rank;

  ifstream file;
  file.open("numeros");
  int numeros[SIZE];

  if(file.is_open()){
    for (int i = 0; i < SIZE; i++){
      file >> numeros[i];
    }
  }
  file.close();

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcessadores);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int limite = SIZE/numProcessadores;

  int soma_local = 0;

  int inicio = rank * limite;

  for (int i = inicio; i < inicio + limite ; i++){
    soma_local += numeros[i];
  }

  int soma_global;
  MPI_Reduce(&soma_local, &soma_global, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0){
    cout << "Soma local: " << soma_local << " Rank : " << rank << endl;
    cout << "Soma global: " << soma_global << endl;
  } else {
    cout << "Soma local: " << soma_local << " Rank : " << rank << endl;
  }

  MPI_Finalize();
  return 0;
}