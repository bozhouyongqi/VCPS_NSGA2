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


#endif
