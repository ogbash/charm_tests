#include "main.decl.h"
#include "main.h"
#include "multiply.decl.h"


CProxy_Main mainProxy;


Main::Main(CkArgMsg* msg) {
  int i,j,k;

  readyCount = 0;
  doneCount = 0;
  matrix_size = 0;
	
 if (msg->argc > 1){
    matrix_size = atoi(msg->argv[1]);
  }
	
	int BLOCK_SIZE = matrix_size*matrix_size/CkNumPes();
	double (*matrix_x)[matrix_size] = (double (*)[matrix_size])new double[matrix_size*matrix_size];
	double (*matrix_y)[matrix_size] = (double (*)[matrix_size])new double[matrix_size*matrix_size];
	double (*split_x)[BLOCK_SIZE] = (double (*)[BLOCK_SIZE]) new double[matrix_size*matrix_size];
	split_bycol = new double[matrix_size*matrix_size];
	double (*split_y)[BLOCK_SIZE] = (double (*)[BLOCK_SIZE]) split_bycol;
	
	result = new double[matrix_size*matrix_size];
 
	for (i = 0; i < matrix_size; i++) {
	  for (j = 0; j < matrix_size; j++) {		
			matrix_x[i][j] = i*matrix_size+j;
			matrix_y[j][i] = i*matrix_size+j;
	  }
	}

  delete msg;

	for (i = 0; i < CkNumPes(); i++) {
		for (j = 0; j < matrix_size/CkNumPes(); j++) {
			for (k = 0; k < matrix_size;k++){
				split_x[i][j*matrix_size + k] = matrix_x[i * matrix_size/CkNumPes() + j][k];
				split_y[i][j*matrix_size + k] = matrix_y[i * matrix_size/CkNumPes() + j][k];
			}		
		}
	}


  CkPrintf("Running with %d elements using %d processors.\n",matrix_size, CkNumPes());
  mainProxy = thisProxy;
  object_array = CProxy_Multiply::ckNew(CkNumPes());
  // distribute
  for (i = 0; i < CkNumPes(); i++) {	  
    object_array[i].store(matrix_size * matrix_size/CkNumPes(), split_x[i],matrix_size);	  
  }
}

Main::Main(CkMigrateMessage* msg) { }

void Main::ready()  {
  int i;
  readyCount += 1;
  int BLOCK_SIZE = matrix_size*matrix_size/CkNumPes();
  double (*split_y)[BLOCK_SIZE] = (double (*)[BLOCK_SIZE]) split_bycol;

  if (readyCount == CkNumPes()) {
    // calculate
    CkPrintf("Start calculation\n");
    for (i = 0; i < CkNumPes(); i++) {	  
      object_array[i].multiply(matrix_size * matrix_size/CkNumPes(), split_y[i],i);	  
    }
  }
}

void Main::save_temp(int SIZE, double *number, int row_number){
	int i,j;

	double (*temp)[matrix_size] = (double (*)[matrix_size]) result;
	
	for(i = 0; i < matrix_size/CkNumPes(); i++){
		for(j = 0; j < matrix_size; j++) {
			temp[i+row_number*matrix_size/CkNumPes()][j] = number[i*matrix_size+j];
		}
	}

	
 	doneCount ++;
	//CkPrintf("donecount: %d ",doneCount);
	if (doneCount == CkNumPes()){
/*
		for (i = 0; i < matrix_size; i++) {
			CkPrintf("tulemus: ");
			for (j = 0; j < matrix_size; j++) {
			
	  			CkPrintf(" %.1f ",temp[i][j]);			
				
			}
			CkPrintf("\n");
		}
*/

		CkExit();
	}
}

#include "main.def.h"
