#include "btree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void find_placement(int x, struct tree_node *t) {

//specialcase
if (t==NULL) {
  t=malloc(sizeof(struct tree_node));
  t->item=x;
  t->left=NULL;
  t->right=NULL;
}

//LEAFNODE
else if (t->left==NULL && t->right==NULL) {

  //Hvis mindre, venstre
  if (x<=t->item) {
    t->left =malloc(sizeof(struct tree_node));
    t->left->item=x;

    //SKAL SÆTTES TIL NULL PÅ MAC... :)
    t->left->left=NULL;
    t->left->right=NULL;

  }

  //Hvis større, højre
  else if (x>t->item) {
    t->right = malloc(sizeof(struct tree_node));
    t->right->item=x;

    //SKAL SÆTTES TIL NULL PÅ MAC
    t->right->left=NULL;
    t->right->right=NULL;
  }

}

//go left. (recursive go back)
else if (t->left != NULL && x<=t->item) {
  find_placement(x,t->left);
}

else if (t->left == NULL && x<=t->item) {
  t->left = malloc(sizeof(struct tree_node));

  t->left->left=NULL;
  t->left->right=NULL;

  t->left->item=x;
}



//go right (recursive go back)
else if (t->right != NULL && x>t->item) {
  find_placement(x,t->right);
}

else if (t->right == NULL && x>t->item) {
  t->right = malloc(sizeof(struct tree_node));

  t->right->left=NULL;
  t->right->right=NULL;

  t->right->item=x;
}


}


struct tree_node *Insert(int x, struct tree_node *t) {
  // Insert item x into the tree t

  if (t==NULL) {
    t = malloc(sizeof(struct tree_node));
    t->item=x;
    t->left=NULL;
    t->right=NULL;
    return t;
  }

  find_placement(x,t);

  //struct tree_node *new_node = malloc(sizeof(struct tree_node));

  return t;
}

void remove_recursively(int x, struct tree_node *t) {

  
  if ((t->left != NULL && x==t->left->item && t->left->left==NULL) || (t->left != NULL && x==t->left->item && t->left->left->item!=x)) {

    t->left=NULL;
    free(t->left);
  } else if ((t->right != NULL && x==t->right->item && t->right->left==NULL) || (t->right != NULL && x==t->right->item && t->right->left->item!=x)){

    t->right=NULL;
    free(t->right);

  } else if (x<=t->item && t->left!=NULL) {
    remove_recursively(x,t->left);
  } else if (x>t->item && t->right!=NULL) {
    remove_recursively(x,t->right);
  }

}


struct tree_node *Remove(int x, struct tree_node *t) {
  // Remove one item from the tree t

  if (x<=t->item && t->left->item==x) {
    free(t->left);
    return t;
  }

  remove_recursively(x,t);

  return t;
}

int Contains(int x, struct tree_node *t) {

  // Return true if the tree t contains item x. Return false otherwise.
  
  //Check root
  if (t->item == x) {
    return true;

  } else if (x<=t->item && t->left!=NULL) {
    return Contains(x, t->left);

  } else if (x>t->item && t->right!=NULL) {
    return Contains(x, t->right);

  } else {
    return false;
  }
}

struct tree_node *Initialize(struct tree_node *t) {
  // Create an empty tree

  t=NULL;

  return t;
}

int Empty(struct tree_node *t) {
  // Test if empty

  if (t==NULL) {
    return 1;
  }

  return 0;
}

int Full(struct tree_node *t) {
  // Test if full
  return 1;
}
