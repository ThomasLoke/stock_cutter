#include "stdafx.h"

#include "solver.h"
#include "CoinPackedVector.hpp"
#include "CbcModel.hpp"
/*#include "CbcCompareDepth.hpp"
#include "CbcCompareObjective.hpp"
#include "CbcCompareEstimate.hpp"*/
using namespace std;

solver::solver(void) {
	N = 0;
	M = 0;
	matrix = nullptr;
	sb = nullptr;
	reset();
}

solver::solver(const solver& inst) {
	objective = inst.objective;
	col_lb = inst.col_lb;
	col_ub = inst.col_ub;
	row_lb = inst.row_lb;
	row_ub = inst.row_ub;
	N = inst.N;
	M = inst.M;
	reset();
	*matrix = *inst.matrix;
	*sb = *inst.sb;
}

solver::solver(int Nv, int Mv) {
	setdim(Nv, Mv);
}

solver::~solver(void) {
	if (matrix != nullptr) {
		delete matrix;
	}
	if (sb != nullptr) {
		delete sb;
	}
}

void solver::reset(void) {
	if (matrix != nullptr) {
		delete matrix;
	}
	matrix = new CoinPackedMatrix(false, 0, 0);
	if (sb != nullptr) {
		delete sb;
	}
	sb = new OsiClpSolverInterface;
}

void solver::run(std::vector<int>& xv, double& objv) {
	int i;
	// Loads the problem into the solver
	sb->loadProblem(*matrix, col_lb.data(), col_ub.data(), objective.data(), row_lb.data(), row_ub.data());
	for (i = 0; i < N; ++i) {
		sb->setInteger(i);
	}
	// Shoves solver into the CBC model
	CbcModel model(*sb);
	// Run CBC model
	/*CbcCompareObjective ccd;
	model.setNodeComparison(ccd);*/
	model.branchAndBound();
	bool optimal = model.isProvenOptimal();
	const double *val = model.getColSolution();
	xv.assign(N, 0);
	for (i = 0; i < N; ++i) {
		xv[i] = (int)val[i];
	}
	objv = model.getObjValue();
}

void solver::setdim(int Nv, int Mv) {
	reset();
	N = Nv;
	M = Mv;
	objective.assign(N, 0.0);
	col_lb.assign(N, 0.0);
	col_ub.assign(N, sb->getInfinity());
	row_lb.assign(M, 0.0);
	row_ub.assign(M, sb->getInfinity());
	matrix->setDimensions(M, N);
}

void solver::setvars(const vector<pttn>& S, const vector<int>& qv, bool uniform_weight) {
	int i, j;
	for (j = 0; j < M; ++j) {
		row_lb[j] = (double)qv[j];
		for (i = 0; i < N; ++i) {
			matrix->modifyCoefficient(j, i, (double)S[i].a[j]);
		}
	}
	for (i = 0; i < N; ++i) {
		if (uniform_weight) {
			objective[i] = 1.0;
		}
		else {
			objective[i] = (double)S[i].c;
		}
	}
}

void solver::zeromat(void) {
	int i, j;
	for (j = 0; j < M; ++j) {
		for (i = 0; i < N; ++i) {
			if (matrix->getCoefficient(j, i) != 0.0) {
				matrix->modifyCoefficient(j, i, 0.0);
			}
		}
	}
}