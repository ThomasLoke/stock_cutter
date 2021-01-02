#pragma once
#include "stdafx.h"

// Object representing a pattern
class pttn {
public:
	// Data:
	std::vector<int> a; // Quantity of each order
	int c; // Cost associated with the pattern
	// Functions:
	// Empty constructor:
	pttn(void);
	// Copy constructor:
	pttn(const pttn& inst);
	// Destructor:
	~pttn(void);
	// print: Prints object info
	void print(bool s = false);
};