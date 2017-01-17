//David Smyth
//Student ID: 13383861
#ifndef _Vector_H_INCLUDED
#define _Vector_H_INCLUDED

class Vector {
private:
   int *entries;
   unsigned int N;
public:
   Vector (unsigned int Size=2);
   Vector (const Vector &old_Vector);
   ~Vector(void);

   unsigned int size(void) {return N;};
   unsigned int geti (unsigned int i);
   void seti (unsigned int i, int x);
   Vector operator +(Vector v);
   Vector &operator=(const Vector &b); // overload assignment operator
   Vector operator-(Vector b); // binary
   Vector operator-(void); // unary
   Vector operator *(double i);
   void print(void);
   double norm(void); // Compute the 2-norm of a Vector
   void zero(); // Set entries of Vector to zero.
   void ones();//Set all entries of Vector to one.
};
#endif // _Vector_H_INCLUDED
