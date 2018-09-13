#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int HTKeyType;
typedef int HTValueType;

enum State
{
	EMPTY,//��״̬
	EXITS,//����Ԫ��
	DELETE,//��λ��ԭ����Ԫ�ر�ɾ��
};

typedef struct HashData
{
	enum State _state;//��λ��״̬
	HTKeyType _key;//
	HTValueType _value;//
}HashData;//�����ϣ���д�ŵ����ݽṹ

typedef struct HashTable
{
	HashData* _tables;
	int _len;//��ϣ��
	int _size;//��Ч���ݸ���
}HashTable;//�����ϣ��ṹ

void HTInit(HashTable* ht, int len);//��ʼ����ϣ��
void HTDestroy(HashTable* ht);//���ٹ�ϣ��
int HTInsert(HashTable* ht, HTKeyType key, HTValueType value);//������Ԫ��
int HTRemove(HashTable* ht, HTKeyType key);//ɾ��Ԫ��
HashData* HTFind(HashTable* ht, HTKeyType key);//����
int HTSize(HashTable* ht);//��С
int HTEmpty(HashTable* ht);//�п�

void TestHashTable();
