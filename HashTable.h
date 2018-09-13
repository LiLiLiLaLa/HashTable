#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int HTKeyType;
typedef int HTValueType;

enum State
{
	EMPTY,//空状态
	EXITS,//存在元素
	DELETE,//该位置原本有元素被删除
};

typedef struct HashData
{
	enum State _state;//该位置状态
	HTKeyType _key;//
	HTValueType _value;//
}HashData;//定义哈希表中存放的内容结构

typedef struct HashTable
{
	HashData* _tables;
	int _len;//哈希表长
	int _size;//有效数据个数
}HashTable;//定义哈希表结构

void HTInit(HashTable* ht, int len);//初始化哈希表
void HTDestroy(HashTable* ht);//销毁哈希表
int HTInsert(HashTable* ht, HTKeyType key, HTValueType value);//加入新元素
int HTRemove(HashTable* ht, HTKeyType key);//删除元素
HashData* HTFind(HashTable* ht, HTKeyType key);//查找
int HTSize(HashTable* ht);//大小
int HTEmpty(HashTable* ht);//判空

void TestHashTable();
