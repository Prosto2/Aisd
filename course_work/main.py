import graph
with open('testpy.txt', 'r') as file:
    lines = file.readlines()
#print(lines)
edges = graph.TGraph()
edges.parsing(lines)
edges.algorithm_kruskal()
edges.adjacency_list()
print('Incidence matrix: ', edges.graph_to_incidence_matrix(edges.mygraph))
#edges.adjacency_matrix()
#print(edges.mygraph)
# print('Answer: ')
# edges.cout()
print('\nDeep crawl: ')
edges.depth_first_search(edges.mylist, 'A')
print('\nWidth traversal: ')
edges.breadth_first_search(edges.mylist, 'A')
print('\n\nAnswer: ')
edges.cout()
