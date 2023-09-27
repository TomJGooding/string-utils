char *string_from_file(char const *filename);

typedef struct TokenArray {
    char **elements;
    char *base_string;
    int length;
} TokenArray;

TokenArray *strtok_to_array(char *str, char const *delim);

void free_token_array(TokenArray *array);
