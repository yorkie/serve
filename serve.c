#include "mongoose.h"

static const char *s_http_port = "8000";
static int s_sig_num = 0;
static struct mg_serve_http_opts s_http_server_opts;

static void signal_handler (int sig_num) {
  signal(sig_num, signal_handler);
  s_sig_num = sig_num;
}

static void ev_handler (struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;
  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      mg_serve_http(nc, hm, s_http_server_opts);
      break;
    default:
      break;
  }
}

int main (int argc, char const *argv[]) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  int i;

  /* set the default root */
  s_http_server_opts.document_root = "./public";

  /* Parse command line arguments */
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-r") == 0) {
      s_http_server_opts.document_root = argv[++i];
    } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
      s_http_port = argv[++i];
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf("\n  $ dest/serve -r [dir] -p [port]\n\n");
      return 0;
    }
  }

  /* Start listening */
  mg_mgr_init(&mgr, NULL);
  nc = mg_bind(&mgr, s_http_port, ev_handler);
  if (nc == NULL) {
    fprintf(stderr, "mg_bind(%s) failed\n", s_http_port);
    return EXIT_FAILURE;
  }
  mg_set_protocol_http_websocket(nc);

  /* Handle with signals */
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  /* Run event loop until signal is received */
  printf("Starting file server on port %s at directory %s\n",
    s_http_port,
    s_http_server_opts.document_root);
  while (s_sig_num == 0) {
    mg_mgr_poll(&mgr, 1000);
  }

  /* Cleanup */
  mg_mgr_free(&mgr);
  printf("Exiting on signal %d\n", s_sig_num);

  return 0;
}
