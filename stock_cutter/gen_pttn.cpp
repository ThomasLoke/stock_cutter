#include "stdafx.h"

#include "gen_pttn.h"
using namespace std;

gen_pttn::gen_pttn(void) {
	M = 0;
	L = 0;
}

gen_pttn::gen_pttn(const gen_pttn& inst) {
	Sb = inst.Sb;
	S = inst.S;
	Lv = inst.Lv;
	M = inst.M;
}

gen_pttn::~gen_pttn(void) {}

void gen_pttn::run(void) {
	int Lmin = Lv[M - 1]; // Assume that the minimum L_j value is the last, i.e. L_j is sorted in descending order
	// Initialize sets
	pttn P0;
	P0.a.assign(M, 0);
	P0.c = L;
	Sb.assign(1, P0);
	S.clear();
	// Iterate through j values
	int j, x, Sbmax, ajmax, v;
	pttn P;
	for (j = 0; j < M; ++j) {
		Sbmax = Sb.size(); // For code clarity - intermediate variable should not be necessary
		for (x = 0; x < Sbmax; ++x) {
			// Compute a_j^{max}(P)
			P = Sb[x];
			ajmax = P.c / Lv[j]; // Integer division should take care of flooring
			if (j != M - 1 && ajmax > 1) {
				// Construct non-maximal patterns and add to Sb
				for (v = 1; v < ajmax; ++v) {
					// Modify base P
					P.a[j] = v;
					P.c -= Lv[j];
					// Add modified P to Sb
					Sb.push_back(P);
				}
			}
			// Construct final new pattern and then classify it accordingly
			if (ajmax > 0) {
				if (j != M - 1) {
					P.a[j] = ajmax;
					P.c -= Lv[j];
					if (P.c < Lmin) {
						S.push_back(P);
					}
					else {
						Sb.push_back(P);
					}
				}
				else {
					P = Sb[x];
					P.a[j] = ajmax;
					P.c -= ajmax * Lv[j];
					S.push_back(P);
				}
			}
		}
	}
}