class Person:
	def __init__(self, name, surname, mark=1):
		self.name = name
		self.surname = surname
		self.mark = mark
		
	def __del__(self):
		pattern = "Ви отримали стипендію {:s} {:s}"
		print(pattern.format(self.name, self.surname))
		
	def info(self):
		pattern = "(Ім'я: {:s}, Прізвище: {:s}, Оцінка: {:d})"
		return pattern.format(self.name, self.surname, self.mark)
		

def show_some_group():
	group = [Person("Сергій", "Левчик", 10),
			Person("Іван", "Богун"),
			Person("Катерина", "Осача", 11)]

	for student in group:
		print(student.info())
		

show_some_group()
input()