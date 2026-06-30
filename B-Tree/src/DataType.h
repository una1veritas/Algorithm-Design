/*
 * DataType.h
 *
 *  Created on: 2026/06/17
 *      Author: sin
 */

#ifndef DATATYPE_H_
#define DATATYPE_H_

#include <string>
#include <cstring>

//typedef std::string DataType;
// required operators or functions are supported by class std::string.

struct Str64 {
	char str[65];
	unsigned int length;

	Str64(void) {
		length = 0;
	}

	Str64(const char * cstr) {
		length = strlen(cstr);
		memcpy(str, cstr, length);
	}

	Str64(const Str64 & str64) {
		*this = str64;
	}

	Str64 & operator=(const Str64 & src) {
		memcpy(this->str, src.str, src.length);
		this->length = src.length;
		return *this;
	}

	Str64(const std::string & cppstr) {
		for(length = 0; length < 64 and length < cppstr.length(); ++length) {
			str[length] = cppstr[length];
		}
	}

	bool operator==(const Str64 & another) const {
		if ( length != another.length )
			return false;
		return memcmp(str, another.str, length) == 0;
	}

	operator char*() {
		str[length] = 0;
		return str;
	}

	bool operator<=(const Str64 & another) const {
		unsigned int ix;
		for(ix = 0; ix < length and ix < another.length; ++ix) {
			if ( str[ix] < another.str[ix] )
				return true;
			else if ( str[ix] > another.str[ix] )
				return false;
		}
		if ( length < another.length )
			return true;
		else if ( length > another.length )
			return false;

		// exactly the same string
		return true;
	}
};

typedef Str64 DataType;

#endif /* DATATYPE_H_ */
