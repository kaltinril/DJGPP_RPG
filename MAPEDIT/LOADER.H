#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <dir.h>

#define BOOL int
#define GOOD 1
#define BAD  0

BOOL open_map();
BOOL save_map();
BOOL make_map();
void get_file();