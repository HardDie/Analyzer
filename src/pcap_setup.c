#include <pcap_setup.h>

#include <pcap/pcap.h>
#include <packet_parser.h>

static pcap_t *handle = NULL;

int8_t pcap_setup_connection(const char *iface) {
	int32_t ret;
	char error_buffer[PCAP_ERRBUF_SIZE];
	// Set 0 then call handler right after timeout is over
	int snapshot_len = 0;
	int promiscuous = 0;
	// Process packets every second
	int timeout = 1000;

	handle = pcap_open_live(iface, snapshot_len, promiscuous, timeout, error_buffer);
	if (!handle) {
		fprintf(stderr, "Could not open device %s: %s\n", iface, error_buffer);
		return -1;
	}

	// Recieve only incoming packets
	ret = pcap_setdirection(handle, PCAP_D_IN);
	if (ret < 0) {
		fprintf(stderr, "Could not setup direction: %s\n", pcap_geterr(handle));
		return -1;
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

	return 0;
}

static void packet_handler(uint8_t *args,
                           const struct pcap_pkthdr* header,
                           const uint8_t* packet) {
	int8_t ret;
	struct variables_t *vars = (struct variables_t*)args;

	ret = packet_parser_is_type_ip(packet);
	if (!ret) {
		// If not IP packet
		return;
	}

	ret = packet_parser_is_proto_udp(packet);
	if (!ret) {
		// If not UDP packet
		return;
	}

	ret = packet_parser_is_src_ip_eq(packet, vars->ip);
	if (!ret) {
		// Wrong Src IP
		return;
	}

	ret = packet_parser_is_src_port_eq(packet, vars->port);
	if (!ret) {
		// Wrong Src Port
		return;
	}

	vars->count++;
	vars->recv_bytes += header->caplen;
}

void pcap_setup_loop_start(struct variables_t *vars) {
	pcap_loop(handle, 0, packet_handler, (uint8_t*)vars);
}

void pcap_setup_loop_stop(void) {
	pcap_breakloop(handle);
	pcap_close(handle);
}
