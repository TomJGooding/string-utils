#include "string_utils.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_from_file(char const *filename) {
    char *string;
    GError *error = NULL;
    GIOChannel *file = g_io_channel_new_file(filename, "r", &error);
    if (!file) {
        fprintf(
            stderr,
            "ERROR: cannot open '%s' for reading: %s\n",
            filename,
            error->message
        );
        return NULL;
    }
    if (g_io_channel_read_to_end(file, &string, NULL, &error) !=
        G_IO_STATUS_NORMAL) {
        fprintf(
            stderr,
            "ERROR: cannot open '%s' for reading: %s\n",
            filename,
            error->message
        );
        return NULL;
    }
    return string;
}

TokenArray *strtok_to_array(char *str, char const *delim) {
    TokenArray *array = malloc(sizeof(TokenArray));
    *array = (TokenArray){.base_string = str};
    char *scratch = NULL;
    char *token = strtok_r(str, delim, &scratch);
    if (!token) {
        return NULL;
    }
    while (token) {
        array->elements =
            realloc(array->elements, sizeof(char *) * ++(array->length));
        array->elements[array->length - 1] = token;
        token = strtok_r(NULL, delim, &scratch);
    }
    return array;
}

void free_token_array(TokenArray *array) {
    if (array == NULL) {
        return;
    }
    free(array->base_string);
    free(array->elements);
    free(array);
}
