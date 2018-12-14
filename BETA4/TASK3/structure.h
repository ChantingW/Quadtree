struct qnode
{
   int level;
   double xy[2];//the coordinate of the left bottom of the square
   struct qnode *child[4];
   int flag;
};
typedef struct qnode Node;
