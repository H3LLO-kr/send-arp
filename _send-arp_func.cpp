#include "send-arp.h"

int		_get_my_ip(char *ip, char *itf)
{
	int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, itf, IFNAMSIZ -1);

    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);

    sprintf(ip, "%s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	return (0);
}

int		_get_my_mac(char *mac)
{
    struct ifreq		ifr;
    struct ifconf		ifc;
    char				buf[1024];
    int					success = 0;
	uint8_t				my_mac[6];

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1)
	{
        return 0;
    };

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1)
	{
        close(sock);
        return 0;
    }

    struct ifreq* it = ifc.ifc_req;
    const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

    for (; it != end; ++it)
	{
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
            if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    success = 1;
                    break;
                }
            }
        }
        else {
            close(sock);
            return 0;
        }
    }

    if (success){
        memcpy(my_mac, ifr.ifr_hwaddr.sa_data, 6);
        sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", my_mac[0],my_mac[1],my_mac[2],my_mac[3],my_mac[4],my_mac[5]);
        close(sock);
        return 1;
    }
    else{
        close(sock);
        return 0;
    }
	return (0);
}

int		_get_victim_mac(char *mac)
{
	return (0);
}
