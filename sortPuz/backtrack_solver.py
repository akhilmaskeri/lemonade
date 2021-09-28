from copy import deepcopy

STACK_SIZE = 4

snapshots = set()

def stack_fully_sorted(stacks, stack_index):

    s = stacks[stack_index]
    if (not s) or (len(s) == STACK_SIZE and len(set(s)) == 1):
        return True

    return False

def is_sorted(stacks):
    for i in range(len(stacks)):
        if not stack_fully_sorted(stacks, i):
            return False

    return True

def print_stack(stacks):
    for stack in stacks:
        print(f" [ { ' '.join(stack) } ] ")

def digest(stacks):
    return hash("".join(["".join(stack) for stack in stacks]))


def backtrack(stacks_):

    if is_sorted(stacks_):
        return True

    current_snapshot = digest(stacks_)
    if current_snapshot not in snapshots:
        snapshots.add(current_snapshot)

    stacks = deepcopy(stacks_)

    for i, stack in enumerate(stacks):
        if not stack or stack_fully_sorted(stacks, i):
            continue

        color = stack.pop()
        
        for j, other_stack in enumerate(stacks):
            if i == j or len(other_stack) == 4 or (other_stack and other_stack[-1] != color):
                continue

            other_stack.append(color)
            new_snapshot = digest(stacks)

            if not new_snapshot in snapshots and backtrack(stacks):
                print(f"moving color:{color} from {i} to {j}")
                # print_stack(stacks)
                return True
            other_stack.pop()

        stack.append(color)

    return False

stacks = [
    ["V", "B", "L", "P"],
    ["O", "B", "O", "R"],
    ["V", "Y", "P", "D"],
    ["O", "D", "V", "Y"],
    ["P", "L", "Y", "R"],
    ["D", "L", "V", "L"],
    ["B", "B", "D", "Y"],
    ["R", "R", "O", "P"],
    [],
    [],
]

print(backtrack(stacks))
