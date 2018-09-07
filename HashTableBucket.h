#ifndef _HashTableBucket__H_
#define _HashTableBucket__H_

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<malloc.h>

typedef int HTBKeyType;
typedef int HTBValueType;
typedef struct HashNode
{
	struct HashNode* next;//ָ����һ���ڵ��ָ��
	HTBKeyType _key;
	HTBValueType _value;
}HashNode;

typedef struct HTBucket
{
	HashNode**_table;//��ϣ��
	int _len;//��ϣ��ĳ���
	int _size;//�����ϣ������ݸ���
}HTBucket;

void HTBInit(HTBucket *htb,int len);//��ʼ��
void HTBDestory(HTBucket *htb);//����
HashNode* BuyNode(HTBKeyType key, HTBValueType value);//����һ���µĽڵ�
int HTBInsert(HTBucket *htb, HTBKeyType key, HTBValueType value);//��ϣͰ�Ĳ���
HashNode* HTBFind(HTBucket *htb, HTBKeyType key);//��ϣʹ�Ĳ���
int HTBRemove(HTBucket *htb, HTBKeyType key);//��ϣ���ɾ��
int HTBSize(HTBucket *htb);//���ϣͰ�Ĵ�С
int HTBEmpty(HTBucket *htb);//�жϹ�ϣͰ�Ƿ�Ϊ��
void HTBPrint(HTBucket *htb);//��ӡ��ϣͰ
void TestHTBucket();//����

#endif