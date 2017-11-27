#include <iostream>
using namespace std;
#include <string>
#include <stdlib.h>
#include <time.h>

double g_min_fit, g_delta_fit;
double g_pcross=0.8,
	g_pmut=0.05;

#include "global_var.h"
#include "struct.h"
#include "init.h"
#include "operateFun.h"

Population oldPop,
		selectedPop,
		crossedPop,
		*old_pop_ptr,
		*selected_pop_ptr,
		*crossed_pop_ptr;

void main() {
	cout << "this is a test console";
	srand((unsigned int)time(0));

	int shiyan = 0,gen = 0;
	for (shiyan = 0; shiyan < Shiyan_NUM; shiyan++) {
		
		init(&oldPop);
		calIndiviualFitness(&oldPop);
		for (int i = 0; i < P_NUM; i++) {
			oldPop.rankno[i] = 0;
			selectedPop.rankno[i] = 0;
			crossedPop.rankno[i] = 0;
		}

		for (gen = 0; gen < GEN_MAX; gen++) {
			// 初始化种群
			applyNonDominatedSorting(&oldPop); // 此时的oldPop均是已经计算过适应度的
			executeSelectOpt(&oldPop, &selectedPop);
			crossSelectedPop(&selectedPop, &crossedPop);
			mutateCrossedPop(&crossedPop);
			calIndiviualFitness(&crossedPop);
			applyEliteStrategy(&oldPop, &crossedPop); // 将oldPop与crossedPop合并，选出新一代种群赋值给oldpPop
		}
	}
}