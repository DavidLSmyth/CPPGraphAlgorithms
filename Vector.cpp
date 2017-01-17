//David Smyth
//Student ID: 13383861

#include <iostream>
#include <math.h>
using namespace std;
#include "Vector.h"

Vector::Vector (unsigned int N)
{
   this->N = N;
   entries = new int[N];
}
//copy constructor
Vector::Vector (const Vector &old_Vector)
{
   N = old_Vector.N;
   entries = new int[N];
   for (unsigned int i=0; i<N; i++)
      entries[i] = old_Vector.entries[i];
}
Vector::~Vector () {
   delete [] entries;
}

void Vector::seti (unsigned int i, int x) {
   if (i<N)
      entries[i]=x;
   else
      cerr << "Vector::seti(): Index out of bounds." << endl;
}

unsigned int Vector::geti (unsigned int i) {
   if (i<N)
      return(entries[i]);
   else {
      cerr << "Vector::geti(): Index out of bounds." << endl;
      return(0);
   }
}


// EDIT 4: NM changed this function so that it will always return something.
Vector Vector::operator+(Vector v)
{
    Vector c(N);
    if(N==v.N){
        for(unsigned int i=0;i<N;i++)
	   c.entries[i]=this->entries[i]+v.entries[i];
    }
    else
       cerr<<"Cannot add Vectors of uneven size"<<endl;
       return c;

}

// Overload the - (binary) operator. As in c=a-b
Vector Vector::operator-(Vector b)
{
   Vector c(N); // Make b the size of a
   if (N != b.N)
      cerr << "Vector:: operator- : dimension mismatch!" << endl;
   else
      c = *this + (-b);
   return(c);
}
// Overload the - (unary) operator. As in b=-a;
Vector Vector::operator-(void)
{
   Vector b(N); // Make b the size of a
   for (unsigned int i=0; i<N; i++)
      b.entries[i] = -entries[i];
   return(b);
}
Vector &Vector::operator=(const Vector &b)
{
   if (this == &b)
      return(*this); // Taking care for self-assignment

   delete [] entries; // In case memory was already allocated

   N = b.N;
   entries = new int[b.N];
   for (unsigned int i=0; i<N; i++){
      entries[i]=b.entries[i];
   }
   return(*this);
}

void Vector::print (void)
{
   for (unsigned int i=0; i<N; i++)
      cout << "[" << entries[i] << "]" << endl;
}

double Vector::norm (void)
{
   double x=0;
   for (unsigned int i=0; i<N; i++)
      x+=entries[i]*entries[i];
   return (sqrt(x));
}

void Vector::zero(void)
{
   for (unsigned int i=0; i<N; i++)
      entries[i]=0;
}
void Vector::ones(void){
    for(unsigned int i=0;i<N;i++){
        entries[i]=1;
    }
}
Vector Vector::operator *(double a){
    Vector returnVector(N);
    for(unsigned int i=0;i<N;i++){
        returnVector.seti(i,entries[i]*a);
    }
    return returnVector;
}

