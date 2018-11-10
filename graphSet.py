import graphGen 
import sys
import os
import math
import shutil

nodes_start = int(sys.argv[1])
nodes_end = int(sys.argv[2])
sparseness = int(sys.argv[3])/100;
weight_lim = int(sys.argv[4])
step = int(sys.argv[5])
path = str(sys.argv[6])

if os.path.exists(path):
    shutil.rmtree(path,ignore_errors = True)

os.mkdir(path)

save_str = path + "/test_" + str(sparseness) + "_"
while nodes_start <= nodes_end:
    
    save_file = save_str + str(nodes_start)
    fp = open(save_file,"w")
    edges = int(sparseness * ((nodes_start * (nodes_start - 1)) / 2))
    veb_size = int(math.pow(2,int(math.log2((nodes_start - 1)*weight_lim)) + 1))
    print(str(veb_size) + " " + str(nodes_start))
    graphGen.generate(nodes_start,edges,weight_lim,fp,veb_size)
    fp.close()
    nodes_start += step

    








