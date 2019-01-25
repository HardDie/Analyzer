#ifndef PCAP_SETUP
#define PCAP_SETUP

#include <pcap/pcap.h>

pcap_t* setup_pcap_connection(const char *iface);

#endif // PCAP_SETUP
