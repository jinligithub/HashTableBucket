#include"CharHTB.h"
void CHTBInit(CHTBucket *htb, int len)//初始化
{
	assert(htb);
	htb->_len = len;//最开始表的长度
	htb->_size = 0;
	htb->_table = (CHashNode**)malloc(sizeof(CHashNode*)*htb->_len);//开辟表长的空间
	memset(htb->_table, 0, sizeof(CHashNode*)*htb->_len);//把表初始化为零
}
void CHTBDestory(CHTBucket *htb)//销毁
{
	//1.assert
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		CHashNode *cur = htb->_table[i];
		//2.判断这个节点是否为空，不为空销毁节点
		while (cur)
		{
			CHashNode *next = cur->_next;
			free(cur);
			cur = next;
		}
		htb->_table[i] = NULL;//防止野指针的出现
	}
	//3.销毁表
	free(htb->_table);
	htb->_size = htb->_len = 0;
	printf("链表销毁成功\n");
}
unsigned long int GetNextPrime(int value)
{
	int i = 0;
	static const unsigned long _PrimeList[28] =
	{
		53ul, 97ul, 193ul, 389ul, 769ul,
		1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
		49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
		1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
		50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};
	for (i = 0; i < 28; i++)
	{
		if (_PrimeList[i]>value)
		{
			return _PrimeList[i];
		}
	}
	return _PrimeList[27];
}

CHashNode* CBuyNode(HTBKeyType key, HTBValueType value)//创建一个新的节点
{
	CHashNode* node = (CHashNode*)malloc(sizeof(CHashNode));//开辟一个节点大小的空间
	node->_key = key;
	node->_value = value;
	node->_next = NULL;
	return node;
}
int StrFunc(const char* str)//计算字符串的长度
{
	int hash = 0;
	while (*str)
	{
		hash++;
		str++;
	}
	return hash;
}
int CHashFunc(HTBKeyType key, int len)//计算字符串的插入位置
{
	return StrFunc(key) % len;
}
void CHTBCheckCapacity(CHTBucket *htb)//扩容，不开辟新的节点，把之前的节点拿过来放在对应的位置
{
	assert(htb);
	if (htb->_len == htb->_size)
	{
		CHTBucket newhtb;
		newhtb._len = GetNextPrime(htb->_len);//新表的表长根据素数表确定
		CHTBInit(&newhtb,newhtb._len);
		int i = 0;
		for (i = 0; i < htb->_len; i++)
		{
			CHashNode*cur = htb->_table[i];
			while (cur)
			{
				CHashNode*next = cur->_next;
				int index = CHashFunc(cur->_key, newhtb._len);//查找数据插入的新位置
				//头插法插入数据
				cur->_next = newhtb._table[index];
				newhtb._table[index] = cur;
				cur = cur->_next;
			}
		}
		CHTBDestory(htb);//销毁旧表
		htb->_table = newhtb._table;//把新表的内容给旧表
		htb->_len = newhtb._len;
		htb->_size = newhtb._size;
	}
}
int CHTBInsert(CHTBucket *htb, HTBKeyType key, HTBValueType value)//哈希桶的插入
{
	assert(htb);
	CHTBCheckCapacity(htb);
	int index = CHashFunc(key, htb->_len);
	CHashNode*cur = htb->_table[index];
	CHashNode*NewNode = NULL;
	while (cur)//判断哈希桶中是否有key,如果存在返回-1
	{
		if (cur->_key == key)
			return -1;
		else
			cur=cur->_next;
	}
	//头插法，插入节点
	NewNode = CBuyNode(key,value);
	NewNode->_next = htb->_table[index];//NewNode->next保存htb->table[index]对应的链表，htb->table[index]为头结点
	htb->_table[index] = NewNode;//让NewNode做htb->_table[index]的头结点
	htb->_size++;
	return 0;

}
CHashNode* CHTBFind(CHTBucket *htb, HTBKeyType key)//哈希痛的查找
{
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		CHashNode*cur = htb->_table[i];
		while (cur)
		{
			if (cur->_key == key)
				return cur;//找到了
			else
				cur = cur->_next;
		}
	}
	return NULL;//没找到
}
int CHTBRemove(CHTBucket *htb, HTBKeyType key)//哈希表的删除
{
	assert(htb);
	int index = CHashFunc(key, htb->_len);
	CHashNode*cur = htb->_table[index];
	CHashNode*prev = NULL;
	//直接删除法
	while (cur)
	{
		if (cur->_key == key)
		{
			//寻找key
			if (prev == NULL)//key为第一个节点
				htb->_table[index] = cur->_next;
			else//不是第一个节点
				prev->_next = cur->_next;
			//删除Key
			free(cur);
			htb->_size--;
			return 0;
		}
		prev = cur;//让prev指向cur的前一个节点
		cur = cur->_next;
	}
}
int CHTBSize(CHTBucket *htb)//求哈希桶的大小
{
	assert(htb);
	return htb->_size;
}
int CHTBEmpty(CHTBucket *htb)//判断哈希桶是否为空
{
	assert(htb);
	return htb->_size ? 0 : 1;//空为0，非空为1
}
void CHTBPrint(CHTBucket *htb)//打印哈希桶
{
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		CHashNode* cur = htb->_table[i];//创建一个节点去遍历哈希桶
		printf("Table");
		while (cur)//cur不为空进循环打印
		{
			printf("-->%s:%s", cur->_key, cur->_value);
			cur = cur->_next;
		}
		printf("-->NULL\n");
	}
	printf("\n");
}
void TestCHTB()
{
	CHTBucket htb;
	CHTBInit(&htb, 3);
	CHashNode*cur = NULL;
	CHTBInit(&htb, 10);
	CHTBInsert(&htb, "char", "字符");
	CHTBInsert(&htb, "int", "字符");
	CHTBInsert(&htb, "short", "字符");
	CHTBInsert(&htb, "long", "字符");
	CHTBInsert(&htb, "size", "字符");
	CHTBInsert(&htb, "how", "字符");
	CHTBInsert(&htb, "double", "字符");
	CHTBInsert(&htb, "zhang ", "字符");
	CHTBInsert(&htb, "lihongli ", "字符");
	CHTBInsert(&htb, "renjing", "字符");
	CHTBPrint(&htb);
	cur = CHTBFind(&htb, "how");
	printf("%s:%s\n", cur->_key, cur->_value);
	cur = CHTBRemove(&htb, "renjing");
	CHTBPrint(&htb);

	/*CHTBInsert(&htb, "zhangcong ", "字符");
	CHTBInsert(&htb, "zhouchanglin ", "字符");*/
	//CHTBInsert(&htb, "pengge ", "字符");

	CHTBPrint(&htb);
	CHTBDestory(&htb);
}