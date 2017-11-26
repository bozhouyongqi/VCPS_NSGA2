#ifndef _INIT_H_
#define _INIT_H_

void initPop(Population *pop_ptr) {
	int ind = 0;
	int agentIndex = 0;
	int taskIndex = 0;
	int processNum = 0;
	double randNum = 0;
	int indIndex = 0;
	for (indIndex = 0; indIndex < P_NUM; indIndex++) {
		for (taskIndex = 0; taskIndex < TASK_NUM; taskIndex++) {
			for (agentIndex = 0; agentIndex < AGENT_ALL; agentIndex++){
				randNum = (double) rand()/RAND_MAX;
				pop_ptr->ind[indIndex].encode[taskIndex][agentIndex] = randNum > 0.5 ? 1 : 0;
			}
		}
	}
}

void initNormalizationValue() {
	for (int obj = 0; obj < F_NUM; obj++) {
		double maxValue = 0;
		for (int agent = 0; agent < AGENT_ALL; agent++) {
			if(agentPara[obj][agent] > maxValue) {
				maxValue = agentPara[obj][agent];
			}
		}
		normalizeValue[obj] = maxValue;
	}
}

void intAgentPara() {
	for (int obj = 0; obj < F_NUM; obj++) {
		int index = 0;
		for (int agent = 0; agent < AGENT1_NUM; agent++) {
			agentPara[obj][index++] = agent1[obj][agent];
		}
		for (int agent = 0; agent < AGENT2_NUM; agent++) {
			agentPara[obj][index++] = agent2[obj][agent];
		}
		for (int agent = 0; agent < AGENT3_NUM; agent++) {
			agentPara[obj][index++] = agent3[obj][agent];
		}
		for (int agent = 0; agent < AGENT4_NUM; agent++) {
			agentPara[obj][index++] = agent4[obj][agent];
		}
		for (int agent = 0; agent < AGENT5_NUM; agent++) {
			agentPara[obj][index++] = agent5[obj][agent];
		}
	}
}

void init(Population *pop_ptr) {
	intAgentPara();
	initNormalizationValue();
	initPop(pop_ptr);
}

#endif
