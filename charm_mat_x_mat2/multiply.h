#ifndef __MULTIPLY_H__
#define __MULTIPLY_H__

class Multiply : public CBase_Multiply {

 public:

	int i;
	int j;
	int k;

  Multiply();
  Multiply(CkMigrateMessage *msg);

	void * getResultArray(int matrix_size);

  /// Entry Methods ///
  void multiply(int B_SIZE, double matrix_x[], double matrix_y[], int row_number, int column_number);	
	void multiply_each(int B_SIZE, double column[], int column_number, int matrix_size);

};


#endif //__MULTIPLY_H__
