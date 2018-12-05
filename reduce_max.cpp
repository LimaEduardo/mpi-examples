#include <iostream>
#include <fstream>
#include <mpi.h>

#define TAMANHO 1000

using namespace std;



int main (int argc, char** argv){
  int rank, num_processadores;

  ifstream arquivo;
  arquivo.open("numeros");
  int numeros[TAMANHO];

  if(arquivo.is_open()){
    for(int i = 0; i < TAMANHO; i++){
      arquivo >> numeros[i];
    }
  }

  arquivo.close();

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_processadores);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int limite = TAMANHO/num_processadores;

  int maior_local = 0;
  int inicio = rank*limite;
  for(int i = inicio; i < inicio + limite; i++){
    if (numeros[i] > maior_local) {
      maior_local = numeros[i];
    }
  }

  int maior_global;
  MPI_Reduce(&maior_local, &maior_global, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

  if (rank == 0){
    cout << "RANK: " << rank << " Maior local: " << maior_local << endl;
    cout << "RANK: " << rank << " Maior global: " << maior_global << endl;
  } else {
    cout << "RANK: " << rank << " Maior local: " << maior_local << endl;
  }

  MPI_Finalize();

  return 0;
}