#ifndef _OPERATE_FUN_H
#define _OPERATE_FUN_H
/************************************************************************/
/* 根据现有编码，只有当每个环节中每个项目的约束都满足时，编码才是合法的，编码不合法时，使error+1
/************************************************************************/
void calIndiviualFitness(Population *pop_ptr) {
	// 先计算每个项目在每个环节上的适应度，然后在累加即是整个个体的适应度，同时可以判断是否满足限制条件

	for (int indIndex = 0; indIndex < P_NUM; indIndex++) {
		double fitness[F_NUM] = {0};
		pop_ptr->ind[indIndex].error = 0;
		for (int taskIndex = 0; taskIndex < TASK_NUM; taskIndex++) {
			int agentStart = 0,agentEnd = 0;
			for (int process = 0; process < PROCESS_NUM; process++) {
				int agentNum = agentNumInEveryProc[process];
				agentStart = agentEnd;
				agentEnd += agentNum;
				double maxTime = 0, quality = 0, cost = 0;
				for (int agent = agentStart; agent < agentEnd; agent++) {
					if (pop_ptr->ind[indIndex].encode[taskIndex][agent] == 1) {
						if (agentPara[0][agent] > maxTime) {
							maxTime = agentPara[0][agent];
						}
						quality += agentPara[1][agent];
						cost += agentPara[2][agent];
						fitness[1] += 1 - agentPara[1][agent] / normalizeValue[1];
						fitness[2] += agentPara[2][agent] / normalizeValue[2];
					}
				}
				fitness[0] += maxTime / normalizeValue[0];
				if (maxTime > constraint[taskIndex][process][0]){ // 判断是否满足限制条件
					pop_ptr->ind[indIndex].error++;
				}
				if (quality < constraint[taskIndex][process][1]) {
					pop_ptr->ind[indIndex].error++;
				}
				if (cost > constraint[taskIndex][process][2]) {
					pop_ptr->ind[indIndex].error++;
				}
			}
		}
		for (int obj = 0; obj < F_NUM; obj++) {
			pop_ptr->ind[indIndex].fitness[obj] = fitness[obj];
		}
	}
}

void applyNonDominatedSorting(Population *pop_ptr) {

}

void executeSelectOpt(Population *old_pop_ptr, Population *selected_pop_ptr) {

};

void crossSelectedPop(Population *selected_pop_ptr, Population *crossed_pop_ptr) {

};

void mutateCrossedPop(Population *crossed_pop_ptr) {

};

void applyEliteStrategy(Population *old_pop_ptr, Population *crossed_pop_ptr) {

}


#endif
