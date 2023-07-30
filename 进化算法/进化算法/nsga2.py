# Program Name: NSGA-II.py
# Description: This is a python implementation of Prof. Kalyanmoy Deb's popular NSGA-II algorithm
# Author: Haris Ali Khan
# Supervisor: Prof. Manoj Kumar Tiwari
"""
优化目标：
    min（f1(x), f2(x))
        f1(x) = -x^2
        f2(X) = -(x-2)^2
    s.t x~[-55, 55]
pop_size = 20
max_gen  =  921

"""
# Importing required modules
import math
import random
import matplotlib.pyplot as plt
import numpy as np


# First function to optimize
def function1(x):
    value = -x ** 2
    return value


# Second function to optimize
def function2(x):
    value = -(x - 2) ** 2
    return value


# 返回list中某个元素的方程
def index_of(a, list):
    for i in range(0, len(list)):
        if list[i] == a:
            return i
    return -1


# Function to sort by values
# list1 是 list of index值 values 是list of value
# 这个方程是对list1的index进行排序,根据value的大小
def sort_by_values(list1, values):
    sorted_list = []
    while len(sorted_list) != len(list1):
        # 如果在前沿内，一个又一个最小值加进去，根据的是函数值的大小排序，但有一个前提是要在front前沿内
        if index_of(min(values), values) in list1:
            sorted_list.append(index_of(min(values), values))
        # 排完序之后变成无穷大
        values[index_of(min(values), values)] = math.inf
    return sorted_list


# 找到非支配解的排序   这里有两个方程，找两个解
def fast_non_dominated_sort(values1, values2):
    # 生成values个空集用来存values1每个支配的解
    S = [[] for i in range(0, len(values1))]
    # 前沿
    front = [[]]
    # 等级n
    n = [0 for i in range(0, len(values1))]
    rank = [0 for i in range(0, len(values1))]
    # 判断p是不是非支配解
    for p in range(0, len(values1)):
        S[p] = []
        n[p] = 0
        for q in range(0, len(values1)):
            # 如果p支配q
            if (values1[p] > values1[q] and values2[p] > values2[q]) or \
                    (values1[p] >= values1[q] and values2[p] > values2[q]) or \
                    (values1[p] > values1[q] and values2[p] >= values2[q]):
                # 如果q不在集合内，q进入p支配的集合
                if q not in S[p]:
                    # S
                    S[p].append(q)
            # 如果q支配p
            elif (values1[q] > values1[p] and values2[q] > values2[p]) or \
                    (values1[q] >= values1[p] and values2[q] > values2[p]) or \
                    (values1[q] > values1[p] and values2[q] >= values2[p]):
                # p的n+1
                n[p] = n[p] + 1
        # 如果np=0
        if n[p] == 0:
            # rank p =0
            rank[p] = 0
            # front的集合加上p，如果p不再前沿内
            if p not in front[0]:
                front[0].append(p)

    i = 0
    while front[i]:
        Q = []
        for p in front[i]:
            # 发现自己被支配了，自己的n-1，减去了i次那个他的rank就是i+1
            for q in S[p]:
                n[q] = n[q] - 1
                if n[q] == 0:
                    rank[q] = i + 1
                    if q not in Q:
                        # 加入下一轮前沿
                        Q.append(q)
        i = i + 1
        front.append(Q)

    del front[len(front) - 1]
    return front


def mfast_non_dominated_sort(values1):
    # 解集是一个二维数据[[1 2 3],[1 2 3],[1 2 3],[1 2 3]] 表示了有4个方程 3组解  1111 2222 3333
    values1 = np.array(values1)
    dim = []
    # 先求出values的个个维度有多少数
    for i in range(len(values1.shape)):
        dim.append(values1.shape[i])
    # 每一代解生成一个集合
    S = [[] for i in range(dim[1])]
    front = [[]]
    n = [0 for i in range(dim[1])]
    rank = [0 for i in range(dim[1])]
    # 每一个p都和他的所有子代比
    for p in range(dim[1]):
        for q in range(dim[1]):
            # 用来数数，看看大于了多少次的
            countg = 0
            # 用来数数，看看等于了多少次的
            counte = 0
            # 用来用来数数，看看等于了多少次的
            countl = 0
            for i in range(dim[0]):
                if values1[i][p] > values1[i][q]:
                    countg = countg + 1
                elif values1[i][p] == values1[i][q]:
                    counte = counte + 1
                # 数小于了多少次
                else:
                    countl = countl + 1
            # 如果存在一个大于，其他都是等于的情况
            if countg + counte == dim[0] and countg != 0:
                # S支配的解的集合集加入第q组解的index q
                if q not in S[p]:
                    S[p].append(q)
            elif countl + counte == dim[0] and countl != 0:
                # 如果被支配，那么排序+1
                n[p] = n[p] + 1
            # 其他情况无事发生

        # 如果是完全非支配，加入解集
        if n[p] == 0:
            # 给出了p的排名
            rank[p] = 0
            # 防止完全一样的情况,index加入第一轮前沿
            front[0].append(p)

    # 当第i级前沿不为空
    i = 0
    while front[i]:
        Q = []
        for p in front[i]:
            for q in S[p]:
                n[q] = n[q] - 1
                if n[q] == 0:
                    rank[q] = i + 1
                    Q.append(q)
        i = i + 1
        front.append(Q)
    # 最后一个是空则删掉
    del front[len(front) - 1]
    return front


# Function to calculate crowding distance
def crowding_distance(values1, values2, front):
    distance = [0 for i in range(0, len(front))]
    sorted1 = sort_by_values(front, values1[:])
    sorted2 = sort_by_values(front, values2[:])
    distance[0] = 4444444444444444
    distance[len(front) - 1] = 4444444444444444
    for k in range(1, len(front) - 1):
        distance[k] = distance[k] + (values1[sorted1[k + 1]] - values2[sorted1[k - 1]]) / (max(values1) - min(values1))
    for k in range(1, len(front) - 1):
        distance[k] = distance[k] + (values1[sorted2[k + 1]] - values2[sorted2[k - 1]]) / (max(values2) - min(values2))
    return distance


# 算的是每一个前沿的之间各点的距离大小
def mcrowding_distance(values1, front):
    # 算记录
    distance = [0 for i in range(0, len(front))]
    # 解集是一个二维数据[[1 2 3],[1 2 3],[1 2 3],[1 2 3]] 表示了有4个方程 3组解  1111 2222 3333
    values1 = np.array(values1)
    dim = []
    # 先求出values的个个维度有多少数
    for i in range(len(values1.shape)):
        dim.append(values1.shape[i])
    # 有几个方程，就有几个集合
    asorted = [[] for i in range(dim[0])]
    # 返回的是每一个方程的数的从小到大index
    for i in range(dim[0]):
        asorted[i] = sort_by_values(front, values1[i][:])
    #     初始化到正无穷
    distance[0] = 4444444444444444
    distance[len(front) - 1] = 4444444444444444
    for i in range(dim[0]):
        for k in range(1, len(front) - 1):
            distance[k] = distance[k] + (values1[i][asorted[i][k + 1]] - values1[i][asorted[i][k - 1]]) / max(
                values1[i]) - min(values1[i])
    return distance

# Function to carry out the crossover
def crossover(a, b):
    r = random.random()
    if r > 0.5:
        return mutation((a + b) / 2)
    else:
        return mutation((a - b) / 2)


# Function to carry out the mutation operator
def mutation(solution):
    mutation_prob = random.random()
    if mutation_prob < 1:
        solution = min_x + (max_x - min_x) * random.random()
    return solution


# Main program starts here
pop_size = 20
max_gen = 921

# Initialization
min_x = -55
max_x = 55
# 随机生成初始种群
solution = [min_x + (max_x - min_x) * random.random() for i in range(0, pop_size)]
gen_no = 0
while gen_no < max_gen:
    # 自适应度计算
    function1_values = [function1(solution[i]) for i in range(0, pop_size)]
    function2_values = [function2(solution[i]) for i in range(0, pop_size)]
    fv = [function1_values[:], function2_values[:]]
    # pareto等级
    non_dominated_sorted_solution = mfast_non_dominated_sort(fv[:][:])
    print("The best front for Generation number ", gen_no, " is")
    for valuez in non_dominated_sorted_solution[0]:
        print(round(solution[valuez], 3), end=" ")
    print("\n")
    # 拥挤度距离计算
    crowding_distance_values = []
    for i in range(0, len(non_dominated_sorted_solution)):
        crowding_distance_values.append(
            mcrowding_distance(fv[:][:], non_dominated_sorted_solution[i][:]))
    solution2 = solution[:]  # P+Q
    # Generating offsprings
    while len(solution2) != 2 * pop_size:
        a1 = random.randint(0, pop_size - 1)
        b1 = random.randint(0, pop_size - 1)
        # 交叉变异
        solution2.append(crossover(solution[a1], solution[b1]))
    # 计算 P+Q种群的适应度
    function1_values2 = [function1(solution2[i]) for i in range(0, 2 * pop_size)]
    function2_values2 = [function2(solution2[i]) for i in range(0, 2 * pop_size)]
    fv2 = [function1_values2[:], function2_values2[:]]
    # 非支配排序
    non_dominated_sorted_solution2 = mfast_non_dominated_sort(fv2[:])
    # 拥挤度距离计算
    crowding_distance_values2 = []
    for i in range(0, len(non_dominated_sorted_solution2)):
        crowding_distance_values2.append(
            mcrowding_distance(fv2[:], non_dominated_sorted_solution2[i][:]))
    # 得到下一代种群P1
    new_solution = []  # index
    for i in range(0, len(non_dominated_sorted_solution2)):
        non_dominated_sorted_solution2_1 = [
            index_of(non_dominated_sorted_solution2[i][j], non_dominated_sorted_solution2[i]) for j in
            range(0, len(non_dominated_sorted_solution2[i]))]
        front22 = sort_by_values(non_dominated_sorted_solution2_1[:], crowding_distance_values2[i][:])
        front = [non_dominated_sorted_solution2[i][front22[j]] for j in
                 range(0, len(non_dominated_sorted_solution2[i]))]
        front.reverse()
        for value in front:
            new_solution.append(value)
            if len(new_solution) == pop_size:
                break
        if len(new_solution) == pop_size:
            break
    solution = [solution2[i] for i in new_solution]
    gen_no = gen_no + 1

# Lets plot the final front now
function1 = [i * -1 for i in function1_values]
function2 = [j * -1 for j in function2_values]
plt.xlabel('Function 1', fontsize=15)
plt.ylabel('Function 2', fontsize=15)
plt.scatter(function1, function2)
plt.show()
