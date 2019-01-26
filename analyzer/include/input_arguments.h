#ifndef INPUT_ARGUMENTS
#define INPUT_ARGUMENTS

#include <stdint.h>
#include <pthread.h>

struct variables_t {
	// Input arguments
	char iface[128];
	uint32_t ip;
	uint16_t port;
	uint64_t period; // miliseconds
	// Statistic
	uint64_t count;
	uint64_t recv_bytes;
	// Mutex
	pthread_mutex_t mutex;
};

int input_arguments_parse(const int argc,
                          char **argv,
                          struct variables_t *in_args);

void input_arguments_print_using(const char *name);

#endif // INPUT_ARGUMENTS
