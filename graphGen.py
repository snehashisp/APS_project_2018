import random
import sys
import math

nodes = int(sys.argv[1])
edges = int(sys.argv[2])
weight_limit = int(sys.argv[3])
filep = open(sys.argv[4],"w")
try:
    vEB_size = int(sys.argv[5])
except:
    vEb_size = 1024

node_init_path = [i for i in range(1,nodes+1)]
random.shuffle(node_init_path)

i = 0
tot_edges = 0
edge_triple = []
exist_E = {}

while i < nodes - 1:

    ran_weight = int(random.uniform(1,weight_limit))
    edge_triple += [(node_init_path[i],node_init_path[i+1],ran_weight)]
    exist_E[(node_init_path[i],node_init_path[i+1])] = 1
    i += 1
    tot_edges += 1

while tot_edges < edges:

    start_edge = int(random.uniform(1,nodes+1))
    end_edge = int(random.uniform(1,nodes+1))
    
    edge = (start_edge,end_edge)
    if edge not in exist_E:

        weight = int(random.uniform(1,weight_limit))
        edge_triple += [(start_edge,end_edge,weight)]
        exist_E[edge] = 1
        tot_edges += 1

filep.writelines(str(nodes) + " " + str(edges) + "\n")
for tup in edge_triple:
    filep.writelines(str(tup[0]) + " " + str(tup[1]) + " " + str(tup[2]) + "\n")

filep.writelines(str(1) + " " + str(vEB_size) + "\n")






    



    




        
