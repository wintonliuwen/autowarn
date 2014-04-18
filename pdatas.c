#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pdatas.h"

ckoption *newoption(char *name, char *chkcommand, int lev, char *warnmsg)
{
	ckoption *newoption = (ckoption *)malloc(sizeof(ckoption));
	newoption->optname = malloc(strlen(name) +1);
	strcpy(newoption->optname, name);
	newoption->chk = malloc(strlen(chkcommand) +1);
	strcpy(newoption->chk, chkcommand);
	newoption->lev = lev;
	newoption->warnmsg = malloc(strlen(warnmsg) +1);
	newoption->warnmsg = warnmsg;
	newoption->next = NULL;
	
	return newoption;
}

void addoption(ckoption *list, ckoption *newoption)
{
	ckoption *cur = list;
	if ( cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = newoption;
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
		pList = (pItem *)malloc(sizeof(pItem));
		pList->next = NULL;
	}
}

pItem* newitem(char *name, char *restartcmd)
{
	pItem *newitem = (pItem *)malloc(sizeof(pItem));
	newitem->pname = malloc(strlen(name) +1);
	strncpy(newitem->pname, name, strlen(name) + 1);
	newitem->restartcmd = malloc(strlen(restartcmd) + 1);
	strncpy(newitem->restartcmd, restartcmd, strlen(restartcmd) + 1);
	newitem->optlist = (ckoption *)malloc(sizeof(ckoption));
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

void clearItem(pItem *list)
{
	

}
