#ifndef __MULTIPLY_H__
#define __MULTIPLY_H__

class Multiply : public CBase_Multiply {

 public:

	int matrix_size;

  Multiply();
  Multiply(CkMigrateMessage *msg);

	void * getResultArray(int matrix_size);

  /// Entry Methods ///
  void store(int B_SIZE, double matrix_x[], int matrix_size);	
  void multiply(int B_SIZE, double matrix_y[], int column_number);	
  void multiply_each(int B_SIZE, double column[], int column_number);

};


#endif //__MULTIPLY_H__
