#pragma once
#include <cstdarg>
#include <cstdio>
namespace esphome {
static inline void esp_log_vprintf_(int, const char*, int, const char*, va_list) {}
}
#define ESPHOME_LOG_LEVEL_ERROR 0
#define ESPHOME_LOG_LEVEL_WARN 1
#define ESPHOME_LOG_LEVEL_INFO 2
#define ESPHOME_LOG_LEVEL_DEBUG 3
#define ESPHOME_LOG_LEVEL_VERBOSE 4
#define ESP_LOGV(tag, fmt, ...) do {} while(0)
#define ESP_LOGVV(tag, fmt, ...) do {} while(0)
#define ESP_LOGD(tag, fmt, ...) do {} while(0)
#define ESP_LOGI(tag, fmt, ...) do {} while(0)
#define ESP_LOGW(tag, fmt, ...) do {} while(0)
#define ESP_LOGE(tag, fmt, ...) do {} while(0)
