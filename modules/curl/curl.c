#include "curl.h"

static gchar *
_format_persist_name(LogThrDestDriver *s)
{
  CurlDestinationDriver *self = (CurlDestinationDriver *) s;
  static gchar persist_name[1024];

  g_snprintf(persist_name, sizeof(persist_name),
             "curl(%s,)", self->url);
  return persist_name;
}

static gchar *
_format_stats_instance(LogThrDestDriver *s)
{
  CurlDestinationDriver *self = (CurlDestinationDriver *) s;
  static gchar stats[1024];

  g_snprintf(stats, sizeof(stats),
             "curl,%s", self->url);
  return stats;
}

static void
_thread_init(LogThrDestDriver *s)
{
  CurlDestinationDriver *self = (CurlDestinationDriver *) s;
  // do stuff when the thread is launched
}

static void
_thread_deinit(LogThrDestDriver *s)
{
  CurlDestinationDriver *self = (CurlDestinationDriver *) s;
  // do stuff when the thread is ended
}

static gboolean
_connect(LogThrDestDriver *s)
{
  CurlDestinationDriver *self = (CurlDestinationDriver *) s;
  // initialize connection. With HTTP we may not do the actual connection
  return TRUE;
}

static void
_disconnect(LogThrDestDriver *s)
{
  CurlDestinationDriver *self = (CurlDestinationDriver *) s;
  // tear down the connection. With HTTP we may not do too much
}

static worker_insert_result_t
_insert(LogThrDestDriver *s, LogMessage *msg)
{
  CurlDestinationDriver *self = (CurlDestinationDriver *) s;

  // insert a log message
  msg_debug("sending a message to this url using curl",
            evt_tag_str("url", self->url),
            NULL);
  return WORKER_INSERT_RESULT_SUCCESS;
}

LogDriver *
curl_dd_new(GlobalConfig *cfg)
{
  CurlDestinationDriver *self = g_new0(CurlDestinationDriver, 1);

  log_threaded_dest_driver_init_instance(&self->super, cfg);

  /* set virtual methods to implement ThreadedDestDriver behaviour */
  self->super.worker.thread_init = _thread_init;
  self->super.worker.thread_deinit = _thread_deinit;
  self->super.worker.connect = _connect;
  self->super.worker.disconnect = _disconnect;
  self->super.worker.insert = _insert;
  self->super.format.persist_name = _format_persist_name;
  self->super.format.stats_instance = _format_stats_instance;
  // self->super.worker.worker_message_queue_empty =

  return &self->super.super.super;
}
