#ifndef __LOG_H
#define __LOG_H
#include <stdio.h>
/* 1. 颜色定义 */
#define LOG_COLOR_RESET   "\033[0m"
#define LOG_COLOR_RED     "\033[31m"
#define LOG_COLOR_GREEN   "\033[32m"
#define LOG_COLOR_YELLOW  "\033[33m"
#define LOG_COLOR_BLUE    "\033[34m"
#define LOG_COLOR_MAGENTA "\033[35m"
#define LOG_COLOR_CYAN    "\033[36m"
#define LOG_COLOR_WHITE   "\033[37m"

#define LOG_COLOR_BRIGHT_RED "\033[91m"
#define LOG_COLOR_ORANGE     "\033[38;5;214m" 

/* 2. 级别定义 */
#define LOG_LEVEL_EMERG   0
#define LOG_LEVEL_ALERT   1
#define LOG_LEVEL_CRIT    2
#define LOG_LEVEL_ERR     3
#define LOG_LEVEL_WARN    4
#define LOG_LEVEL_NOTICE  5
#define LOG_LEVEL_INFO    6
#define LOG_LEVEL_DEBUG   7

/* 3. 全局配置（编译时可覆盖） */
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

/* 4. 全局变量和设置函数 */
extern int g_log_level;
#define SET_LOG_LEVEL(level) (g_log_level = (level))

/* 5. 字符拼接辅助宏 */
#define __LOG_CONCAT(a, b) a##b
#define __LOG_LEVEL_VALUE(level) __LOG_CONCAT(LOG_LEVEL_, level)
#define __LOG_COLOR_VALUE(color) __LOG_CONCAT(LOG_COLOR_, color)

/* 6. 级别到颜色的映射（编译时完成） */
#define __LOG_GET_COLOR(level) \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_EMERG) ? __LOG_COLOR_VALUE(BRIGHT_RED) : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_ALERT)   ? __LOG_COLOR_VALUE(ORANGE) : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_CRIT)  ? __LOG_COLOR_VALUE(MAGENTA) : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_ERR) ? __LOG_COLOR_VALUE(RED) : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_WARN)   ? __LOG_COLOR_VALUE(YELLOW) : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_NOTICE)  ? __LOG_COLOR_VALUE(BLUE) : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_INFO)  ? __LOG_COLOR_VALUE(GREEN) : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_DEBUG) ? __LOG_COLOR_VALUE(WHITE) : \
    __LOG_COLOR_VALUE(CYAN)

/* 7. 级别到字符串的映射 */
#define __LOG_GET_STRING(level) \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_EMERG)  ? "EMERG" : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_ALERT)  ? "ALERT" : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_CRIT) ? "CRIT" : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_ERR) ? "ERR" : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_WARN)   ? "WARN" : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_NOTICE)  ? "NOTICE" : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_INFO)  ? "INFO" : \
    (__LOG_LEVEL_VALUE(level) == LOG_LEVEL_DEBUG) ? "DEBUG" : \
    "INFO"

/* 8. 主LOG宏 */
#define LOG(level, fmt, ...) \
    do { \
        if (__LOG_LEVEL_VALUE(level) <= g_log_level) { \
            printf("%s[%s] " fmt __LOG_COLOR_VALUE(RESET), \
                   __LOG_GET_COLOR(level), \
                   __LOG_GET_STRING(level), \
                   ##__VA_ARGS__); \
        } \
    } while(0)
	
	
#endif
