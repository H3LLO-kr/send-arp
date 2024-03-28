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


/*		_send-arp_func.cpp		*/
int		_get_my_ip(char *ip, char *itf);
int		_get_my_mac(char *mac);
int		_get_victim_mac(char *mac);

#endif
