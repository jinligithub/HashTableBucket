#include"CharHTB.h"
void CHTBInit(CHTBucket *htb, int len)//��ʼ��
{
	assert(htb);
	htb->_len = len;//�ʼ��ĳ���
	htb->_size = 0;
	htb->_table = (CHashNode**)malloc(sizeof(CHashNode*)*htb->_len);//���ٱ��Ŀռ�
	memset(htb->_table, 0, sizeof(CHashNode*)*htb->_len);//�ѱ��ʼ��Ϊ��
}
void CHTBDestory(CHTBucket *htb)//����
{
	//1.assert
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		CHashNode *cur = htb->_table[i];
		//2.�ж�����ڵ��Ƿ�Ϊ�գ���Ϊ�����ٽڵ�
		while (cur)
		{
			CHashNode *next = cur->_next;
			free(cur);
			cur = next;
		}
		htb->_table[i] = NULL;//��ֹҰָ��ĳ���
	}
	//3.���ٱ�
	free(htb->_table);
	htb->_size = htb->_len = 0;
	printf("�������ٳɹ�\n");
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

CHashNode* CBuyNode(HTBKeyType key, HTBValueType value)//����һ���µĽڵ�
{
	CHashNode* node = (CHashNode*)malloc(sizeof(CHashNode));//����һ���ڵ��С�Ŀռ�
	node->_key = key;
	node->_value = value;
	node->_next = NULL;
	return node;
}
int StrFunc(const char* str)//�����ַ����ĳ���
{
	int hash = 0;
	while (*str)
	{
		hash++;
		str++;
	}
	return hash;
}
int CHashFunc(HTBKeyType key, int len)//�����ַ����Ĳ���λ��
{
	return StrFunc(key) % len;
}
void CHTBCheckCapacity(CHTBucket *htb)//���ݣ��������µĽڵ㣬��֮ǰ�Ľڵ��ù������ڶ�Ӧ��λ��
{
	assert(htb);
	if (htb->_len == htb->_size)
	{
		CHTBucket newhtb;
		newhtb._len = GetNextPrime(htb->_len);//�±�ı�����������ȷ��
		CHTBInit(&newhtb,newhtb._len);
		int i = 0;
		for (i = 0; i < htb->_len; i++)
		{
			CHashNode*cur = htb->_table[i];
			while (cur)
			{
				CHashNode*next = cur->_next;
				int index = CHashFunc(cur->_key, newhtb._len);//�������ݲ������λ��
				//ͷ�巨��������
				cur->_next = newhtb._table[index];
				newhtb._table[index] = cur;
				cur = cur->_next;
			}
		}
		CHTBDestory(htb);//���پɱ�
		htb->_table = newhtb._table;//���±�����ݸ��ɱ�
		htb->_len = newhtb._len;
		htb->_size = newhtb._size;
	}
}
int CHTBInsert(CHTBucket *htb, HTBKeyType key, HTBValueType value)//��ϣͰ�Ĳ���
{
	assert(htb);
	CHTBCheckCapacity(htb);
	int index = CHashFunc(key, htb->_len);
	CHashNode*cur = htb->_table[index];
	CHashNode*NewNode = NULL;
	while (cur)//�жϹ�ϣͰ���Ƿ���key,������ڷ���-1
	{
		if (cur->_key == key)
			return -1;
		else
			cur=cur->_next;
	}
	//ͷ�巨������ڵ�
	NewNode = CBuyNode(key,value);
	NewNode->_next = htb->_table[index];//NewNode->next����htb->table[index]��Ӧ������htb->table[index]Ϊͷ���
	htb->_table[index] = NewNode;//��NewNode��htb->_table[index]��ͷ���
	htb->_size++;
	return 0;

}
CHashNode* CHTBFind(CHTBucket *htb, HTBKeyType key)//��ϣʹ�Ĳ���
{
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		CHashNode*cur = htb->_table[i];
		while (cur)
		{
			if (cur->_key == key)
				return cur;//�ҵ���
			else
				cur = cur->_next;
		}
	}
	return NULL;//û�ҵ�
}
int CHTBRemove(CHTBucket *htb, HTBKeyType key)//��ϣ���ɾ��
{
	assert(htb);
	int index = CHashFunc(key, htb->_len);
	CHashNode*cur = htb->_table[index];
	CHashNode*prev = NULL;
	//ֱ��ɾ����
	while (cur)
	{
		if (cur->_key == key)
		{
			//Ѱ��key
			if (prev == NULL)//keyΪ��һ���ڵ�
				htb->_table[index] = cur->_next;
			else//���ǵ�һ���ڵ�
				prev->_next = cur->_next;
			//ɾ��Key
			free(cur);
			htb->_size--;
			return 0;
		}
		prev = cur;//��prevָ��cur��ǰһ���ڵ�
		cur = cur->_next;
	}
}
int CHTBSize(CHTBucket *htb)//���ϣͰ�Ĵ�С
{
	assert(htb);
	return htb->_size;
}
int CHTBEmpty(CHTBucket *htb)//�жϹ�ϣͰ�Ƿ�Ϊ��
{
	assert(htb);
	return htb->_size ? 0 : 1;//��Ϊ0���ǿ�Ϊ1
}
void CHTBPrint(CHTBucket *htb)//��ӡ��ϣͰ
{
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		CHashNode* cur = htb->_table[i];//����һ���ڵ�ȥ������ϣͰ
		printf("Table");
		while (cur)//cur��Ϊ�ս�ѭ����ӡ
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
	CHTBInsert(&htb, "char", "�ַ�");
	CHTBInsert(&htb, "int", "�ַ�");
	CHTBInsert(&htb, "short", "�ַ�");
	CHTBInsert(&htb, "long", "�ַ�");
	CHTBInsert(&htb, "size", "�ַ�");
	CHTBInsert(&htb, "how", "�ַ�");
	CHTBInsert(&htb, "double", "�ַ�");
	CHTBInsert(&htb, "zhang ", "�ַ�");
	CHTBInsert(&htb, "lihongli ", "�ַ�");
	CHTBInsert(&htb, "renjing", "�ַ�");
	CHTBPrint(&htb);
	cur = CHTBFind(&htb, "how");
	printf("%s:%s\n", cur->_key, cur->_value);
	cur = CHTBRemove(&htb, "renjing");
	CHTBPrint(&htb);

	/*CHTBInsert(&htb, "zhangcong ", "�ַ�");
	CHTBInsert(&htb, "zhouchanglin ", "�ַ�");*/
	//CHTBInsert(&htb, "pengge ", "�ַ�");

	CHTBPrint(&htb);
	CHTBDestory(&htb);
}