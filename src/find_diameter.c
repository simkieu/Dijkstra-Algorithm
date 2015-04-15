/*
 ============================================================================
 Name        : test2.c
 Author      : Sim Kieu
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int index;
	struct node *next;
} node;

//Find max value in an array
int array_max(int *d, int size) {
	if (size == 0) {
		fprintf(stderr, "Cannot find the maximum!\n");
		exit(1);
	}
	int i, max_value;
	max_value = -1;
	for (i=0;i<size;i++) {
		if (d[i] > max_value) {
			max_value = d[i];
		}
	}
	return max_value;
}

//Find minimum between 2 integers
int min(int a, int b) {
	return a<b?a:b;
}

//Find the index of the minimum in an array
int min_index(int *d, int size) {
	if (size == 0) {
		fprintf(stderr, "Cannot find the minimum!\n");
		exit(1);
	}
	int ind, i, min_value;
	min_value = 1e6;
	ind = 0;
	for (i=0;i<size;i++) {
		if (d[i] < min_value) {
			min_value = d[i];
			ind = i;
		}
	}
	return ind;
}

int dijkstra(node **g, int N, int s) {
	int ind, edge_ind, length_max;
	struct node* temp;
	int *d_min = (int*) malloc(N*sizeof(int));
	int *flag = (int*) malloc(N*sizeof(int));
	int *d_temp = (int*) malloc(N*sizeof(int));
	int num_in_S = 0;
	int i;
	for (i=0;i<N;i++) {
		d_min[i] = 1e6;
		d_temp[i] = 1e6;
		flag[i] = 0;
	}
	d_min[s] = 0;
	d_temp[s] = 0;
	while (num_in_S < N) {
		ind = min_index(d_temp,N);
		flag[ind] = 1;
		num_in_S++;
		temp = g[ind];
		while (temp != NULL) {
			edge_ind = temp->index;
			temp =  temp->next;
			if (flag[edge_ind] == 0) {
				d_min[edge_ind] = min(d_min[edge_ind],d_min[ind]+1);
				d_temp[edge_ind] = d_min[edge_ind];
			}
		}
		d_temp[ind] = 1e6;
	}
	length_max = array_max(d_min,N);
	return length_max;
}

void PrintGraph(node **g, int size) {
	int i;
	struct node *temp;
	for (i = 0; i < size; i++){
		temp = g[i];
		printf("%d",i);
		while (temp != NULL) {
			printf("->");
			printf("%d",temp->index);
			temp =  temp->next;
		}
		printf("\n");
	}
	printf("\n");
}

void CreateGraph(node **g, int *d, int N) {
	int i,j,ind1,ind2;
	for (i=0;i<N;i++) {
		g[i] = NULL;
	}
	for (j=0;j<N+5;j++) {
		ind1 = d[2*j];
		ind2 = d[2*j+1];

		//Add vertex 2 into vertex 1
		if (g[ind1] == NULL) {
			g[ind1] = (node*) malloc(sizeof(node));
			g[ind1]->index = ind2;
			g[ind1]->next = NULL;
		}
		else {
			node *temp = (node*) malloc(sizeof(node));
			temp->index = ind2;
			temp->next = g[ind1]->next;
			g[ind1]->next = temp;
		}

		//Add vertex 1 into vertex 2
		if (g[ind2] == NULL) {
			g[ind2] = (node*) malloc(sizeof(node));
			g[ind2]->index = ind1;
			g[ind2]->next = NULL;
		}
		else {
			node *temp = (node*) malloc(sizeof(node));
			temp->index = ind1;
			temp->next = g[ind2]->next;
			g[ind2]->next = temp;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2){
		printf("Wrong input\n");
		return -1;
	}
	int i = 0;
	int N, num, j, k, diameter;
	char *filename = argv[1];
	FILE *fp;
	fp = fopen(filename,"r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open input file!\n");
		exit(1);
	}
	fscanf(fp, "%d", &num);
	N = num;
	int num_of_link = N + 5;
	int *d = malloc(2*num_of_link*sizeof(int));
	for (k=0;k<2*num_of_link;k++) {
		fscanf(fp, "%d", &num);
		d[i] = num;
		i = i + 1;
	}

	fclose(fp);
	struct node** g = (node**) malloc(N*sizeof(node*));
	CreateGraph(g,d,N);
	printf("The graph of network:\n");
	PrintGraph(g,N);
	int *d_max = (int*) malloc(N*sizeof(int));
	for (j=0;j<N;j++) {
		d_max[j] = dijkstra(g,N,j);
	}
	diameter = array_max(d_max,N);
	printf("The diameter of the input graph is: %d\n",diameter);
	return 0;
}
