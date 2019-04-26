#include "HashTable.h"
//初始化方法
void HTInit(HashTable* ht, int len)
{
	int i = 0;
	
	assert(ht != NULL);
	assert(len > 0);
	ht->_tables = (HashData*)malloc(sizeof(HashData)*len);//开辟len长度的空间
	ht->_size = 0;
	ht->_len = len;
	for (i = 0; i < len; i++)
	{
		ht->_tables[i]._state = EMPTY;//将哈希表中每个位置置为空
	}
}//初始化

void HTDestroy(HashTable* ht)
{
	assert(ht);
	free(ht->_tables);
	ht->_len = 0;
	ht->_size = 0;
}//销毁

size_t HashFunc(HashTable* ht, HTKeyType key)
{
	assert(ht);
	return key % (ht->_len);
}//计算索引

int HTInsert(HashTable* ht, HTKeyType key, HTValueType value);//两个函数互相包含，需要前置函数申明
void CheckCapacity(HashTable *ht)
{
	if (ht->_size * 10 / ht->_len > 7)//规定负载因子为0.7
	{
		HashTable newht;
		int i = 0;
		HTInit(&newht, ht->_len * 2);//给表增长
		for (i = 0; i < ht->_len; i++)
		{
			if (ht->_tables[i]._state == EXITS)
			{
				HTInsert(&newht, ht->_tables[i]._key, ht->_tables[i]._value);
			}//将原表数据计算后插入新表
		}
		HTDestroy(ht);//销毁原表内容
		ht->_tables = newht._tables;
		ht->_len = newht._len;
		ht->_size = newht._size;//将新表内容赋给原表
	}
}

int HTInsert(HashTable* ht, HTKeyType key, HTValueType value)
{
	size_t index = HashFunc(ht, key);//建立索引
	assert(ht);
	CheckCapacity(ht);
	while (ht->_tables[index]._state == EXITS)
	{
		if (ht->_tables[index]._key == key)//已经存在该元素
		{
			return 0;
		}
		else
		{
			return index;
		}
	}
	ht->_tables[index]._state = EXITS;//插入后该位置状态改变
	ht->_tables[index]._key = key;
	ht->_tables[index]._value = value;
	ht->_size++;
	return 1;
}

int HTRemove(HashTable* ht, HTKeyType key)
{
	size_t index = HashFunc(ht, key);//建立索引
	assert(ht);
	if(ht->_tables[index]._state == EXITS)
	{
		ht->_tables[index]._state = DELETE;
		return 1;
	}
	
	else
	{
		return 0;
	}
}

HashData* HTFind(HashTable* ht, HTKeyType key)
{
	size_t index = HashFunc(ht, key);
	while (ht->_tables[index]._state == EXITS)
	{
		if (ht->_tables[index]._key == key)//存在
		{
			return &(ht->_tables[index]);
		}
		else
		{
			index++;//哈希冲突向后查找
		}
	}
	return NULL;//没找到
}

int HTSize(HashTable* ht)
{
	assert(ht);
	return ht->_size;
}

int HTEmpty(HashTable* ht)
{
	assert(ht);
	return ht->_len == 0 ? 0 : 1;
}

void TestHashTable()
{
	HashTable ht;
	HTInit(&ht, 256);
}
