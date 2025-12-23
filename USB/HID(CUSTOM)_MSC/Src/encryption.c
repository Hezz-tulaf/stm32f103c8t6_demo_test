#include "encryption.h"

#include "stmflash.h"
#include "usart.h"
#include "delay.h"


//stm32芯片的ID地址，把地址减去一个数，避免汇编里面直接出现ID的地址，不然很容易暴露加密与ID号有关
volatile u32 STM32_ID_addr[3]= {0x1ffff7e8 - STM32_ID_D,0x1ffff7ec + STM32_ID_D,0x1ffff7f0 - STM32_ID_D};

/********************************************************************
函数功能：读出stm32的ID，12字节
入口参数：p
返    回：
备    注：把ID的地址做一下处理，加密性更好
********************************************************************/
void STM32_Read_ID(volatile u32 *p)
{
    volatile u32 Addr;
// 因为不想让程序在反汇编后直接找到这个地址，所以这个地址是运算出来的，
// 跟STM32_ID_addr反运算，当然了也可以用高级的算法，注意不能让编译器优化这个地址
    Addr = STM32_ID_addr[0] + STM32_ID_D;
    p[0] = *(vu32*)(Addr);
    Addr = STM32_ID_addr[1] - STM32_ID_D;
    p[1] = *(vu32*)(Addr);
    Addr = STM32_ID_addr[2] + STM32_ID_D;
    p[2] = *(vu32*)(Addr);
}
/********************************************************************
函数功能：加密ID并保存
入口参数：
返    回：
备    注：
********************************************************************/
void STM32_Encrypted_ID(void)
{
    u32 stm32ID[3];

    u16 flash_save[6];

    STM32_Read_ID(stm32ID);

    flash_save[0]=stm32ID[0]&0x0000ffff; //ID0   低十六位
    flash_save[1]=stm32ID[0]>>16;        //ID0   高十六位

    flash_save[2]=stm32ID[1]&0x0000ffff; //ID1   低十六位
    flash_save[3]=stm32ID[1]>>16;        //ID1   高十六位

    flash_save[4]=stm32ID[2]&0x0000ffff; //ID2   低十六位
    flash_save[5]=stm32ID[2]>>16;        //ID2   高十六位

    STMFLASH_Write(ID_FLASH_SAVE_ADDR,(u16*)flash_save,sizeof(flash_save));
    HAL_Delay(500);


}

/********************************************************************
函数功能：比较加密ID，正确返回0
入口参数：
返    回：1：不正确，0：正确
备    注：
********************************************************************/
u32 STM32_CMP_Encrypted_ID(void)
{
    u32 stm32ID[3];
    u16 stm32ID_read[6];
    u16 flash_read[6];

    u8 i;

    STM32_Read_ID(stm32ID);

    //读取的ID
    stm32ID_read[0]=stm32ID[0]&0x0000ffff; //ID0   低十六位
    stm32ID_read[1]=stm32ID[0]>>16;        //ID0   高十六位

    stm32ID_read[2]=stm32ID[1]&0x0000ffff; //ID1   低十六位
    stm32ID_read[3]=stm32ID[1]>>16;        //ID1   高十六位

    stm32ID_read[4]=stm32ID[2]&0x0000ffff; //ID2   低十六位
    stm32ID_read[5]=stm32ID[2]>>16;        //ID2   高十六位

    //FLASH存储的ID

    STMFLASH_Read(ID_FLASH_SAVE_ADDR,(u16*)flash_read, sizeof(flash_read));


    for( i=0; i<6; i++)
    {
        if(stm32ID_read[i]!=flash_read[i]) //FLASH读取和本身ID不一样  提示错误
        {
            while(1)
            {
//                printf("ID error !!!\r\n");
//                delay_ms(100);

            }
        }
        else
        {
//            printf("ID OK !!!\r\n");
//            delay_ms(100);
        }

//         printf("flash_read=%x\r\n",flash_read[i]);
    }


//    while(1)
//    {
//        printf("ID OK !!!\r\n");
//        delay_ms(1000);
//    }

}


////好了，有了上面那个程序，那下再继续
//
//
////===================ID加密控制=====================================================================
//   if(STM32_CMP_Encrypted_ID())
//   {
//      //量产时给一些条件，条件满足就对ID加密，然后把加密结果保存到flash中，把该程序与芯片的ID，唯一对应起来，加密完后，你也可以让它自宫。
//      if(XXXXXX)
//      {
//         STM32_Encrypted_ID();   //加密ID
//         自宫                    //即把加密这段代码从flash里面擦除，直接跳出去继续执行
//      }
//   }
//
//
////===================正常运行时==================================
//
//// 校验一下ID是否正确，
//   if(STM32_CMP_Encrypted_ID())
//   {
//    /*
//	来到这里嘛，当然不正确咯，你别让程序死在这哦，太明显了，很容易找到是你干的，
//    那么，一个系统肯定有一些参数才能运行的，你可以改变一些参数，这可以让系统
//    有时正常有时不正常，，呵呵，要查也不是那么容易的事了
//	*/
//   }
//}

