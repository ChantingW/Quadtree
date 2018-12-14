#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "writeFunctions.h"
#include "addPart.h"
#include "flag.h"
#include "removePart.h"

int add=0;//the times of add children for a  node
int removeN=0;//the times of remove children for a  node
int maxLevel=6;// set the max level of the tree

int main(void)
{
  Node *head = makeNode( 0.0,0.0, 0 );
  growTree(head);
  growTree(head);
  growTree(head);
  Task3(head);
  writeTree(head);
  return 0;
}
