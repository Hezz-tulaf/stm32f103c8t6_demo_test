#ifndef __KEYBOARD_MOUSE_UART_H
#define __KEYBOARD_MOUSE_UART_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

/* USER CODE BEGIN Includes */
#include "sys.h"


#define MOUSE_DEVICE_1  0
#define MOUSE_DEVICE_2  1
	 
// 鼠标按钮定义
typedef enum {
    MOUSE_BUTTON_NONE   = 0x00,
    MOUSE_BUTTON_LEFT   = 0x01,
    MOUSE_BUTTON_RIGHT  = 0x02,
    MOUSE_BUTTON_MIDDLE = 0x04,
    MOUSE_BUTTON_BACK   = 0x08,
    MOUSE_BUTTON_FORWARD= 0x10
} mouse_button_t;

void parse_mouse_command(char *cmd, uint8_t device);
void parse_keyboard_command(char *cmd);
void parse_key_modifier(char *args);
void parse_key_press(char *keys);
void parse_key_press(char *keys);
void parse_key_type(char *text);
void parse_mouse_move(char *args, uint8_t device);
void parse_mouse_move(char *args, uint8_t device);
void parse_mouse_move(char *args, uint8_t device);
void parse_mouse_move(char *args, uint8_t device);
void parse_mouse_button(char *args, uint8_t device, uint8_t button);
void parse_mouse_scroll(char *args, uint8_t device);

void parse_and_execute_command(void);
#endif
