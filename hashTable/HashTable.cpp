#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define P 7
#define NULL_DATA -1
#define BUCKET_NODE_SIZE 3
/*
	现在有一个用来存放整数的Hash表，
	Hash表的存储单位称为桶，每个桶能放3个整数，
	当一个桶中要放的元素超过3个时，
	则要将新的元素存放在溢出桶中，
	每个溢出桶也能放3个元素，
	多个溢出桶使用链表串起来。
	此Hash表的基桶数目为素数P，
	Hash表的hash函数对P取模。

	现在假设hash_table已经初始化好了，
	insert_new_element()函数目的是把一个新得值插入hash_table中，
	元素插入成功时，函数返回0，否则返回-1，完成函数。
 */
struct bucket_node
{
	int data[BUCKET_NODE_SIZE];
	struct bucket_node *next;
};

bucket_node hash_table[P];

void init_bucket_node()
{
	for(int i=0;i<P;i++)
	{
		//将桶中每个数据都初始化为NULL_DATA
		for(int j=0;j<BUCKET_NODE_SIZE;++j)
		{
			hash_table[i].data[j]=NULL_DATA;
		}
		//将每个桶的next都初始化为NULL
		hash_table[i].next=NULL;
	}
}

int hash(int key)
{
	return key%P;
}

int insert_new_element(int x)
{
	int index=hash(x);
	//在index桶里找到一个空位置插入
	for(int i=0;i<BUCKET_NODE_SIZE;++i)
	{
		if(hash_table[index].data[i]==NULL_DATA)
		{
			hash_table[index].data[i]=x;
			return 0;
		}
	}
	
	//index桶里没有空位置，就在next桶里寻找空位置插入
	bucket_node *p=&hash_table[index];
	while(p->next !=NULL)
	{
		p=p->next;
		for(i=0;i<BUCKET_NODE_SIZE;++i)
		{
			if(p->data[i]==NULL_DATA)
			{
				p->data[i]=x;
				return 0;
			}
		}
	}
	//如果index桶的next桶为空，就创建一个next桶，并将元素插入到next桶的第一个位置
	bucket_node *s=(bucket_node*)malloc(sizeof(bucket_node));
	assert(s != NULL);
	for(i=0;i<BUCKET_NODE_SIZE;++i)
	{
		s->data[i]=NULL_DATA;
	}
	s->next=NULL;

	s->data[0]=x;
	p->next=s;//将index桶连接next桶
	return 0;
}

int main()
{
	init_bucket_node();
	int array[] = {15,14,21,87,96,293,35,24,149,19,63,16,103,77,5,153,145,356,51,68,705,453 };
	//int array[] = {1,8,15,22,29,36,43};
	for(int i = 0; i < sizeof(array)/sizeof(int); i++)
	{
		insert_new_element(array[i]);
	}
	return 0;
}




/*
#define ElemType int 
#define P 13 

typedef struct HashNode
{
	ElemType data;
	struct HashNode *link;
}HashNode;

typedef HashNode* HashTable[P];

void initHashTable(HashTable &ht)
{
	for(int i=0;i<P;++i)
	{
		ht[i]=NULL;
	}
}
//哈希函数，采用求模取余的方式计算
int hash(ElemType key)
{
	return key%P;
}

void insertHashTable(HashTable &ht,ElemType x)
{
	int index=hash(x);
	HashNode *s=(HashNode *)malloc(sizeof(HashNode));
	assert(s != NULL);
	s->data=x;

	//采用头插的方式
	s->link=ht[index];
	ht[index]=s;
}

void showHashTable(HashTable &ht)
{
	for(int i=0;i<P;++i)
	{
		printf("%d : ",i);
		HashNode *p=ht[i];
		while(p != NULL)
		{
			printf("%d-->",p->data);
			p=p->link;
		}
		printf("Nul.\n");
	}
}

HashNode* searchHashTable(HashTable &ht,ElemType key)
{
	int index=hash(key);
	HashNode *p=ht[index];
	while(p != NULL && p->data!=key)
		p=p->link;
	return p;
}

bool removeHashTable(HashTable &ht,ElemType key)
{
	HashNode *p=searchHashTable(ht,key);
	if(p == NULL)
		return false;
	int index=hash(key);
	HashNode *q=ht[index];
	//如果是第一个节点
	if(q == p)
	{
		ht[index]=p->link;
		free(p);
		return true;
	}

	while(q->link != p)
		q=q->link;
	q->link=p->link;
	free(p);
	return true;

}

void main()
{
	HashTable ht;
	initHashTable(ht);
	
	ElemType ar[] = {19,14,23,1,68,20,84,27,55,11,10,79};
	int n = sizeof(ar)/sizeof(ElemType);

	for(int i=0;i<P;++i)
	{
		insertHashTable(ht,ar[i]);
	}

	showHashTable(ht);

	ElemType key = 27;
	HashNode *p = searchHashTable(ht, key);
	printf("key=%d\n",p->data);

	removeHashTable(ht, key);
	
	showHashTable(ht);

}
*/
