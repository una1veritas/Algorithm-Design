/*
 * DataType.h
 *
 *  Created on: 2026/06/17
 *      Author: sin
 */

#ifndef DATATYPE_H_
#define DATATYPE_H_

#include <cstring>
#include <string>

//typedef std::string Data;
// required operators or functions are supported by class std::string.

template <size_t N>
struct PString {
	size_t length;
	char str[N];

	PString() : length(0) {
		//str[0] = '\0';
	}

	PString(const char * s) : length(std::min(strlen(s), N)) {
		strncpy(str, s, length);
	}

	PString(const std::string & s) : length(std::min(s.length(), N)) {
		std::strncpy(str, s.c_str(), length);
	}

	char & operator[](size_t index) {
		if (index >= length) {
			throw std::out_of_range("Index out of range");
		}
		return str[index];
	}

	const char & operator[](size_t index) const {
		if (index >= length) {
			throw std::out_of_range("Index out of range");
		}
		return str[index];
	}

	bool operator==(const PString<N>& other) const {
		return length == other.length and std::strncmp(str, other.str, length) == 0;
	}

	bool operator<=(const PString<N>& other) const {
		if ( *this == other) return true;
		return *this < other;
	}

	bool operator<(const PString<N>& other) const {
		int cmp = std::strncmp(str, other.str, std::min(length, other.length));
		if (cmp < 0) return true;
		if (cmp > 0) return false;
		return length < other.length;
	}

	friend std::ostream & operator<<(std::ostream & out, const PString<N>& pstr) {
		char buffer[N + 1];
		std::strncpy(buffer, pstr.str, pstr.length);
		buffer[pstr.length] = '\0'; // Null-terminate the string
		out << buffer;
		return out;
	}
};

typedef PString<64> Data; // Define Data as a fixed-size string of 32 characters

#endif /* DATATYPE_H_ */
