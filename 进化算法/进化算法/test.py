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


pop_size = 100
max_gen = 2

# Initialization
min_x = -55
max_x = 55
# 随机生成初始种群
solution = [min_x + (max_x - min_x) * random.random() for i in range(0, pop_size)]
gen_no = 0
function1_values = [function1(solution[i]) for i in range(0, pop_size)]
function2_values = [function2(solution[i]) for i in range(0, pop_size)]
# pareto等级
function_values = [function1_values, function2_values]
print(function_values)
non_dominated_sorted_solution = mfast_non_dominated_sort(function_values[:])
print(non_dominated_sorted_solution)
non_dominated_sorted_solution = fast_non_dominated_sort(function1_values[:], function2_values[:])
print(non_dominated_sorted_solution)