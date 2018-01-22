#include<iostream>
#include<time.h>
#include<math.h>
#include <fstream>
#include <direct.h>
using namespace std;

#include <string>
#include <stdlib.h>
#include <time.h>

double g_min_fit, g_delta_fit;

#include "global_var.h"
#include "struct.h"
#include "init.h"
#include "operateFun.h"
#include "keepalive.h"

Population oldPop,
		selectedPop,
		crossedPop,
		newPop,
		*old_pop_ptr,
		*selected_pop_ptr,
		*crossed_pop_ptr,
		*new_pop_ptr;

void print_last_gen(int run_num,double cost_time);

void main() {
	srand((unsigned int)time(0));
	clock_t start_time,finish_time;
	double duration_time;
	int shiyan = 0,gen = 0;
	fstream ofz;
	ofz.open("each_run_time_my.txt");

	for (shiyan = 0; shiyan < Shiyan_NUM; shiyan++) {
		
		start_time=clock();
		init(&oldPop);
		calIndiviualFitness(&oldPop);
		for (int i = 0; i < P_NUM; i++) {
			oldPop.rankno[i] = 0;
			selectedPop.rankno[i] = 0;
			crossedPop.rankno[i] = 0;
		}

		for (gen = 0; gen < GEN_MAX; gen++) {
			// ��ʼ����Ⱥ
			applyNonDominatedSorting(&oldPop); // ��ʱ��oldPop�����Ѿ��������Ӧ�ȵ�
			executeSelectOpt(&oldPop, &selectedPop);
			crossSelectedPop(&selectedPop, &crossedPop);
			mutateCrossedPop(&crossedPop);
			calIndiviualFitness(&crossedPop);
			keepalive(&oldPop, &crossedPop, &newPop, gen); // ��oldPop��crossedPop�ϲ���ѡ����һ����Ⱥ����newPop��
			oldPop = newPop;

			if(gen==GEN_MAX-1)	 //��Ⱥ���е����һ��ʱ������һ�������ӽ�����
			{
				old_pop_ptr = &(oldPop);
				finish_time=clock();
				duration_time=(double)(finish_time-start_time)/CLOCKS_PER_SEC;
				cout<<duration_time<<" s"<<endl;

				ofz<<duration_time<<endl;

				print_last_gen(shiyan, duration_time);
			}
			if(0==gen%100)
				cout<<"gen="<<gen<<endl	 ;
		}
	}
	ofz.close();
	cout <<"test over"<<endl;
}

void print_last_gen(int run_num,double cost_time)
{
	char num[100];
	itoa(run_num,num,10);

	char buffer[MAX_PATH];
	getcwd(buffer,MAX_PATH);//���ص�ǰ�����������ļ�Ŀ¼�����buffer��

	char file1[500];
	sprintf(file1,"%s\\last_generation",buffer);//��buffer�еĵ�ǰ�ļ�Ŀ¼д��file1�У�������һ���µ��ļ�����Ϊfitness
	sprintf(file1,"%s\\last_generation%s.txt",file1,num);//��file1��д��ÿ�ε��������Ĳ�ͬfitness�ļ���·��
	last_gen_ptr=fopen(file1,"wt"); 

	char file2[500];
	sprintf(file2,"%s\\to_CompareMine",buffer);
	sprintf(file2,"%s\\to_CompareMine%s.txt",file2,num);
	to_CompareMine=fopen(file2,"wt"); 

	char file3[500];
	sprintf(file3,"%s\\weightedValue",buffer);
	sprintf(file3,"%s\\weightedValue%s.txt",file3,num);
	weightValueFile=fopen(file3,"wt"); 

	int f=0,l=0,m=0,n=0;
	int best_num=0;
	for(f=0;f<P_NUM;f++)
	{
		old_pop_ptr->ind_ptr=&(old_pop_ptr->ind[f]);
		/*--------- for all feasible solutions and non-dominated solutions----------- */
		if((old_pop_ptr->ind_ptr->error < 1e-7)&&(old_pop_ptr->ind_ptr->rank==1) )
		{
			/*-----------��ӡ�����Encode[][]------------*/
			best_num++;
			fprintf(last_gen_ptr,"%s","individual: ");
			fprintf(last_gen_ptr,"%d\n",f);
			fprintf(last_gen_ptr,"%s","encode:\n");
			for(l=0;l<TASK_NUM;l++)
			{
				for(m=0;m<AGENT_ALL;m++)
				{
					fprintf(last_gen_ptr,"%d",old_pop_ptr->ind_ptr->encode[l][m]);
					fprintf(last_gen_ptr,"%s","  ");
				}
				fprintf(last_gen_ptr,"%s","\n");
			}
			fprintf(last_gen_ptr,"%s","\n");

			fprintf(last_gen_ptr,"%s","\n");
			fprintf(last_gen_ptr,"%s","\n");
			fprintf(last_gen_ptr,"%s","��ʱ��= ");
			fprintf(last_gen_ptr,"%f",old_pop_ptr->ind_ptr->fitness[0]);
			fprintf(last_gen_ptr,"%s","   ");	

			fprintf(last_gen_ptr,"%s","����(1-q)=");
			fprintf(last_gen_ptr,"%f,",old_pop_ptr->ind_ptr->fitness[1]);

			fprintf(last_gen_ptr,"%s","����(q)=");
			fprintf(last_gen_ptr,"%f,",old_pop_ptr->ind_ptr->quality);

			fprintf(last_gen_ptr,"%s","�ܻ��ѳɱ�=");
			fprintf(last_gen_ptr,"%f,",old_pop_ptr->ind_ptr->fitness[2]);

			fprintf(last_gen_ptr,"%s","   ");	
			fprintf(last_gen_ptr,"%s","error:  ");
			fprintf(last_gen_ptr,"%d",old_pop_ptr->ind_ptr->error);

			fprintf(last_gen_ptr,"%s","   ");	
			fprintf(last_gen_ptr,"%s","rank:  ");
			fprintf(last_gen_ptr,"%d",old_pop_ptr->ind_ptr->rank);

			fprintf(last_gen_ptr,"%s","\n");
			for(l=0;l<F_NUM;l++){
				if (l == 1) {
					fprintf(to_CompareMine,"%f ",old_pop_ptr->ind_ptr->quality);	// ��ͼ�õ����ݣ�����δ����С������
				}else{
					fprintf(to_CompareMine,"%f ",old_pop_ptr->ind_ptr->fitness[l]);
				}
				
			}
			fprintf(to_CompareMine,"%s","\n");
			fprintf(weightValueFile,"%f\n", old_pop_ptr->ind_ptr->weightedValue);	// �����õ��Ǿ�����С���������������֮ǰ���ֲ���
		}
	}  //for(f) end;
	fprintf(last_gen_ptr,"%s","��һ���������: ");
	fprintf(last_gen_ptr,"%d  ",best_num);

	fprintf(last_gen_ptr,"%s","����ʱ��: ");
	fprintf(last_gen_ptr,"%f",cost_time);

	fclose(last_gen_ptr);
	fclose(to_CompareMine);
}
