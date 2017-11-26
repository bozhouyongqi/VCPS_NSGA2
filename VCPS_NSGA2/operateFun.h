#ifndef _OPERATE_FUN_H
#define _OPERATE_FUN_H
/************************************************************************/
/* 根据现有编码，只有当每个环节中每个项目的约束都满足时，编码才是合法的，编码不合法时，使error+1
/************************************************************************/
void calIndiviualFitness(Population *pop_ptr) {
	// 先计算每个项目在每个环节上的适应度，然后在累加即是整个个体的适应度，同时可以判断是否满足限制条件
	double fitArray[TASK_NUM][PROCESS_NUM][F_NUM] = {0};
	
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
