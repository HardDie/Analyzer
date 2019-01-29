#ifndef NOTIFICATION_LOOP
#define NOTIFICATION_LOOP

#include <input_arguments.h>

int8_t notification_loop_setup(void);
void notification_loop_start(struct variables_t *vars);
void notification_loop_stop(void);

#endif // NOTIFICATION_LOOP
