
// From: https://www.programiz.com/dsa/dijkstra-algorithm
// From: https://gist.github.com/Suman2593/d357d24310b053838077dab5ca2b0c1d

#include "utils.h"

#define INFINITY 0xF00000
#define MAX 10

#define NUM_NODES 4

void dijkstra(int G[MAX][MAX],int n,int startnode)
{
  int cost[MAX][MAX],distance[MAX],pred[MAX];
  int visited[MAX],count,mindistance,nextnode,i,j;

  //pred[] stores the predecessor of each node
  //count gives the number of nodes seen so far
  //create the cost matrix
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      if(G[i][j]==0)
        cost[i][j]=INFINITY;
      else
        cost[i][j]=G[i][j];

  //initialize pred[],distance[] and visited[]
  for(i=0;i<n;i++)
  {
    distance[i]=cost[startnode][i];
    pred[i]=startnode;
    visited[i]=0;
  }

  distance[startnode]=0;
  visited[startnode]=1;
  count=1;

  while(count<n-1)
  {
    mindistance=INFINITY;

    //nextnode gives the node at minimum distance
    for(i=0;i<n;i++)
      if(distance[i]<mindistance&&!visited[i])
      {
        mindistance=distance[i];
        nextnode=i;
      }

      //check if a better path exists through nextnode
      visited[nextnode]=1;
      for(i=0;i<n;i++)
        if(!visited[i]) {
          if(mindistance+cost[nextnode][i]<distance[i])
          {
            distance[i]=mindistance+cost[nextnode][i];
            pred[i]=nextnode;
          }
        }
    count++;
  }

  //print the path and distance of each node
  for(i=0;i<n;i++)
    if(i!=startnode)
    {
      printf("Distance of node %x=%x\n",i,distance[i]);
      printf("Path=%x",i);

      j=i;
      do
      {
        j=pred[j];
        printf("<-%x",j);
      }while(j!=startnode);
      printf("\n");
  }
}

int dijkstra_main() {
  int Graph[MAX][MAX];

  Graph[0][0] = 0;
  Graph[0][1] = 0x400;
  Graph[0][3] = 0x1000;
  Graph[0][2] = 0;

  Graph[1][0] = 0x400;
  Graph[1][1] = 0;
  Graph[1][3] = 0x2000;
  Graph[1][2] = 0x100;

  Graph[3][0] = 0x1000;
  Graph[3][1] = 0x2000;
  Graph[3][3] = 0;
  Graph[3][2] = 0x100;

  Graph[2][0] = 0;
  Graph[2][1] = 0x100;
  Graph[2][3] = 0x100;
  Graph[2][2] = 0;

  dijkstra(Graph, NUM_NODES, 0);

  return 0;
}