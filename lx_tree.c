#include "lx_tree.h"
#include "hash.h"

inline static lx_node * lx_lookup2(rb_node *root, 
				     char *str, 
				     rb_node **n, 
				     int *key) {		
	lx_node *lx;
	size_t len;

	*key = hash(str);
	*n = rb_lookup(root, *key);

	if (NULL != *n) {
		len = strlen(str);
		for (lx = RB_VAL(*n); NULL != lx; lx = LX_NEXT(lx))
			if (0 == strncmp(str, LX_STR(lx), len + 1)) return lx;
	}

	return NULL;
}

inline static void * lx_nalloc(char *str, void *val) {
	lx_node *lx;

	lx = malloc(sizeof(lx_node));
	if (NULL == lx) return NULL;

	LX_NEXT(lx) = LX_PREV(lx) = NULL;
	LX_STR(lx) = str;
	LX_VAL(lx) = val;

	return lx;
}

int lx_apply(rb_node *root, void (*func)(lx_node *)) {
	int i, j;

	i = 0;

	void lx_cb(rb_node *n) {
		lx_node *lx, *tmp;

		lx = RB_VAL(n);

		while (NULL != lx) {
			tmp = LX_NEXT(lx);
			func(lx);
			lx = tmp;
			++i;
		}
	}

	j = rb_apply(root, lx_cb);
	if (-1 == j) return -1;

	return i;
}

int lx_insert(rb_node **root, char *str, void *val) {
	lx_node *lx;
	rb_node *n;
	int key;

	if (NULL == *root) { 
		key = hash(str);
		lx = lx_nalloc(str, val);

		if (NULL == lx)
			return -1;
		else if (NULL == (*root = rb_nalloc(key, lx))) {
			free(lx);
			return -1;
		}

		return 1;
	} 

	lx = lx_lookup2(*root, str, &n, &key);

	if ((NULL != n) && (NULL != lx)) {
		LX_VAL(lx) = val;
		return 0;
	}

	lx = lx_nalloc(str, val);
	if (NULL == lx) return -1;

	if (NULL == n) {
		n = rb_nalloc(key, lx);

		if (NULL == n) {
			free(lx);
			return -1;
		}

		rb_insert(root, n);
	} else {
		if (NULL != (LX_NEXT(lx) = RB_VAL(n))) LX_PREV(LX_NEXT(lx)) = lx;
		RB_VAL(n) = lx;
	}

	return 1;
}

int lx_lookup(rb_node *root, char *str, void **val) {
	lx_node *lx;
        rb_node *n;
        int key;

	if ((NULL != root) && 
	    (NULL != (lx = lx_lookup2(root, str, &n, &key)))) {
		*val = LX_VAL(lx);
		return 1;
	}

	*val = NULL;
	return 0;
}

int lx_remove(rb_node **root, char *str, void **val) {
	lx_node *lx;
        rb_node *n;
        int key;

	if ((NULL != *root) &&
	    (NULL != (lx = lx_lookup2(*root, str, &n, &key)))) {
		*val = LX_VAL(lx);

		if (NULL != LX_PREV(lx)) LX_NEXT(LX_PREV(lx)) = LX_NEXT(lx);
		else RB_VAL(n) = LX_NEXT(lx);

		if (NULL != LX_NEXT(lx))
			LX_PREV(LX_NEXT(lx)) = LX_PREV(lx);

		free(lx);
	
		if (NULL == RB_VAL(n)) {
			n = rb_remove(root, n);
			free(n);
		}

		return 1;
	} 

	return 0;
}
