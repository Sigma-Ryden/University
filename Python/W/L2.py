import math

def is_palindrom(s):
	mid = len(s)//2
	
	for i in range(mid):
		if s[i]!=s[-i-1]:
			return 0
			
	return 1
	
def task_1():
	print('Result:', is_palindrom('ab s ba'))
	

def example_str():
	return 'Hello, World!'
	
	
def to_upper_case(s):
	return s.upper()
	
def task_2():
	s = example_str()
	print(to_upper_case(s))
	
	
def to_lower_case(s):
    return s.lower()
    
def task_3():
	s = example_str()
	print(to_lower_case(s))


def to_title_format(s):
	text = s.split(' ')
	s = ''
	for word in text:
		s += word.title() + ' '
		
	return s
		
def task_4():
	print(to_title_format('Hi, my name is Bixy!'))
	

def replace_char_from_to(s, c_from, c_to):
	return s.replace(c_from, c_to)
	
def task_5():
	s = 'речь идет о геодезических куполах'
	print(replace_char_from_to(s, 'а', 'о'))
	
	
def example_arr():
	return [-1,3,0,4,9, -5,3,2,8,7, -6,2,3,1,-3]


def task_6():
	X = example_arr()
	M = int(input('Enter M: '))
	
	Y = []
	for i in X:
	    if math.fabs(i) > M:
	    	Y.append(i)
	    	
	print('X:', X)
	print('Y:', Y)
	
	
def as_positive(arr):
	for i in range(len(arr)):
		if arr[i] < 0:
			arr[i] = -arr[i]
			
	return arr
	
def task_7():
	arr = example_arr()
	
	print('arr:', arr)
	print('Positive arr:', as_positive(arr))


def max_item(arr):
	max_idx = 0
	
	for i in range(len(arr)):
		if arr[max_idx] < arr[i]:
		    max_idx = i

	return arr[max_idx]

def task_8():
	arr = []
	n = 10 + 5
	for i in range(n):
		msg = 'Enter arr[' + str(i) + ']: '
		var = int(input(msg))
		arr.append(var)
		
	arr.reverse()
	print('arr:', arr)
	print('max:', max_item(arr))


def handbook():
	return [['Group-1', ['Student-11', 'Student-13']],
	['Group-2', ['Student-21', 'Student-22']],
	['Group-3', ['Student-32', 'Student-34', 'Student-35']]]
	
def handbook_students(group_name):
	list = handbook()
	for group in list:
		if group[0] == group_name:
			return group[1]
	
	return []
	
def task_9():
	group_name = 'Group-2'
	students = handbook_students(group_name)
	
	width = 32
	print(group_name.center(width, ' '))
	for s in students:
		print(s.center(width, ' '))
	
	
def task_10():
	a = int(input('Enter a: '))
	c = int(input('Enter c: '))
	
	sum = 0
	for i in range(a, c):
		if i % 2 != 0:
			sum += i
			
	print('Sum from', a, 'to', c, 'is equal to:', sum)
	
	
def task_11():
	s = input('Enter number: ')
	result = 1;
	for c in s:
		result *= int(c)
		
	print('Product of digits:', result)
	
	
def partial_by_7(number, parts):
	part = number % 7;
	for p in parts:
		if p == part:
			return 1
	
	return 0
	
def task_12():
	begin = 35
	end = 87+1
	
	parts = [1,2,5]
	arr = []
	
	while begin != end:
		if partial_by_7(begin, parts):
			arr.append(begin)
		
		begin += 1
		
	arr.reverse()
	print(arr)
	print('max:', max(arr))
	
	
def money_preset():
	return [1000,500,100,50,20,10,5,2,1]
	
def greed(money, preset):
	cash = []
	for i in range(len(preset)):
		ss = preset[i]
		while money >= ss:
			money -= ss
			cash.append(ss)
			
	return cash
		
def task_13():
	money = int(input('Enter money: '))
	print('Cash:', greed(money, money_preset()))
	
	
def merge(X, Y):
	Z = X
	Z.extend(Y)
	Z.sort()
	return Z;
	
def task_14():
	X = [0,2,7,-3,4]
	Y = [-1,6,5]
	
	print('X:', X)
	print('Y:', Y)
	print('Merge X and Y:', merge(X, Y))
	

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
task_14()