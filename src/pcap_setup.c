#include <pcap_setup.h>

#include <pcap/pcap.h>

pcap_t* setup_pcap_connection(const char *iface) {
	int32_t ret;
	pcap_t *handle = NULL;
	char error_buffer[PCAP_ERRBUF_SIZE];
	// Set 0 then call handler right after timeout is over
	int snapshot_len = 0;
	int promiscuous = 0;
	// Process packets every second
	int timeout = 1000;

	handle = pcap_open_live(iface, snapshot_len, promiscuous, timeout, error_buffer);
	if (!handle) {
		fprintf(stderr, "Could not open device %s: %s\n", iface, error_buffer);
		return NULL;
	}

	// Recieve only incoming packets
	ret = pcap_setdirection(handle, PCAP_D_IN);
	if (ret < 0) {
		fprintf(stderr, "Could not setup direction: %s\n", pcap_geterr(handle));
	}

	/*
	 * Here we can configure packet filtering according to the rule
	 *
	 * char filter_exp[] = "udp && src X.X.X.X && src port X";
	 * struct bpf_program filter;
	 *
	 * if (pcap_compile(handle, &filter, filter_exp, 0, 0) == -1) {
	 *   fprintf(stderr, "Bad filter - %s\n", pcap_geterr(handle));
	 *   return -1;
	 * }
	 * if (pcap_setfilter(handle, &filter) == -1) {
	 *   fprintf(stderr, "Error setting filter - %s\n", pcap_geterr(handle));
	 *   return -1;
	 * }
	 *
	 * and the packet_handler will recieve only the correct packets.
	 * But we will use manual filtering.
	 */

	return handle;
}
