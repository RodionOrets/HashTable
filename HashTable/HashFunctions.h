#ifndef FUNCTIONS
#define FUNCTIONS

#include <string>

namespace HFunctions
{
	template <typename key_t>
	inline unsigned int DivHash(const key_t& _key, int _tSize) {
		return _key % _tSize;
	}

	template <typename key_t>
	inline unsigned int DivHashStep(const key_t& _key, int _tSize) {
		return _key % (_tSize - 2) + 1;
	}

	inline unsigned int DivHash(const std::string _key, int _tSize) {
		unsigned int res = 0;
		for (int i = 0; i < _key.size(); i++) {
			res += (int)_key[i];
		}
		return res % _tSize;
	}

	inline unsigned int DivHashStep(const std::string& _key, int _tSize) {
		unsigned int res = 0;
		for (int i = 0; i < _key.size(); i++) {
			res += (int)_key[i];
		}
		return res % (_tSize - 2) + 1;
	}
}


#endif