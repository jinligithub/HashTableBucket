#ifndef _CharHTB__H_
#define _CharHTB__H_

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<malloc.h>

typedef char* HTBKeyType;
typedef char* HTBValueType;
typedef  struct CHashNode
{
	struct CHashNode* _next;
	HTBKeyType _key;
	HTBValueType _value;
}CHashNode;
typedef struct CHTBucket
{
	CHashNode **_table;
	int _len;
	int _size;
}CHTBucket;

void CHTBInit(CHTBucket *htb, int len);//��ʼ��
void CHTBDestory(CHTBucket *htb);//����
CHashNode* CBuyNode(HTBKeyType key, HTBValueType value);//����һ���µĽڵ�
void HTBCheckCapacity(CHTBucket *htb);//���ݣ��������µĽڵ㣬��֮ǰ�Ľڵ��ù������ڶ�Ӧ��λ��
int HTBInsert(CHTBucket *htb, HTBKeyType key, HTBValueType value);//��ϣͰ�Ĳ���
CHashNode* CHTBFind(CHTBucket *htb, HTBKeyType key);//��ϣʹ�Ĳ���
int CHTBRemove(CHTBucket *htb, HTBKeyType key);//��ϣ���ɾ��
int CHTBSize(CHTBucket *htb);//���ϣͰ�Ĵ�С
int CHTBEmpty(CHTBucket *htb);//�жϹ�ϣͰ�Ƿ�Ϊ��
void CHTBPrint(CHTBucket *htb);//��ӡ��ϣͰ


#endif