#include <cstdio>
#include <cstdlib>
#include <vector>

#define JSON_TOKENIZER_IMPLEMENTATION
#include "json_tokenizer.h"

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

enum class gender_t { MALE, FEMALE };

struct person_t {
	int age;
	std::string name;
	gender_t gender;
	std::string company;
	std::string email;
	std::vector<std::string> tags;
};

int main(void)
{
	//
	// Test the tokenizer with the sample file from [https://www.json.org/JSON_checker/].

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

	//
	// Example: Read from a sample file and put the result in a struct.
	//
	
	json_t* sample = json_fopen("sample.json");
	if(sample == nullptr) {
		printf("Failed to open sample.json");
		exit(-1);
	}
	json_token_t tok;
	std::vector<person_t> persons;

	// Search for the start of the object
	while((tok = json_next_token(sample)) != JSON_START_ARRAY) {}
	while(true) {
		person_t person;

		// If the next token is the end of the array then we are done.
		if((tok = json_next_token(sample)) == JSON_END_ARRAY) break;
		
		// Read age
		while((tok = json_next_token(sample)) != JSON_NAME) {}
		while((tok = json_next_token(sample)) != JSON_UINT64) {}
		person.age = static_cast<int>(std::atol(json_get_value(sample)));

		// Read name
		while((tok = json_next_token(sample)) != JSON_NAME) {}
		while((tok = json_next_token(sample)) != JSON_STRING) {}
		person.name = json_get_value(sample);

		// Read gender
		while((tok = json_next_token(sample)) != JSON_NAME) {}
		while((tok = json_next_token(sample)) != JSON_STRING) {}
		person.gender = strcmp(json_get_value(sample), "male") ? gender_t::MALE : gender_t::FEMALE;

		// Read company
		while((tok = json_next_token(sample)) != JSON_NAME) {}
		while((tok = json_next_token(sample)) != JSON_STRING) {}
		person.company = json_get_value(sample);

		// Read email
		while((tok = json_next_token(sample)) != JSON_NAME) {}
		while((tok = json_next_token(sample)) != JSON_STRING) {}
		person.email = json_get_value(sample);

		// Read the tags
		while((tok = json_next_token(sample)) != JSON_START_ARRAY) {}
		while(true) {
			if((tok = json_next_token(sample)) == JSON_END_ARRAY) break;;
			person.tags.push_back(json_get_value(sample));
		}

		// skip favoriteFruit

		// Search for the end of the object
		while((tok = json_next_token(sample)) != JSON_END_OBJECT) {}

		persons.push_back(person);
	}
	return 0;
}