#pragma once
#ifndef HASHTABLE
#define HASHTABLE

#include "LinkedList.h"
#include "HashFunctions.h"


template <typename key_t, typename value_t>
class HashTable 
{
public:

	HashTable() : size(50)
	{
		m_map = new LinkedList<key_t, value_t>[size];
		for (int i = 0; i < size; i++) {
			m_map[i] = LinkedList<key_t, value_t>();
		}
	}
	
	HashTable(const int _tSize) : size(_tSize)
	{
		m_map = new LinkedList<key_t, value_t>[size];
		for (int i = 0; i < size; i++) {
			m_map[i] = LinkedList<key_t, value_t>();
		}
	}

	void insertItem(const key_t& _key, const value_t& _value)
	{
		const unsigned int hashIndex = emptyBucket(_key);
		m_map[hashIndex].pushBack(_key, _value);
	}

	void insertList(LinkedList<key_t, value_t>& _list)
	{
		Item<key_t, value_t>* _iter = _list.Begin();
		while (_iter) 
		{
			insertItem( _iter->getKey(), _iter->getValue());
			_iter = _iter->getNext();
		}
	}

	bool removeItem(const key_t& _key)
	{
		const unsigned int hashIndex = equalBucket(_key);
		if (hashIndex == -1) 
		{
			return false;
		}
		else 
		{
			return m_map[hashIndex].removeItem(_key);
		}
	}

	value_t searchItem(const key_t& _key)
	{
		const unsigned int hashIndex = equalBucket(_key);
		if (hashIndex == -1) 
		{
			return -1;
		} else 
		{
			return m_map[hashIndex].searchItem(_key);
		}
	}

	void clearTable()
	{
		for (int i = 0; i < size; i++) 
		{
			m_map[i].clearList();
		}
	}

	void printTable()
	{
		for (int i = 0; i < size; i++) 
		{
			m_map[i].printList();
		}
	}

	~HashTable()
	{
		clearTable();
	}

private:

	int emptyBucket(const key_t& _key) 
	{
		int hashIndex = HFunctions::DivHash(_key, size);
		const int step = HFunctions::DivHashStep(_key, size);

		if (m_map[hashIndex].empty()) 
		{
			return hashIndex;
		} 
		else 
		{
			for (int i = 0; i < size; i++) {
				hashIndex += step;
				hashIndex = hashIndex % size;

				if (m_map[hashIndex].empty()) 
				{
					return hashIndex;
				}
			}
		}

		resizeTable();           // in case of filled table
		return emptyBucket(_key); // resizing and searching for empty bucket in resized table
	}

	int equalBucket(const key_t& _key) 
	{
		int hashIndex = HFunctions::DivHash(_key, size);
		const int step = HFunctions::DivHashStep(_key, size);

		if (m_map[hashIndex].searchItem(_key) != -1)
		{
			return hashIndex;
		}
		else
		{
			for (int i = 0; i < size; i++) {
				hashIndex += step;
				hashIndex = hashIndex % size;

				if (m_map[hashIndex].searchItem(_key) != -1) 
				{
					return hashIndex;
				}
			}
		}

		return -1;
	}

	void resizeTable()
	{
		LinkedList<key_t, value_t>* t_map 
			= new LinkedList<key_t, value_t>[size];

		for (int i = 0; i < size; i++) 
		{
			t_map[i] = m_map[i];
		}

		delete[] m_map;
		size = size * 2;
		m_map = new LinkedList<key_t, value_t>[size];

		for (int i = 0; i < size / 2; i++) 
		{
			insertList( t_map[i] );
		}

		delete[] t_map;
	}


	unsigned int size;
	LinkedList<key_t, value_t>* m_map;

};

#endif // HASHTABLE

