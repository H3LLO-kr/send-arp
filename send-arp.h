#ifndef SEND_ARP_H

#define SEND_ARP_H

#include <stdio.h>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <pcap.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include "ethhdr.h"
#include "arphdr.h"
#include "mac.h"

typedef struct s_info
{
	Mac		mac;
	Ip		ip;
} t_info;

/*		_send-arp_func.cpp		*/
int		_get_my_mac(t_info *Info, char *ifc);
int		_get_victim_mac(char *mac);

#endif
