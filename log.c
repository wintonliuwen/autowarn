#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include "defines.h"

void logmsg(char *msg)
{
	openlog(APPNAME, LOG_PID, LOG_USER);
	syslog(LOG_WARNING, "%s\n", msg);
	closelog();
}

void logerr(char *msg)
{
	openlog(APPNAME, LOG_PID, LOG_USER);
	syslog(LOG_ERR, "%s\n", msg);
	closelog();
}
