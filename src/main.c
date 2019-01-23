#include <stdio.h>
#include <string.h>

#include <input_arguments.h>

int main(int argc, char **argv) {
	int ret;
	struct in_args_t in_args;
	memset(&in_args, 0, sizeof(in_args));

	ret = input_arguments_parse(argc, argv, &in_args);
	if (ret < 0) {
		return 0;
	}

	if (in_args.port == 0  || in_args.period == 0 ||
	    in_args.ip[0] == 0 || in_args.iface[0] == 0) {
		input_arguments_print_using(argv[0]);
		return 0;
	}

	return 0;
}
