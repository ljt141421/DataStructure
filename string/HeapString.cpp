#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<string.h>

typedef struct HString
{
	char *ch;
	int  length;
}HString;

//函数申明
void initString(HString *s);
void printString(HString *s);

//赋值串
void strAssign(HString *s,char *str);
void strCopy(HString *s,HString *t);
bool strEmpty(HString *s);
int strCompare(HString *s,HString *t);
int strLength(HString *s);
void strConnect(HString *t,HString *s1,HString *s2);
//截子串
void subString(HString *s,HString *sub,int pos,int len);
void strInsert(HString *s,int pos,HString *t);
void strDelete(HString *s,int pos,int len);
void strClear(HString *s);
////////模式匹配,目前暂不实现
int strIndex(HString *s,HString *t,int pos);
void strReplace(HString *s,HString *t,HString *v);

void main()
{
	HString s;
	initString(&s);
	strAssign(&s,"abcefgh");

	strDelete(&s,1,3);

	printString(&s);
	//printf("%d \n",strCompare(&s,&t));
}
void initString(HString *s)
{
	s->ch=NULL;
	s->length=0;
}
void printString(HString *s)
{
	for(int i=0;i<s->length;++i)
	{
		printf("%c",s->ch[i]);
	}
	printf("\n");
}

//赋值串
void strAssign(HString *s,char *str)
{
	int len=strlen(str);
	if(s->ch != NULL)
	{
		free(s->ch);
	}
	s->ch=(char*)malloc(sizeof(char)*len);
	assert(s->ch != NULL);
	for(int i=0;i<len;++i)
	{
		s->ch[i]=str[i];
	}
	s->length=len;
	
}
//拷贝串
void strCopy(HString *s,HString *t)
{
	int len=strLength(t);
	if(s->ch != NULL)
	{
		free(s->ch);
	}
	s->ch=(char*)malloc(sizeof(char)*len);
	assert(s->ch != NULL);
	for(int i=0;i<len;++i)
	{
		s->ch[i]=t->ch[i];
	}
	s->length=len;
}
//判空
bool strEmpty(HString *s)
{
	return s->length == 0;
}
//比较字符串大小
int strCompare(HString *s,HString *t)
{
	if(s->length == 0 && t->length == 0)
	{
		return 0;
	}
	int result=0;
	int i=0;
	int j=0;
	while(i<s->length && j<t->length)
	{
		if(s->ch[i]>t->ch[j])
		{
			return 1;
		}
		else if(s->ch[i]<t->ch[j])
		{
			return -1;
		}
		else
		{
			i++;
			j++;
		}
	}
	if(i<s->length)
	{
		result=1;
	}
	if(j<t->length)
	{
		result=-1;
	}
	return result;
}
int strLength(HString *s)
{
	return s->length;
}
//连接两个字符串
void strConnect(HString *t,HString *s1,HString *s2)
{
	if(t->ch != NULL)
	{
		free(t->ch);
	}
	int len1=s1->length;
	int len2=s2->length;
	t->ch=(char*)malloc(sizeof(char)*(len1+len2));
	assert(t->ch != NULL);
	for(int i=0;i<len1;++i)
	{
		t->ch[i]=s1->ch[i];
	}
	for(int j=0;j<len2;++j)
	{
		t->ch[i+j]=s2->ch[j];
	}
	t->length=len1+len2;

}
//截子串
void subString(HString *s,HString *sub,int pos,int len)
{
	if(pos <0 || pos > s->length || len < 0 || len > s->length-pos)
	{
		printf("截取子串非法\n");
		return;
	}
	if(sub->ch != NULL)
	{
		free(sub->ch);
	}
	sub->ch=(char*)malloc(sizeof(char)*len);
	assert(sub->ch != NULL);
	
	int j=pos;
	for(int i=0;i<len;++i)
	{
		sub->ch[i]=s->ch[j+i];
	}
	sub->length=len;
}
//插入子串
void strInsert(HString *s,int pos,HString *t)
{
	if(t->length == 0)
	{
		printf("所插入串不合法\n");
		return;
	}
	if(pos < 0 || pos>s->length)
	{
		printf("插入位置不合法\n");
		return;
	}
	char *ch=(char*)realloc(s->ch,sizeof(char)*(s->length+t->length));
	assert(ch != NULL);
	s->ch=ch;
	
	for(int i=s->length-1;i>=pos;--i)
	{
		s->ch[i+t->length]=s->ch[i];
	}
	int j=pos;
	for(i=0;i<t->length;++i)
	{
		s->ch[j+i]=t->ch[i];
	}
	s->length +=t->length;

}
//删除串
void strDelete(HString *s,int pos,int len)
{
	if(pos <0 || pos>s->length)
	{
		printf("删除位置不合法\n");
		return;
	}
	if(len <0 || len>s->length)
	{
		printf("删除长度不合法\n");
		return;
	}
	int j=pos;
	for(int i=0;i<len;++i)
	{
		s->ch[j+i]=s->ch[j+i+len];
	}
	s->length -=len;
}
//清除当前串的内容
void strClear(HString *s)
{
	s->length=0;
	if(s->ch != NULL)
	{
		free(s->ch);
	}
	s->ch=NULL;
}
////////模式匹配,目前暂不实现
int strIndex(HString *s,HString *t,int pos)
{
	return 0;
}
void strReplace(HString *s,HString *t,HString *v){}
