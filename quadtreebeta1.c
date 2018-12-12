#include <stdio.h>
#include <stdlib.h>
#include "math.h"
struct qnode
{
   int level;
   double xy[2];
   struct qnode *child[4];
   int flag;
};
typedef struct qnode Node;

void writeNode( FILE *fp, Node *node );
void writeTree( Node *head )
{
    FILE *fp = fopen("quad.out","w");
    writeNode(fp,head);
    fclose(fp);
    return;
}

void printOut( FILE *fp, Node *node ) {
  double x = node->xy[0];
  double y = node->xy[1];
  int level = node->level;
  double h = pow(2.0,-level);

  fprintf(fp, " %g %g\n",x,y);
  fprintf(fp, " %g %g\n",x+h,y);
  fprintf(fp, " %g %g\n",x+h,y+h);
  fprintf(fp, " %g %g\n",x,y+h);
  fprintf(fp, " %g %g\n\n",x,y);

  return;
}

void writeNode( FILE *fp, Node *node )
{
    int i;
    if( node->child[0] == NULL )
        printOut( fp, node );
    else
    {
        for ( i=0; i<4; ++i )
        {
            writeNode( fp, node->child[i] );
        }
    }
    return;
}


Node *makeNode( double x, double y, int level )
{
  int i;
  Node *node = (Node *)malloc(sizeof(Node));
  node->level = level;
  node->xy[0] = x;
  node->xy[1] = y;
  node->flag=0;
  for( i=0; i<4; ++i )
    node->child[i] = NULL;
  return node;
}

void addChildren ( Node *parent)
{
  double x = parent->xy[0];
  double y = parent->xy[1];
  int level = parent->level;
  double hChild = pow(2.0,-(level+1));
  parent->child[0] = makeNode( x,y, level+1 );
  parent->child[1] = makeNode( x+hChild,y, level+1 );
  parent->child[2] = makeNode( x+hChild,y+hChild, level+1 );
  parent->child[3] = makeNode( x,y+hChild, level+1 );
  return;
}
void DestoryNode( Node *node );
void DestoryTree( Node *head )
{

  while (  head!=NULL  )
  {
  DestoryNode(head);
  }

  return;
}


void DestoryNode( Node *node )
{
  if (node==NULL)
    return;


  int i;
  int j;
  int count=0;
  for (j=0; j<4; ++j)
  {
    if (node->child[j] != NULL)
    {
      count++;
    }
  }
  if( count==0 )
    free(node);
  else
  {
    for ( i=0; i<4; ++i )
    {
      if (node->child[i]!=NULL)
        DestoryNode( node->child[i] );
    }
  }
return;
}

void growTree( Node *node)
{
  int i;
  if (node->child[0]!=NULL)
  {
    for ( i=0; i<4; ++i )
    {
      growTree( node->child[i] );
    }
  }
  else
    addChildren( node );
}

//T2
void removeChildren( Node *parent )
{
  int i;
  for (i=0; i<4; ++i)
    free(parent->child[i]);
  return;
}

//T3







// Evaluate function at centre of quadtree node
double value( double x, double y, double time );
double nodeValue( Node *node, double time )
{

  int level = node->level;
  double x = node->xy[0];
  double y = node->xy[1];

  double h = pow(2.0,-level);

  return( value( x+0.5*h, y+0.5*h, time ) );
}

// Data function

double value( double x, double y, double time )
{
  return( 2.0*exp(-8.0*(x-time)*(x-time)) - 1.0 ) ;
}

void changeFlag( Node* node)
{
  int i;
  if (node->child[0]!=NULL)
  {
    for (i=0; i<4; ++i)
      changeFlag(node->child[i]);
  }
  else
  {
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

int add=0;
int removeN=0;
int maxLevel=6;

void adaptFlag( Node* node)
{
  if (  (node->flag=1)  &&  ( (node->level)<maxLevel ) )
  {
    addChildren(node);
    add++;
    return;
  }
  int i;
  int n=0;
  for (i=0;i<4;++i)
  {
    if ((node->child[i])->flag==-1)
      n++;
  }
  if (n==4)
  {
    removeChildren(node);
    removeN++;
    return;
  }
  if (node->child[0]!=NULL)
  {
    for (i=0; i<4; ++i)
      adaptFlag(node->child[i]);
  }
  return;
}


void adapt( Node *head )
{
  add=0;
  removeN=0;
  changeFlag(head);

  adaptFlag(head);

  printf("Add number:%i\n",add );
  printf("Remove number:%i\n",removeN );
  return;
}

int main(void)
{
  Node *head = makeNode( 0.0,0.0, 0 );
  growTree(head);
  //growTree(head);
  //DestoryTree(head);
  writeTree(head);
  return 0;
}
