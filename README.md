# stm32f103c8t6_demo_test
test case for stm32f103c8t6，基于HAl库构建.

# 1 目录说明
## 1.1 **USB/**下是usb各种*device*测试case
覆盖了多种USB设备类，包括CDC（通信设备类）、HID（人机接口设备类）、MSC（大容量存储设备类），以及它们的组合。
- **CDC例程**：实现USB CDC类，适用于串口通信。
- **HID例程**：实现USB HID类，适用于键盘、鼠标等人机接口设备。
- **MSC例程**：实现USB MSC类，适用于U盘等大容量存储设备。
- **CDC+HID例程**：同时实现CDC和HID类，适用于需要同时支持串口通信和人机接口的场景。
- **HID+MSC例程**：实现了HID和MSC类（该case可以作为很好的例程参考）
    - 使用说明：实现了两个hid鼠标和一个hid键盘，另外模拟了一个U盘
    - hid可以通过串口输入命令来控制鼠标键盘移动，具体命令可参考代码
- **CDC+HID+MSC例程**：同时实现CDC、HID和MSC类，适用于需要支持多种USB功能的复杂应用。

# 删除结果即中间文件
- 执行bat脚本del_result_file.bat

## 许可证
本仓库中的代码遵循MIT许可证，你可以自由使用、修改和分发这些代码。