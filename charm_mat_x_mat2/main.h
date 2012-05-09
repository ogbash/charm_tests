#ifndef __MAIN_H__
#define __MAIN_H__


class Main : public CBase_Main {

 private:
  /// Member Variables (Object State) ///
  
  int readyCount;
  int doneCount;
  double *result;
  double *split_bycol;
  CProxy_Multiply object_array;

 public:

	int matrix_size;
  /// Constructors ///
  Main(CkArgMsg* msg);
  Main(CkMigrateMessage* msg);

  /// Entry Methods ///
  void save_temp(int SIZE, double number[], int row_number);
  void ready();

};


#endif //__MAIN_H__
