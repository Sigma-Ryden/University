def task_1():
	L = 7
	pairs = [(a, b) for a in range(L) if a % 2 != 0
					for b in range(L) if b % 2 == 0]
					
	print(pairs)
	

def task_2():
	N = 5
	A = [[11, N, 44, 55],
		[1, 2, N, 4],
		[11, 12, 13, 14],
		[21, 31, 41, N]]
		
	M = [[1, 2, 3, 6],
		[4, 5, 6, 0],
		[7, 8, 9, 7],
		[71, 8, 93, 7]]
		
	# works only for square matrix
	main_diagonal = [A[i][i] for i in range(len(A))]
	side_diagonal = [A[-1-i][-1-i] for i in range(len(A))]
	
	second_column = [A[i][1] for i in range(len(A))]
	
	upper_matrix = [
		[A[i][j] + N for j in range( len(A[i]) )]
		for i in range(len(A))]
					 
	hadamard_product = [
		[A[i][j] * M[i][j] for j in range( len(A[i]) )]
		for i in range(len(A))]
										 
	print(main_diagonal)
	print(side_diagonal)
	print(second_column)
	
	print(upper_matrix)
	
	print(hadamard_product)
	
	
def generate_cube(N):
	for i in range(N):
		yield i ** 3

def task_3():
	N = 5
	for i in generate_cube(N):
		print(i, end=' ')


task_1()
task_2()
task_3()