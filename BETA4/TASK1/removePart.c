#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "writeFunctions.h"
#include "addPart.h"
#include "flag.h"



//remove 4 children for the node
void removeChildren( Node *parent )//note that all children of the parent must be leaves
{
  int i;
  for (i=0; i<4; ++i)
  {
    free(parent->child[i]);
    parent->child[i]=NULL;
  }
  return;
}

//to remove all node that below the parameter and the parameter itself
void DestoryTree( Node *node )
{
  int i;
  if (isLeaf(node)==1)
  {
    free(node);
    node=NULL;//free the memory and set it point to NULL
  }
  else//if it is not leaf
  {
    for ( i=0; i<4; ++i )//recurse to the 4 children
    {
        DestoryTree( node->child[i] );
    }
    free(node);//after remove all node that is under the parameter, then remove the parameter
    node=NULL;
  }
return;
}

