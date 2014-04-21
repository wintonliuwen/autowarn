#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pdatas.h"

ckoption *newoption(char *name, char *chkcommand, int lev, char *warnmsg)
{
	ckoption *newoption = (ckoption *)calloc(sizeof(ckoption), 1);
	newoption->optname = calloc(strlen(name) +1, sizeof(char));
	strncpy(newoption->optname, name, strlen(name) + 1);
	newoption->chk = calloc(strlen(chkcommand) +1, sizeof(char));
	strncpy(newoption->chk, chkcommand, strlen(chkcommand) + 1);
	newoption->lev = lev;
	newoption->warnmsg = calloc(strlen(warnmsg) +1, sizeof(char));
	strncpy(newoption->warnmsg, warnmsg, strlen(warnmsg) + 1);
	newoption->next = NULL;

	return newoption;
}

void addoption(ckoption *list, ckoption *newoption)
{
	ckoption *cur = list;
	while ( cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = newoption;
}

void printoption(ckoption *option)
{
	if (option->optname == NULL)
	{
		printf("option is null\n");
	}
	else
	{
		printf("optionname:%s chkcommand:%s warnmsg:%s lev:%d  ", option->optname, option->chk, option->warnmsg, option->lev);
		if (option->next == NULL)
		{
			printf("next is NULL\n");
		}
		else
		{
			printf("next is nont NULL\n");
		}
	}
}

void printoptions(ckoption *oplist)
{
    ckoption *cur = oplist;
    printf("print options:\n");
    while (cur->next != NULL)
    {
        printoption(cur);
        cur = cur->next;
    }
    printoption(cur);
}


/*void removeoption(ckoption **head)
{
	for (ckoption** curr = head; *curr; )
	{
		ckoption *entry = *curr;
		*curr = entry->next;
		free(entry);
	}
}
*/
void initPitems(void)
{
	if ( pList == NULL)
	{
		pList = (pItem *)calloc(sizeof(pItem), 1);
		pList->next = NULL;
	}
}

pItem* newitem(char *name, char *restartcmd)
{
	pItem *newitem = (pItem *)calloc(sizeof(pItem),1);
	newitem->pname = calloc(strlen(name) +1, sizeof(char));
	strncpy(newitem->pname, name, strlen(name) + 1);
	newitem->restartcmd = calloc(strlen(restartcmd) + 1, sizeof(char));
	strncpy(newitem->restartcmd, restartcmd, strlen(restartcmd) + 1);
	newitem->optlist = (ckoption *)calloc(sizeof(ckoption), 1);
	newitem->next = NULL;
	return newitem;
}

void additem(pItem *list, pItem *newitem)
{
	pItem *cur;
	cur = list;
	while ( cur->next != NULL)
		cur = cur->next;
	cur->next = newitem;
}

void printitem(pItem *item)
{
    printf("procesname:%s restartcmd:%s\n", item->pname, item->restartcmd);
    printoptions(item->optlist);
    if (item->next == NULL)
    {
        printf("next is NULL\n");
    }
    else
    {
        printf("next isnot null\n");
    }
}


void clearItem(pItem *list)
{
	

}
