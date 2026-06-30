#include "web_server.h"

#include "esp_http_server.h"
#include "esp_log.h"

static const char *TAG = "WEB";
extern const uint8_t index_html_start[] asm("_binary_index_html_start");
extern const uint8_t index_html_end[]   asm("_binary_index_html_end");

extern const uint8_t style_css_start[] asm("_binary_style_css_start");
extern const uint8_t style_css_end[]   asm("_binary_style_css_end");

extern const uint8_t script_js_start[] asm("_binary_script_js_start");
extern const uint8_t script_js_end[]   asm("_binary_script_js_end");

static esp_err_t root_get_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "ROOT PAGE REQUEST RECEIVED");
    ESP_LOGI(TAG, "Serving index.html");

    httpd_resp_set_type(req, "text/html");

    httpd_resp_send(
        req,
        (const char*)index_html_start,
        index_html_end - index_html_start
    );

    return ESP_OK;
}
static esp_err_t css_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/css");

    httpd_resp_send(
        req,
        (const char*)style_css_start,
        style_css_end - style_css_start
    );

    return ESP_OK;
}
static esp_err_t js_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "application/javascript");

    httpd_resp_send(
        req,
        (const char*)script_js_start,
        script_js_end - script_js_start
    );

    return ESP_OK;
}

void start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_uri_t root = {
            .uri      = "/",
            .method   = HTTP_GET,
            .handler  = root_get_handler,
            .user_ctx = NULL
        };

        httpd_register_uri_handler(server, &root);
        httpd_uri_t css = {
    .uri = "/style.css",
    .method = HTTP_GET,
    .handler = css_get_handler,
    .user_ctx = NULL
};
httpd_register_uri_handler(server, &css);

httpd_uri_t js = {
    .uri = "/script.js",
    .method = HTTP_GET,
    .handler = js_get_handler,
    .user_ctx = NULL
};

httpd_register_uri_handler(server, &js);
        ESP_LOGI(TAG, "HTTP Server Started");
    }
}