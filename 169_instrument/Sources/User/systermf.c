
#include "typedef.h"


char *my_strcat(char *str1, char *str2)
{
	char *pt = str1;
	while(*str1!='\0') str1++;
	while(*str2!='\0') *str1++ = *str2++;
	*str1 = '\0';
	return pt;
}


unsigned int   my_atoi(char   *s)
{
	char   *p   =   s;
	char   c;
	int   i   =   0;
	while(c=*p++)
	{
		if(c>='0'   &&   c<='9')
		{
			i   =   i*10   +   (c-'0');
		}
		else
			return   -1;                     //Invalid   string
	}
	return   i;
}

unsigned long   my_atol(char   *s)
{
	char   *p   =   s;
	char   c;
	long   i   =   0;
	while(c=*p++)
	{
		if(c>='0'   &&   c<='9')
		{
			i   =   i*10   +   (c-'0');
		}
		else
			return   -1;                     //Invalid   string
	}
	return   i;
}

void my_ltoa( unsigned long i,char *buf, int base)
{
	char *s;
#define LEN	25
	int rem;
	char rev[LEN+1];

	if (i == 0)
		s = "0";
	else
	{
		rev[LEN] = 0;
		s = &rev[LEN];
		while (i)
		{
			rem = i % base;
			if (rem < 10)
				*--s = rem + '0';
			else if (base == 16)
				*--s = "ABCDEF"[rem - 10];
			i /= base;
		}
	}
	strcpy(buf, s);
}


unsigned char* my_strstr(unsigned char *s1, unsigned char* s2)
{
	int n;
	if (*s2)
	{
		while (*s1)
		{
			for (n=0; *(s1 + n) == *(s2 + n); n++)
			{
				if (!*(s2 + n + 1))
					return (unsigned char *)s1;
			}
			s1++;
		}
		return 0;
	}
	else
		return (unsigned char *)s1;
}


int my_strlen(unsigned char* str)
{
	if(str==0)
		return 0;
	if(*str!='\0')
		return 1+my_strlen(++str);
	else
		return 0;

}

void strupr(unsigned char *str)
{
	int  k;

	for (k=0; k<strlen(str)&&k<30; str++)
		*str = tolower(*str);

}


void bubble_sort_better(int a[],int n)//n为数组a的元素个数
{
	//最多进行N-1轮比较
	int i,j;
	int temp;
	for(i=0; i<n-1; i++)
	{
		//每一轮比较前n-1-i个，即已排序好的最后i个不用比较
		for(j=0; j<n-1-i; j++)
		{
			if(a[j] > a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1]=temp;
			}
		}
	}
}

void pirce_buff(unsigned int N,unsigned char *output)
{
	unsigned char buff[10];
	memset(output,0,10);
	my_ltoa(N/100,buff,10);
	strcat(output,buff);
	strcat(output,".");
	my_ltoa(N%100/10,buff,10);
	strcat(output,buff);
	my_ltoa(N%10,buff,10);
	strcat(output,buff);
}

void Hex2String(unsigned char hex,unsigned char *p)
{
	if(CHECKBIT(hex, B0))	{	p[7]='1';}
	else					{	p[7]='0';	}
	if(CHECKBIT(hex, B1))	{	p[6]='1';	}
	else				  { p[6]='0';}
	if(CHECKBIT(hex, B2))	{	p[5]='1';	}
	else					{	p[5]='0';}
	if(CHECKBIT(hex, B3))	{	p[4]='1';	}
	else					{	p[4]='0';	}
	if(CHECKBIT(hex, B4))	{	p[3]='1';	}
	else					{	p[3]='0';	}
	if(CHECKBIT(hex, B5))	{	p[2]='1';	}
	else					{	p[2]='0';	}
	if(CHECKBIT(hex, B6))	{	p[1]='1';	}
	else					{	p[1]='0';	}
	if(CHECKBIT(hex, B7))	{	p[0]='1';	}
	else					{	p[0]='0';	}
}


