#ifndef LIST
#define LIST

#define LIST_ENTRY(type) type *_next, *_prev

#define LIST_NEXT(node) ((node)->_next)
#define LIST_PREV(node) ((node)->_prev)
#define LIST_HEAD(node) (LIST_NEXT(node))
#define LIST_TAIL(node) (LIST_PREV(node))

#define LIST_APPEND(list, node)						\
	do {								\
		LIST_PREV(node) = LIST_NEXT(node) = NULL;		\
	        if (LIST_HEAD(list)) {					\
	                LIST_PREV(node) = LIST_TAIL(list);		\
	                LIST_NEXT(LIST_TAIL(list)) = node;		\
	        } else							\
	                LIST_HEAD(list) = (node);			\
	        LIST_TAIL(list) = node;					\
	} while(0)

#define LIST_DETACH(list, node) 					\
	do {								\
	        if (LIST_HEAD(list) == (node))				\
	                LIST_HEAD(list) = LIST_NEXT(node);		\
	        if (LIST_TAIL(list) == (node))				\
	                LIST_TAIL(list) = LIST_PREV(node);		\
	        if (LIST_PREV(node))					\
        	        LIST_NEXT(LIST_PREV(node)) = LIST_NEXT(node);	\
	        if (LIST_NEXT(node)) 					\
	                LIST_PREV(LIST_NEXT(node)) = LIST_PREV(node);	\
	        LIST_PREV(node) = LIST_NEXT(node) = NULL;		\
	} while(0)

#endif /* LIST */
