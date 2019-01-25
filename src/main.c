#include <stdio.h>
#include <string.h>

#include <input_arguments.h>
#include <pcap_setup.h>
#include <packet_parser.h>

void packet_handler(uint8_t *args,
                    const struct pcap_pkthdr* header,
                    const uint8_t* packet);

int main(int argc, char **argv) {
	int32_t ret;
	struct variables_t vars;
	memset(&vars, 0, sizeof(vars));

	// Parse input arguments
	ret = input_arguments_parse(argc, argv, &vars);
	if (ret < 0) {
		return 0;
	}

	// Setup capture loop
	pcap_t *handle = setup_pcap_connection(vars.iface);
	if (!handle) {
		return -1;
	}

	// Start capture loop
	pcap_loop(handle, 0, packet_handler, (uint8_t*)&vars);

	pcap_close(handle);
	return 0;
}

void packet_handler(uint8_t *args,
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
