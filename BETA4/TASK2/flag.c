#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "writeFunctions.h"
#include "addPart.h"
#include "removePart.h"

  extern int add;//the times of add children for a  node
  extern int removeN;//the times of remove children for a  node
  extern int maxLevel;// set the max level of the tree


//to judge if the node is a leaf
int isLeaf (Node* node)
{
  int j;
  int count=0;
  for (j=0; j<4; ++j)
  {
    if (node->child[j] != NULL)//if the node has one child
    {
      count++;
    }
  }//now count is the number of the node's children
  if( count==0 )//it have 0 child
    return 1;//if is leaf, return 1
  else//it have child
    return 0;//if is not leaf, return 0
}

// Data function
double value( double x, double y, double time )
{
  return( 2.0*exp(-8.0*(x-time)*(x-time)) - 1.0 ) ;
}

// Evaluate function at centre of quadtree node
double nodeValue( Node *node, double time )
{

  int level = node->level;
  double x = node->xy[0];
  double y = node->xy[1];

  double h = pow(2.0,-level);//the length of the square of the node

  return( value( x+0.5*h, y+0.5*h, time ) );
}

//to change the flag of all leaf under the node
void changeFlag( Node* node)
{
  int i;
  if (isLeaf(node)==0)//if it is not leaf
  {
    for (i=0; i<4; ++i)//recurse to the  4 children
      changeFlag(node->child[i]);
  }
  else//if it is leaf calculate the value of node, if smaller than -0.5,set flag to -1
  {                                              //if bigger than 0.5, set flag to 1
    if (nodeValue(node,0.0)<(-0.5))
    {
      node->flag=-1;
      return;
    }
    if (nodeValue(node,0.0)>0.5)
    {
      node->flag=1;
      return;
    }
  }
  return;
}

//to calculate the number of flag:-1 children
int calMinusOne (Node* node)
{
    int i;
    int n=0;
    for (i=0;i<4;++i)
    {
        if(node->child[i]->flag==-1)//if the flag of the child is -1
            ++n;
    }
    if (n==4)
        return 1;//return 1 if the number is 4
    else
        return 0;

}

//to judge if the 4 children of the node is all leaf
int isFather( Node* node)
{
    int i;
    int n=0;
    for(i=0;i<4;++i)
    {
        if(isLeaf(node->child[i])==1)
            n++;
    }
    if(n==4)
        return 1;//return 1 if the 4 children of the node is all leaf
    else
        return 0;
}

//if the node should add 4 children, then implement it
void addFlag(Node* node)
{

  if (isLeaf(node)==1)//if it is leaf
  {
      if(node->flag==1 && node->level<maxLevel)//the condition that it should add 4 children
      {
        add++;//+1 to the times of implement adding
        addChildren(node);//add 4 children
      }
      return;
  }
  else//if it is not leaf
  {
    int i;
    for (i=0;i<4;++i)
    {
        addFlag(node->child[i]);//recurse to the children
    }
  }
}

//if the node should remove 4 children, then implement it
void removeFlag( Node *node)
{

    if (isLeaf(node)==1)//when reach the end of the tree
    {
        return;
    }
    if (isFather(node)==1)//if it has 4 children and the 4 children are all leaves
    {
        if(calMinusOne(node)==1)//if the 4 children's flags is all -1
        {
            removeN++;//the times of remove +1
            removeChildren(node);//remove 4 children
        }
        return;
    }
    else//if is not leaf and not "father"(maybe grandpa)
    {   int i;
        for (i=0;i<4;++i)
        {

            removeFlag(node->child[i]);//recurse to the children
        }

    }
}

//to execute the task3
void Task3( Node *head )
{
  add=0;//when come to a new round, set the times of add and remove to 0
  removeN=0;
  changeFlag(head);

  addFlag(head);
  removeFlag(head);

  printf("Add number:%i\n",add*4 );
  printf("Remove number:%i\n",removeN*4 );
  printf("\n");
  return;
}

void adapt(Node* head)
{
  do
  {
      Task3(head);
  }
  while((add+removeN)!=0);
  return;
}
