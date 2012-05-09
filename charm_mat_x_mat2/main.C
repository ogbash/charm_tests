#include "main.decl.h"
#include "main.h"
#include "multiply.decl.h"


CProxy_Main mainProxy;


Main::Main(CkArgMsg* msg) {

  doneCount = 0;
  matrix_size = 4;
	
 if (msg->argc > 1){
    matrix_size = atoi(msg->argv[1]);
  }
	
	double matrix_x[matrix_size][matrix_size];
	double matrix_y[matrix_size][matrix_size];
	double split_x[CkNumPes()][matrix_size * matrix_size/CkNumPes()];
	double split_y[CkNumPes()][matrix_size * matrix_size/CkNumPes()];
	
 
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
  CProxy_Multiply object_array = CProxy_Multiply::ckNew(CkNumPes());
	for (i = 0; i < CkNumPes(); i++) {	  
	  object_array[i].multiply(matrix_size * matrix_size/CkNumPes(), split_x[i],split_y[i],matrix_size,i);	  
	}
}

Main::Main(CkMigrateMessage* msg) { }

void Main::save_temp(int SIZE, double *number, int row_number){
	
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
			
	  			CkPrintf(" %d ",temp[i][j]);			
				
			}
			CkPrintf("\n");
		}
*/
		CkExit();
	}
}

#include "main.def.h"