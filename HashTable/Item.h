#pragma once
#ifndef ITEM_H
#define ITEM_H

template <typename key_t, typename value_t>
class Item
{
public:

	Item() 
		: m_key(0), m_value(0), next(nullptr) { }

	Item(const key_t& _key, const value_t& _val):
		m_key(_key), m_value(_val), next(nullptr) { }

	~Item() 
	{
		delete next;
	}

	key_t   getKey()   { return m_key;   }
	value_t getValue() { return m_value; }

	Item<key_t, value_t>* getNext() { return next; }

	void setNext(Item<key_t, value_t>* _next) {
		next = _next;
	}

private:

	key_t m_key;
	value_t m_value;

	Item <key_t, value_t>* next;
};

#endif // ITEM_H


