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

	return 0;
}
