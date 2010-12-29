#include <strings.h>
#include "strsave.h"
#include "rb_tree.h"
#include "hash.h"

char * strsave(char *str) {
	static rb_node *root;
	struct alist {
		struct alist *next;
		char *str;
	} *list;
	rb_node *n;
	int key;

        key = hash(str);
        n = rb_lookup(root, key);

        if (NULL != n) {
		for (list = RB_VAL(n); NULL != list; list = list->next)
			if (0 == strcmp(list->str, str)) { 
				return list->str;
			}
	} else {
		n = rb_nalloc(key, NULL);
		if (NULL == n) return NULL;
		rb_insert(&root, n);
        }

	list = malloc(sizeof(struct alist));
	if (NULL == list) return NULL;

	list->str = strdup(str);
	if (NULL == list->str) return NULL;

        list->next = RB_VAL(n);
        RB_VAL(n) = list;

        return list->str;
}
