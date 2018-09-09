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

void CHTBInit(CHTBucket *htb, int len);//初始化
void CHTBDestory(CHTBucket *htb);//销毁
CHashNode* CBuyNode(HTBKeyType key, HTBValueType value);//创建一个新的节点
void HTBCheckCapacity(CHTBucket *htb);//扩容，不开辟新的节点，把之前的节点拿过来放在对应的位置
int HTBInsert(CHTBucket *htb, HTBKeyType key, HTBValueType value);//哈希桶的插入
CHashNode* CHTBFind(CHTBucket *htb, HTBKeyType key);//哈希痛的查找
int CHTBRemove(CHTBucket *htb, HTBKeyType key);//哈希表的删除
int CHTBSize(CHTBucket *htb);//求哈希桶的大小
int CHTBEmpty(CHTBucket *htb);//判断哈希桶是否为空
void CHTBPrint(CHTBucket *htb);//打印哈希桶


#endif