class BPlusTree:
    def __init__(self, order=3):
        self.order = order
        self.root = BPlusTreeNode(order=order)

    def insert(self, key, value):
        self.root.insert(key, value)

    def search(self, key):
        return self.root.search(key)

    def traverse(self):
        self.root.traverse()


class BPlusTreeNode:
    def __init__(self, order):
        self.order = order
        self.keys = []
        self.values = []
        self.children = []

    def insert(self, key, value):
        index = 0
        while index < len(self.keys) and key > self.keys[index]:
            index += 1

        if len(self.children) > 0:
            child = self.children[index]
            child.insert(key, value)
        else:
            self.keys.insert(index, key)
            self.values.insert(index, value)

        if len(self.keys) > self.order:
            self.split()

    def split(self):
        middle = len(self.keys) // 2
        left_node = BPlusTreeNode(self.order)
        right_node = BPlusTreeNode(self.order)

        left_node.keys = self.keys[:middle]
        left_node.values = self.values[:middle]
        right_node.keys = self.keys[middle:]
        right_node.values = self.values[middle:]

        if len(self.children) > 0:
            left_node.children = self.children[:middle + 1]
            right_node.children = self.children[middle + 1:]

        self.keys = [left_node.keys[-1]]
        self.values = [left_node.values[-1]]
        self.children = [left_node, right_node]

    def search(self, key):
        index = 0
        while index < len(self.keys) and key > self.keys[index]:
            index += 1

        if len(self.children) > 0:
            return self.children[index].search(key)
        else:
            return self.values[index]

    def traverse(self):
        for child in self.children:
            child.traverse()
        for value in self.values:
            print(value)



