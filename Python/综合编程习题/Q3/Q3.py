from collections import Counter

import re


def count_word():
    # 请补全代码
    # 导入re包\

    # 匹配字符串中是否含有数字，含有字母的话是[a-z]
    # pattern = re.compile('[0-9]+')
    # # findall是返回所有符合匹配的项，返回形式为数组
    # match = pattern.findall(station)
    # # if后加变量的意思是判断变量是否为空，不为空则为true，反之为false
    # if match:
    #     print('contain numbers')
    # else:
    #     print('no numbers')
    with open("./Q3.txt", "r") as f:
        readline = f.readlines()
        word = []  # 存储单词
        for line in readline:
            # 因为原文中每个单词都是用空格 或者逗号加空格分开的，
            line = line.replace(',', '')  # 除去逗号只要空格来分开单词
            line = line.replace('.', '')  # 除去逗号只要空格来分开单词
            line = line.strip()
            wo = line.split(' ')
            pattern = re.compile('[0-9]+')
            for i in wo:

                # match = pattern.findall(i)
                if pattern.findall(i) or i == '':
                    pass
                else:
                    word.append(i)
        print(len(word))


count_word()
