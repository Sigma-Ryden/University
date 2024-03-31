import math

def task_1():
	question = 'Коли нарешті карантин? '
	answer = input(question)
	
	
def Z(x, t):
	a = (9*math.pi*t+10*math.cos(x))*math.exp(x)
	b = math.sqrt(t)-math.fabs(math.sin(t))
	
	return a/b

def task_2():
    result = Z(5, 1)
    print('Результат:', '{0:.2f}'.format(result))
    
    
def f_positive(x):
	return 0.5-math.pow(math.fabs(x), 1/4)
	
def f_negative(x):
	return (math.sin(x*x)**2)/math.fabs(x+1)
	
def f(x):
    return f_negative(x) if x < 0 else f_positive(x)
    
def task_3():
    x = int(input('Значення аргументу х: '))
    print('Результат:', f(x))
 
       
def is_in_range(begin, end, x):
	return x >= begin and x <= end
	
def select_in_range(begin, end, arr):
	for i in arr:
		if is_in_range(begin, end, i):
			print('Число', i, 'належить інтервалу', begin, ':', end)
			
def task_4():
	a1 = int(input('Введіть а1:'))
	a2 = int(input('Введіть a2:'))
	a3 = int(input('Введіть a3:'))
	
	arr = [a1, a2, a3]
	
	select_in_range(1, 5, arr)
	
	
def max(a, b, c):
	if a < b:
		a = b
	if a < c:
		a = c
		
	return a
	
def task_5():
	a = int(input('Введіть а:'))
	b = int(input('Введіть b:'))
	c = int(input('Введіть c:'))
	
	result = max(a, b, c)
	print('Максимальне число серед a, b та c:', result)
	
	
task_1()
task_2()
task_3()
task_4()
task_5()