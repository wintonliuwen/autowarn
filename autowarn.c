#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "pdatas.h"
#include "defines.h"

char confpath[MAXPATH] = CONFILE;
int interval = CHECK_INTERVAL;

static void printversion(void)
{
	printf("%s v%s", APPNAME, VERSION);
	printf("\r\nWritten by %s.\r\n\n", AUTHO);
}

void usage(char *progname)
{
	printversion();
	printf("Usage: %s options\r\n", progname);
	printf("Options:\r\n");
	printf("-f conffile   set configuration file, the default is %s\n", CONFILE);
	printf("-t minutes    set check interval time as minutes, the default is 5minutes\n");
}


int main(int argc, char **argv)
{
	char *progname = argv[0];
	int ch, ret;

	initPitems();

	while ((ch = getopt(argc, argv, "f:t:")) != -1)
	{
		switch (ch) {
			case 'f':
				strncpy(confpath, optarg, strlen(optarg)+1);
				break;
			case 't':
				interval = atoi(optarg);
				break;
			default:
				usage(progname);
				return -1;
		}
	}

	ret = load_conf(confpath);
	if (ret < 0)
	{
		printf("Load file %s error. Please check whether it is correct\n", confpath);
		return -1;
	}

	processloop();
	
}
