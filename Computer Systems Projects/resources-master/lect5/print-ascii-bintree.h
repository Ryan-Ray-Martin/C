#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!Code originally from /http://www.openasthra.com/c-tidbits/printing-binary-trees-in-ascii/
  !!! Just saved it, cause the website is down.
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  Printing Binary Nodes in Ascii
  Here we are not going to discuss what binary trees are (please refer this, if you are looking for binary search trees), or their operations but printing them in ascii.
  The below routine prints tree in ascii for a given Node representation which contains list of nodes, and node structure is this
      struct Node
          {
                Node * left, * right;
                      int element;
                          };
                          This pic illustrates what the below routine does on canvas..
                          ascii tree
                          Here is the printing routine..
                              b5855d39a6b8a2735ddcaa04a404c125001
                              Auxiliary routines..
*/

#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)


int MIN (int X, int Y)  ;

int MAX (int X, int Y) ;


// Here is the asciii tree structure…
typedef struct Node Node;

struct Node {
  Node* leftChild;
  Node* rightChild;
  char* element;
  char* data;
  Node* parent; 
};


typedef struct asciinode_struct asciinode;


struct asciinode_struct{
  asciinode * left, * right;

  //length of the edge from this node to its children
  int edge_length;

  int height;

  int lablen;

  //-1=I am leftChild, 0=I am root, 1=right
  int parent_dir;

  //max supported unit32 in dec, 10 digits max
  char label[11];
};

//=====================

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode *node, int x, int y);

void compute_rprofile(asciinode *node, int x, int y);
//=========

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode *node, int x, int level) ;



//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(asciinode *node) ;

asciinode * build_ascii_tree_recursive(Node * t) ;

//Copy the tree into the ascii node structre
asciinode * build_ascii_tree(Node * t);

//Free all the nodes of the given tree
void free_ascii_tree(asciinode *node) ;


void print_ascii_tree(Node * t) ;
