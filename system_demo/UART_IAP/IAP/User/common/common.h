#ifndef __common_h__
#define __common_h__

#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <time.h>

#define IS_AF(c)  ((c >= 'A') && (c <= 'F'))
#define IS_af(c)  ((c >= 'a') && (c <= 'f'))
#define IS_09(c)  ((c >= '0') && (c <= '9'))
#define ISVALIDHEX(c)  IS_AF(c) || IS_af(c) || IS_09(c)
#define ISVALIDDEC(c)  IS_09(c)
#define CONVERTDEC(c)  (c - '0')

#define CONVERTHEX_alpha(c)  (IS_AF(c) ? (c - 'A'+10) : (c - 'a'+10))
#define CONVERTHEX(c)   (IS_09(c) ? (c - '0') : CONVERTHEX_alpha(c))


//=================================================

void  memREset(unsigned char *buf,unsigned char setb,unsigned char num);
void	str_cat(unsigned char	*need_cat,const char *src_cat);
unsigned char  memCpare(unsigned char *buf1,unsigned char *buf2,unsigned char num);
unsigned char	str_cmp(unsigned char	*buf1,const char *buf2);
void  memcopy(unsigned char *buf1,unsigned char *srcbuf,unsigned int num);
void	str_cpy(unsigned char	*buf1,unsigned char	*srcbuf);
unsigned int str_cpy1(unsigned char	*buf,unsigned char	*srcbuf);
unsigned int str_cpy2(unsigned char	*buf,unsigned char	*srcbuf);
unsigned char INT2Sry(long n, unsigned char *s);////将整数nn转为字符数组ss//
unsigned int str_len(unsigned char	*str);
void  Int2ASCII(unsigned char *ascbuf,unsigned long dataInt,unsigned char  num);
unsigned long  Nstr2Long(unsigned char  *str,unsigned char pp);
unsigned char Do_XOR(unsigned char *inbuf,unsigned int len);
unsigned char Do_SUM(unsigned char *inbuf,unsigned int len);
unsigned char	ASCII2HEX(unsigned char * ascbuf, unsigned char len ,unsigned char * rehexbuf);
unsigned int	HEX2ASCII(unsigned char * hexbuf, unsigned int num ,unsigned char * ascbuf);
void FormatRunTime2(unsigned char *nowtime);
unsigned char RCVAtoI(unsigned char *str);
unsigned char Int_hasbits(unsigned long n);
unsigned char Buffercmp(unsigned char *buffer1,unsigned char *buffer2,unsigned char len);
unsigned char HexToBcd(unsigned char Value);
unsigned char BcdToHex(unsigned char Value);
unsigned int Str2Int(unsigned char *inputstr, unsigned int *intnum);
unsigned int random(unsigned int seed,unsigned int maxnum,unsigned int minnum);
#endif
