#ifndef PDATAS_H
#define PDATAS_H

#define WARNCHK 0
#define WARNRESTART 1

struct _ckoption {
	char *optname;
	char *chk;
	int lev;
	char *warnmsg;
	struct _ckoption *next;
};

typedef struct _ckoption ckoption;

struct _pItem {
	char *pname;
	ckoption *optlist;
	char *restartcmd;
	struct _pItem *next;
};

typedef struct _pItem pItem;

pItem *pList;

void initPitems(void);
void additem(pItem *list, pItem *newitem);
void clearItem(pItem *list);

void initoptions(void);
void addoption(ckoption *list, ckoption *newoption);
void clearoption(ckoption *list);
int load_conf(char *filename);

#endif

