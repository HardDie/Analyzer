#include <notification_loop.h>

#include <pthread.h>
#include <libubus.h>
#include <libubox/blobmsg_json.h>
#include <json-c/json_object.h>

static pthread_t notification_thread;
json_object *obj;
struct ubus_context *ctx;

static void clean_objects(void) {
	json_object_put(obj);
	ubus_free(ctx);
}

static void* main_loop(void *arg) {
	struct variables_t *vars = (struct variables_t*)arg;
	static struct blob_buf b;
	const char *msg;

	while(1) {
		// Init
		blob_buf_init(&b, 0);

		// Assemble json string
		json_object_object_add(obj, "Packet count", json_object_new_int(vars->count));
		json_object_object_add(obj, "Recieve bytes", json_object_new_int(vars->recv_bytes));
		msg = json_object_to_json_string(obj);

		if (!blobmsg_add_json_from_string(&b, msg)) {
			fprintf(stderr, "Failed to parse message data\n");
			goto end;
		}

		ubus_send_event(ctx, "Statistic", b.head);

	end:
		// Clean
		blob_buf_free(&b);
		usleep(vars->period * 1000);
	}

	clean_objects();

	pthread_exit(NULL);
	return NULL;
}

int8_t notification_loop_start(struct variables_t *vars) {
	const char *ubus_socket = NULL;

	if (!(obj = json_object_new_object())) {
		fprintf(stderr, "Failed to create json object\n");
		return -1;
	}

	ctx = ubus_connect(ubus_socket);
	if (!ctx) {
		fprintf(stderr, "Failed to connect to ubus\n");
		return -1;
	}

	pthread_create(&notification_thread, NULL, main_loop, vars);

	return 0;
}

void notification_loop_stop(void) {
	pthread_cancel(notification_thread);
	pthread_join(notification_thread, NULL);
}
