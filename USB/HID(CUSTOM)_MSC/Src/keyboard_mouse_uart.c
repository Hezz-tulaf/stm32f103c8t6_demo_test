#include "keyboard_mouse_uart.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include <ctype.h>
// 命令格式：[设备类型][操作类型][参数]
// 示例: M1M10,20   表示鼠标1移动X=10,Y=20
//       KPTabc     表示键盘按下abc

// 设备类型
#define DEV_MOUSE1   'M'  // 鼠标1
#define DEV_MOUSE2   'N'  // 鼠标2（使用N作为第二个鼠标）
#define DEV_KEYBOARD 'K'  // 键盘

// 鼠标操作
#define MOUSE_MOVE   'M'  // 移动
#define MOUSE_LEFT   'L'  // 左键
#define MOUSE_RIGHT  'R'  // 右键
#define MOUSE_MIDDLE 'C'  // 中键
#define MOUSE_SCROLL 'S'  // 滚轮

// 键盘操作
#define KEY_PRESS    'P'  // 按下
#define KEY_TYPE     'T'  // 输入字符串
#define KEY_MODIFIER 'M'  // 修改键

// 特殊键值
#define KEY_ENTER    '\n'
#define KEY_SPACE    ' '
#define KEY_BACKSPACE '\b'
#define KEY_TAB      '\t'
#define KEY_ESC      0x1B



// 命令缓冲区
extern uint8_t g_rx_buffer;//USART1接收的Buffer
#define CMD_BUFFER_SIZE 64
static char cmd_buffer[CMD_BUFFER_SIZE];
static uint8_t cmd_index = 0;
static uint8_t cmd_ready = 0;

// 按键映射表
static const uint8_t keymap[128] = {
    [0x04] = 0x1E, // a -> Keyboard a and A
    [0x05] = 0x30, // b -> Keyboard b and B
    [0x06] = 0x2E, // c -> Keyboard c and C
    [0x07] = 0x20, // d -> Keyboard d and D
    [0x08] = 0x12, // e -> Keyboard e and E
    [0x09] = 0x21, // f -> Keyboard f and F
    [0x0A] = 0x22, // g -> Keyboard g and G
    [0x0B] = 0x23, // h -> Keyboard h and H
    [0x0C] = 0x17, // i -> Keyboard i and I
    [0x0D] = 0x24, // j -> Keyboard j and J
    [0x0E] = 0x25, // k -> Keyboard k and K
    [0x0F] = 0x26, // l -> Keyboard l and L
    [0x10] = 0x32, // m -> Keyboard m and M
    [0x11] = 0x31, // n -> Keyboard n and N
    [0x12] = 0x18, // o -> Keyboard o and O
    [0x13] = 0x19, // p -> Keyboard p and P
    [0x14] = 0x10, // q -> Keyboard q and Q
    [0x15] = 0x13, // r -> Keyboard r and R
    [0x16] = 0x1F, // s -> Keyboard s and S
    [0x17] = 0x14, // t -> Keyboard t and T
    [0x18] = 0x16, // u -> Keyboard u and U
    [0x19] = 0x2F, // v -> Keyboard v and V
    [0x1A] = 0x11, // w -> Keyboard w and W
    [0x1B] = 0x2D, // x -> Keyboard x and X
    [0x1C] = 0x15, // y -> Keyboard y and Y
    [0x1D] = 0x2C, // z -> Keyboard z and Z
    [0x1E] = 0x27, // 1 -> Keyboard 1 and !
    [0x1F] = 0x1E, // 2 -> Keyboard 2 and @
    [0x20] = 0x1F, // 3 -> Keyboard 3 and #
    [0x21] = 0x20, // 4 -> Keyboard 4 and $
    [0x22] = 0x21, // 5 -> Keyboard 5 and %
    [0x23] = 0x22, // 6 -> Keyboard 6 and ^
    [0x24] = 0x23, // 7 -> Keyboard 7 and &
    [0x25] = 0x24, // 8 -> Keyboard 8 and *
    [0x26] = 0x25, // 9 -> Keyboard 9 and (
    [0x27] = 0x26, // 0 -> Keyboard 0 and )
    [' ']  = 0x2C, // 空格
    ['\n'] = 0x28, // 回车
    ['\b'] = 0x2A, // 退格
    ['\t'] = 0x2B, // 制表符
    [0x1B] = 0x29, // ESC
};

/**
 * @brief 串口接收中断回调
 * @param huart 串口句柄
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) {
        // 处理接收到的字符
        if (g_rx_buffer == '\r' || g_rx_buffer == '\n') {
            // 命令结束
            if (cmd_index > 0) {
                cmd_buffer[cmd_index] = '\0';  // 添加字符串结束符
                cmd_index = 0;  // 重置索引
            }
        } 
        else if (cmd_index < 63) {
            // 存储命令字符
            cmd_buffer[cmd_index++] = g_rx_buffer;
        } 
        else {
            // 缓冲区满，清空
            printf("Buffer overflow!\r\n");
            cmd_index = 0;
        }
        
        HAL_UART_Receive_IT(huart, &g_rx_buffer, 1);
    }
	cmd_ready = 1;
}

/**
 * @brief 解析并执行命令
 */
void parse_and_execute_command(void)
{
    if (!cmd_ready) return;

    char *cmd = cmd_buffer;
    char device = cmd[0];
    printf("cmd:%s device :%d\r\n",cmd_buffer,cmd[0]);
    switch (device) {
        case DEV_MOUSE1:
			printf("mouse\r\n");
            parse_mouse_command(cmd, MOUSE_DEVICE_1);
            break;

        case DEV_MOUSE2:
            parse_mouse_command(cmd, MOUSE_DEVICE_2);
            break;

        case DEV_KEYBOARD:
            parse_keyboard_command(cmd);
            break;

        default:
            // 未知设备
            break;
    }
    
    cmd_ready = 0;
}

/**
 * @brief 解析鼠标命令
 * @param cmd 命令字符串
 * @param device 鼠标设备
 */
void parse_mouse_command(char *cmd, uint8_t device)
{
    if (strlen(cmd) < 2) return;
    
    char operation = cmd[1];
    
    switch (operation) {
        case MOUSE_MOVE:
            // 格式: MM10,20 或 MM-10,5
		    printf("move\r\n");
            parse_mouse_move(cmd + 2, device);
            break;
            
        case MOUSE_LEFT:
            // 格式: ML 或 MLD (按下) / MLU (释放)
            parse_mouse_button(cmd + 2, device, MOUSE_BUTTON_LEFT);
            break;
            
        case MOUSE_RIGHT:
            parse_mouse_button(cmd + 2, device, MOUSE_BUTTON_RIGHT);
            break;
            
        case MOUSE_MIDDLE:
            parse_mouse_button(cmd + 2, device, MOUSE_BUTTON_MIDDLE);
            break;
            
        case MOUSE_SCROLL:
            // 格式: MS5 (向上滚动5) 或 MS-5 (向下滚动5)
            parse_mouse_scroll(cmd + 2, device);
            break;
    }
}

/**
 * @brief 解析鼠标移动命令
 */
void parse_mouse_move(char *args, uint8_t device)
{
    int8_t x = 0, y = 0;
    char *comma = strchr(args, ',');
    
    if (comma) {
        *comma = '\0';
        x = (int8_t)atoi(args);
        y = (int8_t)atoi(comma + 1);
        
        // 限制范围
        if (x > 127) x = 127;
        if (x < -127) x = -127;
        if (y > 127) y = 127;
        if (y < -127) y = -127;
        
        // 移动鼠标
		printf("x:%d y:%d\r\n",x,y);
        rel_mouse_send(0, x, y, 0);
    }
}

/**
 * @brief 解析鼠标按键命令
 */
void parse_mouse_button(char *args, uint8_t device, uint8_t button)
{
    if (strlen(args) == 0) {
        // 点击: 按下然后释放
        rel_mouse_send(button, 0, 0, 0);
        HAL_Delay(20);
        rel_mouse_send(0, 0, 0, 0);
    } else if (args[0] == 'D') {
        // 按下
        rel_mouse_send(button, 0, 0, 0);
    } else if (args[0] == 'U') {
        // 释放
        rel_mouse_send(0, 0, 0, 0);
    }
}

/**
 * @brief 解析鼠标滚轮命令
 */
void parse_mouse_scroll(char *args, uint8_t device)
{
    int8_t delta = (int8_t)atoi(args);
    
    if (delta > 127) delta = 127;
    if (delta < -127) delta = -127;
    
    rel_mouse_send(0, 0, 0, delta);
    HAL_Delay(5);
    rel_mouse_send(0, 0, 0, 0);
}

/**
 * @brief 解析键盘命令
 */
void parse_keyboard_command(char *cmd)
{
    if (strlen(cmd) < 2) return;
    
    char operation = cmd[1];
    char *args = cmd + 2;
    
    switch (operation) {
        case KEY_PRESS:
            // 格式: KPabc 或 KPA (单个键)
            parse_key_press(args);
            break;
            
        case KEY_TYPE:
            // 格式: KThello world
            parse_key_type(args);
            break;
            
        case KEY_MODIFIER:
            // 格式: KMCa (Ctrl+A)
            parse_key_modifier(args);
            break;
    }
}

/**
 * @brief 解析按键按下命令
 */
void parse_key_press(char *keys)
{
    for (int i = 0; keys[i] != '\0'; i++) {
        char c = keys[i];
        uint8_t keycode = keymap[(uint8_t)c];
        
        if (keycode != 0) {
            // 按下键
            keyboard_send(0, keycode, 0, 0, 0, 0, 0);
            HAL_Delay(20);
            // 释放键
            keyboard_send(0, 0, 0, 0, 0, 0, 0);
            HAL_Delay(10);
        }
    }
}

/**
 * @brief 解析字符串输入命令
 */
void parse_key_type(char *text)
{
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        uint8_t keycode = keymap[(uint8_t)c];
        uint8_t modifier = 0;
        
        // 检查是否需要Shift（大写字母和特殊符号）
        if (isupper(c) || 
            (c >= '!' && c <= '&') || 
            c == '(' || c == ')' || 
            c == '*' || c == '@' ||
            c == '#' || c == '$' ||
            c == '%' || c == '^') {
            modifier = 0x02; // Left Shift
        }
        
        if (keycode != 0) {
            // 按下修饰键（如果需要）
            if (modifier != 0) {
                keyboard_send(modifier, 0, 0, 0, 0, 0, 0);
                HAL_Delay(10);
            }
            
            // 按下字符键
            keyboard_send(modifier, keycode, 0, 0, 0, 0, 0);
            HAL_Delay(20);
            
            // 释放所有键
            keyboard_send(0, 0, 0, 0, 0, 0, 0);
            HAL_Delay(10);
            
            // 释放修饰键（如果需要）
            if (modifier != 0) {
                keyboard_send(0, 0, 0, 0, 0, 0, 0);
                HAL_Delay(10);
            }
        }
    }
}

/**
 * @brief 解析修饰键组合命令
 */
void parse_key_modifier(char *args)
{
    if (strlen(args) < 2) return;
    
    uint8_t modifier = 0;
    char key = args[1];
    
    // 解析修饰键
    switch (args[0]) {
        case 'C': modifier = 0x01; break; // Ctrl
        case 'S': modifier = 0x02; break; // Shift
        case 'A': modifier = 0x04; break; // Alt
        case 'W': modifier = 0x08; break; // Windows
    }
    
    uint8_t keycode = keymap[(uint8_t)key];
    if (keycode != 0) {
        // 按下组合键
        keyboard_send(modifier, keycode, 0, 0, 0, 0, 0);
        HAL_Delay(50);
        // 释放
        keyboard_send(0, 0, 0, 0, 0, 0, 0);
    }
}
