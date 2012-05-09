#ifndef __MAIN_H__
#define __MAIN_H__


class Main : public CBase_Main {

 private:
  /// Member Variables (Object State) ///
  
  int doneCount;
	int i;
	int j;
	int k;
	double *result;

 public:

	int matrix_size;
  /// Constructors ///
  Main(CkArgMsg* msg);
  Main(CkMigrateMessage* msg);

  /// Entry Methods ///
	void save_temp(int SIZE, double number[], int row_number);

};


#endif //__MAIN_H__
