#include"HashTableBucket.h"
void HTBInit(HTBucket *htb,int len)//��ʼ��
{
	assert(htb);
	htb->_len = len;//�ʼ��ĳ���
	htb->_size = 0;
	htb->_table = (HashNode**)malloc(sizeof(HashNode*)*htb->_len);//���ٱ��Ŀռ�
	memset(htb->_table, 0, sizeof(HashNode*)*htb->_len);//�ѱ��ʼ��Ϊ��
}
void HTBDestory(HTBucket *htb)//����
{
	//1.assert
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		HashNode*cur = htb->_table[i];
		//2.�ж�����ڵ��Ƿ�Ϊ�գ���Ϊ�����ٽڵ�
		while (cur)
		{
			HashNode *next = cur->next;
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
void HTBCheckCapacity(HTBucket *htb)//�������µĽڵ㣬��֮ǰ�Ľڵ��ù������ڸǷ���λ��
{
	assert(htb);
	int i = 0;
	if (htb->_len = htb->_size)
	{
		HTBucket Newhtb ;//����һ���±�
		Newhtb._len = 2 * htb->_len;//�ı��ĳ���
		HTBInit(&Newhtb, Newhtb._len);
		for (i = 0; i < htb->_len; i++)
		{
			HashNode*cur = htb->_table[i];
			while (cur)
			{
				HashNode*next = cur->next;//�ȱ���cur����һ��ֵ
				int index = HashBFunc(cur->_key, Newhtb._len);//�����µĲ���λ��
				//����ڵ�
				cur->next = Newhtb._table[index];
				Newhtb._table[index] = cur;
				cur = next;//��cur ����һ��ֵ��cur
			}
			htb->_table[i] = NULL;
		}
		HTBDestory(htb);//���پɱ�
		htb->_table = Newhtb._table;//���±�Ķ������ɱ�
		htb->_len = Newhtb._len;
		htb->_size = Newhtb._size;
	}
}
//��ϣͰ�Ĳ���,ѡ��ͷ�壬��Ϊͷ����ҵ�Ч�ʸ�
int HTBInsert(HTBucket *htb, HTBKeyType key, HTBValueType value)
{
	//1.assert
	assert(htb);
	//2.����keyҪ�����λ��
	int index = 0;
	index = HashBFunc(key, htb->_len);//����key�Ĳ���λ��
	HashNode*cur = NULL;
	HashNode*NewNode = NULL;
	cur = htb->_table[index];
	while (cur)
	{
		if (cur->_key == key)//�ҵ�key,����key�Ѿ�����
		{
			return -1;
		}
		cur = cur->next;//��������ѭ��Ѱ��key
	}
	//3.����key
	NewNode = BuyNode(key, value);
	NewNode->next = htb->_table[index];//��NewNode->nextָ��htb->_table[index]����һ���ڵ��ֵ
	htb->_table[index] = NewNode;//��htb->table[index]��ֵ����NewNode
	htb->_size++;
	return 0;
}
HashNode* HTBFind(HTBucket *htb, HTBKeyType key)//��ϣʹ�Ĳ���
{
	//1.assert
	assert(htb);
	//2.����key
	int index = 0;
	index = HashBFunc(key, htb->_len);
	HashNode*cur = NULL;
	cur = htb->_table[index];
	while (cur)
	{
		if (cur->_key == key)//key���ڣ�����key
		{
			return cur;
		}
		cur = cur->next;//����ѭ������key
	}
	return NULL;//û�ҵ�
}
int HTBRemove(HTBucket *htb, HTBKeyType key)//��ϣ���ɾ��
{
	assert(htb);
	HashNode*cur = NULL;
	HashNode*prev = NULL;
	int index = HashBFunc(key, htb->_len);
	cur = htb->_table[index];
	//prev = htb->_table[index--];
	while (cur)
	{
		if (cur->_key == key)//ֱ��ɾ����
		{
			if (prev == NULL)//keyΪ��һ���ڵ�
				htb->_table[index] = cur->next;
			else//key���ǵ�һ���ڵ�
				prev->next = cur->next;
			free(cur);
			htb->_size--;
			return 0;
		}
		prev = cur;
		cur = cur->next;
	}
	return -1;//ɾ���ڵ�ʧ��

}
int HTBSize(HTBucket *htb)//���ϣͰ�Ĵ�С
{
	assert(htb);
	return htb->_size;
}
int HTBEmpty(HTBucket *htb)//�жϹ�ϣͰ�Ƿ�Ϊ��
{
	assert(htb);
	return htb->_size == 0 ? 0 : 1;//�շ���0���ǿշ���1
}
void HTBPrint(HTBucket *htb)//��ӡ��ϣͰ
{
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		HashNode*cur = NULL;
		cur = htb->_table[i];
		printf("table��%d��",i);
		while (cur)
		{
		    printf("-->%d :%d", cur->_key, cur->_value);//�ǿ�
			cur = cur->next;
		}
			printf("-->NULL\n");//��
	}
	printf("\n");
}
void TestHTBucket()
{
	HTBucket htb;//����һ���ṹ��Ĺ�ϣͰ���������Ϊָ�����;ͱ��뿪���ڴ�
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
		printf("��Ϊ��\n");
	else
		printf("Ϊ��\n");
	pos = HTBSize(&htb);
	if (pos != 0)
		printf("%d\n", pos);
	pos = HTBRemove(&htb, 5);

	if (pos == 0)
		printf("ɾ���ɹ�\n");
	else
		printf("�����ڸ�Ԫ��\n");
	HTBPrint(&htb);

	cur = HTBFind(&htb, 5);
	if (cur != 0)
		printf("�ҵ���%d: %d\n", cur->_key, cur->_value);
	else
		printf("Ϊ��\n");
	HTBDestory(&htb);
}