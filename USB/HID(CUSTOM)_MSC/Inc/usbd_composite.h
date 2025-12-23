/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_COMPOSITE_H
#define __USBD_COMPOSITE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_msc.h"
#include  "usbd_customhid.h"
#include "usbd_storage_if.h"
#include "usbd_custom_hid_if.h"

#define WBVAL(x) (x & 0xFF),((x >> 8) & 0xFF)
#define DBVAL(x) (x & 0xFF),((x >> 8) & 0xFF),((x >> 16) & 0xFF),((x >> 24) & 0xFF)

#define USBD_KeyBoard_INTERFACE      0
#define USBD_Mouse_INTERFACE         1
#define USBD_MSC_INTERFACE           2


#define MSC_INDATA_NUM              (MSC_EPIN_ADDR & 0x0F)
#define MSC_OUTDATA_NUM             (MSC_EPOUT_ADDR & 0x0F)


#define CustomHID_KeyBoard_INDATA_NUM           (CUSTOM_HID_EPIN_ADDR & 0x0F)
#define CustomHID_KeyBoard_OUTDATA_NUM          (CUSTOM_HID_EPOUT_ADDR & 0x0F)

#define CustomHID_Mouse_INDATA_NUM              (CUSTOM_HID_EP2IN_ADDR & 0x0F)
#define CustomHID_Mouse_OUTDATA_NUM             (CUSTOM_HID_EP2OUT_ADDR & 0x0F)

#define USBD_COMPOSITE_DESC_SIZE    96//配置描述符大小  三个接口


extern USBD_ClassTypeDef    USBD_COMPOSITE;

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __USBD_MSC_H */
/**
  * @}
  */
