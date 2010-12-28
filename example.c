#include <stdio.h>
#include "dict.h"

int main(int argc, char ** argv) {
	dict dictionary;
	char *key, *val;
	int i;

	DICT_INIT(dictionary); /* Initialize dictionary. */

	for (i = 1; i < argc; i++) {
		key = argv[i];
		val = malloc(10);
		snprintf(val, 10, "%d", i);
		DICT_INSERT(dictionary, key, val); /* key references value. */
		printf("Inserting: %s => %s\n", key, val);
	}	

	for (i = 1; i < argc; i++) {
		key = argv[i];
		DICT_LOOKUP(dictionary, key, val); /* Lookup the value of key and put value in val. */
		printf("Lookup: %s => %s\n", key, val);
	}

	for (i = 1; i < argc; i += 2) {
		key = argv[i];
		DICT_REMOVE(dictionary, key, val); /* Remove every other key and put value in val. */
		printf("Removed: %s => %s\n", key, val);
		free(val);
	}

	for (i = 1; i < argc; i++) {
		key = argv[i];
		if (1 == DICT_REMOVE(dictionary, key, val)) { /* Remove key if it exists. */
			printf("Removed: %s => %s\n", key, val);
			free(val);
		}
	}

	return 0;
}
