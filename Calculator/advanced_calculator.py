from stack import Stack
from simple_calculator import SimpleCalculator


def calculate1(tokens):
    operators = {'+': 1, '-': 1, '*': 2, '/': 2}
    values = Stack()
    operator_stack = Stack()

    def perform_operation():
        b = values.pop()
        a = values.pop()
        op = operator_stack.pop()
        if op == '+':
            result = a + b
        elif op == '-':
            result = a - b
        elif op == '*':
            result = a * b
        elif op == '/':
            result = a / b
        values.push(result)

    for token in tokens:
        if token == '(' or token == '{':
            operator_stack.push(token)
        elif token.isdigit():
            values.push(int(token))
        elif token in operators.keys():
            if len(operator_stack) > 0 and operator_stack.peek() not in '{(':
                while (len(operator_stack) > 0 and operator_stack.peek() not in '{('
                       and operators[token] <= operators[operator_stack.peek()]):
                    perform_operation()
                operator_stack.push(token)
            else:
                operator_stack.push(token)
        elif token in '})':
            while operator_stack.peek() not in '({':
                perform_operation()
            operator_stack.pop()

    while len(operator_stack) > 0:
        perform_operation()
    return values.peek()
def tokenize1(input_expression):
    tokens = []
    current_token = ''

    for char in input_expression:
        if char in ' /*-+(){}':
            if len(current_token) > 0:
                tokens.append(current_token)
                current_token = ''
            if char != ' ':
                if char in '-+':
                    if len(tokens) == 0 or tokens[-1] in '({':
                        tokens.append('0')
                    tokens.append(char)
                else:
                    tokens.append(char)
        else:
            current_token += char

    if len(current_token) > 0:
        tokens.append(current_token)

    return tokens
def tokenize2(input_expression):
    tokens = []
    current_token = ''

    for char in input_expression:
        if char in ' /*-+(){}':
            if len(current_token) > 0:
                tokens.append(current_token)
                current_token = ''
            if char != ' ':
                if char in '-+':
                    if len(tokens) == 0 or tokens[-1] in '({':
                        tokens.append('0')
                    tokens.append(char)
                else:
                    tokens.append(char)
        else:
            current_token += char

    if len(current_token) > 0:
        tokens.append(int(current_token))

    return tokens
def calculate2(tokens):
    operators = {'+': 1, '-': 1, '*': 2, '/': 2}
    values = Stack()
    operator_stack = Stack()

    def perform_operation():
        b = values.pop()
        a = values.pop()
        op = operator_stack.pop()
        if op == '+':
            result = a + b
        elif op == '-':
            result = a - b
        elif op == '*':
            result = a * b
        elif op == '/':
            result = a / b
        values.push(result)

    for token in tokens:
        if token == '(' or token == '{':
            operator_stack.push(token)
        elif str(token).isdigit():
            values.push(token)
        elif token in operators.keys():
            if len(operator_stack) > 0 and operator_stack.peek() not in '{(':
                while (len(operator_stack) > 0 and operator_stack.peek() not in '{('
                       and operators[token] <= operators[operator_stack.peek()]):
                    perform_operation()
                operator_stack.push(token)
            else:
                operator_stack.push(token)
        elif token in '})':
            while operator_stack.peek() not in '({':
                perform_operation()
            operator_stack.pop()

    while len(operator_stack) > 0:
        perform_operation()
    return values.peek()
def check_brackets3(tokens):
    brackets = ""
    for token in tokens:
        if str(token) in '(){}':
            brackets += str(token)

    def is_matching(i, j):
        return (i == '{' and j == '}') or (i == '(' and j == ')')

    def check_balanced(t):
        stack = Stack()

        for token in t:
            if token == '(':
                stack.push(token)
            elif token == '{':
                if stack.peek() == '(':
                    return False
                elif stack.peek() == '{' or stack.is_empty():
                    stack.push(token)
            else:
                if is_matching(stack.peek(), token):
                    stack.pop()
                else:
                    return False
        return len(stack) == 0

    return check_balanced(brackets)
class AdvancedCalculator(SimpleCalculator):

    def _init_(self):
        self.history = []

    def evaluate_expression(self, input_expression):
        result = None
        if check_brackets3(input_expression):
            try:
                result = calculate1(tokenize1(input_expression))
            except:
                result = 'Error'
        else:
            result = 'Error'

        self.history.append((input_expression, result))

        if result == 'Error':
            return 'Error'
        else:
            return float(result)

    def tokenize(self, input_expression):
        return tokenize2(input_expression)
    def check_brackets(self, list_tokens):
        return check_brackets3(list_tokens)
    def evaluate_list_tokens(self, list_tokens):
        result = None

        if check_brackets3(list_tokens):
            try:
                result = calculate2(list_tokens)
            except:
                result = 'Error'
        else:
            result = 'Error'

        self.history.append((list_tokens, result))

        if result == 'Error':
            return 'Error'
        else:
            return float(result)

    def get_history(self):
        return self.history

