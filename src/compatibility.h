#ifndef COMPATIBILITY_H
#define COMPATIBILITY_H

#ifdef __AROS__

#define __saveds

struct TimeVal
{
	/* same as struct timeval */;
	unsigned AROS_32BIT_TYPE tv_secs;
	unsigned AROS_32BIT_TYPE tv_micro;
};

struct TimeRequest{
	/* same as struct timerequest */
	struct IORequest tr_node;
	struct timeval   tr_time;
};

#endif

#endif
