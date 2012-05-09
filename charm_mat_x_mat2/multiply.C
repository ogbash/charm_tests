#include "multiply.decl.h"
#include "multiply.h"
#include "main.decl.h"


extern CProxy_Main mainProxy;

Multiply::Multiply() {}

Multiply::Multiply(CkMigrateMessage *msg) {}

//const int T_SIZE = 2000;
double *temp_row = NULL;
void *tulemus = NULL;
int counter = 0;

void Multiply::store(int B_SIZE, double *row, int matrix_size) {
	this->matrix_size = matrix_size;
	temp_row = new double[B_SIZE];
	int SIZE = matrix_size;
	for (int i = 0; i < SIZE*SIZE/CkNumPes(); i++){			
		temp_row[i] = row[i];		
	}

	mainProxy.ready();
}

void * Multiply::getResultArray(int matrix_size) {
	if (tulemus==NULL) 
		tulemus = new double[matrix_size*matrix_size];
  return tulemus;
}

void Multiply::multiply(int B_SIZE, double* column, int column_number){
	int i,j,k;

	double (*temp_tulemus)[matrix_size] = 
		(double (*)[matrix_size]) getResultArray(matrix_size);

	int SIZE = matrix_size;
	for (i = 0; i < SIZE/CkNumPes(); i++){
		for (j = 0; j < SIZE/CkNumPes(); j++){			
			for (k= 0; k < SIZE; k++){
				temp_tulemus[SIZE/CkNumPes()*thisIndex+i][column_number * SIZE/CkNumPes() + j] += temp_row[i*SIZE + k] * column[j*SIZE + k];		
			}
		}		
	}


	for (i = 0; i < CkNumPes()-1; i++){
		thisProxy[(thisIndex + 1+ i)%CkNumPes()].multiply_each(SIZE * SIZE/CkNumPes(),column, column_number);
	}		

}

void Multiply::multiply_each(int B_SIZE, double* column, int column_number){
	int i,j,k;

	double (*temp_tulemus)[matrix_size] = (double (*)[matrix_size]) getResultArray(matrix_size);

	int SIZE = matrix_size;
	for (i = 0; i < SIZE/CkNumPes(); i++){
		for (j = 0; j < SIZE/CkNumPes(); j++){			
			for (k= 0; k < SIZE; k++){		
				temp_tulemus[SIZE/CkNumPes()*thisIndex+i][column_number*SIZE/CkNumPes() + j] += temp_row[i*SIZE + k] * column[j*SIZE + k];			
			}
		}		
	}

double temp_split[CkNumPes()][SIZE/CkNumPes() * SIZE + SIZE];

	for (i = 0; i < CkNumPes(); i++) {
		for (j = 0; j < SIZE/CkNumPes(); j++) {
			for (k = 0; k < SIZE;k++){
				temp_split[i][j*SIZE + k] = temp_tulemus[i * SIZE/CkNumPes() + j][k];
				
			}		
		}
	}

	counter++;
	if (counter == CkNumPes()-1){
		mainProxy.save_temp(SIZE * SIZE/CkNumPes(),temp_split[thisIndex],thisIndex);	
	}	
}

#include "multiply.def.h"
