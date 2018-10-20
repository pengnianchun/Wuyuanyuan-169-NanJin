#ifndef __systermf_h
#define __systermf_h

extern void Hex2String(unsigned char hex,unsigned char *p);
unsigned char *my_strcat(unsigned char *str1, unsigned char *str2);
void my_ltoa( unsigned long i,char *buf, int base);
unsigned char* my_strstr(unsigned char *s1, unsigned char* s2);   
unsigned int   my_atoi(unsigned char   *s);
unsigned long   my_atol(unsigned char   *s);
int my_strlen(unsigned char* str);
void strupr(unsigned char *str);
void bubble_sort_better(int a[],int n);


#endif