#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct{
	// ÿһ���������5����룬�ֱ��Ӧ5������
	int encode1[TASK_NUM][AGENT1_NUM];
	int encode2[TASK_NUM][AGENT2_NUM];
	int encode3[TASK_NUM][AGENT3_NUM];
	int encode4[TASK_NUM][AGENT4_NUM];
	int encode5[TASK_NUM][AGENT5_NUM];

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