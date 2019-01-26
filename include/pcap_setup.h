#ifndef PCAP_SETUP
#define PCAP_SETUP

#include <pcap/pcap.h>
#include <input_arguments.h>

int8_t pcap_setup_connection(const char *iface);
void pcap_setup_loop_start(struct variables_t *vars);
void pcap_setup_loop_stop(void);

#endif // PCAP_SETUP
