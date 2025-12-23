#ifndef __KEYBOARD_MOUSE_UART_H
#define __KEYBOARD_MOUSE_UART_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "usbd_customhid.h"
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

/* 简单相对鼠标操作 */
typedef struct {
	uint8_t report_id;
    uint8_t buttons;  // 按钮状态
    int8_t  x;        // X轴移动 (-127~127)
    int8_t  y;        // Y轴移动 (-127~127)
    int8_t  wheel;    // 滚轮 (-127~127)
} mouse_report_t;

/* 简单键盘操作 */
typedef struct {
    uint8_t modifier;   // 修饰键 (BYTE0)
    uint8_t reserved;   // 保留 (BYTE1)
    uint8_t keycode[6]; // 按键码 (BYTE2-BYTE7)
} keyboard_report_t;


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


void rel_mouse_send(uint8_t buttons, int8_t x, int8_t y, int8_t wheel);
void abs_mouse_send(uint8_t buttons, uint16_t x, uint16_t y, int8_t wheel);
void keyboard_send(int8_t key_sp,int8_t key1,int8_t key2,int8_t key3,int8_t key4,int8_t key5,int8_t key6);
#endif
