#include <notification_loop.h>

#include <pthread.h>
#include <libubus.h>
#include <libubox/blobmsg_json.h>
#include <json-c/json_object.h>

static pthread_t notification_thread;
struct ubus_context *ctx;

/**
 * Close ubus connection
 */
static void clean_objects(void) {
	ubus_free(ctx);
}

/**
 * Main notification loop, started in thread
 *
 * Init blob, put value into blob,
 * put json object to blob and send blob to ubus server
 *
 * @param [in] arg : get struct variables_t for read statistic value
 */
static void* main_loop(void *arg) {
	struct variables_t *vars = (struct variables_t*)arg;
	static struct blob_buf b;

	while(1) {
		// Init
		blob_buf_init(&b, 0);

		pthread_mutex_lock(&vars->mutex);
		blobmsg_add_u32(&b, "Packet count", vars->count);
		blobmsg_add_u32(&b, "Receive bytes", vars->recv_bytes);
		pthread_mutex_unlock(&vars->mutex);

		ubus_send_event(ctx, "Statistic", b.head);

		// Clean
		blob_buf_free(&b);
		usleep(vars->period * 1000);
	}

	clean_objects();

	pthread_exit(NULL);
	return NULL;
}

/**
 * Open ubus connection
 */
int8_t notification_loop_setup(void) {
	const char *ubus_socket = NULL;

	ctx = ubus_connect(ubus_socket);
	if (!ctx) {
		fprintf(stderr, "Failed to connect to ubus\n");
		return -1;
	}
	return 0;
}


/**
 * Start main notification loop in thread
 *
 * @param [in] vars
 */
void notification_loop_start(struct variables_t *vars) {
	pthread_create(&notification_thread, NULL, main_loop, vars);
}

void notification_loop_stop(void) {
	pthread_cancel(notification_thread);
	pthread_join(notification_thread, NULL);
}
