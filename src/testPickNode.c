//This program tests if PickNode is producing random numbers of the desired distribution
//Run this program several times to see that the index for node number returned is uniformly distributed
//over discrete values 0,1,2,3 because I initialized the Node Degree to be the same = 3 for every of 4 nodes.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int PickNode (int *D, int N, int DTotal);

int main(){
	int ind;
	int D[4] = {3, 3, 3, 3}; //A Node Degree Array for a fully connected network with 4 nodes
	srand (time(NULL));
	ind = PickNode(D, 4, 12); //Return the node number which will be picked to add an edge to a new node
	printf("%d\n",ind);
	return 0;
}

int PickNode (int *D, int N, int DTotal){
	int accu_sum = 0;
	int i = 0;
	double r;
	r = (double) rand()/RAND_MAX;  //Uniformly random number from 0 to 1
	printf("%f\n",r);
	while (accu_sum < DTotal) {
		accu_sum = accu_sum + D[i];
		if ((double) accu_sum/DTotal >= r) {
			break;
		}
		i++;
	}
	return i;   //Return the node number which will be picked to add an edge to a new node
}
