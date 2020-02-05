#include<iostream>
#include<map>
using namespace std;

struct LRUNode      //定义双向链表节点
{   
	int m_key;             //标签值 
	int m_value;               //实际值
	LRUNode* pPre, * pNext;
	LRUNode(int k, int v) :m_key(k), m_value(v), pPre(NULL), pNext(NULL) {}     //结构体内定义构造函数
};

class LRUCache
{
public:
	//构造函数初始化大小
	LRUCache(int size)
	{
		m_capacity = size;
		pHead = NULL;
		pTail = NULL;
	}

	//释放内存
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

	//移除节点，但是并没有删除节点释放内存
	void Remove(LRUNode* node)
	{
		//如果删除的是头结点
		if (node->pPre == NULL)
		{
			pHead = node->pNext;
			pHead->pPre = NULL;
		}
		//如果删除的是尾节点
		if (node->pNext == NULL)
		{
			pTail = node->pPre;
			pTail->pNext = NULL;
		}
		//删除的就是中间节点
		else
		{
			//**搞清节点的下一位和上一位
			node->pPre->pNext = node->pNext;
			node->pNext->pPre = node->pPre;
		}
	}
	//永远把使用的数据放在头部位置
	void setHead(LRUNode* node)
	{
		node->pNext = pHead;          //先把节点连接到头部，然后再移动头结点指针
		node->pPre = NULL;            //节点的前驱指针先指向空
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
	
	//先判断该值是否在链表中，如果不在就将该值插入
	void Set(int key, int value)
	{
		map<int, LRUNode* >::iterator it = mp.find(key);
		if (it != mp.end())             //证明节点在链表中，需将节点移至队列头部
		{
			LRUNode* node = it->second;                 //修改节点信息
			node->m_value = value;                
			Remove(node);
			setHead(node);
		}
		else
		{
			LRUNode* node = new LRUNode(key, value);
			if (mp.size() >= m_capacity)
			{
				//删除尾部节点
				map<int, LRUNode*>::iterator it = mp.find(pTail->m_key);
				Remove(pTail);              //删除节点
				delete it->second;
				mp.erase(it);
			}
			setHead(node);     //将其位置移到头部
			mp[key] = node;
		}
	}

	int Get(int key)
	{
		map<int, LRUNode*>::iterator it = mp.find(key);
		if (it != mp.end())
		{
			LRUNode* Node = it->second;           //取到的是key值
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
	int m_capacity;              //缓存容量
	LRUNode* pHead, *pTail;
	map<int, LRUNode*> mp;
};

int main03()
{
	//LRUCache lruCache(3);
	LRUCache* lruCache = new LRUCache(3);      //调用构造函数
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