import math
import random as rand

def float_generator():
	return rand.random()
	
def random_fill_arr(arr, generator):
	for i in range(len(arr)):
		arr[i] = generator()
	
	return arr
	
def p(y, arr):
	result = 0
	for i in range(len(arr)):
		result += arr[i] * math.pow(y, i)
		
	return result
	
def task_1():
	a = [0] * 7 # fix size
	random_fill_arr(a, float_generator)
	
	arr_x = [1, 3, 4]
	for x in arr_x:
		result = p(x, a) + p(x + 1, a)
		print(result)
	

def task_2():
	a = [0] * 13
	random_fill_arr(a, float_generator)
	
	s = rand.random()
	t = rand.random()
	x = float(input('Enter value of the x: '))
	
	result = p(1, a) - p(t, a) + p(s - t, a) - p(t, a)
	print(result)


# x^2+2x+1=0 => (x+1)^2=0 => x=-1
# x^2-4x+4=0 => (x-2)^2=0 => x=2
def task_3():
	X = -1
	Y = 2
	Z = (X+Y)/(X-Y) # 1/(-3)
	print(Z)
	

def is_less(a, b):
	return 1 if a < b else 0
	
def is_bigger(a, b):
	return not is_less(a, b)

def find_matrix_idx(matrix, predicate):
	hold_i = 0
	hold_j = 0
	
	for i in range(len(matrix)):
		for j in range(len(matrix[i])):
			it = matrix[i][j]
			if predicate(matrix[hold_i][hold_j], it):
				hold_i = i
				hold_j = j
	
	return (hold_i, hold_j)
			
def random_fill_matrix(matrix, generator):
	for arr in matrix:
		random_fill_arr(arr, generator)
	
	return matrix

def task_4():
	A = 4 * [5 * [0]]
	B = 5 * [3 * [0]]
	
	random_fill_matrix(A, float_generator)
	random_fill_matrix(B, float_generator)
	
	C = [A, B]
	
	for matrix in C:
		(min_i, min_j) = find_matrix_idx(matrix, is_bigger)
		(max_i, max_j) = find_matrix_idx(matrix, is_less)
		
		print(matrix)
		
		msg = 'matrix[{:d}][{:d}]: {:f}'
		print('min' + msg.format(min_i, min_j, matrix[min_i][min_j]))
		print('max' + msg.format(max_i, max_j, matrix[max_i][max_j]))
		

def accumulate_arr(arr):
	result = 0
	for i in arr:
		result += i
		
	return result

def random_integer_in_range(min, max):
	return int(rand.random() * (max - min + 1) + min)

def integer_generator():
	return random_integer_in_range(-10, 10)
	
def task_5():
	N = random_integer_in_range(1, 10)
	M = random_integer_in_range(1, 10)
	X = [0] * N
	Y = [0] * M
	
	random_fill_arr(X, integer_generator)
	random_fill_arr(Y, integer_generator)
	
	(s1, k1) = (accumulate_arr(X), len(X))
	(s2, k2) = (accumulate_arr(Y), len(Y))
	
	result = (s1 + s2) / (k1 + k2)
	print(result)


def task_6():
	N = 3 * [6 * [0]]
	random_fill_matrix(N, integer_generator)
	
	for row in N:
		for col in row:
			if col % 3 == 0:
				print(col)
	

def arr_filter(arr, condition):
	out = []
	for i in arr:
		if condition(i):
			out.append(i)
			
	return out

def is_negative(x):
	return x < 0
	
def is_positive(x):
	return not is_negative(x)
	
def task_7():
	X = [0] * 10
	Y = [0] * 15
	
	random_fill_arr(X, integer_generator)
	random_fill_arr(Y, integer_generator)
	
	positive_X = arr_filter(X, is_positive)
	negative_Y = arr_filter(Y, is_negative)
	
		
	(s1, k1) = (accumulate_arr(positive_X), len(positive_X))
	(s2, k2) = (accumulate_arr(negative_Y), len(negative_Y))
	
	result = (math.exp(s1)+ math.exp(s2)) / (k1 * k2)
	print(result)


def replace_if(arr, condition, pattern):
	for i in range(len(arr)):
		if condition(arr[i]):
			arr[i] = pattern
			
def task_8():
	X = [0] * 10
	Y = [0] * 15
	
	random_fill_arr(X, integer_generator)
	random_fill_arr(Y, integer_generator)
	
	X.sort()
	Y.sort()
	
	replace_if(X, is_negative, 0)
	replace_if(Y, is_negative, 0)
	
	
def find_arr_idx(arr, predicate):
	hold_i = 0
	
	for i in range(len(arr)):
		if predicate(arr[hold_i], arr[i]):
			hold_i = i
			
	return hold_i
	
def task_9():
	X = [0] * 10
	Y = [0] * 12
	
	random_fill_arr(X, float_generator)
	random_fill_arr(Y, float_generator)
	
	Xmax = X[find_arr_idx(X, is_less)]
	Ymin = Y[find_arr_idx(Y, is_bigger)]
	Z = (Xmax - Ymin) / 2
	
	
def matrix_filter(matrix, condition):
	out = []
	for arr in matrix:
		out.append(arr_filter(arr, condition))
		
	return out
	
def accumulate_matrix(matrix):
	result = 0
	for arr in matrix:
		result += accumulate_arr(arr)
		
	return result
	
def task_10():
	A = 5 * [6 * [0]]
	B = 4 * [3 * [0]]
	
	random_fill_matrix(A, integer_generator)
	random_fill_matrix(B, integer_generator)
	
	positiveA = matrix_filter(A, is_positive)
	positiveB = matrix_filter(B, is_positive)
	
	sum_positiveA = accumulate_matrix(A)
	sum_positiveB = accumulate_matrix(B)
	

def task_11():
	A = 5 * [5 * [0]]
	B = 4 * [5 * [0]]
	
	random_fill_matrix(A, float_generator)
	random_fill_matrix(B, float_generator)
	
		
	negativeA = matrix_filter(A, is_negative)
	negativeB = matrix_filter(B, is_negative)
	
	sum_negativeA = accumulate_matrix(A)
	sum_negativeB = accumulate_matrix(B)
	
def task_12():
	sequance_a = [0] * random_integer_in_range(1, 10)
	sequance_b = [0] * random_integer_in_range(1, 10)
	
	random_fill_arr(sequance_a, integer_generator)
	random_fill_arr(sequance_b, integer_generator)
	
	max_sequance_a_idx = find_arr_idx(sequance_a, is_less)
	max_sequance_b_idx = find_arr_idx(sequance_b, is_less)

	# bad - dublicate code
	for i in range(max_sequance_a_idx, len(sequance_a)):
		sequance_a[i] = 0.5
		
	for i in range(max_sequance_b_idx, len(sequance_b)):
		sequance_b[i] = 0.5


def subtask_13(arr, K):
	K_idx = 0
	has_K = 0
	
	for i in range(len(arr)):
		if arr[i] == K:
			K_idx = i
			has_K = 1
			break
	
	it = K_idx if has_K else find_arr_idx(arr, is_less)

	for i in range(it, len(arr)):
		arr[i] = K
	
def task_13():
	sequance_a = [0] * random_integer_in_range(1, 10)
	sequance_b = [0] * random_integer_in_range(1, 10)
	
	random_fill_arr(sequance_a, integer_generator)
	random_fill_arr(sequance_b, integer_generator)
	
	subtask_13(sequance_a, integer_generator())
	subtask_13(sequance_b, 10)
	
	
task_1()
task_2()
task_3()
task_4()
task_5()
task_6()
task_7()
task_8()
task_9()
task_10()
task_11()
task_12()
task_13()