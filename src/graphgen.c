//This program create a network of N nodes following the requirement and write into the file .txt file
//Read README.txt in the zip file to know how to run this program on jinx cluster

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int PickNode(int *D, int N, int DTotal);

int main(int argc, char* argv[]) {
	if (argc<2){
		printf("Wrong input\n");
		return -1;
	}
	int n0 = 5;  //Number of nodes that a fully connected network has at the beginning
	int N = atoi(argv[1]);  //The number of nodes here
	int *D;					//Node Degree array
	D = (int*) malloc(N*sizeof(int));
	int DTotal = 0;  //Number of total node degree
	int ind;  //Index to indicate the node number will be picked, returned by PickNode
	int i,j,k; //Variable for the for loop
	for (k=0;k<N;k++){
		if (k<n0) {
			D[k] = n0-1;
		}
		else {
			D[k] = 0;
		}
		DTotal = DTotal + D[k];
	}

	srand(time(NULL));
	FILE *fp;
	char *filename = "my_graph";
	fp = fopen(filename,"w");
	fprintf(fp,"%d\n",N);
	for (i=0;i<N;i++){
		if (i<n0) {  //Write into the text file the edges for the fully connected network with n0 = 5 nodes
			for (j=i+1;j<(n0<N?n0:N);j++){
				fprintf(fp,"%d %d\n",i,j);
			}
		}
		else {    //Write into the text file the edges when a new node is added according to the preferential attachment rule
			ind = PickNode(D,N,DTotal);
			D[ind]++;
			D[i]++;
			DTotal = DTotal+2;
			fprintf(fp,"%d %d\n",i,ind);
		}
	}
	fclose(fp);
	return 0;
}

int PickNode(int *D, int N, int DTotal) {
	int accu_sum = 0;
	int i = 0;
	double r;
	r = (double) rand()/RAND_MAX;  //Uniformly random number from 0 to 1
	while(accu_sum < DTotal) {
		accu_sum = accu_sum + D[i];
		if ((double) accu_sum/DTotal >= r) {
			break;
		}
		i++;
	}
	return i;  //Return the node number which will be picked to add an edge to a new node
}
