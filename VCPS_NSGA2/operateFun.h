#ifndef _OPERATE_FUN_H
#define _OPERATE_FUN_H
/************************************************************************/
/* �������б��룬ֻ�е�ÿ��������ÿ����Ŀ��Լ��������ʱ��������ǺϷ��ģ����벻�Ϸ�ʱ��ʹerror+1
/************************************************************************/
void calIndiviualFitness(Population *pop_ptr) {
	// �ȼ���ÿ����Ŀ��ÿ�������ϵ���Ӧ�ȣ�Ȼ�����ۼӼ��������������Ӧ�ȣ�ͬʱ�����ж��Ƿ�������������
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
