#include <input_arguments.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <arpa/inet.h> // inet_aton()

/**
 * @param [in] argc
 * @param [in] argv
 * @param [out] in_args
 */
int input_arguments_parse(const int argc,
                          char **argv,
                          struct variables_t *in_args) {
	struct option long_options[] = {
	    {"iface",  required_argument, 0, 'n'},
	    {"ip",     required_argument, 0, 'i'},
	    {"port",   required_argument, 0, 'p'},
	    {"period", required_argument, 0, 't'},
	    {0, 0, 0, 0}
	};

	int c;
	int option_index;
	struct in_addr ipaddr;

	while (1) {
		c = getopt_long(argc, argv, "n:i:p:t:",
		                long_options, &option_index);
		if (c == -1) {
			break;
		}

		switch(c) {
		case 'n':
			strncpy(in_args->iface, optarg, sizeof(in_args->iface));
			break;
		case 'i':
			inet_aton(optarg, &ipaddr);
			in_args->ip = ipaddr.s_addr;
			break;
		case 'p':
			in_args->port = atoi(optarg);
			break;
		case 't':
			in_args->period = atol(optarg);
			break;

		case '?':
		case 'h':
		default:
			goto error;
		}
	}

	if (in_args->port == 0  || in_args->period == 0 ||
	    in_args->ip == 0 || in_args->iface[0] == 0) {
		printf("Please specify all parametrs\n\n");
		goto error;
	}

	return 0;
 error:
	input_arguments_print_using(argv[0]);
	return -1;
}

void input_arguments_print_using(const char *name) {
	printf("Usage: %s [OPTION]...\n", name);
	printf("\n");
	printf("  -n, --iface   Name network interface\n");
	printf("  -i, --ip      Source ip\n");
	printf("  -p, --port    Source port\n");
	printf("  -t, --period  Period for send statistic\n");
	printf("\n");
}
