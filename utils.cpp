#include "send-arp.h"

int		_get_my_mac(t_info *Info, char *ifc)
{
	struct ifreq		data;
	int					fd;

	fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    strcpy(data.ifr_name, ifc);

    if (!ioctl(fd, SIOCGIFHWADDR, &data))
		Info->mac = Mac((uint8_t *)data.ifr_hwaddr.sa_data);
	else
		return (1);

	close(fd);
	return (0);
}

int		_get_victim_mac(t_info *Victim)
{
		
}
