#include"HashTableBucket.h"
void HTBInit(HTBucket *htb,int len)//初始化
{
	assert(htb);
	htb->_len = len;//最开始表的长度
	htb->_size = 0;
	htb->_table = (HashNode**)malloc(sizeof(HashNode*)*htb->_len);//开辟表长的空间
	memset(htb->_table, 0, sizeof(HashNode*)*htb->_len);//把表初始化为零
}
void HTBDestory(HTBucket *htb)//销毁
{
	//1.assert
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		HashNode*cur = htb->_table[i];
		//2.判断这个节点是否为空，不为空销毁节点
		while (cur)
		{
			HashNode *next = cur->next;
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
int HashBFunc(HTBKeyType key, int len)
{
	return key%len;
}
HashNode*cur = NULL;
HashNode* BuyNode(HTBKeyType key, HTBValueType value)
{
	HashNode* node = (HashNode*)malloc(sizeof(HashNode));
	node->_key = key;
	node->_value = value;
	node->next = NULL;
	return node;
}
void HTBCheckCapacity(HTBucket *htb)//不开辟新的节点，把之前的节点拿过来放在盖房的位置
{
	assert(htb);
	int i = 0;
	if (htb->_len = htb->_size)
	{
		HTBucket Newhtb ;//建立一个新表
		Newhtb._len = 2 * htb->_len;//改变表的长度
		HTBInit(&Newhtb, Newhtb._len);
		for (i = 0; i < htb->_len; i++)
		{
			HashNode*cur = htb->_table[i];
			while (cur)
			{
				HashNode*next = cur->next;//先保存cur的下一个值
				int index = HashBFunc(cur->_key, Newhtb._len);//查找新的插入位置
				//插入节点
				cur->next = Newhtb._table[index];
				Newhtb._table[index] = cur;
				cur = next;//把cur 的下一个值给cur
			}
			htb->_table[i] = NULL;
		}
		HTBDestory(htb);//销毁旧表
		htb->_table = Newhtb._table;//把新表的东西给旧表
		htb->_len = Newhtb._len;
		htb->_size = Newhtb._size;
	}
}
//哈希桶的插入,选择头插，因为头插查找的效率高
int HTBInsert(HTBucket *htb, HTBKeyType key, HTBValueType value)
{
	//1.assert
	assert(htb);
	//2.查找key要插入的位置
	int index = 0;
	index = HashBFunc(key, htb->_len);//查找key的插入位置
	HashNode*cur = NULL;
	HashNode*NewNode = NULL;
	cur = htb->_table[index];
	while (cur)
	{
		if (cur->_key == key)//找到key,并且key已经存在
		{
			return -1;
		}
		cur = cur->next;//继续向下循环寻找key
	}
	//3.插入key
	NewNode = BuyNode(key, value);
	NewNode->next = htb->_table[index];//让NewNode->next指向htb->_table[index]的下一个节点的值
	htb->_table[index] = NewNode;//让htb->table[index]的值等于NewNode
	htb->_size++;
	return 0;
}
HashNode* HTBFind(HTBucket *htb, HTBKeyType key)//哈希痛的查找
{
	//1.assert
	assert(htb);
	//2.查找key
	int index = 0;
	index = HashBFunc(key, htb->_len);
	HashNode*cur = NULL;
	cur = htb->_table[index];
	while (cur)
	{
		if (cur->_key == key)//key存在，返回key
		{
			return cur;
		}
		cur = cur->next;//继续循环查找key
	}
	return NULL;//没找到
}
int HTBRemove(HTBucket *htb, HTBKeyType key)//哈希表的删除
{
	assert(htb);
	HashNode*cur = NULL;
	HashNode*prev = NULL;
	int index = HashBFunc(key, htb->_len);
	cur = htb->_table[index];
	//prev = htb->_table[index--];
	while (cur)
	{
		if (cur->_key == key)//直接删除法
		{
			if (prev == NULL)//key为第一个节点
				htb->_table[index] = cur->next;
			else//key不是第一个节点
				prev->next = cur->next;
			free(cur);
			htb->_size--;
			return 0;
		}
		prev = cur;
		cur = cur->next;
	}
	return -1;//删除节点失败

}
int HTBSize(HTBucket *htb)//求哈希桶的大小
{
	assert(htb);
	return htb->_size;
}
int HTBEmpty(HTBucket *htb)//判断哈希桶是否为空
{
	assert(htb);
	return htb->_size == 0 ? 0 : 1;//空返回0，非空返回1
}
void HTBPrint(HTBucket *htb)//打印哈希桶
{
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		HashNode*cur = NULL;
		cur = htb->_table[i];
		printf("table【%d】",i);
		while (cur)
		{
		    printf("-->%d :%d", cur->_key, cur->_value);//非空
			cur = cur->next;
		}
			printf("-->NULL\n");//空
	}
	printf("\n");
}
void TestHTBucket()
{
	HTBucket htb;//建立一个结构体的哈希桶，如果建立为指针类型就必须开辟内存
	int pos = 0;
	HashNode* cur = NULL;
	HTBInit(&htb, 10);
	HTBInsert(&htb, 1, 10);
	HTBInsert(&htb, 2, 12);
	HTBInsert(&htb, 3, 13);
	HTBInsert(&htb, 5, 14);
	HTBInsert(&htb, 14, 15);
	HTBInsert(&htb, 66, 16);
	HTBInsert(&htb, 12, 17);
	HTBInsert(&htb, 55, 18);
	HTBPrint(&htb);


	pos = HTBEmpty(&htb);
	if (pos != 0)
		printf("不为空\n");
	else
		printf("为空\n");
	pos = HTBSize(&htb);
	if (pos != 0)
		printf("%d\n", pos);
	pos = HTBRemove(&htb, 5);

	if (pos == 0)
		printf("删除成功\n");
	else
		printf("不存在该元素\n");
	HTBPrint(&htb);

	cur = HTBFind(&htb, 5);
	if (cur != 0)
		printf("找到了%d: %d\n", cur->_key, cur->_value);
	else
		printf("为空\n");
	HTBDestory(&htb);
}