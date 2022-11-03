#include <assert.h> /* assert */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

#include "linked_list.h"

/* functions to create lists */
node *make_node(int v, node *q) {
  node *p = malloc(sizeof(node));
  p->value = v;
  p->next = q;
  return p;
}

/* free all nodes in the list p */
void free_list(node *p) {
  node *q;
  while (p != NULL) {
    q = p->next;
    free(p);
    p = q;
  }
}

/* print list to console */
void print_list(node *p) {
  // Add your code for exercise 1
  // There is NO testcode for this
  if (p->next==NULL) {
  }
  else {
    printf("%d",p->next->value);
    print_list(p->next);
  }
}

int sum_squares(node *p) {
  // Add your code for excercise 2
  // You can find the tests in tests.cpp
  int sum = 0;
  
  if (p==NULL) {
    return 0;
  }
  if (p->next==NULL) {
    sum+= (p->value)*(p->value);
  } else {
    sum+=(p->value)*(p->value);
    sum+=sum_squares(p->next);
  }

  return sum;

}

typedef int (*fn_int_to_int)(int);

//ved ikke om dette er den korrekte fremgangsmåde/forståelse af opgaven.

//Recursive map function 
node *map(node *p, fn_int_to_int f) { 
  //Recursive map function
  node *temp = malloc(sizeof(node));

  if (p->next==NULL) {
    temp->value=f(p->value);
    return temp;
  }

  temp->next=map(p->next,f);
  temp->value=f(p->value);

  return temp; 
}

int square(int x) { return x * x; }

// example of another function that can be passed to map
// returns the sign of the number
// -1 if negative, 0 if zero, 1 if positive
int sign(int x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }
