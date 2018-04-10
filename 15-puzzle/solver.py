
# huge respect to Ken'ichiro Takahashi and Orson Peters

import random

# idea is to use iterative deepning A* search

class Solver:

	def __init__(self,h,neighbours):

		self.h = h
		self.neighbours = neighbours
		self.found = object()

	def solve(self,root,is_goal,max_cost = None):
	
		self.is_goal = is_goal
		self.path = [root]
		self.is_in_path = {root}
		self.path_desc = []
		self.nodes_evaluated = 0

		bound = self.h(root)

		while True:
			t = self._search(0,bound)
			if t is self.found: 
				return self.path,self.path_desc,bound,self.nodes_evaluated
			if t is None:
				return None
			bound = t		

	def _search(self,g,bound):
		self.nodes_evaluated += 1

		node = self.path[-1]
		f = g + self.h(node)

		if f > bound:
			return f

		if self.is_goal(node):
			return self.found

		m = None
		for cost,n,desc in self.neighbours(node):
			if n in self.is_in_path: continue

			self.path.append(n)
			self.is_in_path.add(n)
			self.path_desc.append(desc)

			t = self._search(g+cost,bound)

			if t == self.found: return self.found
			if m is None or (t is not None and t < m): m = t

			self.path.pop()
			self.path_desc.pop()
			self.is_in_path.remove(n)

		return m


def board_neighbours():
	moves = []

	for gap in range(16):
		
		x , y = gap % 4 , gap / 4
		move = []

		if x > 0 : move.append(-1)
		if x < 3 : move.append(1)
		if y > 0 : move.append(-4)
		if y < 3 : move.append(4)

		moves.append(move)

	def get_neighbours(t):

		gap = t.index(0)
		l = list(t)

		for m in moves[gap]:
			
			l[gap] = l[gap+m]
			l[gap+m] = 0

			yield (1 , tuple(l) , (l[gap],m) )

			l[gap + m ] = l[gap]
			l[gap] = 0

	return get_neighbours

def display(board):

	for i in range(4):
		for j in range(4):
			if board[i*4 + j] == 0:
				print "__ ",
			elif board[i*4 + j] <= 9 :
				print " "+str(board[i*4 + j])+" ",
			else:
				print str(board[i*4 + j])+" ",
		print ""

def encode(board):
	r = 0

	for i in range(16):
		r |= board[i] << (3*i)

	return r

def wd():

	goal = [4,0,0,0,0,4,0,0,0,0,4,0,0,0,0,3]

	table = {}
	to_visit = [(goal,0,3)]

	while to_visit:
		
		board,cost,e = to_visit.pop(0)

		hash = encode(board)

		if hash in table : continue

		table[hash] = cost

		for d in [-1,1]:
			if 0 <= e+d < 4 :
				for c in range(4):
					if board[4*(e+d) + c] > 0:
						nboard = list(board)
						nboard[4*(e+d) +c ] -=1
						nboard[4*e + c ]+=1

						to_visit.append((tuple(nboard),cost+1,e+d))

	return table

def H(goal):
	
	h = wd()
	goals = {i : goal.index(i) for i in goal }

	def caluculate(p):
		ht = 0
		vt = 0
		d = 0

		for i,c in enumerate(p):
			
			if c == 0 : continue
			g = goals[c]

			xi,yi = i%4 , i / 4
			xg,yg = g%4 , g / 4

			ht += 1 << (3*(4*yi+yg))
			vt += 1 << (3*(4*xi+xg))

			if yg == yi :
				for k in range(i+1,i - i%4 + 4):
					if p[k] and goals[p[k]] / 4 == yi and goals[p[k]] < g:
						d += 2
			if xg == xi:
				for k in range(i+4, 16, 4):
					if p[k] and goals[p[k]] % 4 == xi and goals[p[k]] < g:
						d += 2
		d += h[ht] + h[vt]
		return d

	return caluculate

if __name__ == "__main__":

	final = (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0)

	print "enter the board"
	r1 = [int(i) for i in raw_input().split() ]
	r2 = [int(i) for i in raw_input().split() ]
	r3 = [int(i) for i in raw_input().split() ]
	r4 = [int(i) for i in raw_input().split() ]
	
 	
	board = tuple(r1+r2+r3+r4)

	is_goal = lambda p: p == final
	neighbours = board_neighbours()

	solver = Solver(H(final),neighbours)

	path,moves,cost,num_eval = solver.solve(board,is_goal,80)

	display(board)

	print("".join({-1: "L", 1: "R", -4: "U", 4: "D"}[move[1]] for move in moves))
