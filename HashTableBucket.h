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
	struct HashNode* next;//指向下一个节点的指针
	HTBKeyType _key;
	HTBValueType _value;
}HashNode;

typedef struct HTBucket
{
	HashNode**_table;//哈希表
	int _len;//哈希表的长度
	int _size;//存入哈希表的数据个数
}HTBucket;

void HTBInit(HTBucket *htb,int len);//初始化
void HTBDestory(HTBucket *htb);//销毁
HashNode* BuyNode(HTBKeyType key, HTBValueType value);//创建一个新的节点
int HTBInsert(HTBucket *htb, HTBKeyType key, HTBValueType value);//哈希桶的插入
HashNode* HTBFind(HTBucket *htb, HTBKeyType key);//哈希痛的查找
int HTBRemove(HTBucket *htb, HTBKeyType key);//哈希表的删除
int HTBSize(HTBucket *htb);//求哈希桶的大小
int HTBEmpty(HTBucket *htb);//判断哈希桶是否为空
void HTBPrint(HTBucket *htb);//打印哈希桶
void TestHTBucket();//测试

#endif