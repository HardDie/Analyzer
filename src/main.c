#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <input_arguments.h>
#include <pcap_setup.h>
#include <notification_loop.h>

static void sig_handler(int signo) {
	pcap_setup_loop_stop();
	notification_loop_stop();
}

static void init_environment(struct variables_t *vars) {
	memset(vars, 0, sizeof(struct variables_t));

	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
}

int main(int argc, char **argv) {
	int32_t ret;
	struct variables_t vars;

	init_environment(&vars);

	// Parse input arguments
	ret = input_arguments_parse(argc, argv, &vars);
	if (ret < 0) {
		return 0;
	}

	ret = pcap_setup_connection(vars.iface);
	if (ret < 0) {
		return -1;
	}

	ret = notification_loop_start(&vars);
	if (ret < 0) {
		return -1;
	}

	pcap_setup_loop_start(&vars);

	// Start both loop and wait SIGINT or SIGTERM signals

	return 0;
}
