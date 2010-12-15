#ifndef LX_TREE
#define LX_TREE

#include <stdlib.h>
#include <string.h>

#include "rb_tree.h"

#define LX_NEXT(n)	((n)->next)
#define LX_PREV(n)	((n)->prev)
#define LX_STR(n)	((n)->str)
#define LX_VAL(n)	((n)->val)

typedef struct _lx_node {
	struct _lx_node *next, *prev;
	char *str;
	void *val;
} lx_node;

int lx_apply(rb_node *root, void (*func)(lx_node *));
int lx_insert(rb_node **root, char *str, void *val);
int lx_lookup(rb_node *root, char *str, void **val);
int lx_remove(rb_node **root, char *str, void **val);

#endif /* LX_TREE */
