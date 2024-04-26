#include <stdio.h>
#include <stdlib.h>

// TODO
// ----
// + Suppoert  RFC7159 (can start with a object, array, number, boolean or null, change NEXTCH to int json__getc(int* out)
// + Add the get int64, uint64, double and boolean functions.
// + Add document to the header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSON_TOKENIZER_IMPLEMENTATION
#include "json-tokenizer.h"

const char* passes[] = {
	"JsonChecker\\pass1.json",
	"JsonChecker\\pass2.json",
	"JsonChecker\\pass3.json"
};

const char* failes[] = {
	"JsonChecker\\fail1.json",
	"JsonChecker\\fail2.json",
	"JsonChecker\\fail3.json",
	"JsonChecker\\fail4.json",
	"JsonChecker\\fail5.json",
	"JsonChecker\\fail6.json",
	"JsonChecker\\fail7.json",
	"JsonChecker\\fail8.json",
	"JsonChecker\\fail9.json",
	"JsonChecker\\fail10.json",
	"JsonChecker\\fail11.json",
	"JsonChecker\\fail12.json",
	"JsonChecker\\fail13.json",
	"JsonChecker\\fail14.json",
	"JsonChecker\\fail15.json",
	"JsonChecker\\fail16.json",
	"JsonChecker\\fail17.json",
	"JsonChecker\\fail18.json",
	"JsonChecker\\fail19.json",
	"JsonChecker\\fail20.json",
	"JsonChecker\\fail21.json",
	"JsonChecker\\fail22.json",
	"JsonChecker\\fail23.json",
	"JsonChecker\\fail24.json",
	"JsonChecker\\fail25.json",
	"JsonChecker\\fail26.json",
	"JsonChecker\\fail27.json",
	"JsonChecker\\fail28.json",
	"JsonChecker\\fail29.json",
	"JsonChecker\\fail30.json",
	"JsonChecker\\fail31.json",
	"JsonChecker\\fail32.json",
	"JsonChecker\\fail33.json"
};

void replace_backslash(char* path) {
	if(path == NULL) return;

	for (char* p = path; *p != '\0'; ++p) {
        if (*p == '\\') {
            *p = '/';
        }
    }
}

int check_json_file(const char* path)
{
	char* path_copy = (char*)malloc(strlen(path) + 1);
	strcpy(path_copy, path);

	#if defined(__APPLE__) || defined(__linux__)
	replace_backslash(path_copy);
	#endif

	json_t* sample = json_fopen(path_copy);
	if (sample == NULL) return -1;

	json_token_t tok = json_next_token(sample);
	while (tok != JSON_END_DOCUMENT) {
		if (tok == JSON_ERROR) {
			return 0;
		}
		tok = json_next_token(sample);
	}

	json_close(sample);
	return 1;
}

int main(void)
{
	// Test the pass files
	for (int i = 0; i < sizeof(passes) / sizeof(const char*); i++) {
		printf("%s: ", passes[i]);
		int result = check_json_file(passes[i]);
		if (result == -1) {
			printf("failed open file!\n");
		}
		else if (result == 1) {
			printf("ok\n");
		}
		else {
			printf("failed!\n");
		}
	}

	// Test the fail files
	for (int i = 0; i < sizeof(failes) / sizeof(const char*); i++) {
		printf("%s: ", failes[i]);
		int result = check_json_file(failes[i]);
		if (result == -1) {
			printf("failed open file!\n");
		}
		else if (result == 0) {
			printf("ok\n");
		}
		else {
			printf("failed!\n");
		}
	}
	return 0;
}