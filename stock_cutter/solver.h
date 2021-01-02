#pragma once
#include "stdafx.h"

#include "pttn.h"
#include "CoinPackedMatrix.hpp"
#include "OsiClp/OsiClpSolverInterface.hpp"

// Object wrapping the MIP solver
class solver {
public:
	// Data:
	std::vector<double> objective; // Objective coefficients, which is c_j
	std::vector<double> col_lb; // Lower bound for x_i, which is 0
	std::vector<double> col_ub; // Upper bound for x_i, which is sb->getInfinity()
	std::vector<double> row_lb; // Lower bound for \sum_{i=1}^{N} a_{ij} x_i, which is q_j
	std::vector<double> row_ub; // Upper bound for \sum_{i=1}^{N} a_{ij} x_i, which is sb->getInfinity()
	int N, M; // Number of columns (patterns) and rows (orders) respectively
	CoinPackedMatrix *matrix; // Constraint matrix, which is a_{ji} for i = 1,...,N and j = 1,...,M
							  // Note: Indexing system of this object also starts from (0,0)
	OsiClpSolverInterface *sb; // CLP solver
	// Functions:
	// Empty constructor:
	solver(void);
	// Copy constructor:
	solver(const solver& inst);
	// Constructor with dimensions:
	solver(int Nv, int Mv);
	// Destructor:
	~solver(void);
	// reset: Resets the COIN variables by deallocating (if necessary) and reallocating
	void reset(void);
	// run: Loads the problem to the solver interface and then solves the problem using CBC methods, returning the result in xv
	void run(std::vector<int>& xv, double& objv);
	// setdim: Sets the dimensions of all the data
	void setdim(int Nv, int Mv);
	// setvars: Sets the costs c_i, the quantities q_j and the constraint matrix a_{ji}
	void setvars(const std::vector<pttn>& S, const std::vector<int>& qv, bool uniform_weight = false);
	// zeromat: Zeroes matrix elements
	void zeromat(void);
};