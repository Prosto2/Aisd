from collections import defaultdict
from collections import deque
class TGraph():
    def __init__(self):
        self.mygraph = []
        self.answer = []
        self.matrix = []
        self.mylist = {}
        #self.parsing(lines)

    def graph_to_incidence_matrix(self, graph):
        vertices = set()

        edges = []

        # Get all unique vertices and edges from the graph
        for edge in graph:
            vertices.add(edge[0])
            vertices.add(edge[1])
            edges.append(edge)

        # Create an empty incidence matrix
        incidence_matrix = [[0] * len(edges) for _ in range(len(vertices))]

        # Fill in the incidence matrix
        for i, vertex in enumerate(vertices):
            for j, edge in enumerate(edges):
                if vertex == edge[0]:
                    incidence_matrix[i][j] = 1
                elif vertex == edge[1]:
                    incidence_matrix[i][j] = 1

        return incidence_matrix

    def adjacency_matrix(self, matrix):
        copy_matrix = matrix.copy()
        copy_matrix.pop(0)
        for i in range(len(copy_matrix)):
            for j in range(len(copy_matrix[i])):
                if copy_matrix[i][j].isdigit:
                    copy_matrix[i][j] = int(copy_matrix[i][j])
        self.matrix = copy_matrix
        print('Adjacency matrix: ', self.matrix)

    def depth_first_search(self, graph, start):
        visited = set()
        stack = [start]

        while stack:
            vertex = stack.pop()
            if vertex not in visited:
                print(vertex, end=' ')
                visited.add(vertex)
                stack.extend([v for v, _ in graph[vertex]][::-1])

    def breadth_first_search(self, graph, start):
        visited = set()
        queue = deque([start])

        while queue:
            vertex = queue.popleft()
            if vertex not in visited:
                print(vertex, end=' ')
                visited.add(vertex)
                queue.extend(v for v, _ in graph[vertex])

    def adjacency_list(self):
        graph_adjacency = {}

        for edge in self.mygraph:
            source, target, weight = edge

            # Добавляем вершину source в список смежности
            if source not in graph_adjacency:
                graph_adjacency[source] = []
            graph_adjacency[source].append((target, weight))

            # Добавляем вершину target в список смежности
            if target not in graph_adjacency:
                graph_adjacency[target] = []
            graph_adjacency[target].append((source, weight))

        sorted_dict = {}

        for key in sorted(graph_adjacency.keys()):
            sorted_dict[key] = sorted(graph_adjacency[key], key=lambda x: x[0])

        self.mylist = sorted_dict

        print('Adjacency list: ', sorted_dict)

    def parsing(self, lines):
        # with open('testpy.txt', 'r') as file:
        #     lines = file.readlines()
        matrix = [line.strip().split() for line in lines]  # разделить каждую строку на отдельные элементы
        n = len(matrix)  # определить размер матрицы
        self.adjacency_matrix(matrix)
        edges = []
        for i in range(1, n):
            for j in range(i, n - 1):
                if matrix[i][j] != '0':
                    edges.append((matrix[0][i - 1], matrix[0][j], int(matrix[i][j])))
        edges = self.sort(edges)
        self.mygraph = edges

    def sort(self, lst):
        for i in range(len(lst) - 1, 0, -1):
            for j in range(i):
                if lst[j][2] > lst[j + 1][2]:
                    lst[j], lst[j + 1] = lst[j + 1], lst[j]
        return lst

    def algorithm_kruskal(self):
        parent = defaultdict(lambda: None)
        rank = defaultdict(lambda: 0)

        def find(x):
            if parent[x] is None:
                return x
            parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            root_x = find(x)
            root_y = find(y)
            if root_x != root_y:
                if rank[root_x] < rank[root_y]:
                    parent[root_x] = root_y
                else:
                    parent[root_y] = root_x
                    if rank[root_x] == rank[root_y]:
                        rank[root_x] += 1

        for item in self.mygraph:
            if find(item[0]) != find(item[1]):
                union(item[0], item[1])
                self.answer.append(item)

        return self.answer

    # def algorithm_kraskal(self):
    #     check = []
    #     for item in self.mygraph:
    #         if(item[0] not in check or item[1] not in check):
    #             check.append(item[0])
    #             check.append(item[1])
    #             self.answer.append(item)

    def cout(self):
        for i in self.answer:
            print(i[0], i[1])
        print(sum(edge[2] for edge in self.answer))

