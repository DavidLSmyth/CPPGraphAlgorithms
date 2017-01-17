//David Smyth
//Student ID: 13383861

#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include "Vector.h"

class matrix {
private:
   double *entries;
   unsigned int N;
public:
   matrix (unsigned int Size);
   matrix (const matrix &m);
   ~matrix(void) { delete [] entries; };

   unsigned int size(void) {return (N);};
   double getij (unsigned int i, unsigned int j);
   void setij (unsigned int i, unsigned int j, double x);
   matrix &operator=(const matrix &B);
   matrix operator+(matrix m);
   matrix operator*(matrix m);
   matrix operator*(double d);
   void zeros(void);
   Vector operator*(Vector v);
   friend Vector operator /(Vector v, matrix L);
   void print(void);
   double norm(void);
   matrix transpose(void);
};
#endif
