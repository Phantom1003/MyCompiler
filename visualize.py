from graphviz import Digraph
from random import randint

class Viz:
    def __init__(self, root=None):
        self.dot = Digraph("AST")
        self.count = 0
        if root:
            self.build(root)

    def build(self, root):
        stack = [(root, self.count)]
        self.dot.node(str(self.count), root.type)
        self.count += 1
        while len(stack) > 0:
            current, last_id = stack.pop(0)
            for child in current.children:
                stack.append((child, self.count))
                if child.name != "":
                    self.dot.node(str(self.count), "%s : %s" % (child.type, child.name))
                else:
                    self.dot.node(str(self.count), child.type)
                self.dot.edge(str(last_id), str(self.count))
                self.count += 1


    def png(self):
        self.dot.format = 'png'
        self.dot.render('AST', view=True)
