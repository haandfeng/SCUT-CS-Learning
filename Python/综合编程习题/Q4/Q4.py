import math


class BigNum(object):
    # 请补全代码

    def __init__(self, num):
        self.num = str(num)
        self.arr = []
        if self.num[0] == '-':
            self.sign = "-"
            if len(self.num) > 21:
                self.num = "-inf"
            else:
                for i in self.num:
                    if i == "-":
                        pass
                    else:
                        self.arr.append(int(i))
        else:
            self.sign = "+"
            if len(self.num) > 20:
                self.num = "inf"
            else:
                for i in self.num:
                    self.arr.append(int(i))

    def __str__(self):
        return self.num

    def __add__(self, other):
        # 反转两个列表
        array1 = self.arr[::-1]
        array2 = other.arr[::-1]
        if self.sign == '-' and other.sign == '+':
            ans = other - self
            return ans
        if self.sign == '+' and other.sign == '-':
            ans = self - other
            return ans
        if self.sign == other.sign:
            if len(array1) <= len(array2):  # 两种情况，第一种：1的长度小于2的长度，第二种情况反过来。
                # 新建立一个与较长长度一致的全为0的列表
                ans = [0 for x in range(len(array2) + 1)]
                # 把较短的列表后面全添加上0使长度与较长的列表一致
                for i in range(len(array2) - len(array1)):
                    array1.append(int(0))
            else:
                ans = [0 for x in range(len(array1) + 1)]
                for i in range(len(array1) - len(array2)):
                    array2.append(int(0))
            # 让对应的位相加
            for i in range(len(ans) - 1):
                ans[i] += array1[i] + array2[i]
                if ans[i] >= 10:  # 如果和大于10，则保留个位数值，并进位
                    ans[i] -= 10
                    ans[i + 1] += 1
            # 把结果列表反转
            ans = ans[::-1]
            i = 0
            # 0不要
            while ans[i] == 0:
                i += 1
            if self.sign == "-":
                ans1 = "-"
            else:
                ans1 = ""
            for j in ans[i:]:
                ans1 += str(j)
            # ans1=str(ans)
        return BigNum(ans1)

    def __sub__(self, other):

        if self.sign == '-' and other.sign == '+':
            other.sign = '-'
            ans = self + other
            other.sign = "+"
            return ans
        if self.sign == '+' and other.sign == '-':
            other.sign = '+'
            ans = self + other
            other.sign = "-"
            return ans
        if self.sign == other.sign:
            a = BigNum(self.num)
            b = BigNum(other.num)
            ans = []
            flag = '+'
            if a.sign == '-':
                a.num = a.num.strip('-')
                b.num = b.num.strip('-')
            if a.comp(b) == 1 and a.sign == '-':
                s = a
                a = b
                b = s
                flag = '+'
            # 如果a<b
            elif a.comp(b) == -1:
                if a.sign != '-':
                    s = a
                    a = b
                    b = s
                flag = "-"
            elif a.comp(b) == 0:
                return 0
            # 从末尾开始相减
            for i in range(len(b.num)):
                flag_a = len(a.num) - 1 - i
                flag_b = len(b.num) - 1 - i
                if a.arr[flag_a] >= b.arr[flag_b]:
                    # a的第i位大于b
                    ans.append(a.arr[flag_a] - b.arr[flag_b])
                else:
                    # a的第i位小于b
                    ans.append(10 + a.arr[flag_a] - b.arr[flag_b])
                    while a.arr[flag_a - 1] == 0:
                        a.arr[flag_a - 1] = 9
                        flag_a -= 1
                    a.arr[flag_a - 1] -= 1

            # 把多余的位置加进来
            for j in range(len(a.num) - len(b.num) - 1, -1, -1):
                ans.append(a.arr[j])
            ans = ans[::-1]
            if flag == '-':
                ans1 = '-'
            else:
                ans1 = ''
            # 判断是不是0，是的话要删除前置0
            zero_flag = 0
            for i in range(len(ans)):
                if ans[i] != 0:
                    zero_flag = 1
                    break
                else:
                    del ans[i]
            if zero_flag == 0:
                return BigNum('0')

            for j in ans[:]:
                ans1 += str(j)
        return BigNum(ans1)

    def comp(self, other):
        if self.sign == '-' and other.sign == '-':
            if len(self.arr) < len(other.arr):
                return 1
            if len(self.arr) > len(other.arr):
                return -1
            if len(self.arr) == len(other.arr):
                for i in range(len(self.arr)):
                    if self.arr[i] > other.arr[i]:
                        return -1
                    if self.arr[i] < other.arr[i]:
                        return 1
                    if i == (len(self.arr) - 1):
                        if self.arr[i] == other.arr[i]:
                            return 0
        elif self.sign == '+' and other.sign == '+':
            if len(self.arr) < len(other.arr):
                return -1
            if len(self.arr) > len(other.arr):
                return 1
            if len(self.arr) == len(other.arr):
                for i in range(len(self.arr)):
                    if self.arr[i] > other.arr[i]:
                        return 1
                    if self.arr[i] < other.arr[i]:
                        return -1
                    if i == (len(self.arr) - 1):
                        if self.arr[i] == other.arr[i]:
                            return 0
        elif self.sign == "+" and other.sign == "-":
            return 1
        else:
            return -1


a = BigNum(99)
b = BigNum(999)
c = BigNum(-99999999999999999999)
d = BigNum(99999999999999999999)
print(b + a)
print(a - b)
print(a.comp(b))
print(b.comp(a))
print(a.comp(a))

print(c)
print(a)
print(c - a)
print(d + a)
