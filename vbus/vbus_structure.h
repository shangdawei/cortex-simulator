#ifndef __VBUS_STRUCTURE_H__
#define __VBUS_STRUCTURE_H__

typedef enum{false=0, true} bool;

typedef struct{
	int INT_ID;
	char prority;
	struct INT_descriptor* next;
	bool in_use;
}INT_descriptor;

typedef struct{
	char* descript_file;
	char* busname;
	int poolsize;
	struct INT_descriptor* INT_queue;
	int INT_number;
	bool event_addr;

	int INTsize;
	int INTstart;
}vbus_descriptor;

#endif