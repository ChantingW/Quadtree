#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "writeFunctions.h"
#include "flag.h"
#include "removePart.h"


//to create a new node
Node *makeNode( double x, double y, int level )
{
  int i;
  Node *node = (Node *)malloc(sizeof(Node));//create the memory for the new node
  node->level = level;
  node->xy[0] = x;
  node->xy[1] = y;
  node->flag=0;
  for( i=0; i<4; ++i )
    node->child[i] = NULL;//set the all children to NULL
  return node;//return the pointer
}

//add for children for a node which is leaf before the function implements.
void addChildren ( Node *parent)//the parent must be a leaf before the function implements
{
  double x = parent->xy[0];
  double y = parent->xy[1];//get the coordinate of the parent
  int level = parent->level;//get the level of the parent
  double hChild = pow(2.0,-(level+1));//calculate the length of the square for the children
  parent->child[0] = makeNode( x,y, level+1 );
  parent->child[1] = makeNode( x+hChild,y, level+1 );
  parent->child[2] = makeNode( x+hChild,y+hChild, level+1 );
  parent->child[3] = makeNode( x,y+hChild, level+1 );//make the four children
  return;
}

//let every leaf add 4 children
void growTree( Node *node)
{
  int i;
  if (isLeaf(node)==0)//if the node is not leaf
  {
    for ( i=0; i<4; ++i )
    {
      growTree( node->child[i] );//recurse to the 4 children
    }
  }
  else// if the node is leaf
    addChildren( node );//add 4 children to it
}
