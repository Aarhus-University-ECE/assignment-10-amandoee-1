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
bool removed = false;

struct tree_node* remove_recursively(int x, struct tree_node *t) {

  //hvis t er root.
  if ((x==t->item && t->left->item!=x) || (x==t->item && t->left==NULL)) {
    return t;
  }

  if ((t->left != NULL && x==t->left->item && t->left->left==NULL) || (t->left != NULL && x==t->left->item && t->left->left->item!=x)) {

    //t->left=NULL;
    //free(t->left);
    //return t->left;
    
    //return parent node i stedet til fremtidigt brug.
    return t;

  } else if ((t->right != NULL && x==t->right->item && t->right->left==NULL) || (t->right != NULL && x==t->right->item && t->right->left->item!=x)){

     //t->right=NULL;
    //free(t->right);
    //return t->right;

    //samme årsag som ovenfor.
    return t;

  } else if (x<=t->item && t->left!=NULL) {
    return (remove_recursively(x,t->left));
  } else if (x>t->item && t->right!=NULL) {
    return (remove_recursively(x,t->right));
  }

  

}

struct tree_node *find_erstatning(struct tree_node *erstatning) {

if (erstatning->right==NULL) {
  return erstatning;
}
else {
  return find_erstatning(erstatning->right);
}

}

struct tree_node *find_parent_erstatning(struct tree_node *erstatning) {

if (erstatning->right->right==NULL) {
  return erstatning;
}
else {
  return find_erstatning(erstatning->right);
}

}



void change_places(int x, struct tree_node *parent_of_node_to_be_removed) {

struct tree_node *node_to_be_removed = malloc(sizeof(struct tree_node));

if (x<=parent_of_node_to_be_removed->item) {
  node_to_be_removed = parent_of_node_to_be_removed->left;
} else {
  node_to_be_removed = parent_of_node_to_be_removed->right;
}


//Specialcase, hvor den der skal fjernes er en leafnode.
if (node_to_be_removed->left == NULL && node_to_be_removed->right==NULL) {
    node_to_be_removed->left=NULL;
    node_to_be_removed->right=NULL;

    if (parent_of_node_to_be_removed->left==node_to_be_removed) {
      parent_of_node_to_be_removed->left=NULL;
      free(node_to_be_removed);
    } else if (parent_of_node_to_be_removed->right==node_to_be_removed) {
      parent_of_node_to_be_removed->right=NULL;
      free(node_to_be_removed);
    }

  } else {
    
    struct tree_node *erstatning = malloc(sizeof(struct tree_node));

    if (node_to_be_removed->left!=NULL) {
        erstatning = find_erstatning(node_to_be_removed->left);
    } else {
        erstatning = find_erstatning(node_to_be_removed->right);
    }

    if (erstatning==node_to_be_removed->left) {
      node_to_be_removed->item=node_to_be_removed->left->item;
      node_to_be_removed->left=NULL;
      free(erstatning);
    }

    else if (erstatning!=node_to_be_removed->left) {


      struct tree_node *parent_of_erstatning = malloc(sizeof(struct tree_node));

      if (node_to_be_removed->left != NULL) {
        parent_of_erstatning = find_parent_erstatning(node_to_be_removed->left);
      } else {
        parent_of_erstatning = find_parent_erstatning(node_to_be_removed);
      }
      

      node_to_be_removed->item=erstatning->item;
      parent_of_erstatning->right=NULL;

    free(erstatning);
    }

    //Hvis erstatningen er et direkte barn af den node der skal fjernes.
    
    
  }

  //Finder erstatningsnoden
  


  //Bytter dem rundt
}


struct tree_node *Remove(int x, struct tree_node *t) {
  // Remove one item from the tree t
  
  if (Contains(x,t)==true) {
    struct tree_node *will_be_removed_parent = malloc(sizeof(struct tree_node));

  //lav den om, så den bare laver change places indeni.

    will_be_removed_parent = remove_recursively(x,t);

    change_places(x,will_be_removed_parent);
  }
  

  //Du skal finde en leafnode, der opfylder samme egenskaber, og så blot indsætte den i stedet. Free den gamle derefter.
  return t;
}


//Indsæt childnodes fra node_to_be_removed, men med betingelsen om, at det er et andet sted. Muligvis overtage den gamle.



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
