//David Smyth
//Student ID: 13383861
#include "Vector.h"
#include "Triplet.h"
#ifndef _GRAPH_H_INCLUDED
#define _GRAPH_H_INCLUDED

class RandomKRegularGraph {
private:
   unsigned int Degree;
   unsigned int NotKDegree;
   unsigned int NoOfVertices;
   triplet* A;
public:
   RandomKRegularGraph (unsigned int degree,unsigned int noOfVertices);
   RandomKRegularGraph(const RandomKRegularGraph &old_RandomKRegularGraph);
   RandomKRegularGraph &operator=(const RandomKRegularGraph &old_RandomKRegularGraph);
   ~RandomKRegularGraph(void);
   void PrintGraph(void);
   bool writeToDotFile(void);
   bool isKRegular(void);
   bool isConnected(void);
   int getRowSum(unsigned int row);
   bool verifyGraphIsKConnected(void);
   void printEulerianPath(void);
   //needs changing
   Vector getNotFullNodes(Vector v,unsigned int toFill, unsigned int currentVertex);//toFill=verticesleftoConnect
   bool bfs(unsigned int node1,unsigned int node2);
   bool EulerianPathExists();

};
#endif // _VECTOR_H_INCLUDED

