#ifndef _OPERATE_FUN_H
#define _OPERATE_FUN_H

int indcmp3(double *ptr1,double *ptr2);

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
	int i,j,k,       /*counters*/
	rnk,           /*rank*/
	val,           /*value obtained after comparing two individuals*/
	nondom,        /*no of non dominated members*/
	maxrank1,      /*Max rank of the population*/
	rankarr[P_NUM], /*Array storing the individual number at a rank*/
	q;
	double *ptr1,*ptr2,*err_ptr1,*err_ptr2;

	/*------------------------------* RANKING *------------------------------*/

	/*Initializing the ranks to zero*/
	rnk = 0 ;
	nondom = 0 ;
	maxrank1 = 0;
	/*min_fit is initialize to start distributing the dummy fitness = 
	P_NUM to the rank one individuals and keeping the record such 
	that the minimum fitness of the better rank individual is always 
	greater than max fitness of the relatively worse rank*/

	min_fit = P_NUM;

	/*Difference in the fitness of minimum dummy fitness of better rank 
	and max fitness of the next ranked individuals*/

	delta_fit = 0.1 * P_NUM;

	/*Initializing all the flags to 2*/

	for( j = 0 ;j < P_NUM; j++)
		pop_ptr->ind[j].flag = 2;						   //意思是都没有分配排名
	q = 0;
	for(k =  0;k < P_NUM;k++,q=0){
		for(j = 0;j < P_NUM;j++){
			if (pop_ptr->ind[j].flag != 1)				//下面的代码可能会改变个体的flag
				break;
			/*Break if all the individuals are assigned a rank*/
		}
		if(j == P_NUM)
			break;
		rnk = rnk + 1;
		for( j = 0 ;j < P_NUM; j++){
			if(pop_ptr->ind[j].flag == 0)
				pop_ptr->ind[j].flag = 2;
			/*Set the flag of dominated individuals to 2*/
		}
		for(i = 0;i < P_NUM ; i++){
			/*Select an individual which rank to be assigned*/
			pop_ptr->ind_ptr = &(pop_ptr->ind[i]);
			if(pop_ptr->ind_ptr->flag != 1 && pop_ptr->ind_ptr->flag != 0){ 		//不就是选flag=2的个体吗
				ptr1 = &(pop_ptr->ind_ptr->fitness[0]);
				err_ptr1 = &(pop_ptr->ind_ptr->error);
				for(j = 0;j < P_NUM ; j++){
					/*Select the other individual which has not got a rank*/
					if( i!= j){
						if(pop_ptr->ind[j].flag != 1){
							pop_ptr->ind_ptr = &(pop_ptr->ind[j]);
							ptr2 = &(pop_ptr->ind_ptr->fitness[0]);
							err_ptr2 = &(pop_ptr->ind_ptr->error);

							if(*err_ptr1 < 1.0e-6 && *err_ptr2 > 1.0e-6) {				//只要*err_ptr1大于0，就说明，该方案不满足约束条件，不可行
								/*first ind is feasible second individaul 
								is infeasible*/
								pop_ptr->ind[j].flag = 0;					 //flag=0意思是说该个体不合法
							}
							else
							{
								if(*err_ptr1 > 1.0e-6 && *err_ptr2 < 1.0e-6)
								{
									/*first individual is infeasible and 
									second is feasible*/
									pop_ptr->ind[i].flag = 0;
									break;
								}
								else
								{
									/*both are feasible or both are infeasible*/
									if(*err_ptr1 > *err_ptr2)
									{
										pop_ptr->ind[i].flag = 0;
										/*first individual is more infeasible*/
										break;
									}
									else
									{
										if(*err_ptr1 < *err_ptr2)
										{
											pop_ptr->ind[j].flag = 0;
											/*second individual is more 
											infeasible*/
										}
										else
										{
											/*Compare the two individuals for 
											fitness*/
											val = indcmp3(ptr1,ptr2);						   //应该就是两个个体都合法

											/*VAL = 2 for dominated individual 
											which rank to be given*/

											/*VAL = 1 for dominating individual 
											which rank to be given*/

											/*VAL = 3 for non comparable 
											individuals*/

											if( val == 2)
											{ 
												pop_ptr->ind[i].flag = 0;
												/* individual 1 is dominated */
												break;
											}

											if(val == 1)
											{
												pop_ptr->ind[j].flag = 0;
												/* individual 2 is dominated */
											}

											if(val == 3)
											{
												nondom++;
												/* individual 1 & 2 are 
												non dominated */
												if(pop_ptr->ind[j].flag != 0)
													pop_ptr->ind[j].flag = 3;
											}

										}   
									}       
								}
							}
						}//if( pop_ptr->ind[j].flag != 1) loop end
					}	 /* i != j loop ends*/
				}        /*loop over j ends*/
				if( j == P_NUM)
				{
					/*Assign the rank and set the flag*/
					pop_ptr->ind[i].rank = rnk;
					pop_ptr->ind[i].flag = 1;
					rankarr[q] = i;
					q++;
				}
			}       /*Loop over flag check ends*/
		}           /*Loop over i ends */
		pop_ptr->rankno[rnk-1] = q ;
	}
	maxrank1 = rnk;

	/*     Find Max Rank of the population    */
	for(i = 0;i < P_NUM;i++)
	{
		rnk = pop_ptr->ind[i].rank;

		if(rnk > maxrank1)
			maxrank1 = rnk;

	}

	pop_ptr->maxrank = maxrank1;
}

void executeSelectOpt(Population *old_pop_ptr, Population *selected_pop_ptr) {

};

void crossSelectedPop(Population *selected_pop_ptr, Population *crossed_pop_ptr) {

};

void mutateCrossedPop(Population *crossed_pop_ptr) {

};

void applyEliteStrategy(Population *old_pop_ptr, Population *crossed_pop_ptr) {

}


/************************************************************************/
/*  Routine Comparing the two individuals                                                                    */
/************************************************************************/
int indcmp3(double *ptr1,double *ptr2)
{
	double fit1[F_NUM],fit2[F_NUM];
	int i,value,m,n;
	for(i = 0;i < F_NUM ;i++)
	{
		fit1[i] = *ptr1++;
		fit2[i] = *ptr2++;
	}
	m = 0;
	n = 0;
	while(m < F_NUM && fit1[m] <= fit2[m]) 
	{
		if(fit1[m]== fit2[m]) n++;
		m++;
	}
	if(m == F_NUM) 
	{
		if(n == F_NUM) value = 3;
		else value = 1;             /*value = 1 for dominationg*/
	}
	else 
	{
		m = 0;
		n = 0;
		while(m < F_NUM && fit1[m] >= fit2[m])
		{
			if(fit1[m]== fit2[m]) n++;
			m++;
		}
		if(m == F_NUM)
		{
			if(n != F_NUM)
				value = 2;                       /*value =  2 for dominated */
			else value =3;
		}
		else value = 3;                   /*value = 3 for incomparable*/
	}

	return value;
}
#endif
