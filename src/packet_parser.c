#include <packet_parser.h>

#include <net/ethernet.h> // struct ether_header
#include <netinet/ip.h> // struct ip
#include <netinet/udp.h> // struct udphdr
#include <arpa/inet.h> // inet_ntoa()

int8_t packet_parser_is_type_ip(const uint8_t *packet) {
	struct ether_header *eth_header = (struct ether_header *)packet;
	if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
		return 1;
	}
	return 0;
}

int8_t packet_parser_is_proto_udp(const uint8_t *packet) {
	const struct iphdr *ip_header;
	ip_header = (const struct iphdr*)(packet + sizeof(struct ether_header));
	if (ip_header->protocol == IPPROTO_UDP) {
		return 1;
	}
	return 0;
}

int8_t packet_parser_is_src_ip_eq(const uint8_t *packet, const uint32_t ip) {
	const struct ip *ip_header;
	ip_header = (const struct ip*)(packet + sizeof(struct ether_header));
	if (ip_header->ip_src.s_addr == ip) {
		return 1;
	}
	return 0;
}

int8_t packet_parser_is_src_port_eq(const uint8_t *packet, const uint16_t port) {
	const struct ip *ip_header;
	ip_header = (const struct ip*)(packet + sizeof(struct ether_header));

	const struct udphdr *udp_header;
	udp_header = (const struct udphdr*)(((const uint8_t*)ip_header) + sizeof(struct ip));

	if (ntohs(udp_header->source) == port) {
		return 1;
	}
	return 0;
}
