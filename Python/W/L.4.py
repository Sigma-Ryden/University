import math
import random as rand
from functools import reduce

def task_1():
	A = [22, 33, 44, 55, 66]

	X = list(map((lambda x: x * 5), A))
	
	print(X)


def task_2():
	N = 5
	A = [5, 6, 7, 8, 9]
	B = [3, 4, 5, 8, N]
	
	X = list(map(math.pow, A, B))
	
	print(X)


def task_3():
	N = 5
	L = [
	lambda n: n + N,
	lambda n: math.pow(n, 3),
	lambda n: n - 1,
	lambda n: math.pow(n, 5)
	]
	
	for f in L:
		print(f(N + 2))


def task_4():
	A = list(range(-15, 15))
	N = 5
	
	X = list(filter((lambda x: x < N), A))


def task_5():
	N = 5
	A = [12, 34, 45, 66, N]
	sum = reduce((lambda x, y: x + y), A)
	product = reduce((lambda x, y: x * y), A)
	
	print(sum, product)

def fibonacci(n):
	Fl, Fr = 0, 1
	for _ in range(n):
		Fl, Fr = Fr, Fl + Fr
		
	return Fl
	
def task_6():
	N = 5
	print(fibonacci(10 + N))


def accumulate_fibonacci(n):
	Fl, Fr = 0, 1
	sum = Fl
	for _ in range(n):
		Fl, Fr = Fr, Fl + Fr
		sum += Fl
		
	return sum
	
def task_7():
	N = 5
	print(accumulate_fibonacci(10 + N))


def factorial(n):
	product = 1
	while n > 0:
		product *= n
		n -= 1
		
	return product
	
def task_8():
	N = 5
	print(factorial(10 + N))


def task_9():
	N = 5
	L = [
	lambda n: n * N,
	lambda n: math.pow(n, 6),
	lambda n: n - 2,
	lambda n: math.pow(n, 2)
	]

	for f in L:
		print(f(N + 3))


task_1()
task_2()
task_3()
task_4()
task_5()
task_6()
task_7()
task_8()
task_9()