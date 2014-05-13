#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "pdatas.h"
#include "defines.h"

extern int interval;

int checkcmd(char *cmd)
{
	int ret = 0;

	ret = system(cmd);
	printf("ret:%d\n", ret);
	if (ret != 0)
	{
		// check again to see it's really not work
		sleep(10);
		if ((ret = system(cmd)) != 0)
			return WORKOFF;
	}

	return WORKON;
}

void warn(char *msg)
{
	printf("%s\n", msg);
}

int checkoptions(ckoption *oplist)
{
	int ret = 0;
	int lev = 0;
	char opname[32] = {0};
	char chkcmd[64] = {0};
	char warnmsg[256] = {0};
	ckoption *cur;

	if (oplist->optname == NULL)
	{
		cur = oplist->next;
	}
	else
	{
		cur = oplist;
	}

	do
	{
		lev = cur->lev;
		strncpy(opname, cur->optname, strlen(cur->optname) +1);
		strncpy(chkcmd, cur->chk, strlen(cur->chk) +1);
		strncpy(warnmsg, cur->warnmsg, strlen(cur->warnmsg) +1);

		if (checkcmd(chkcmd) == WORKOFF)
		{
			if (lev == WARNRESTART)
			{
				ret += 1;
			}
			else if (lev == WARNCHK)
			{
				warn(warnmsg);
			}
		}

		if (cur->next != NULL)
		{
			cur = cur->next;
		}
		else
		{
			break;
		}
	}
	while (cur->next != NULL);

	return ret;
}

void checkloop(pItem *itemlist)
{
	char restartcmd[64] = {0};
	int ret = 0;
	pItem *cur;
	if (itemlist->pname == NULL)
	{
		cur = itemlist->next;
	}
	else
	{
		cur = itemlist;
	}

	do
	{
		strncpy(restartcmd, cur->restartcmd, strlen(cur->restartcmd) +1);
		ret = checkoptions(cur->optlist);

		if (ret > 0)
		{
			printf("Restarting process %s\n", cur->pname);
			system(restartcmd);
		}
		if (cur->next != NULL)
			cur = cur->next;
		else
			break;
	}
	while(cur->next != NULL);
}

void processloop(void)
{
	while(1)
	{
		checkloop(pList);
		sleep(interval*60);
	}
}
