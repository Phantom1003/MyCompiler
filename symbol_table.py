from CompilerError import *
class SymTab:
    def __init__(self):
        self.tables = []

    def pop(self):
        self.tables.pop()

    def create_tab(self):
        self.tables.append({})

    def find(self, name):
        for i in range(len(self.tables)-1, -1, -1):
            if name in self.tables[i]:
                return self.tables[i][name]
        return None

    def insert(self, entry):  # [name, ir_element]
        if entry[0] in self.tables[-1].keys():
            raise MultiDefinedError(("Duplicated symbol %s" % entry[0],))
        self.tables[-1][entry[0]] = {"entry": entry[1]}

    def insert_b(self, entry):  # {"name": name, "addr": addr, "const": const}
        if entry[0] in self.tables[-1].keys():
            raise MultiDefinedError(("Duplicated symbol %s" % entry[0],))
        for key in entry.keys():
            pass
        # self.tables[-1]

