#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <jansson.h>
#include "pdatas.h"

int load_conf(char *filename)
{
	json_t *root;
	json_t *processes;
	json_error_t error;
	int i, j;
	
	root = json_load_file(filename,0 , &error);
	if (!root)
	{
		return -1;
	}

	processes = json_object_get(root, "process");
	if (!json_is_array(processes))
	{
		return -1;
	}
	
	for (i = 0; i < json_array_size(processes); i++)
	{
		json_t *process, *name, *restart, *options;
		pItem *newpitem = NULL;		

		process = json_array_get(processes, i);
		if (!json_is_object(process))
		{
			return -1;
		}
		name = json_object_get(process, "name");
		restart = json_object_get(process, "restartcmd");
		if (!json_is_string(name) || !json_is_string(restart))
		{
			return -1;
		}
		
		newpitem = newitem(json_string_value(name), json_string_value(restart));
		printf("process %d name: %s, restartcmd:%s\n", i+1, json_string_value(name), json_string_value(restart));
		options = json_object_get(process, "options");
		if (!json_is_array(options))
		{
			return -1;
		}
		for (j = 0; j < json_array_size(options); j++)
		{
			json_t *option, *opname, *chkcmd, *warnmsg, *level;
			ckoption *coption;
			option = json_array_get(options, j);
			if (!json_is_object(option))
			{
				return -1;
			}
			opname = json_object_get(option, "optname");
			chkcmd = json_object_get(option, "chkcmd");
			warnmsg = json_object_get(option, "warnmsg");
			level = json_object_get(option, "level");
			if (!json_is_string(opname) || !json_is_string(chkcmd) || !json_is_string(warnmsg) || !json_is_integer(level))
			{
				return -1;
			}
			coption = newoption(json_string_value(opname), json_string_value(chkcmd), (int)json_integer_value(level), json_string_value(warnmsg));
			printf("option %d name:%s, chkcmd:%s, level:%d warnmsg:%s\n", j+1, json_string_value(opname), json_string_value(chkcmd),(int)json_integer_value(level),  json_string_value(warnmsg));
			addoption(newpitem->optlist, coption);
		}
		additem(pList, newpitem);
		
	}

	return 1;

}

