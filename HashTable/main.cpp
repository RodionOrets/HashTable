#include "HashTable.h"

#include <fstream>

template <typename key_t, typename value_t>
HashTable<key_t, value_t>* getFromFile(const std::string& fileName);

int main()
{
	HashTable<std::string, double>* map
		= getFromFile<std::string, double>("Input.txt");


	std::getchar();
	return 0;
}

template <typename key_t, typename value_t>
HashTable<key_t, value_t>* getFromFile(const std::string& fileName)
{
	HashTable<key_t, value_t>* _map
		= new HashTable<key_t, value_t>(25);

	std::ifstream input(fileName);
	if (!input.is_open()) {
		std::cerr << "Error opening file: " << fileName << std::endl;
		return _map;
	}

	key_t _key;
	value_t _value;

	while (input.good()) {
		input >> _key >> _value;
		_map->insertItem( _key, _value );
	}

	_map->printTable();
	_map->removeItem(_key);
	_map->printTable();

	input.close();
	return _map;
}