// David Smyth
//Student Number: 13383861
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Vector.h"
#include "Matrix.h"
#include "RandomKRegularGraph.h"

using namespace std;
int getN();
int getK();


//Don't generate a graph with more than 1000 nodes! It takes minutes as the program has to check if the graph is connected
int main(void){
    //N is the number of vertices
   int N;
   //K is the number of edges per vertex.
   int K;
   N=getN();
   K=getK();
   //get valid user input
   while(N<=(K+1)){
        cout<<"This graph can't be generated, please try again"<<endl;
        N=getN();
        K=getK();
   }
   cout<<"Constructing the graph"<<endl;
    RandomKRegularGraph g(K,N);
    while(g.verifyGraphIsKConnected()==false){
        std::srand(time(0));
        //cout<<"Restarting"<<endl;
        //this is the same as the above graph!
        RandomKRegularGraph g1(K,N);
        g=g1;
    }
    cout<<"Graph has been constructed "<<endl;
    cout<<"Is the graph connected as specified?(1=true, 0=false) "<<g.verifyGraphIsKConnected()<<endl;
    //g.PrintGraph();
    char input;
    do{
        cout<<"Would you like to write to a DOT file?(y/n)";
        cin>>input;
    }
    while(input!='y'&&input!='n');
    if(input=='y'){
        g.writeToDotFile();
    }
    cout<<"Checking if an Eulerian path exists"<<endl;
    if(g.EulerianPathExists()==true){
        g.printEulerianPath();
    }
    else{
        cout<<"There is no Eulerian path in this graph"<<endl;
    }
    return (0);
}

int getN(){
   unsigned int N;
   cout<<"Please enter the number of nodes in the graph"<<endl;
   cin>>N;
   return N;
}
int getK(){
   unsigned int K;
   cout<<"Please enter the number of edges per node of the random k-regular graph"<<endl;
   cin>>K;
   return K;
}
