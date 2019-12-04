#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define P 7
#define NULL_DATA -1
#define BUCKET_NODE_SIZE 3
/*
	������һ���������������Hash��
	Hash��Ĵ洢��λ��ΪͰ��ÿ��Ͱ�ܷ�3��������
	��һ��Ͱ��Ҫ�ŵ�Ԫ�س���3��ʱ��
	��Ҫ���µ�Ԫ�ش�������Ͱ�У�
	ÿ�����ͰҲ�ܷ�3��Ԫ�أ�
	������Ͱʹ������������
	��Hash��Ļ�Ͱ��ĿΪ����P��
	Hash���hash������Pȡģ��

	���ڼ���hash_table�Ѿ���ʼ�����ˣ�
	insert_new_element()����Ŀ���ǰ�һ���µ�ֵ����hash_table�У�
	Ԫ�ز���ɹ�ʱ����������0�����򷵻�-1����ɺ�����
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
		//��Ͱ��ÿ�����ݶ���ʼ��ΪNULL_DATA
		for(int j=0;j<BUCKET_NODE_SIZE;++j)
		{
			hash_table[i].data[j]=NULL_DATA;
		}
		//��ÿ��Ͱ��next����ʼ��ΪNULL
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
	//��indexͰ���ҵ�һ����λ�ò���
	for(int i=0;i<BUCKET_NODE_SIZE;++i)
	{
		if(hash_table[index].data[i]==NULL_DATA)
		{
			hash_table[index].data[i]=x;
			return 0;
		}
	}
	
	//indexͰ��û�п�λ�ã�����nextͰ��Ѱ�ҿ�λ�ò���
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
	//���indexͰ��nextͰΪ�գ��ʹ���һ��nextͰ������Ԫ�ز��뵽nextͰ�ĵ�һ��λ��
	bucket_node *s=(bucket_node*)malloc(sizeof(bucket_node));
	assert(s != NULL);
	for(i=0;i<BUCKET_NODE_SIZE;++i)
	{
		s->data[i]=NULL_DATA;
	}
	s->next=NULL;

	s->data[0]=x;
	p->next=s;//��indexͰ����nextͰ
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
//��ϣ������������ģȡ��ķ�ʽ����
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

	//����ͷ��ķ�ʽ
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
	//����ǵ�һ���ڵ�
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
