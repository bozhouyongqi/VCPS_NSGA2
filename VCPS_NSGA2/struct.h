#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct{
	// 0-AGENT1_NUM-1 Ϊ����1�ı��룬AGENT1_NUM - (AGENT1_NUM + AGENT2_NUM -1) Ϊ����2�ı���
	int encode[TASK_NUM][AGENT1_NUM + AGENT2_NUM + AGENT3_NUM + AGENT4_NUM + AGENT5_NUM];

	int rank;
	int flag;
	double fitness[F_NUM];
	double cub_len;
	double error; 
}Individual;


typedef struct 
{
	int maxrank;
	int rankno[P_NUM];
	Individual ind[P_NUM],
		*ind_ptr;

}Population;


#endif