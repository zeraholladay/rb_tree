#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdlib.h>

#define RB_COUNT(n) (rb_apply(n, 0))
#define RB_KEY(n) ((n)->key)
#define RB_VAL(n) ((n)->val)

struct _rb_node {
	struct _rb_node *left, *right, *parent;
	int color, key;
	void *val;
};

typedef struct _rb_node rb_node;

int rb_apply(rb_node *n, void (*func)(rb_node *));
int rb_rapply(rb_node *n, void (*func)(rb_node *));
void rb_insert(rb_node **root, rb_node *n);
rb_node * rb_lookup(rb_node *root, int key);
rb_node * rb_nalloc(int key, void *val);
rb_node * rb_remove(rb_node **root, rb_node *n);

#endif /*RB_TREE_H*/
