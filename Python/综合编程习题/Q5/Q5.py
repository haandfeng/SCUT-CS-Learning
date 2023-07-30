import csv
from collections import Counter

with open("data.csv", "r", encoding='UTF-8-sig') as f:
    counts3 = {}
    numbers = {}
    n = 0
    reader = csv.DictReader(f)
    for row in reader:
        row['人均价格'] = int(row['人均价格'].replace('￥', ""))
        if not row['评分'] in counts3.keys():
            counts3[row['评分']] = 0
            numbers[row['评分']] = 0
        counts3[row['评分']] = row['人均价格'] + counts3[row['评分']]
        numbers[row['评分']] += 1
    for k in counts3.keys():
        counts3[k] /= numbers[k]
    counts3 = sorted(counts3.items(), key=lambda kv: (kv[1], kv[0]))
    with open('不同评分的餐厅人均价格平均值.csv', 'wt') as f2:
        cw = csv.writer(f2)
        for item in counts3:
            cw.writerow(item)
