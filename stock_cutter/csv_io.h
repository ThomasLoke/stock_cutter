#pragma once
#include "stdafx.h"

#include "pttn.h"

// Sorting function (DESCENDING order):
template <typename T> std::vector<int> get_order(const std::vector<T>& v);

// Parsing functions:
std::string merge_cells(const std::vector<std::string>& cells);
std::vector<std::string> split_line(const std::string& line);

// Object handling i/o for csv files and proper sorting
class csv_io {
public:
	// Data:
	std::string fname;
	std::ifstream ifile;
	std::ofstream ofile;
	int L, M;
	std::vector<int> Lv, qv;
	// Functions:
	// Empty constructor:
	csv_io(void);
	// Copy constructor - really don't need one + its a bit twisted due to lack of = operators...
	// Destructor:
	~csv_io(void);
	// getproblem: Finds the next problem and loads it
	bool getproblem(void);
	// reset: Resets variables
	void reset(void);
	// setfilename: Sets the root filename for the input/output csv files and attempts to open them
	void setfilename(const std::string& root);
	// sort: Sorts Lv, qv in descending order
	void sort(void);
	// writesolution: Writes the solution to the output csv file
	void writesolution(const std::vector<int>& xv, const std::vector<pttn>& S);
};