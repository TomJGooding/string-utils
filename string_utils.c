#include <glib.h>
#include <stdio.h>

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
