#include <ndk.h>
#include <libngx_go_poc.h>

/* declare */
static ngx_int_t ngx_http_set_userid(ngx_http_request_t *r, ngx_str_t *val, ngx_http_variable_value_t *v);
static ngx_int_t ngx_http_go_set_userid(ngx_http_request_t *r, ngx_str_t *val, ngx_http_variable_value_t *v);
static ngx_int_t set_response_userId(u_char* userId, ngx_http_request_t *r, ngx_str_t *res);

static ndk_set_var_t ngx_http_set_userid_var = {
  NDK_SET_VAR_VALUE,
  (void *) ngx_http_set_userid,
  2,
  NULL
};

static ndk_set_var_t ngx_http_go_set_userid_var = {
  NDK_SET_VAR_VALUE,
  (void *) ngx_http_go_set_userid,
  2,
  NULL
};

static ngx_command_t ngx_http_poc_commands[] = {
  {
    ngx_string("set_userid"),
    NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
    ndk_set_var_value,
    0,
    0,
    &ngx_http_set_userid_var
  },
  {
    ngx_string("go_set_userid"),
    NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
    ndk_set_var_value,
    0,
    0,
    &ngx_http_go_set_userid_var
  },
  ngx_null_command
};

/* module context */
static ngx_http_module_t ngx_http_poc_module_ctx = { 
  NULL, /* preconfiguration */ 
  NULL, /* postconfiguration */
  NULL, /* create main configuration */
  NULL, /* init main configuration */
  NULL, /* create server configuration */
  NULL, /* merge server configuration */
  NULL, /* create location configuration */
  NULL  /* merge location configuration */
};


ngx_module_t ngx_http_poc_module = {
  NGX_MODULE_V1,
  &ngx_http_poc_module_ctx, /* module context */
  ngx_http_poc_commands,    /* module directives */
  NGX_HTTP_MODULE,              /* module type */
  NULL,                         /* init master */
  NULL,                         /* init module */
  NULL,                         /* init process */
  NULL,                         /* init thread */
  NULL,                         /* exit thread */
  NULL,                         /* exit process */
  NULL,                         /* exit master */
  NGX_MODULE_V1_PADDING
};

/* execute function from go */
static ngx_int_t ngx_http_set_userid(ngx_http_request_t *r, ngx_str_t *res, ngx_http_variable_value_t *v) {
  u_char* userId = GetUserID();

  ngx_str_t ngx_userId = { strlen(userId), userId };;

  return set_response_userId(userId, r, res);
}

/* execute function from go */
static ngx_int_t ngx_http_go_set_userid(ngx_http_request_t *r, ngx_str_t *res, ngx_http_variable_value_t *v) {
  void *go_module = dlopen("libngx_go_poc.so", RTLD_LAZY);
  if (!go_module) {
    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "go module not found");
    return NGX_ERROR;
  }

  u_char* (*getUserId)() = (u_char* (*)()) dlsym(go_module, "GetUserID");
  u_char* userId = getUserId();

  return set_response_userId(userId, r, res); 
}

/* set response */
static ngx_int_t set_response_userId(u_char* userId, ngx_http_request_t *r, ngx_str_t *res) {
  ngx_str_t ngx_userId = { strlen(userId), userId };;

  res->data = ngx_palloc(r->pool, ngx_userId.len);
  if (res->data == NULL) {
    return NGX_ERROR;
  }

  ngx_memcpy(res->data, ngx_userId.data, ngx_userId.len);
  res->len = ngx_userId.len;

  return NGX_OK;
}
