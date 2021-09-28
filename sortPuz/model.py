import json

class InvalidStackIdException(Exception):
    """ Stack of input index does not exist """

class Stack:
    
    EMPTY_COLOR = "-"

    def __init__(self, elements, size):
        self.s = elements
        self.size = size

    @property
    def top(self):
        return self.s[-1]

    def set(self):
        return set(self.s)
    
    def append(self, e):
        if len(self.s) < self.size:
            self.s.append(e)

    def pop(self):
        return self.s.pop()

    def __repr__(self):
        tube = self.s + [Stack.EMPTY_COLOR for i in range(self.size - len(self.s))]
        return " ".join(tube)

    def __len__(self):
        return len(self.s)

    def __getitem__(self, index):
        return self.s[index]

class Board():

    @staticmethod
    def create(object_dict:dict) -> "Board":

        board_data = json.loads(object_dict)

        stack_size = board_data["stack_size"]
        stack_count = len(board_data["stacks"])

        stacks = []

        for i in range(stack_count):
            elements = board_data["stacks"][i]
            stacks.append(Stack(elements, stack_size))

        b = Board(
            stack_size=stack_size,
            stacks=stacks,
            helpers_count=board_data["helpers"]
        )

        return b

    def __init__(self, stack_size, stacks, helpers_count):

        self.stack_size = stack_size
        self.helpers_count = helpers_count

        self.stacks = stacks
        for i in range(helpers_count):
            self.stacks.append(Stack())

    def move(self, pick_stack, drop_stack):
    
        while pick_stack and len(drop_stack) < self.stack_size:

            drop_stack.append(pick_stack.pop())
            if pick_stack and pick_stack.top != drop_stack.top:
                break

    def stack_fully_sorted(self, stack_index):

        s = self.stacks[stack_index]
        if (not s) or (len(s) == self.stack_size and len(s.set()) == 1):
            return True

        return False

    def stack_partly_sorted(self, stack_index):

        s = self.stacks[stack_index]
        if len(s.set()) == 1:
            return True

        return False

    def is_sorted(self):

        for i in range(len(self.stacks)):

            if not self.stack_fully_sorted(i):
                return False

        return True

    def __repr__(self):
        
        res = ""

        for i, stack in enumerate(self.stacks):
            res += f"{i}: [ {stack} ] #{len(stack)}" + "\n"

        return res

class Game():

    def __init__(self, level):
        
        f = open(f"boards/{level}.json").read()
        self.level = level
        self.board = Board.create(f)
    
    def play(self):
        moves = []

        while True:
            print(self.board)
            pick, drop = map(int, input("pick, drop :").split(" "))

            self.board.move(
                self.board.stacks[pick], 
                self.board.stacks[drop]
            )

            moves.append({"pick": pick, "drop": drop})

            if self.board.is_sorted():
                print(self.board)
                print("Game!")
                break