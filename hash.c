#include "hash.h"

int hash(char *str) {
	int c, key = 191;
	while (0 != (c = *str++)) key += 32 * key + c * c;
	return key;
}
