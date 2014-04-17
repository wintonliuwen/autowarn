#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "pdatas.h"

int main(int argc, char **argv)
{
	initPitems();

	load_conf(argv[1]);
}
