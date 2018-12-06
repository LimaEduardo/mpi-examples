#include <iostream>
#include <fstream>
#include <mpi.h>

using namespace std;

int main (int argc, char** argv){
  int n = 90, num_processadores, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_processadores);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank != 0){
    cout << "Recebi a mensagem " << n << ". Rank = " << rank << endl;
  }

  MPI_Finalize();

  return 0;
}