#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct
{
	double fitness[F_NUM];
	double cub_len;
	double error; 
	int encode[TASK_NUM][AGENT_ALL];
	int rank;
	int flag;
}Individual;


typedef struct 
{
	int maxrank;
	int rankno[P_NUM];
	Individual ind[P_NUM],
		*ind_ptr;

}Population;


#endif