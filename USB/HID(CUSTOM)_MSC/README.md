将 STM32F103C8T6 的 CustomHID 和 MSC USB 设备进行复合，其中

- EP0 用于枚举 
- EP1 用于键盘设备
- EP2 用于鼠标设备（支持绝对模式和相对模式）
- EP3用于 MSC 设备（配有官方 demo 版本和 FAT16 版本（默认））。

正常情况下，**键鼠设备**可以共用一个接口，利用报告 ID 作为前缀，发送不同的report 到主机上。但是这种情况下，报告描述符是写在同一个数组内的，当遇到某些主机（如 IBM 的 AIX7 系统）枚举阶段是 boot 启动模式时，并不会启动报告描述符的请求，那么键鼠均不能用，**因此键鼠需要分配不同的接口（interface）**。虽然以 CUSTOMHID 和 MSC 为复合对象，但是也可为其他复合设备，双复合，甚至是三复合均可。

这里说明不会写得太详细，仅为一些需要修改的东西，所涉及的内容某些作者也不是很理解。要求读者有一定的 USB device 的相关知识，方可有参考意义。

1. 加入usbd_composite.c 和 usbd_composite.h 文件来整合hid和msc设备的各项类操作

   - 定义hid和msc的handle

   - 定义复合函数结构体

   - 定义配置描述符，将hid和msc设备写在一起。详细参考代码

   - PMA 地址设置。每个 EP(EP0、EP1 EP2 PE3)都要有一个缓存区，需要配置每个 EP 的 IN 和

     OUT 端点的缓存地址，该函数在 usbd_conf.c 函数里面。

2. usbd_conf.c 、usbd_conf.h修改
   - 每个设备需要占据不同的内存空间，而默认生成的工程是以你母版工程的默认设备的地址，比如：
``` C
#define USBD_malloc_MSC         (uint32_t *)USBD_static_malloc_MSC
#define USBD_malloc_CHID         (uint32_t *)USBD_static_malloc_CHID
```
3. 去掉 CustomHID 发送 report 函数的 state 判断，直接往某个端点上发送报文

> 在MSC与HID的复合设备执行初始化的时候，会执行对应USBD_HID_Init与USBD_MSC_Init的初始化函数。这些个初始化函数的作用主要是为HID与MSC分配对应类型的操作句柄（如：USBD_HID_HandleTypeDef与USBD_MSC_BOT_HandleTypeDef）并将对应的操作句柄添加到USB设备的操作句柄中（USBD_HandleTypeDef）的pClassData。但是由于HID与MSC的初始化有分先后，所以最终USB设备中的pClassData指向的是最后一个USB设备类型的操作句柄（MSC或者HID的操作句柄）。这样的原因导致在使用USBD_HID_SendReport的时候，并不能获取到真正HID操作句柄，因此没办法判断正确的hhid->state，所以导致无法发送报文。

- 解决方法：

>分别创建HID与MSC操作句柄的全局变量，并且将原来USBD_HID_Init中分配堆空间的操作，改为直接指向对应的全局变量。然后对应Delnit中将有关堆空间释放的操作给注释掉。

>在复合设备中的DataIn与DataOut以及其他有关对应类型的数据交互中，需要将USBD_HandleTypeDef *pdev->pClassData指向对应USB类型的全局变量，以及USBD_HandleTypeDef *pdev->pUserData指向对应USB类型的用户函数。

4. 测试
编译下载到后（记得重新插拔下usb线），会在设备管理器上识别出键盘、两个鼠标和一个U盘。通过uart可以向鼠标键盘发送命令来控制。
- 通过以下命令测试
   - `KThello world`键盘键入hello world
   
   - `MM10,10`相对鼠标移动

   - `MN100,100`绝对鼠标移动
   
     具体的规则参考代码。
