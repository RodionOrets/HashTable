#pragma once
#ifndef LINKEDLIST
#define LINKEDLIST

#include "Item.h"

#include <iostream>
#include <fstream>
#include <string>

template <typename key_t, typename value_t>
class LinkedList
{
public:

	LinkedList()
		: begin(nullptr), end(nullptr) {}


	void operator = (LinkedList& _other)
	{
		begin = end = nullptr;

		if ( !_other.empty() ) 
		{
			Item<key_t, value_t> *other_iter = _other.begin;
			while (other_iter) {
				pushBack(other_iter->getKey(),
					     other_iter->getValue());
			}
			other_iter 
				= other_iter->getNext();
		}
	}

	void pushBack(const key_t& _key, const value_t& _value) 
	{
		Item <key_t, value_t>* entry
			= new Item<key_t, value_t>(_key, _value);

		if (!begin) {
			begin = end = entry;
		} else {
			end->setNext(entry);
			end = entry;
		}
	}

	bool removeItem(const key_t& _key)
	{
		Item<key_t, value_t>* iter = begin;
		while (iter)
		{
			if (iter->getKey() == _key) {
				Item<key_t, value_t>* iter_next = iter->getNext();
				delete iter;
				iter = iter_next;
				begin = end = nullptr;
				return true;
			}
			iter = iter->getNext();
		}
		return false;
	}

	value_t searchItem(const key_t& _key)
	{
		Item<key_t, value_t>* iter = begin;
		while (iter) 
		{
			if (iter->getKey() == _key) {
				return iter->getValue();
			}
			iter = iter->getNext();
		}
		return -1;
	}

	void printList()
	{
		Item<key_t, value_t>* iter = begin;
		while (iter) {
			std::cout << iter->getKey() << " " << iter->getValue() << std::endl;
			iter = iter->getNext();
		}
	}

	void printList(const std::string& fileName)
	{
		std::ofstream output(fileName, std::ios_base::trunc);
		if (!output.is_open()) {
			std::cerr << "Error opening file: " << fileName << std::endl;
			return;
		}

		Item<key_t, value_t>* iter = begin;
		while (iter) {
			output << iter->getKey() << " " << iter->getValue() << std::endl;
			iter = iter->getNext();
		}

		output.close();
	}

	bool empty() const { return begin == nullptr; }

	void clearList()
	{
		while (begin)
		{
			end = begin->getNext(); 
			delete begin;           
			begin = end;            
		}
	}

	~LinkedList()
	{
		clearList();
	}

	Item<key_t, value_t>* Begin() { return begin; }

private:

	Item<key_t, value_t>* begin;
	Item<key_t, value_t>* end;
};

#endif // LINKEDLIST

