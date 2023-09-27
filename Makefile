OBJECTS = string_utils.o
CFLAGS = -g -Wall -O3 `pkg-config --cflags glib-2.0`
LDLIBS = `pkg-config --libs glib-2.0`

.PHONY: test
test: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) test_string_utils.c -o test_string_utils.o $(LDLIBS)
	./test_string_utils.o
