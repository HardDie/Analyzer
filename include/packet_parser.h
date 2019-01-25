#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

int8_t packet_parser_is_type_ip(const uint8_t *packet);
int8_t packet_parser_is_proto_udp(const uint8_t *packet);
int8_t packet_parser_is_src_ip_eq(const uint8_t *packet, const uint32_t ip);
int8_t packet_parser_is_src_port_eq(const uint8_t *packet, const uint16_t port);

#endif // UTILS_H
