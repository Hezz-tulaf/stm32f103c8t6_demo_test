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


extern USBD_HandleTypeDef hUsbDeviceFS;
// 命令缓冲区
extern uint8_t g_rx_buffer;//USART1接收的Buffer
#define CMD_BUFFER_SIZE 64
static char cmd_buffer[CMD_BUFFER_SIZE];
static uint8_t cmd_index = 0;
static uint8_t cmd_ready = 0;

// 按键映射表
static const uint8_t keymap[128] = {
    [0x00] = 0x00, // NULL (无键值)
    // 数字键 (0-9)
    [0x30] = 0x27, // 0 -> Keyboard 0 and )
    [0x31] = 0x1E, // 1 -> Keyboard 1 and !
    [0x32] = 0x1F, // 2 -> Keyboard 2 and @
    [0x33] = 0x20, // 3 -> Keyboard 3 and #
    [0x34] = 0x21, // 4 -> Keyboard 4 and $
    [0x35] = 0x22, // 5 -> Keyboard 5 and %
    [0x36] = 0x23, // 6 -> Keyboard 6 and ^
    [0x37] = 0x24, // 7 -> Keyboard 7 and &
    [0x38] = 0x25, // 8 -> Keyboard 8 and *
    [0x39] = 0x26, // 9 -> Keyboard 9 and (
    
    // 小写字母 (a-z)
    [0x61] = 0x04, // a -> Keyboard a and A
    [0x62] = 0x05, // b -> Keyboard b and B
    [0x63] = 0x06, // c -> Keyboard c and C
    [0x64] = 0x07, // d -> Keyboard d and D
    [0x65] = 0x08, // e -> Keyboard e and E
    [0x66] = 0x09, // f -> Keyboard f and F
    [0x67] = 0x0A, // g -> Keyboard g and G
    [0x68] = 0x0B, // h -> Keyboard h and H
    [0x69] = 0x0C, // i -> Keyboard i and I
    [0x6A] = 0x0D, // j -> Keyboard j and J
    [0x6B] = 0x0E, // k -> Keyboard k and K
    [0x6C] = 0x0F, // l -> Keyboard l and L
    [0x6D] = 0x10, // m -> Keyboard m and M
    [0x6E] = 0x11, // n -> Keyboard n and N
    [0x6F] = 0x12, // o -> Keyboard o and O
    [0x70] = 0x13, // p -> Keyboard p and P
    [0x71] = 0x14, // q -> Keyboard q and Q
    [0x72] = 0x15, // r -> Keyboard r and R
    [0x73] = 0x16, // s -> Keyboard s and S
    [0x74] = 0x17, // t -> Keyboard t and T
    [0x75] = 0x18, // u -> Keyboard u and U
    [0x76] = 0x19, // v -> Keyboard v and V
    [0x77] = 0x1A, // w -> Keyboard w and W
    [0x78] = 0x1B, // x -> Keyboard x and X
    [0x79] = 0x1C, // y -> Keyboard y and Y
    [0x7A] = 0x1D, // z -> Keyboard z and Z
    
    // 大写字母 (A-Z) - 需要结合Shift键
    [0x41] = 0x04, // A -> Keyboard a and A (实际使用时需要加Shift)
    [0x42] = 0x05, // B -> Keyboard b and B
    [0x43] = 0x06, // C -> Keyboard c and C
    [0x44] = 0x07, // D -> Keyboard d and D
    [0x45] = 0x08, // E -> Keyboard e and E
    [0x46] = 0x09, // F -> Keyboard f and F
    [0x47] = 0x0A, // G -> Keyboard g and G
    [0x48] = 0x0B, // H -> Keyboard h and H
    [0x49] = 0x0C, // I -> Keyboard i and I
    [0x4A] = 0x0D, // J -> Keyboard j and J
    [0x4B] = 0x0E, // K -> Keyboard k and K
    [0x4C] = 0x0F, // L -> Keyboard l and L
    [0x4D] = 0x10, // M -> Keyboard m and M
    [0x4E] = 0x11, // N -> Keyboard n and N
    [0x4F] = 0x12, // O -> Keyboard o and O
    [0x50] = 0x13, // P -> Keyboard p and P
    [0x51] = 0x14, // Q -> Keyboard q and Q
    [0x52] = 0x15, // R -> Keyboard r and R
    [0x53] = 0x16, // S -> Keyboard s and S
    [0x54] = 0x17, // T -> Keyboard t and T
    [0x55] = 0x18, // U -> Keyboard u and U
    [0x56] = 0x19, // V -> Keyboard v and V
    [0x57] = 0x1A, // W -> Keyboard w and W
    [0x58] = 0x1B, // X -> Keyboard x and X
    [0x59] = 0x1C, // Y -> Keyboard y and Y
    [0x5A] = 0x1D, // Z -> Keyboard z and Z
    
    // 特殊字符
    [0x20] = 0x2C, // 空格 -> Keyboard Spacebar
    [0x0D] = 0x28, // 回车 -> Keyboard Return (ENTER)
    [0x08] = 0x2A, // 退格 -> Keyboard Delete (Backspace)
    [0x09] = 0x2B, // 制表符 -> Keyboard Tab
    [0x1B] = 0x29, // ESC -> Keyboard Escape
    [0x2D] = 0x2D, // - -> Keyboard - and _
    [0x3D] = 0x2E, // = -> Keyboard = and +
    [0x5B] = 0x2F, // [ -> Keyboard [ and {
    [0x5D] = 0x30, // ] -> Keyboard ] and }
    [0x5C] = 0x31, // \ -> Keyboard \ and |
    [0x3B] = 0x33, // ; -> Keyboard ; and :
    [0x27] = 0x34, // ' -> Keyboard ' and "
    [0x60] = 0x35, // ` -> Keyboard ` and ~
    [0x2C] = 0x36, // , -> Keyboard , and <
    [0x2E] = 0x37, // . -> Keyboard . and >
    [0x2F] = 0x38, // / -> Keyboard / and ?
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

    switch (device) {
        case DEV_MOUSE1:
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
        
		if(MOUSE_DEVICE_1 == device) {
			// 相对移动鼠标
			rel_mouse_send(0, x, y, 0);
		} else {
			// 绝对移动鼠标
			abs_mouse_send(0, x, y, 0);
		}
    }
}

/**
 * @brief 解析鼠标按键命令
 */
void parse_mouse_button(char *args, uint8_t device, uint8_t button)
{
	if(MOUSE_DEVICE_1 == device) {
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
	} else {
		if (strlen(args) == 0) {
			// 点击: 按下然后释放
			abs_mouse_send(button, 0, 0, 0);
			HAL_Delay(20);
			abs_mouse_send(0, 0, 0, 0);
		} else if (args[0] == 'D') {
			// 按下
			abs_mouse_send(button, 0, 0, 0);
		} else if (args[0] == 'U') {
			// 释放
			abs_mouse_send(0, 0, 0, 0);
		}
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
    if(MOUSE_DEVICE_1 == device) {
		rel_mouse_send(0, 0, 0, delta);
		HAL_Delay(5);
		rel_mouse_send(0, 0, 0, 0);
	} else {
		abs_mouse_send(0, 0, 0, delta);
		HAL_Delay(5);
		abs_mouse_send(0, 0, 0, 0);
	}
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
            }
            // 按下字符键
            keyboard_send(modifier, keycode, 0, 0, 0, 0, 0);
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
    }
}

void rel_mouse_send(uint8_t buttons, int8_t x, int8_t y, int8_t wheel) //x为左右   y为上下
{
    mouse_report_t report;
	report.report_id = 0x01; //0x01: 为相对鼠标报告ID   在报告描述符中可更改
    report.buttons = buttons; // 鼠标动作
    report.x = x;
    report.y = y;
    report.wheel = wheel; //滚轮的步进量  QT中滚轮转动一个格子 15° 返回数值120  HID中 滚轮步进量范围为-127~127  往下为负  往上为正

    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&report, sizeof(report),2);
}

#define SCREEN_WIDTH   1920
#define SCREEN_HEIGHT  1080
/*这里简单实现了下绝对坐标的鼠标*/
void abs_mouse_send(uint8_t buttons, uint16_t x, uint16_t y, int8_t wheel)
{
    // 转换到HID绝对坐标范围 (0-32767)
    uint16_t hid_x = (uint32_t)x * 32767 / SCREEN_WIDTH;
    uint16_t hid_y = (uint32_t)y * 32767 / SCREEN_HEIGHT;
    
    // 确保在范围内
    if (hid_x > 32767) hid_x = 32767;
    if (hid_y > 32767) hid_y = 32767;
	
    uint8_t buf[7] = {
        0x02,
        buttons,
        hid_x & 0xFF,
        (hid_x >> 8) & 0xFF,
        hid_y & 0xFF,
        (hid_y >> 8) & 0xFF,  
        wheel& 0xFF
    };
    
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, buf, 7, 2);
}


void keyboard_reset()
{
    keyboard_report_t report = {0};
    while(USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&report, 8, 1)!= USBD_OK);
}

void keyboard_send(int8_t key_sp,int8_t key1,int8_t key2,int8_t key3,int8_t key4,int8_t key5,int8_t key6)
{
    keyboard_report_t report;
    report.modifier = key_sp;
    report.reserved = 0;
    report.keycode[0] = key1;
    report.keycode[1] = key2;
    report.keycode[2] = key3;
    report.keycode[3] = key4;
    report.keycode[4] = key5;
    report.keycode[5] = key6;

    while(USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&report, 8, 1)!= USBD_OK);

    HAL_Delay(2);  //延时是必要的
    keyboard_reset(); //发送0  表示键盘弹起 否则一直相应之前的键值
    HAL_Delay(2);
}

