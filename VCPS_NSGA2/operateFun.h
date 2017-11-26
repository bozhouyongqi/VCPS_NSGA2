#ifndef _OPERATE_FUN_H
#define _OPERATE_FUN_H
/************************************************************************/
/* �������б��룬ֻ�е�ÿ��������ÿ����Ŀ��Լ��������ʱ��������ǺϷ��ģ����벻�Ϸ�ʱ��ʹerror+1
/************************************************************************/
void calIndiviualFitness(Population *pop_ptr) {
	// �ȼ���ÿ����Ŀ��ÿ�������ϵ���Ӧ�ȣ�Ȼ�����ۼӼ��������������Ӧ�ȣ�ͬʱ�����ж��Ƿ�������������
	double fitArray[TASK_NUM][PROCESS_NUM][F_NUM] = {0};
	
	for (int indIndex = 0; indIndex < P_NUM; indIndex++) {
		for (int task = 0; task < TASK_NUM; task++) {
			double maxTime = 0, quality = 0, cost = 0;
			double qualitySum = 0, costSum = 0;
			// �ȼ���encode1������1�ı�����Ӧ��
			
			for (int agent = 0; agent < AGENT1_NUM; agent++) {
				if (pop_ptr->ind[indIndex].encode1[task][agent] == 1) {
					if (agent1[0][agent] > maxTime) {
						maxTime = agent1[0][agent];
					}
					qualitySum += agent1[1][agent];
					costSum += agent1[2][agent];
					fitArray[task][0][1] += (1 - agent1[1][agent] / maxArray[1]);
					fitArray[task][0][2] += (agent1[2][agent] / maxArray[2]);
				}
			}
			fitArray[task][0][0] = (maxTime / maxArray[0]);
			
			// ����encode1������2�ı�����Ӧ��
			maxTime = 0, quality = 0, cost = 0;
			qualitySum = 0, costSum = 0;
			for (int agent = 0; agent < AGENT2_NUM; agent++) {
				if (pop_ptr->ind[indIndex].encode2[task][agent] == 1) {
					if (agent2[0][agent] > maxTime) {
						maxTime = agent2[0][agent];
					}
					qualitySum += agent2[1][agent];
					costSum += agent2[2][agent];
					fitArray[task][0][1] += (1 - agent2[1][agent] / maxArray[1]);
					fitArray[task][0][2] += (agent2[2][agent] / maxArray[2]);
				}
			}
			fitArray[task][1][0] = (maxTime / maxArray[0]);

			// ����encode1������3�ı�����Ӧ��
			maxTime = 0, quality = 0, cost = 0;
			qualitySum = 0, costSum = 0;
			for (int agent = 0; agent < AGENT3_NUM; agent++) {
				if (pop_ptr->ind[indIndex].encode3[task][agent] == 1) {
					if (agent3[0][agent] > maxTime) {
						maxTime = agent3[0][agent];
					}
					qualitySum += agent3[1][agent];
					costSum += agent3[2][agent];
					fitArray[task][0][1] += (1 - agent3[1][agent] / maxArray[1]);
					fitArray[task][0][2] += (agent3[2][agent] / maxArray[2]);
				}
			}
			fitArray[task][2][0] = (maxTime / maxArray[0]);

			// ����encode1������4�ı�����Ӧ��
			maxTime = 0, quality = 0, cost = 0;
			qualitySum = 0, costSum = 0;
			for (int agent = 0; agent < AGENT4_NUM; agent++) {
				if (pop_ptr->ind[indIndex].encode4[task][agent] == 1) {
					if (agent4[0][agent] > maxTime) {
						maxTime = agent4[0][agent];
					}
					qualitySum += agent4[1][agent];
					costSum += agent4[2][agent];
					fitArray[task][0][1] += (1 - agent4[1][agent] / maxArray[1]);
					fitArray[task][0][2] += (agent4[2][agent] / maxArray[2]);
				}
			}
			fitArray[task][3][0] = (maxTime / maxArray[0]);

			// ����encode1������5�ı�����Ӧ��
			maxTime = 0, quality = 0, cost = 0;
			qualitySum = 0, costSum = 0;
			for (int agent = 0; agent < AGENT5_NUM; agent++) {
				if (pop_ptr->ind[indIndex].encode5[task][agent] == 1) {
					if (agent5[0][agent] > maxTime) {
						maxTime = agent5[0][agent];
					}
					qualitySum += agent5[1][agent];
					costSum += agent5[2][agent];
					fitArray[task][0][1] += (1 - agent5[1][agent] / maxArray[1]);
					fitArray[task][0][2] += (agent5[2][agent] / maxArray[2]);
				}
			}
			fitArray[task][4][0] = (maxTime / maxArray[0]);
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
