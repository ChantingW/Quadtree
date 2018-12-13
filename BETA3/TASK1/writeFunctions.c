#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "addPart.h"
#include "flag.h"
#include "removePart.h"


//print out the coordinate of the node to the file
void printOut( FILE *fp, Node *node ) {
  double x = node->xy[0];
  double y = node->xy[1];
  int level = node->level;
  double h = pow(2.0,-level);//the length of the square

  fprintf(fp, " %g %g\n",x,y);
  fprintf(fp, " %g %g\n",x+h,y);
  fprintf(fp, " %g %g\n",x+h,y+h);
  fprintf(fp, " %g %g\n",x,y+h);
  fprintf(fp, " %g %g\n\n",x,y);

  return;
}

//output the coordinates of all leaves to the file
void writeNode( FILE *fp, Node *node )
{
    int i;
    if( node->child[0] == NULL )//if the node is a leaf
        printOut( fp, node );
    else
    {
        for ( i=0; i<4; ++i )
        {
            writeNode( fp, node->child[i] );//recurse to the 4 children
        }
    }
    return;
}

//create a "quad.out" file and write the coordinates of all leaves to it
void writeTree( Node *head )
{
    FILE *fp = fopen("quad.out","w");//create the file
    writeNode(fp,head);
    fclose(fp);
    return;
}
