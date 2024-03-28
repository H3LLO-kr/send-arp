#include <cstdio>
#include <pcap.h>
#include "ethhdr.h"
#include "arphdr.h"
#include "send-arp.h"

#pragma pack(push, 1)
struct EthArpPacket final
{
	EthHdr eth_;
	ArpHdr arp_;
};
#pragma pack(pop)

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
	char	*m_ip = (char *)malloc(16);
	char	*m_mac = (char *)malloc(18);

	_get_my_ip(m_ip, argv[1]);
	printf("%s\n", m_ip);
	_get_my_mac(m_mac);
	printf("%s\n", m_mac);

	/*
	for (int i = 0; i < argc / 2; i++)
	{
		char* dev = argv[1];
		char errbuf[PCAP_ERRBUF_SIZE];
		pcap_t* handle = pcap_open_live(dev, 0, 0, 0, errbuf);
		if (handle == nullptr)
		{
			fprintf(stderr, "couldn't open device %s(%s)\n", dev, errbuf);
			return -1;
		}

		EthArpPacket packet;


		char	*v_ip = argv[2 * i];
		char	*t_ip = argv[2 * i + 1];
		char	*v_mac;

		packet.eth_.dmac_ = Mac("00:00:00:00:00:00");
		packet.eth_.smac_ = Mac("00:00:00:00:00:00");
		packet.eth_.type_ = htons(EthHdr::Arp);

		packet.arp_.hrd_ = htons(ArpHdr::ETHER);
		packet.arp_.pro_ = htons(EthHdr::Ip4);
		packet.arp_.hln_ = Mac::SIZE;
		packet.arp_.pln_ = Ip::SIZE;
		packet.arp_.op_ = htons(ArpHdr::Request);
		packet.arp_.smac_ = Mac("00:00:00:00:00:00");
		packet.arp_.sip_ = htonl(Ip("0.0.0.0"));
		packet.arp_.tmac_ = Mac("00:00:00:00:00:00");
		packet.arp_.tip_ = htonl(Ip("0.0.0.0"));

		int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&packet), sizeof(EthArpPacket));
		if (res != 0)
		{
			fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
		}

		pcap_close(handle);
	}
	*/
	free(m_ip);
	free(m_mac);

	return (0);
}
