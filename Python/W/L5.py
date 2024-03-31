import random as rand
from copy import deepcopy

def example_matrix():
	N = 5
	return [[1, 7, N], [8, N, 29], [N, 2, 4]]
	
def print_matrix(matrix, padding):
	for arr in matrix:
		for i in arr:
			print(i, end=padding)
			
		#print(end=('\n' * 3))
		print()
		
def task_1():
	A = example_matrix()
	print_matrix(A, ' ' * 3)


def for_all(x):
	return 1
	
def fill_matrix(matrix, generator, condition):
	for i in range(len(matrix)):
		for j in range(len(matrix[i])):
			if condition(matrix[i][j]):
				matrix[i][j] = generator()

def task_2():
	A = example_matrix()
	fill_matrix(A, (lambda: 9), for_all)
			
	print(A)
	
	
def task_4():
	A = example_matrix()
	
	print(A)
	
	min_item = A[0][1]
	for i in range(1, len(A)):
		it = A[i][1]
		if min_item > it:
			min_item = it
	
	print('min item at 2 column:', min_item)	


def task_5():
	A = example_matrix()
	
	print(A)
	
	min_item = A[2][0]
	for j in range(1, len(A[2])):
		it = A[2][j]
		if min_item > it:
			min_item = it
	
	print('min item at 3 row:', min_item)	
	

def integer_generator():
	return int(rand.random() * 16 - 5)
	
def create_matrix(rows, cols):
	return [cols * [0] for i in range(rows)]
	
def task_6():
	m = 4
	n = 3
	A = create_matrix(m, n)
	
	fill_matrix(A, integer_generator, for_all)
	
	B = deepcopy(A)
	fill_matrix(B, (lambda: 1), (lambda i: i >= 0))
	fill_matrix(B, (lambda: 0), (lambda i: i < 0))
	
	print(A)
	print(B)
	
	
def task_9():
	N = 6
	A = create_matrix(N, N)
	fill_matrix(A, integer_generator, for_all)
	
	row = 2
	col = 1
	hold = A[row][col]
	
	for n in range(N):
		A[n][col] = 0
		A[row][n] = 0
		
	A[row][col] = hold
	
	print_matrix(A, ' ')
	
	
def arr_item_idx(arr, compare):
	hold_idx = 0
	for i in range(1, len(arr)):
		if compare(arr[hold_idx], arr[i]):
			hold_idx = i
			
	return hold_idx
	
def task_10():
	N = 10
	A = create_matrix(N, N)
	fill_matrix(A, integer_generator, for_all)
	
	is_less = lambda a, b: a < b
	max_item_idx = lambda arr: arr_item_idx(arr, is_less)
	
	max_items_sum = 0
	for arr in A:
		max_items_sum += arr[max_item_idx(arr)]

	print_matrix(A, ' ')
	print('sum of max items:', max_items_sum)
	

def task_11():
	N = 6
	A = create_matrix(N, N)

	for i in range(1, N):
		for j in range(0, i):
			A[i][j] = 0
			
	for i in range(N):
		inc = 1
		for j in range(i, N):
			A[i][j] = inc
			inc += 1
			
	print_matrix(A, ' ')


task_1()
task_2()
task_4()
task_5()
task_6()
task_9()
task_10()
task_11()