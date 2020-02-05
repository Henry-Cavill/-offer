#include<iostream>
#include<map>
using namespace std;

struct LRUNode      //����˫������ڵ�
{   
	int m_key;             //��ǩֵ 
	int m_value;               //ʵ��ֵ
	LRUNode* pPre, * pNext;
	LRUNode(int k, int v) :m_key(k), m_value(v), pPre(NULL), pNext(NULL) {}     //�ṹ���ڶ��幹�캯��
};

class LRUCache
{
public:
	//���캯����ʼ����С
	LRUCache(int size)
	{
		m_capacity = size;
		pHead = NULL;
		pTail = NULL;
	}

	//�ͷ��ڴ�
	~LRUCache()
	{
		map<int, LRUNode*>::iterator it = mp.begin();
		for (; it != mp.end();)
		{
			delete it->second;
			it->second = NULL;
			mp.erase(it++);
		}
		pHead = NULL;
		delete pHead;
		pTail = NULL;
		delete pTail;
	}

	//�Ƴ��ڵ㣬���ǲ�û��ɾ���ڵ��ͷ��ڴ�
	void Remove(LRUNode* node)
	{
		//���ɾ������ͷ���
		if (node->pPre == NULL)
		{
			pHead = node->pNext;
			pHead->pPre = NULL;
		}
		//���ɾ������β�ڵ�
		if (node->pNext == NULL)
		{
			pTail = node->pPre;
			pTail->pNext = NULL;
		}
		//ɾ���ľ����м�ڵ�
		else
		{
			//**����ڵ����һλ����һλ
			node->pPre->pNext = node->pNext;
			node->pNext->pPre = node->pPre;
		}
	}
	//��Զ��ʹ�õ����ݷ���ͷ��λ��
	void setHead(LRUNode* node)
	{
		node->pNext = pHead;          //�Ȱѽڵ����ӵ�ͷ����Ȼ�����ƶ�ͷ���ָ��
		node->pPre = NULL;            //�ڵ��ǰ��ָ����ָ���
		if (pHead==NULL)          //**
		{
			pHead = node;
		}
		else
		{
			pHead->pPre = node;
			pHead = node;
		}
		if (pTail==NULL)
		{
			pTail = pHead;
		}
	}
	
	//���жϸ�ֵ�Ƿ��������У�������ھͽ���ֵ����
	void Set(int key, int value)
	{
		map<int, LRUNode* >::iterator it = mp.find(key);
		if (it != mp.end())             //֤���ڵ��������У��轫�ڵ���������ͷ��
		{
			LRUNode* node = it->second;                 //�޸Ľڵ���Ϣ
			node->m_value = value;                
			Remove(node);
			setHead(node);
		}
		else
		{
			LRUNode* node = new LRUNode(key, value);
			if (mp.size() >= m_capacity)
			{
				//ɾ��β���ڵ�
				map<int, LRUNode*>::iterator it = mp.find(pTail->m_key);
				Remove(pTail);              //ɾ���ڵ�
				delete it->second;
				mp.erase(it);
			}
			setHead(node);     //����λ���Ƶ�ͷ��
			mp[key] = node;
		}
	}

	int Get(int key)
	{
		map<int, LRUNode*>::iterator it = mp.find(key);
		if (it != mp.end())
		{
			LRUNode* Node = it->second;           //ȡ������keyֵ
			Remove(Node);
			setHead(Node);
			return Node->m_value;
		}
		else
		{
			return -1;
		}
	}

	int GetSize()
	{
		return mp.size();
	}

private:
	int m_capacity;              //��������
	LRUNode* pHead, *pTail;
	map<int, LRUNode*> mp;
};

int main03()
{
	//LRUCache lruCache(3);
	LRUCache* lruCache = new LRUCache(3);      //���ù��캯��
	lruCache->Set(1, 1);
	lruCache->Set(2, 3);
	cout << lruCache->GetSize() << endl;
	lruCache->Set(3, 5);
	cout << lruCache->GetSize() << endl;
	cout << lruCache->Get(1) << endl;
	lruCache->Set(6, 3);
	cout << lruCache->GetSize() << endl;
	cout << lruCache->Get(3) << endl;
	cout << lruCache->Get(1) << endl;
	cout << lruCache->Get(2) << endl;

	return 0;

}