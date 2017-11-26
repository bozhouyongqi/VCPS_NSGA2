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
			for (processNum = 0; processNum < PROCESS_NUM; processNum++) {
				for (agentIndex = 0; agentIndex < corpNumInEveryProc[processNum]; agentIndex++){
					randNum = (double) rand()/RAND_MAX;
					switch(processNum) {
					case 0:pop_ptr->ind[indIndex].encode1[taskIndex][agentIndex] = randNum > 0.5 ? 1 : 0; break;
					case 1:pop_ptr->ind[indIndex].encode2[taskIndex][agentIndex] = randNum > 0.5 ? 1 : 0; break;
					case 2:pop_ptr->ind[indIndex].encode3[taskIndex][agentIndex] = randNum > 0.5 ? 1 : 0; break;
					case 3:pop_ptr->ind[indIndex].encode4[taskIndex][agentIndex] = randNum > 0.5 ? 1 : 0; break;
					case 4:pop_ptr->ind[indIndex].encode5[taskIndex][agentIndex] = randNum > 0.5 ? 1 : 0; break;
					default: break;
					}
				}
			}
		}
	}
}

void initConst() {
	double time = 0, quality = 0, cost = 0;
	for (int obj = 0; obj < F_NUM; obj ++) {
		for (int agent = 0; agent < AGENT1_NUM; agent++) {
			if (agent1[obj][agent] > maxArray[obj]) {
				maxArray[obj] = agent1[obj][agent];
			}
		}
		for (int agent = 0; agent < AGENT2_NUM; agent++) {
			if (agent2[obj][agent] > maxArray[obj]) {
				maxArray[obj] = agent2[obj][agent];
			}
		}
		for (int agent = 0; agent < AGENT3_NUM; agent++) {
			if (agent3[obj][agent] > maxArray[obj]) {
				maxArray[obj] = agent3[obj][agent];
			}
		}
		for (int agent = 0; agent < AGENT4_NUM; agent++) {
			if (agent4[obj][agent] > maxArray[obj]) {
				maxArray[obj] = agent4[obj][agent];
			}
		}
		for (int agent = 0; agent < AGENT5_NUM; agent++) {
			if (agent5[obj][agent] > maxArray[obj]) {
				maxArray[obj] = agent5[obj][agent];
			}
		}
	}
}

#endif
