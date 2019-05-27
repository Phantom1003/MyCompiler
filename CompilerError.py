class MultiDefinedError(BaseException):
    def __init__(self, args):
        self.args = args


class NotDefinedError(BaseException):
    def __init__(self, args):
        self.args = args


class SplTypeError(BaseException):
    def __init__(self, args):
        self.args = args


class OpError(BaseException):
    def __init__(self, args):
        self.args = args


class ExpressionError(BaseException):
    def __init__(self, args):
        self.args = args