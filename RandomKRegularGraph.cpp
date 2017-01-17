//David Smyth
//ID: 13383861
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Matrix.h"
#include "Triplet.h"
#include "Vector.h"
#include "RandomKRegularGraph.h"
#include <queue>
#include <stack>
using namespace std;
RandomKRegularGraph::RandomKRegularGraph(unsigned int degree,unsigned int noOfVertices){
   //cerr << "RandomKRegularGraph Entered the regular constructor" << endl;
   //Initialise

   NoOfVertices=noOfVertices;
   Degree=degree;

   //A=new matrix(NoOfVertices);
   A=new triplet(NoOfVertices,80000);
   //A->zeros();

   unsigned int ConnectedToOtherVertices;
   unsigned int VerticesLeftToConnectTo;
   //keeps track of how many edges each node has
   Vector KConnected(NoOfVertices);
   //tells vertex which other vertices available to connect to
   Vector Connect(Degree);
   //nothing is connected at the start
   KConnected.zero();
   Connect.zero();
   unsigned int counter=1;
   //if graph isn't K connected start again!
   //if N=6 and K=2:
   //e.g.   .__.
    //    . \  \.
    //      . \./
   for(unsigned int row=0;row<NoOfVertices-1;row++){
        ConnectedToOtherVertices=this->getRowSum(row);
        //cout<<"Node equals"<<row<<"and is connected to "<<ConnectedToOtherVertices<<"other vertices"<<endl;
        if(ConnectedToOtherVertices==Degree){
            //cout<<"vertex is already fully connected"<<endl;
            continue;
        }
        else{
            VerticesLeftToConnectTo=Degree-ConnectedToOtherVertices;
            //cout<<"need to connect to"<<VerticesLeftToConnectTo<<"other vertices"<<endl;
            Connect=this->getNotFullNodes(KConnected,VerticesLeftToConnectTo,row);
            //cout<<"Connect to"<<endl;
            //Connect.print();
            //cout<<"Kconnected"<<endl;
            //KConnected.print();
            //cout<<""<<endl;
            for(unsigned int j=0;j<Connect.size();j++){
                //set to counter instead of one so that I can keep track of which edges
                //have been visited already i.e. counter represents the edge number
                A->setij(row,Connect.geti(j),1);
                A->setij(Connect.geti(j), row,1);
                counter++;
              //  cout<<"Connected vertex "<<row<<" to vertex "<<Connect.geti(j)<<endl;
                //cout<<"Kconnected.geti(j)"<<KConnected.geti(Connect.geti(j))<<endl;
                KConnected.seti(row,KConnected.geti(row)+1);
                KConnected.seti(Connect.geti(j),KConnected.geti(Connect.geti(j))+1);
            }
        }
        //cout<<"KConnected"<<endl;
        //KConnected.print();
   }
   unsigned int s;
   //NotKDegree is the degree of the single node that can be less than K
   NotKDegree=Degree;
   for(unsigned int a=0;a<NoOfVertices;a++){
       s=this->getRowSum(a);
       //cout<<"S: "<<s<<endl;
       if((s)<Degree){
            //cout<<"Setting NotKDegree to: "<<s<<endl;
            NotKDegree=s;
       }
   }
   //cout<<"algorithm has finished"<<endl;
   //cout<<"NotKDegree "<<NotKDegree<<endl;
   //cerr << "RandomKRegularGraph Exiting the regular constructor" << endl;

}
//copy consctructor
RandomKRegularGraph &RandomKRegularGraph::operator=(const RandomKRegularGraph &B){
    //cerr << "RandomKRegularGraph: entering assignment constructor"<<endl;
    if (this == &B)
      return(*this);
    else{
        Degree = B.Degree;
        NoOfVertices=B.NoOfVertices;
        NotKDegree=B.NotKDegree;
        A=B.A;
        return (*this);
    }
    //cerr << "RandomKRegularGraph: exiting  assignment constructor"<<endl;
}


RandomKRegularGraph::~RandomKRegularGraph(void){
   //cerr << "RandomKRegularGraph: entering deconstructor"<<endl;
   //cerr << "Releasing memory stored at " <<  A;
   //cerr << "RandomKRegularGraph: entering deconstructor"<<endl;
}


void RandomKRegularGraph::PrintGraph(void){
    A->print();
}
Vector RandomKRegularGraph::getNotFullNodes(Vector v,unsigned int toFill,unsigned int currentVertex){
   std::srand(time(0)); // EDIT NM removed this so to get reproducable results.
    unsigned int counter=0;
    //represents how many vertices don't have k edges
    unsigned int sum=0;
    //total number of nodes that aren't full
    unsigned int total=0;
    //cout<<"Current vertex "<<currentVertex;
    //cout<<"v"<<endl;
    //v.print();
    for(unsigned int j=0;j<v.size();j++){
        if((v.geti(j)<Degree)&&j!=currentVertex){
           // cout<<"v.geti"<<v.geti(j)<<endl;
            total++;
        }
    }
    //cout<<"total: "<<total<<endl;
    //cout<<"Current Node: "<<currentVertex<<endl;
    //cout<<"NEED TO FILL: "<<toFill<<endl;
    int nonFull[total];
    //put all the non "full" vertices into an array
    //cout<<"current vertex"<<currentVertex<<endl;
    for(unsigned int i=0;i<v.size();i++){
        if(v.geti(i)!=Degree&&(i!=currentVertex)){
            //cout<<"i"<<i<<endl;
            sum++;
            //ith element in v represents a not "full" vertex
            nonFull[counter]=i;
            counter++;
        }
    }
    //cout <<"nonFull elements: "<<endl;
    //for (int x=0;x<total; x++){
        //cout<< "notFfull["<<x<<"]: "<<nonFull[x]<<endl;
    //}
    //shuffle the array to randomize selection
    random_shuffle(&nonFull[0],&nonFull[total]);
    //currently easier to return a Vector than an array
    if(toFill>total){
        //cerr<<"algorithm needs to start again"<<endl;
        toFill=total;
    }
    Vector returnVector(toFill);
    returnVector.zero();
    for(unsigned int a=0;a<toFill;a++){
        //cout<<"setting "<<a<<"to "<<nonFull[a]<<endl;
        if(unsigned(nonFull[a])<=NoOfVertices){
           returnVector.seti(a,nonFull[a]);
        }
        else{
            //cout<<"a: "<<a<<"nonFull[a]: "<<nonFull[a]<<endl;
            cerr<<"Bug detected"<<endl;
        }
    }
    return returnVector;
}
bool RandomKRegularGraph::isConnected(){
    bool flag=false;
    //breadth first search from arbitrary node to all other nodes
    for(unsigned int i=0;i<NoOfVertices;i++){
        if(bfs(0,i)==false){
            flag=true;
            break;
        }
    }
    if(flag==false){
        //cout<<"Graph is connected"<<endl;
        return true;
    }
    else{
        //cout<<"Graph isn't connected"<<endl;
        return false;
    }
}

bool RandomKRegularGraph::isKRegular(void){
   unsigned int total=0;
   //checks that maximum of one node is not connected to k others
   int onlyOne=0;
   for(unsigned int s=0;s<A->size();s++){
       total=0;
       for(unsigned int r=0;r<A->size();r++){
            if(A->getij(s,r)!=0){
                total++;
            }
       }
       if(total!=Degree){
            onlyOne++;
       }
   }
   //cout<<"onlyOne: "<<onlyOne<<endl;
    if(onlyOne==0||onlyOne==1){
        return true;
    }
    else{
        return false;
    }
}
//gets the sum of any row, represents the degree of the corresponding node
int RandomKRegularGraph::getRowSum(unsigned int row){
    int RowSum=0;
    for(unsigned int j=0;j<A->size();j++){
        if(A->getij(row,j)!=0){
            RowSum++;
        }
    }
    return RowSum;
}
bool RandomKRegularGraph::writeToDotFile(void){
    ofstream CSVFile;
    string FileName="dotfile.csv";

   CSVFile.open(FileName.c_str()); // Open take a "C string" argument
   for (unsigned int i=0; i<NoOfVertices; i++)
   {
    for (unsigned int j=0; j<NoOfVertices-1; j++){
        if(A->getij(i,j)>0){
            CSVFile <<1 << ",";
        }
        else{
            CSVFile <<0<< ",";
        }
        }
        if(A->getij(i,NoOfVertices-1)>0){
            CSVFile<<1<<endl;
        }
        else{
            CSVFile<<0<<endl;
        }
   }

   CSVFile.close() ;
    string AdjFileName="dotfile.csv";
   ifstream AdjFile;

   // Prompt the user  for the name of the file
   AdjFile.open(AdjFileName.c_str());
   while (AdjFile.fail())
   {
      cerr << "Error - can't open file " << AdjFileName
	   << ". Try again. " << endl;
      cout << "Enter the name of a \"csvt\" file: " << endl;
      cin >> AdjFileName;
   }

   // Check the number of rows in the file
   int N=0;
   char c;
   AdjFile.get(c);
   while(!AdjFile.eof())
   {
      if (c == '\n')
	 N++;
      AdjFile.get(c);
   }

   cout << AdjFileName << " has " << N << " rows." << endl;

   // Should really check that there are the same number of rows
   //   but we are going to be a little lazy

   // Rewind...
   AdjFile.clear();
   AdjFile.seekg(ios::beg);

   // Now make the output file:
   string DotFileName  = AdjFileName;
   // Change ".csv" to ".gv"
   DotFileName[DotFileName.length()-3]='g';
   DotFileName[DotFileName.length()-2]='v';
   DotFileName[DotFileName.length()-1]='\0';

   cout << "Writing to " << DotFileName << endl;
   ofstream DotFile(DotFileName.c_str());
   if (DotFile.fail())
   {
      cout << "Error opening " << DotFileName << endl;
      exit(EXIT_FAILURE);
   }

   DotFile << "digraph G {" << endl;
   for (int row=1; row<=N; row++)
   {
      DotFile << row << " -> {";
      for (int col=1; col<=N; col++)
      {
	 AdjFile.get(c); // this should be a 0 or 1
	 if (c =='1')
	    DotFile << col << " ";
	 AdjFile.get(c); // this should be a comma or '\n'
      }
      DotFile << "}" << endl;
   }
   DotFile << "}" << endl;

   AdjFile.close() ;
   DotFile.close();
   return true;
}
//breadth first search method
bool RandomKRegularGraph::bfs(unsigned int node1,unsigned int node2){
    //cout<<"in bfs"<<endl;
    unsigned int counter=0;
    //size accommodates maximum number of edges in the graph
    Vector visited(NoOfVertices);
    visited.zero();
    queue<int> q;
    q.push(node1);
    unsigned int current;
    bool flag;
    bool ispath=false;
    unsigned int get;
    //string yes;
    bool flag1;
    while(q.empty()==false&&counter<NoOfVertices){
        current=q.front();
        q.pop();
        flag1=false;
        for(unsigned int x=0;x<counter;x++){
            //cout<<"x, visited.getx(coutner) "<<x<<" "<<visited.geti(x)<<endl;
            if(current==visited.geti(x)){
                //cout<<"flagged, node "<<x<<" has already been visited"<<endl;
                flag1=true;
                break;
            }
        }
        if(flag1==true){
            continue;
        }
        else{
        //cout<<"continue>"<<endl;
        //cin>>yes;
        //cout<<"current, goal"<<current<<"   "<<node2<<endl;
        //cout<<current<<" has been visited"<<endl;
        visited.seti(counter,current);
        if(current==node2){
            //cout<<"Path Found!"<<endl;
            ispath=true;
            break;
        }
        else{
            //cout<<"visited"<<endl;
            //visited.print();
            //move onto next node
            counter++;
            for(unsigned int i=0;i<A->size();i++){
                get=A->getij(current,i);
                if(get!=0){
                    flag=false;
                    for(unsigned int c=0;c<counter;c++){
                        //cout<<"i, visited.geti(coutner) "<<i<<" "<<visited.geti(c)<<endl;
                        if(i==visited.geti(c)){
                            //cout<<"flagged, node "<<i<<" has already been visited"<<endl;
                            flag=true;
                            break;
                        }
                    }
                    if(flag==false){
                        //cout<<i<<"pushed onto the queue"<<endl;
                        q.push(i);
                    }
                }
            }
        }
    }
    }
    if(ispath==true){
        return true;
    }
    else{
    //visited.print();
    cout<<"Cannot reach vertex "<<node2<<" from vertex "<<node1<<endl;
    return false;
    }
}
// EDIT NM: This function does not appear to do anything!
//works
bool RandomKRegularGraph::EulerianPathExists(){
    if(this->isConnected()==false){
        cout<<"The graph has connected components, there is no Eulerian path!"<<endl;
        return false;
    }
    else{
        //cout<<"Degree%: "<<Degree%2<<endl;
        //cout<<"NotKDegree: "<<NotKDegree<<endl;
        //cout<<"NotKDegree%2: "<<NotKDegree%2<<endl;
        if(Degree%2==0){
            if(NotKDegree%2==0){
                //cout<<"Eulerian path exists!"<<endl;
                return true;
            }
            else{
                //cout<<"Eulerian path doens't exist!"<<endl;
                return false;
            }
        }
        else{
            //the reason for this is the graph is K connected: if we are to have two vertices of odd degree and one of even degree
            //then the degree of the even degree vertex must be less than that of the other two; but this graph cannot be generated as
            //there will never be enough vertices to satisfy this condition unless K=1 in which case the remaining vertex will be of
            //degree 0 - so there is still no Eulerian path.
            //cout<<"Eulerian path doesn't exist!"<<endl;
            return false;
        }
    }
}
//checks that the graph is indeed random k regular
bool RandomKRegularGraph::verifyGraphIsKConnected(void){
   unsigned int total=0;
   //checks that maximum of one node is not connected to k others
   //i.e. if only one is greater than one, then there has been a problem
   int onlyOne=0;
   for(int s=0; s < (int)(A->size()); s++){
       total=0;
       for(int r=0; r < (int)(A->size());r++){
            if(A->getij(s,r)!=0){
                total++;
            }
       }
       if(total<Degree){
            onlyOne++;
       }
       if(total>Degree){
           cout<<"This shouldn't be happening, one of the nodes has too many elements"<<endl;
           return false;
       }
   }
   //cout<<"onlyOne: "<<onlyOne<<endl;
    if(onlyOne==0||onlyOne==1){
        return true;
    }
    else{
        return false;
    }
}
void RandomKRegularGraph::printEulerianPath(void){
//assuming that an eulerian circuit is an Eulerian path
//An undirected graph has an eulerian circuit if and only if it is connected and each vertex has an even
//degree (degree is the number of edges that are adjacent to that vertex).
//An undirected graph has an eulerian path if and only if it is connected and all vertices except 2 have
//even degree. One of those 2 vertices that have an odd degree must be the start vertex,
//and the other one must be the end vertex.
    //cout<<"Trying to print eulerian path"<<endl;
    stack<int> s1;
    Vector v1((Degree*NoOfVertices)/2);
    int v1Pos=0;
    v1.zero();
    //make a copy of A so that edges can be removed
    triplet* B=A;
    //int currEdge=B->getij(0,0);
    unsigned int currVertex=0;
    bool flag=false;
    //cout<<"ok as far as here"<<endl;
    do{
        flag=false;
        for(unsigned int i=0;i<NoOfVertices;i++){
            if(B->getij(currVertex,i)!=0&&(currVertex!=i)){
                flag=true;
                //cout<<"B->getij(currVertex,i)"<<B->getij(currVertex,i)<<endl;
                //cout<<"pushing: "<<currVertex<<endl;
                s1.push(currVertex);
                //remove the edge
                B->setij(currVertex,i,0);
                B->setij(i,currVertex,0);
                //cout<<"setting the current vertex to: "<<i<<endl;
                currVertex=i;
            }
        }
        if(flag==false){
            //cout<<"setting "<<v1Pos<<" to "<<currVertex<<endl;
            v1.seti(v1Pos,currVertex+1);
            v1Pos++;
            currVertex=s1.top();
            //cout<<"Current vertex is now: "<<currVertex<<endl;
            s1.pop();
        }
    }
    while(s1.empty()==false);
    //Print out the path to take
    char input;
    do{
        cout<<"An Eulerian path has been found, would you like to print it? (y/n)"<<endl;
        cin>>input;
    }
    while(input!='y'&&input!='n');
    if(input=='y'){
        cout<<"start at vertex 1 "<<endl;
        int x;
        for(int j=((Degree*NoOfVertices)/2)-1;j>0;j--){
            x=v1.geti(j);
            //because vector might not be full!
            if(x!=0){
                cout<<"then go to vertex "<<x<<endl;
            }
        }
        cout<<"And finish at vertex 1"<<endl;
    }

    else{
        cout<<"Path not printed"<<endl;
    }
}
