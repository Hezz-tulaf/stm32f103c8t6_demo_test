#include "common.h"

//====================================================
unsigned char Do_XOR(unsigned char *inbuf,unsigned int len)
{
	unsigned char xxor;
	unsigned int tmpint;

  xxor=0;
	for (tmpint=0;tmpint<len ;tmpint++ )
	{
		xxor^=inbuf[tmpint];
	}
	return xxor;
}

//====================================================
unsigned char Do_SUM(unsigned char *inbuf,unsigned int len)
{
	unsigned char xsum;
	unsigned int tmpint;

  xsum=0;
	for (tmpint=0;tmpint<len ;tmpint++ )
	{
		xsum+=inbuf[tmpint];
	}
	return xsum;
}

//=============================================================//
unsigned int str_len(unsigned char	*buf)
{
	unsigned int	i = 0;
	do
	{
		i++;
		if(i>65530)	return(0);
	}while(*buf++>0);
	return(i-1);
}

//======================================================================================//
unsigned char  memCpare(unsigned char *buf1,unsigned char *buf2,unsigned char num)
{
	unsigned char j;

	for(j=0;j<num;j++)
	{
		if( buf1[j]!=buf2[j] )
		{ return 0; }
	}
	return 1;
}

//数组比较
unsigned char Buffercmp(unsigned char *buffer1,unsigned char *buffer2,unsigned char len)
{
	while(len--)
	{
		if(*buffer1 != *buffer2)
		{
			return 1;
		}
		buffer1++;
		buffer2++;
	}
	
	return 0;
}

//====================================================================//
unsigned char	str_cmp(unsigned char	*buf1,const char *buf2)
{
	unsigned char i;
  unsigned char j;
  
  j=str_len((unsigned char *)buf2);
  
	for(i = 0;i<j;i++)
	{
		if( buf1[i] != buf2[i] )
		{ return 0; }
	}

	return(1);
						
}
//==========================================================================//
void  memREset(unsigned char *buf,unsigned char setb,unsigned char num)
{
	unsigned char j;
	for(j=0;j<num;j++)
	{
	   buf[j]=setb;
	}
}
//==========================================================================//
void	str_cat(unsigned char	*dest,const char *srcstr)
{
	unsigned int i,j,k;

	j = str_len(dest);
	k=str_len((unsigned char *)srcstr);
	
	for(i = 0;i<k;i++) 
	{
		dest[j+i] = srcstr[i];
	}
	dest[j+i] = 0;
}

//==========================================================================//
void  memcopy(unsigned char *buf1,unsigned char *srcbuf,unsigned int num)
{
	unsigned int j;
	
	for(j=0;j<num;j++)
	{
	   buf1[j]=srcbuf[j];
	}
}
//==========================================================================//
void	str_cpy(unsigned char	*buf1,unsigned char	*srcbuf)
{
	unsigned int	j,num;
	
	num=str_len(srcbuf);
	
	for(j = 0;j<num;j++)
	{	buf1[j] = srcbuf[j];}
	
	buf1[j] = 0;
}
//==========================================================================//
unsigned int str_cpy1(unsigned char	*buf,unsigned char	*srcbuf)
{
	unsigned int i=0;
	
	while(*srcbuf != '\0')
	{
		*buf = *srcbuf;
		buf++;
		srcbuf++;
		i++;
	}
	
	*buf = '\0';
	return i;
}
unsigned int str_cpy2(unsigned char	*buf,unsigned char	*srcbuf)
{
	unsigned int i=0;
	
	while((*srcbuf != '\0')&&(*srcbuf != ' '))
	{
		*buf = *srcbuf;
		buf++;
		srcbuf++;
		i++;
	}
	
	*buf = '\0';
	return i;
}
unsigned char Int_hasbits(unsigned long n)
{
	unsigned char count = 0;
	
	while (n / 10 > 0) 
	{
		count++;
		n = n / 10;
	}
	count++;
	
	return count;
}
//=================================================================================//
unsigned char INT2Sry(long n, unsigned char *s)
{
    unsigned char	tempbuf[16];
    int i,sign ;
    unsigned char	j;

    if (n == 0x80000000) //最小负数//
    {
        str_cpy(s,(unsigned char *)"-2147483648\0");
        return(0);
    }
    
    sign = n;
    
    if (sign < 0) { n = -n; }
    
    i = 0;
    do
    {
       tempbuf[i++] = n % 10 + '0';
    }while ((n /= 10) > 0);
    
    if (sign < 0)
    {
        tempbuf[i++] = '-';
    }
    tempbuf[i] = '\0';
    
    for(j = 0;j<i;j++)
    {s[j] = tempbuf[i-j-1];}
    s[j] = '\0';
    
    return(i);
}
//======================================================================================//
void Int2ASCII(unsigned char *ascbuf,unsigned long dataInt,unsigned char  num)
{
    unsigned long  divv;//
    unsigned char  i;//
    
    divv=0;
    
    if(num == 8)
    {  divv=10000000;}
    else if(num == 9)
    { divv=100000000;}
    
		for(i=0;i<num;i++)
		{
	    ascbuf[i] = dataInt/divv;
		  ascbuf[i]+='0';
		  dataInt  %= divv;
		  divv /=10;
		}
}
//============================================================//
//999999_0X000F423F//
//============================================================//
unsigned long  Nstr2Long(unsigned char  *str,unsigned char pp)
{
    unsigned char   j;
    unsigned long  tmp32;
    
    tmp32=0;
    
    for(j=0;j<pp;j++)
    {
       tmp32 *=10;
       tmp32 += str[j]-'0';  
    }
    return(tmp32);
}
//=============================================
//=======================================================================================//
unsigned char	ASCII2HEX(unsigned char * ascbuf, unsigned char len ,unsigned char * rehexbuf)
{
	unsigned char i,temp;
	
	temp=0;
	for(i = 0;i<(len/2);i++)
	{
		if( ('0'<=ascbuf[2*i])&&(ascbuf[2*i]<='9') )
		{
			temp = (((ascbuf[2*i]-'0')<<4)&0xf0);
			if(('0'<=ascbuf[2*i+1])&&(ascbuf[2*i+1]<='9'))
				{ rehexbuf[i] = (((ascbuf[2*i+1]-'0')&0x0f)|temp); }
			else if(('A'<=ascbuf[2*i+1])&&(ascbuf[2*i+1]<='F'))
				{ rehexbuf[i] = (((ascbuf[2*i+1]-'7')&0x0f)|temp); }
		}
		else if(('A'<=ascbuf[2*i])&&(ascbuf[2*i]<='F'))
		{
			temp = (((ascbuf[2*i]-'7')<<4)&0xf0);
			if(('0'<=ascbuf[2*i+1])&&(ascbuf[2*i+1]<='9'))
				{ rehexbuf[i] = (((ascbuf[2*i+1]-'0')&0x0f)|temp); }
			else if(('A'<=ascbuf[2*i+1])&&(ascbuf[2*i+1]<='F'))
				{ rehexbuf[i] = (((ascbuf[2*i+1]-'7')&0x0f)|temp); }
		}
		else
		{ rehexbuf[i] = 0; }
	}
	rehexbuf[i] = '\0';
	//---------------------------------------------------//
	if(len%2 == 1)
	{
		if(('0'<=ascbuf[2*i])&&(ascbuf[2*i]<='9'))
		{
			temp = (((ascbuf[2*i]-'0')<<4)&0xf0);
		}
		else if(('A'<=ascbuf[2*i])&&(ascbuf[2*i]<='F'))
		{
			temp = (((ascbuf[2*i]-'7')<<4)&0xf0);
		}
		else
		{ rehexbuf[i] = 0; }
		rehexbuf[i] = temp;
		rehexbuf[i+1] = '\0';
		return(i+1);
	}
	return(i);
}
//================================================================//
unsigned int	HEX2ASCII(unsigned char * hexbuf, unsigned int num ,unsigned char * ascbuf)
{
	unsigned int m;
	unsigned char hextmp;
	
	hextmp=0;
	for(m = 0;m <num;m++)
	{
		hextmp = ((hexbuf[m]>>4)&0x0f);
		if(hextmp<=9)
		{ascbuf[2*m] = (hextmp+'0');}
		else
		{ascbuf[2*m] = (hextmp+'7');}
		hextmp = (hexbuf[m]&0x0f);
		if(hextmp<=9)
		{ascbuf[2*m+1] = (hextmp+'0');}
		else
		{ascbuf[2*m+1] = (hextmp+'7');}
	}
	ascbuf[2*m] = '\0';
	
	return(2*m);
}

//==============================================================//
void FormatRunTime2(unsigned char *nowtime)
{

}

unsigned char RCVAtoI(unsigned char *str) 
{
	unsigned char n,i; 
	n=0;
	for(i=0;;i++)
	{
		if(str[i]==0X0D){break;} //
		if((str[i] < 0x30)||(str[i] > 0x39))
		{
			n = 0;
			return n;
		} 
		n*=10;
		n+=(str[i]-'0');
	}	
	return n;
}

unsigned char HexToBcd(unsigned char Value)
{
  unsigned char bcdhigh = 0;
  
  while (Value >= 10)
  {
    bcdhigh++;
    Value -= 10;
  }
  return  ((unsigned char)(bcdhigh << 4) | Value);
}

unsigned char BcdToHex(unsigned char Value)
{
  unsigned char tmp = 0;
  tmp = ((unsigned char)(Value & (unsigned char)0xF0) >> (unsigned char)0x4) * 10;
  return (tmp + (Value & (unsigned char)0x0F));
}

/**
  * @brief  Convert a string to an integer
  * @param  inputstr: The string to be converted
  * @param  intnum: The intger value
  * @retval 1: Correct
  *         0: Error
  */
unsigned int Str2Int(unsigned char *inputstr, unsigned int *intnum)
{
  unsigned int i = 0, res = 0;
  unsigned int val = 0;

  if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X'))
  {
    if (inputstr[2] == '\0')
    {
      return 0;
    }
    for (i = 2; i < 11; i++)
    {
      if (inputstr[i] == '\0')
      {
        *intnum = val;
        /* return 1; */
        res = 1;
        break;
      }
      if (ISVALIDHEX(inputstr[i]))
      {
        val = (val << 4) + CONVERTHEX(inputstr[i]);
      }
      else
      {
        /* return 0, Invalid input */
        res = 0;
        break;
      }
    }
    /* over 8 digit hex --invalid */
    if (i >= 11)
    {
      res = 0;
    }
  }
  else /* max 10-digit decimal input */
  {
    for (i = 0;i < 11;i++)
    {
      if (inputstr[i] == '\0')
      {
        *intnum = val;
        /* return 1 */
        res = 1;
        break;
      }
      else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0))
      {
        val = val << 10;
        *intnum = val;
        res = 1;
        break;
      }
      else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0))
      {
        val = val << 20;
        *intnum = val;
        res = 1;
        break;
      }
      else if (ISVALIDDEC(inputstr[i]))
      {
        val = val * 10 + CONVERTDEC(inputstr[i]);
      }
      else
      {
        /* return 0, Invalid input */
        res = 0;
        break;
      }
    }
    /* Over 10 digit decimal --invalid */
    if (i >= 11)
    {
      res = 0;
    }
  }

  return res;
}

unsigned int random(unsigned int seed,unsigned int maxnum,unsigned int minnum)
{
	unsigned int value;
	
  srand(seed);
	value = rand();
  //value = value % (maxnum + 1 - minnum)+ minnum;
	
  return value;
}

