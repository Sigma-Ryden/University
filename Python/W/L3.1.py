import math
import random as rand

def example_list():
	return ['ccc','ddd','yyy','iii','ccc','dd']
	
def task_1():
	my_set = set('Hello, World!')


def task_2():
	v = example_list()
	s = set(v)

def example_set():
	return set(example_list())

def task_3():
	s = example_set()
	s_copy = s.copy()
	
	print(s_copy)
	
	
def task_4():
	s = example_set()
	s_length = len(s)
	
	print(s_length)
	
	
def task_5():
	a = set(['a','b','d','f'])
	b = set(['b','c','a'])
	
	c = a.intersection(b)
	
	print(a)
	print(b)
	print(c)
	
	
def task_6():
	s = example_set()
	s.add('xxx')
	
	print(s)

def task_7():
	s = example_set()
	s.discard('ccc') # or unsafe: s.remove('ccc')
	
	print(s)
	

def task_8():
	s = example_set()
	s.pop()
	
	print(s)
	
	
def task_9():
	s = example_set()
	s.clear()
	

x = 5

def task_10():
	global x
	x = math.pow(x, 4)
	
	print(x)
	
	
def digit_sum(number):
	sum = 0
	while number != 0:
		sum += number % 10
		number = number // 10
	
	return sum
	
def task_11():
	var = int(input('Enter number: '))
	
	print('Digit sum:', digit_sum(var))
	
	
def triangle_square(a, b, c):
	p = (a + b + c) / 2
	S = math.sqrt(p * (p - a) * (p - b) * (p - c))
	
	return S
	
def has_equal_items(arr):
	for i in range(len(arr) - 1):
		if arr[i] != arr[i + 1]:
			return 0
	
	return 1
			
def task_12():
	triangles_n = 3
	triangles = [3 * [0]] * triangles_n
	
	for triangle in triangles:
		for side in range(len(triangle)):
			triangle[side] = int(input('Enter triangle side: '))
			
		print() # println

	squares = []
	for triange in triangles:
		s = triangle_square(triange[0], triangle[1], triangle[2])
		squares.append(s)

	is_equal = has_equal_items(squares)
	s = 'All squares are ' + ('equal' if is_equal else 'not equal')
	print(s)
	

def task_13():
	X = []
	length = int(input('Enter array length: '))
	for i in range(length):
		msg = 'Enter array[' + str(i) + ']: '
		value = int(input(msg))
		X.append(value)
		
	Y = X.copy()
	
	temp = Y[-1]
	Y[-1] = Y[0]
	Y[0] = temp
	
	print('X:', X)
	print('Y:', Y)
	
	
def print_sum_and_average(arr):
	sum = 0
	for i in arr:
		sum += i
		
	avg = sum / len(arr)
	
	print('sum:', sum, 'avg:', avg)
	
	
def task_14():
	X = [1,2,-6,5,0]
	Y = [5,3,-2,-1]
	Z = [1,7,0,-7,3,2,9]
	
	D = [X, Y, Z]
	for arr in D:
		print_sum_and_average(arr)
	
	
def random_fill(arr, min, max):
	for i in range(len(arr)):
		result = rand.random() * (max - min + 1) + min
		arr[i] = int(result)
		
	return arr
	
def max_item(arr):
	max_idx = 0
	
	for i in range(len(arr)):
		if arr[max_idx] < arr[i]:
		    max_idx = i

	return arr[max_idx]
	
def task_15():
	arr = [0] * 16
	arr = random_fill(arr, -4, 4)
	
	max = max_item(arr)
	
	amplitude = 0.3 # better than 0.1
	near_max = max * (1 - amplitude)
	
	near_max_arr = []
	for i in arr:
		if i >= near_max:
			near_max_arr.append(i)
			
	print('arr:', arr)
	print('max item:', max)
	print('near max arr:', near_max_arr)
	
	
task_1()
task_2()
task_3()
task_4()
task_5()
task_6()
task_7()
task_8()
task_9()
task_9()
task_10()
task_11()
task_12()
task_13()
task_14()
task_15()