# Dijkstra-Algorithm

%Instruction on how to run my code on jinx-cluster:

1/ Start PuTTY or any SSH software

2/ Log-in into jinx cluster named: jinx-login.cc.gatech.edu

3/ Upload codes in .c files to cluster using WinSCP, in this case, is find_diameter.c

4/ Put all the graph files into the same folder where the file find_diameter.c is located

5/ Submit job to compute node by typing: qsub -I -q class -l nodes=1

6/ Compile file by typing: gcc filename.c

7/ Run compiled file by typing: ./a.out filename

For example, to find the diameter of the network in the file graph_10, type:
./a.out graph_10

*Note: Can put comment in front of the command line PrintGraph in find_diameter.c to 
prevent the program from printing out the graph.
