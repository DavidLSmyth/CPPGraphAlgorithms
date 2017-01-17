//David Smyth
//Student ID: 13383861

#include <iostream>
#include <math.h>
using namespace std;
#include "Matrix.h"
#include "Vector.h"

matrix::matrix (unsigned int Size)
{
   N = Size;
   entries = new double [N*N];
}

void matrix::setij (unsigned int i, unsigned int j, double x)
{
   if (i<N && j<N)
      entries[i*N+j]=x;
   else
      cerr << "matrix::setij(): Index out of bounds, "<<i<<"  "<<j<<" are not valid" << endl;
}
matrix::matrix (const matrix &m)
{
   N = m.N;
   entries = new double[N*N];
   for (unsigned int i=0; i<N*N; i++)
      entries[i] = m.entries[i];
}


// Overload the assignment = operator.
matrix &matrix::operator=(const matrix &B)
{
   if (this == &B)
      return(*this); // Taking care for self-assignment

   delete [] entries; // Just in case there was any memory
   // already allocated to this

   entries = new double[(B.N)*(B.N)];
   for (unsigned int i=0; i<N*N; i++)
      entries[i] = B.entries[i];

   return(*this);
}
double matrix::getij (unsigned int i, unsigned int j)
{
   if (i<N && j<N)
      return(entries[i*N+j]);
   else
   {
      cerr << "matrix::getij(): Index out of bounds." << endl;
      return(0);
   }
}

void matrix::print (void)
{
//   cout << "matrix is of size " << M << "-by-" << N << endl;
   for (unsigned int i=0; i<N; i++)
   {
      for (unsigned int j=0; j<N; j++)
        cout << "[" << entries[i*N+j] << "]";
      cout << endl;
   }
}

//works only for square matrices
// EDIT 3: NM changed this function so that it will always return something.
matrix matrix::operator*(matrix m){
    matrix returnMatrix(m.size());
    returnMatrix.zeros();
    int msize=m.size();
    if(m.size()!=N)
    {
        cerr<<"You can't multiply matrices that aren't the same size!"<<endl;
    }
    else{
        //row pos in lhs and result matrix
       for(int i=0;i<msize;i++){
           //col pos in result matrix
            for(int j=0;j<msize;j++){
                double setval=0;
                //column position in rhs matrix
                for(int k=0;k<msize;k++){
                    setval+=(this->getij(i,k)*m.getij(k,j));
                }
                returnMatrix.setij(i,j,setval);
            }
       }
    }
    return returnMatrix;
}

// EDIT 3: NM changed this function so that it will always return something.
Vector matrix::operator*(Vector v){
    int vsize=v.size();
    int msize=N;
    Vector returnVector(vsize);
    if(msize!=vsize){
        cerr<<"Matrix and Vector uneven size, please try again"<<endl;
    }
    else{
        Vector v1=Vector(vsize);
        for(int i=0;i<vsize;i++){
            double sum=0;
            for(int j=0;j<vsize;j++){
                sum+=this->getij(i,j)*v.geti(j);
            }
            returnVector.seti(i,sum);
            //cout<<"sum: "<<sum<<endl;;
        }
    }
    return returnVector;

}
//used to solve Lx=b, where L is a lower triangular matrix(including diagonal,
//x is an unknown Vector and b is a known Vector.
//L/b=x will solve this problem using the overloaded / operator
// EDIT 2: NM changed this function so that it will always return something.
Vector operator /(Vector v, matrix L)
{
   int rows=L.size();
   //cout<<"size: "<<rows<<endl;
   bool flag=false;
   double sum;
   Vector returnVector(rows);
   returnVector.zero();
   Vector printvec(rows);
   //check if the matrix is lower triangular
   for(int i=0;i<rows;i++){
      for(int j;j<rows;j++){  // EDIT: Some problem here: j is defined twice in this function
	 if(L.getij(i,j)!=0){
	    flag=true;
	    break;
	 }
      }
   }
   if(flag==true){
      cerr<<"Matrix argument needs to be lower triangluar!"<<endl;
   }
   else{
      double addition;
      returnVector.zero();
      returnVector.seti(0,v.geti(0)/L.getij(0,0));
      for(int b=1;b<rows;b++){
	 sum=0;
	 for(int a=0;a<b;a++){
	    sum+=L.getij(b,a)*returnVector.geti(a);
	 }
	 addition=(v.geti(b)-sum)/L.getij(b,b);
	 returnVector.seti(b,addition);
      }
   }
   return returnVector;
}


// EDIT 2: NM changed this function so that it will always return something.
matrix matrix::operator +(matrix m){

   int size1=this->size();
   int size2=m.size();
   matrix result(size1);

   if(size1!=size2){
      cerr<<"Size mismatch, matrices can't be added"<<endl;
   }
   else{
      for(int i=0;i<size1;i++){
	 for(int j=0;j<size1;j++){
	    result.setij(i,j,this->getij(i,j)+m.getij(i,j));
	 }
      }
   }
      return result;
}

//computer the two norm of a matrix
double matrix::norm(void){
    double maximum=0;
    for(unsigned int i=0;i<N;i++){
        double sum=0;
        for(unsigned int j=0;j<N;j++){
            sum+=sqrt(this->getij(i,j)*this->getij(i,j));
        }
        if(sum>maximum){
            maximum=sum;
        }
    }
    return maximum;
}
void matrix::zeros(void){
    for(unsigned int i=0;i<this->N;i++){
        for(unsigned int j=0;j<this->N;j++){
            this->setij(i,j,0);
        }
    }
}
matrix matrix::operator*(double d){
    matrix newmatrix(this->N);
    for(unsigned int i=0;i<this->N;i++){
        for(unsigned int j=0;j<this->N;j++){
            newmatrix.setij(i,j,this->getij(i,j)*d);
        }
    }
    return newmatrix;
}
matrix matrix::transpose(void){
    cout<<"in tranpose"<<endl;
    matrix result(this->N);
    for(unsigned int i=0;i<this->N;i++){
        for(unsigned int j=0;j<this->N;j++){
            result.setij(j,i,this->getij(i,j));
        }
    }
    return result;
}

