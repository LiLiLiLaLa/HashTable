#include "HashTable.h"

void HTInit(HashTable* ht, int len)
{
	int i = 0;
	assert(ht != NULL);
	assert(len > 0);
	ht->_tables = (HashData*)malloc(sizeof(HashData)*len);//����len���ȵĿռ�
	ht->_size = 0;
	ht->_len = len;
	for (i = 0; i < len; i++)
	{
		ht->_tables[i]._state = EMPTY;//����ϣ����ÿ��λ����Ϊ��
	}
}//��ʼ��

void HTDestroy(HashTable* ht)
{
	assert(ht);
	free(ht->_tables);
	ht->_len = 0;
	ht->_size = 0;
}//����

size_t HashFunc(HashTable* ht, HTKeyType key)
{
	assert(ht);
	return key % (ht->_len);
}//��������

int HTInsert(HashTable* ht, HTKeyType key, HTValueType value);//�������������������Ҫǰ�ú�������
void CheckCapacity(HashTable *ht)
{
	if (ht->_size * 10 / ht->_len > 7)//�涨��������Ϊ0.7
	{
		HashTable newht;
		int i = 0;
		HTInit(&newht, ht->_len * 2);//��������
		for (i = 0; i < ht->_len; i++)
		{
			if (ht->_tables[i]._state == EXITS)
			{
				HTInsert(&newht, ht->_tables[i]._key, ht->_tables[i]._value);
			}//��ԭ�����ݼ��������±�
		}
		HTDestroy(ht);//����ԭ������
		ht->_tables = newht._tables;
		ht->_len = newht._len;
		ht->_size = newht._size;//���±����ݸ���ԭ��
	}
}

int HTInsert(HashTable* ht, HTKeyType key, HTValueType value)
{
	size_t index = HashFunc(ht, key);//��������
	assert(ht);
	CheckCapacity(ht);
	while (ht->_tables[index]._state == EXITS)
	{
		if (ht->_tables[index]._key == key)//�Ѿ����ڸ�Ԫ��
		{
			return 0;
		}
		else
		{
			return index;
		}
	}
	ht->_tables[index]._state = EXITS;//������λ��״̬�ı�
	ht->_tables[index]._key = key;
	ht->_tables[index]._value = value;
	ht->_size++;
	return 1;
}

int HTRemove(HashTable* ht, HTKeyType key)
{
	size_t index = HashFunc(ht, key);//��������
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
		if (ht->_tables[index]._key == key)//����
		{
			return &(ht->_tables[index]);
		}
		else
		{
			index++;//��ϣ��ͻ������
		}
	}
	return NULL;//û�ҵ�
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