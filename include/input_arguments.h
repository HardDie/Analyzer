#ifndef INPUT_ARGUMENTS
#define INPUT_ARGUMENTS

struct in_args_t {
	char iface[128];
	char ip[16];
	int port;
	int period;
};

int input_arguments_parse(const int argc,
                          char **argv,
                          struct in_args_t *in_args);

void input_arguments_print_using(const char *name);

#endif // INPUT_ARGUMENTS
