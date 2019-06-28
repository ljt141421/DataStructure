#include<stdio.h>
#include<string.h>

#define MAX_STR_LEN 20
#define u_char unsigned char

//最后一位存储'\0'，代表串的结束
typedef u_char SString[MAX_STR_LEN+1];

//函数申明
void initString(SString s);
void printString(SString s);

//赋值串
void strAssign(SString s,char *str);
void strCopy(SString s,SString t);
bool strEmpty(SString s);
int strCompare(SString s,SString t);
int strLength(SString s);
void strConnect(SString t,SString s1,SString s2);
//截子串
void subString(SString s,SString sub,int pos,int len);
void strInsert(SString s,int pos,SString t);
void strDelete(SString s,int pos,int len);
void strClear(SString s);
////////模式匹配,目前暂不实现
int strIndex(SString s,SString t,int pos);
void strReplace(SString s,SString t,SString v);

void main()
{
	SString s;
	initString(s);
	strAssign(s,"ababcababcbaab");

	SString t;
	initString(t);
	strAssign(t,"abc");

	SString v;
	initString(v);
	strAssign(v,"xy");

	strReplace(s,t,v);

	printString(s);

	//int index=strIndex(s,t,0);
	//printf("%d\n",index);
}
void initString(SString s)
{
	s[0]='\0';//0位设置为'\0'，代表当前为空串
}
void printString(SString s)
{
	printf("%s\n",s);
}

//赋值串
void strAssign(SString s,char *str)
{
	int len=strlen(str);
	for(int i=0;i<len;++i)
	{
		s[i]=str[i];
	}
	s[len]='\0';
}
//拷贝串
void strCopy(SString s,SString t)
{
	int len=strLength(t);
	for(int i=0;i<len;++i)
	{
		s[i]=t[i];
	}
	s[len]='\0';
}
//判空
bool strEmpty(SString s)
{
	return s[0]=='\0';
}
//比较字符串大小
int strCompare(SString s,SString t)
{
	int result=0;
	while(*s != '\0' || *t != '\0')
	{
		result=*s-*t;
		if(result != 0)
		{
			break;
		}
		s++;
		t++;
	}
	if(result>0)
	{
		result=1;
	}
	else if(result <0)
	{
		result = -1;
	}
	return result;
}
int strLength(SString s)
{
	int len=0;
	while(*s != '\0')
	{
		len++;
		s++;
	}
	return len;
}
//连接两个字符串
void strConnect(SString t,SString s1,SString s2)
{
	int s1_len=strLength(s1);
	int s2_len=strLength(s2);
	
	//大串长度足够
	if((s1_len+s2_len)<=MAX_STR_LEN)
	{
		for(int i=0;i<s1_len;++i)
		{
			t[i]=s1[i];
		}
		for(int j=0;j<s2_len;++j)
		{
			t[i+j]=s2[j];
		}
		t[s1_len+s2_len]='\0';
	}//大串长度不能容纳两个串
	else if(s1_len<MAX_STR_LEN)
	{
		for(int i=0;i<s1_len;++i)
		{
			t[i]=s1[i];
		}
		for(int j=0;j<MAX_STR_LEN - s1_len;++j)
		{
			t[i+j]=s2[j];
		}
		t[MAX_STR_LEN]='\0';
	}//大串长度只够容纳一个串
	else
	{
		for(int i=0;i<s1_len;++i)
		{
			t[i]=s1[i];
		}
		t[MAX_STR_LEN]='\0';
	}
	

}
//截子串
void subString(SString s,SString sub,int pos,int len)
{
	int s_len=strLength(s);
	if(pos <0 || pos >= s_len || len < 0 || len > s_len )
	{
		printf("截取子串非法\n");
		return;
	}
	int j=pos;
	for(int i=0;i<len;++i)
	{
		sub[i]=s[pos+i];
	}
	sub[len]='\0';
}
//插入子串
void strInsert(SString s,int pos,SString t)
{
	int s_len=strLength(s);
	int t_len=strLength(t);
	//空间足够
	if((s_len + t_len)<=MAX_STR_LEN)
	{
		for(int i=s_len-1;i>=pos;--i)
		{
			s[i+t_len]=s[i];
		}
		int j=pos;
		for(i=0;i<t_len;++i)
		{
			s[j+i]=t[i];
		}
		s[s_len+t_len]='\0';
	}//空间不足以容乃两个串
	else if(s_len < MAX_STR_LEN)
	{
		t_len=MAX_STR_LEN-s_len;
		for(int i=s_len-1;i>=pos;--i)
		{
			s[i+t_len]=s[i];
		}
		int j=pos;
		for(i=0;i<t_len;++i)
		{
			s[j+i]=t[i];
		}
		s[s_len+t_len]='\0';
	}
}
//删除串
void strDelete(SString s,int pos,int len)
{
	int s_len=strLength(s);
	for(int i=pos;i<s_len;++i)
	{
		s[i]=s[i+len];
	}
	s[s_len-len]='\0';

}
//清除当前串的内容
void strClear(SString s)
{
	s[0]='\0';
}
////////模式匹配,目前暂不实现
int strIndex(SString s,SString t,int pos)
{
	int i=pos;
	int j=0;
	while(s[i] != '\0' && t[j] != '\0')
	{
		if(s[i]==t[j])
		{
			i++;
			j++;
		}
		else
		{
			i=i-j+1;
			j=0;
		}
	}
	if(t[j]=='\0')
		return i-j;
	return -1;
}
void strReplace(SString s,SString t,SString v)
{
	int s_len=strLength(s);
	int t_len=strLength(t);
	int v_len=strLength(v);
	int index=-1;
	int pos=0;
	while(pos<s_len)
	{
		index=strIndex(s,t,pos);
		printf("%d\n",index);
		if(index == -1)
		{
			printf("没有对应的模式串，无法替换\n");
			return;
		}
		strDelete(s,index,t_len);
		strInsert(s,index,v);

		pos=index+v_len;
	}
}
