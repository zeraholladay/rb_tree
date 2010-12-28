#ifndef DICT
#define DICT

#include "lx_tree.h"

typedef rb_node * dict;

#define DICT_INIT(identifier) 		(identifier = NULL)			    /* Use when the dict pointer is not malloc'd */
#define DICT_APPLY(dict, function)	(lx_apply(dict, function))		    /* Returns -1 on failure, otherwise n times function applied. */
#define DICT_INSERT(dict, key, value)	(lx_insert(&(dict), key, (void *) value))   /* Returns 1 on success, 0 otherwise if malloc failed. */
#define DICT_LOOKUP(dict, key, value)	(lx_lookup(dict, key, (void **) &(value)))  /* Returns 1 if found, 0 if no match. */
#define DICT_REMOVE(dict, key, value)	(lx_remove(&(dict), key, (void **) &(value)))  /* Returns 1 if removed, 0 if nothing to remove. */

#endif
