#include "stdafx.h"

#include "pttn.h"
using namespace std;

pttn::pttn(void) {
	c = 0;
}

pttn::pttn(const pttn& inst) {
	a = inst.a;
	c = inst.c;
}

pttn::~pttn(void) {}

void pttn::print(bool s) {
	int i;
	printf("{ ");
	for (i = 0; i < a.size()-1; ++i) {
		printf("%i, ", a[i]);
	}
	printf("%i }", a[i]);
	if (s) {
		printf(" with cost %i", c);
	}
}
