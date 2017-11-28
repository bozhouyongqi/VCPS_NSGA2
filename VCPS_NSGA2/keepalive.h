#ifndef  _KEEPALIVEN_
#define _KEEPALIVEN_

typedef struct{
	int maxrank;						  //该种群中最大的分层数目
	int rankar[2*P_NUM][2*P_NUM];
	int rankno[2*P_NUM];				   //不同层次上个体的数量
	Individual indnew[2*P_NUM],			//种群
		*ind_ptr;							  //  该种群的地址
}globpop;

globpop globalpop,*global_pop_ptr;


void grankc(int gen);//对所有个体分层，gen是代数

int indcmp1(double *ptr1,double *ptr2);

void gshare(int rnk);//确定层rnk的所有个体拥挤度

void gsort(int rnk,int sel);//拥挤度排序，在rnk层筛选sel个个体

void sort(int rnk);

int left,Lastrank;
double fpara1[2*P_NUM][2];			  //  fpara1[3*P_NUM][0]:是个体的编号；fpara1[3*P_NUM][1]：是个体的适应度值

void keepalive(Population *pop1_ptr,Population *pop2_ptr,Population *pop3_ptr,int gen)
{
	int i,k,m,rec;

	int st,pool,poolf,sel;

	for(i = 0;i < P_NUM;i++){
		globalpop.indnew[i]=pop1_ptr->ind[i];
		globalpop.indnew[i+P_NUM]=pop2_ptr->ind[i];
	}
	for(i=0;i<2*P_NUM;i++){
		for(k=i+1;k<2*P_NUM;k++){
			if(globalpop.indnew[i].fitness[0]==globalpop.indnew[k].fitness[0]&&
				globalpop.indnew[i].fitness[1]==globalpop.indnew[k].fitness[1]&&
				globalpop.indnew[i].fitness[2]==globalpop.indnew[k].fitness[2]){
				globalpop.indnew[i].fitness[0]=INT_MAX;
				globalpop.indnew[i].fitness[1]=INT_MAX;
				globalpop.indnew[i].fitness[2]=INT_MAX;
			}
		}
	} 

	global_pop_ptr = &(globalpop);

	grankc(gen);//分层

	m = globalpop.maxrank;

	for(i = 0;i < m;i++){
		gshare(i+1);//每层拥挤度计算	
	}

	poolf = P_NUM;//总共找p-num个 
	pool = 0;

	for(i = 0;i < 2*P_NUM;i++){
		globalpop.indnew[i].flag = 0;
	}

	rec = 0;
	st = 0;
	for(i = 0 ;i < m ; i++){
		st = pool;
		pool += globalpop.rankno[i];

		if(pool <= P_NUM){
			for(k = 0;k < 2*P_NUM ;k++){
				if(globalpop.indnew[k].rank == i+1)
					globalpop.indnew[k].flag = 1;
			}
			pop3_ptr->rankno[i] = globalpop.rankno[i];
		}
		else{
			sel = P_NUM - st;					   //pop3再需要sel个下一层的个体，种群数就达到P_NUM个了
			Lastrank = i+1;
			pop3_ptr->rankno[i] = sel;
			gsort(i+1,sel);

			break;
		}
	}

	k = 0;
	for(i = 0,k = 0;i < 2*P_NUM && k < P_NUM; i++)
	{
		if(globalpop.indnew[i].flag == 1)
		{
			pop3_ptr->ind[k]=globalpop.indnew[i];
			k++; 
		}
	}
	pop3_ptr->maxrank = Lastrank;
	return;
}


void grankc(int gen)//对所有个体分层，gen是代数
{
	int i,j,k,rnk,val,nondom,popsize1,gflg[2*P_NUM],q;
	double *ptr1,*ptr2;					//fitness指针
	double *err_ptr1,*err_ptr2;	    //error指针

	rnk = 0;
	nondom = 0;
	popsize1 = 2*P_NUM;
	g_min_fit = popsize1;
	g_delta_fit = 0.1 *popsize1;
	for(i=0;i<popsize1;i++)
	{ 
		gflg[i] = 2;
	}
	for(k = 0;k < popsize1;k++)
	{
		q =  0;
		for(j = 0;j < popsize1;j++)
		{
			if (gflg[j] != 1) break;
		}
		if(j == popsize1) break;
		rnk = rnk +1;
		for( j = 0 ;j < popsize1; j++)
		{
			if(gflg[j] == 0) gflg[j] = 2;
		}
		for(i = 0;i< popsize1 ; i++)
		{
			if(gflg[i] != 1 && gflg[i] != 0) 
			{
				ptr1 = &(globalpop.indnew[i].fitness[0]);
				err_ptr1 = &(globalpop.indnew[i].error);
				for(j = 0;j < popsize1 ; j++)
				{
					if( i!= j)
					{
						if(gflg[j] != 1)
						{
							ptr2 = &(globalpop.indnew[j].fitness[0]);
							err_ptr2 = &(globalpop.indnew[j].error);

							if(*err_ptr1 < 1.0e-6 && *err_ptr2 > 1.0e-6)
							{/* first feasible second individaul is infeasible*/
								gflg[j] = 0;
							}
							else
							{
								if(*err_ptr1 >1.0e-6 && *err_ptr2 < 1.0e-6)
								{/*first individual is infeasible and second is feasible*/
									gflg[i] = 0;
									break;
								}
								else
								{/*both feasible or both infeasible*/
									if(*err_ptr1 > *err_ptr2)
									{
										gflg[i] = 0;
										/*first individual is more infeasible*/
										break;
									}
									else
									{
										if(*err_ptr1 < *err_ptr2)
											gflg[j] = 0;
										/*second individual is more infeasible*/

										else
										{
											val = indcmp1(ptr1,ptr2);
											if( val == 2)
											{ 
												gflg[i] = 0;
												/* individual 1 is dominated */
												break;
											}
											if(val == 1)
											{
												gflg[j] = 0;
												/* individual 2 is dominated */
											}
											if(val == 3)
											{
												nondom++;/* individual 1 & 2 are non dominated */
												if(gflg[j] != 0) gflg[j] = 3;
											}
										}
									}
								}
							}
						}
					}
				}
				if( j == popsize1)
				{
					globalpop.indnew[i].rank = rnk;
					gflg[i] = 1;
					global_pop_ptr->rankar[rnk-1][q] =  i;
					q++;
				}
			}
		}
		global_pop_ptr->rankno[rnk-1] = q;
	} 
	global_pop_ptr->maxrank = rnk;
}

int indcmp1(double *ptr1,double *ptr2)
{
	double fit1[F_NUM],fit2[F_NUM];
	int i,value,m,n;
	for(i = 0;i < F_NUM ;i++)
	{
		fit1[i] = *ptr1++;
		fit2[i] = *ptr2++;
	}
	m = 0;n=0;
	while(m < F_NUM && fit1[m] <= fit2[m]) 
	{
		if((fit2[m] - fit1[m]) < 1e-7) n++;
		m++;
	}
	if(m == F_NUM) 
	{
		if(n == F_NUM) value = 3;
		else value = 1;                    /*value = 1 for dominating*/
	}
	else 
	{
		m = 0;n = 0;
		while(m < F_NUM && fit1[m] >= fit2[m]) 
		{
			if((fit1[m] - fit2[m]) < 1e-7) n++;
			m++;
		}
		if(m == F_NUM)
		{
			if(n != F_NUM)
				value = 2;                       /*value =  2 for dominated */
			else value = 3;
		}
		else value = 3;                   /*value = 3 for incomparable*/
	}
	return value;
}


/* This is the file used to sort the dummyfitness arrays */
void gsort(int rnk,int sel)//拥挤度排序，在rnk层筛选sel个个体
{
	int i,j,a,q;
	double array[2*P_NUM][2],temp,temp1;

	q = globalpop.rankno[rnk-1];

	for(i = 0 ;i < q ;i++)
	{
		array[i][0] = globalpop.rankar[rnk-1][i];
		a = globalpop.rankar[rnk-1][i];
		array[i][1] = globalpop.indnew[a].cub_len;
	}
	for(i = 0;i < q ;i++)
	{
		for(j = i+1;j < q;j++)
		{
			if(array[i][1] < array[j][1])
			{
				temp = array[i][1];
				temp1 = array[i][0];
				array[i][1] = array[j][1];
				array[i][0] = array[j][0];

				array[j][1] = temp;
				array[j][0] = temp1;
			}
		}
	}

	for(i = 0;i < sel;i++)
	{
		a = array[i][0];
		globalpop.indnew[a].flag = 1;
	}
	return;
}

/*========================================================================*/

void gshare(int rnk)//确定层rnk的个体拥挤度
{
	double length[2*P_NUM][2];
	int i,j,m1,a ;
	double max,min, Diff;  // Added 18.08.2003

	m1 = globalpop.rankno[rnk-1];							  //m1:处在rnk层个体的数量

	for(j = 0;j < F_NUM;j++)
	{
		for(i = 0;i < m1;i++)
		{
			fpara1[i][0] = 0;
			fpara1[i][1] = 0;
		}

		for(i = 0;i < m1;i++)
		{
			a = globalpop.rankar[rnk-1][i];				
			fpara1[i][0] = (double)a ;
			fpara1[i][1] = globalpop.indnew[a].fitness[j];
		}

		sort(m1); 

		max = fpara1[m1-1][1];
		min = fpara1[0][1];  
		Diff = max-min;        
		if (Diff < 0.0) 
		{
			printf("Something wrong in keepaliven.h\n");
			exit(1);
		}
		for(i = 0;i < m1;i++)
		{
			if(i == 0 ||i == (m1-1))
			{ 
				length[i][0] = fpara1[i][0];
				length[i][1] = 100.0*max;
			}
			else
			{
				length[i][0] = fpara1[i][0];
				length[i][1] = (double)fabs(fpara1[i+1][1]- fpara1[i-1][1])/Diff; // crowding distances are normalized 18.08.2003	整数的绝对值用abs();float型用fabs()
				//length[i][1] = abs(fpara1[i+1][1]- fpara1[i-1][1]);
			}
		}
		for(i = 0;i < m1;i++)
		{
			a =(int) length[i][0];
			globalpop.indnew[a].cub_len += length[i][1];
		}
	}

	return;
}


void sort(int m1)//
{
	double temp,temp1; 
	int i1,k1;
	for(k1 = 0;k1 < m1-1;k1++)
	{
		for(i1 = k1+1;i1 < m1;i1++)
		{
			if(fpara1[k1][1] > fpara1[i1][1]||fpara1[k1][1] == fpara1[i1][1])
			{
				temp = fpara1[k1][1];
				temp1 = fpara1[k1][0];
				fpara1[k1][1] = fpara1[i1][1];
				fpara1[k1][0] = fpara1[i1][0];
				fpara1[i1][1] = temp;
				fpara1[i1][0] = temp1;
			}
		}
	}
	return;
}

#endif