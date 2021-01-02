#pragma once
#include "stdafx.h"

#include "pttn.h"

// Object implementing the pattern generation algorithm
class gen_pttn {
public:
	// Data:
	std::vector<pttn> Sb; // Set of non-maximal patterns
	std::vector<pttn> S; // Set of maximal patterns
	std::vector<int> Lv; // List of order lengths, i.e. L_j values
	int M; // Number of types of orders
	int L; // Length of stock material
	// Functions:
	// Empty constructor:
	gen_pttn(void);
	// Copy constructor:
	gen_pttn(const gen_pttn& inst);
	// Destructor:
	~gen_pttn(void);
	// run: Runs the pattern generation algorithm, assuming Lv, M and L have been initialized
	void run(void);
};