def welcomeForStudent
	puts "welcome to the student system"
end
def welcomeForTeacher
	puts "welcome to the teacher system"
end
class Student
	@@num_student = 0
	def initialize(name,gpa,numbers)
		@student_name = name
		@student_gpa = gpa
		@student_numbers = numbers
	end
	def display_details()
		puts "student name is #@student_name"
		puts "student gpa is #@student_gpa"
		puts "student numbers is #@student_numbers"
	end
	def studentPlus()
		@@num_student+=1
	end
	def putStudentNum()
		puts @@num_student
	end
end
class Teacher < Student
	@@num_teacher = 0
	def initialize(name,nums)
		@teacher_name = name
		@teacher_nums = nums
	end
	def display_details()
		puts "teacher's name is #@teacher_name"
		puts "teacher's nums is #@teacher_nums"
	end
	def teacherPlus()
		@@num_teacher+=1
	end
	def change(Student student_para,name,gpa)
		if student_para.name==@@student_name
			@@student_name = name
			@@student_gpa = gpa
		end	
	end
end
lbt = Student.new(lbt,4.0,0101)
lbt.studentPlus()
yy = Student.new(yy,2.5,0311)
yy.studentPlus()
yxy = Teacher.new(yxy,0000)
yxy.teacherPlus()
para = 0
while para != -1
	para = gets.chomp
	puts "are you a student or teacher?"
	inst = gets.chomp
	if inst == "Student"
		welcomeForStudent
		lbt.display_details
		yy.display_details
	else if inst == "Teacher"
		welcomeForTeacher
		yxy.display_details
		puts "whether u need to change someone's gpa"
		para1 = gets.chomp
		if(para1 != -1)
			name1 = gets.chomp
			gpa1 = gets.chomp
			yxy.change(yy,name1,gpa1)
			yy.display_details
			name2 = gets.chomp
			gpa2 = gets.chomp
			yxy.change(lbt,name2,gpa2)
			lbt.display_details
		end
	else puts "fault input"
	end
puts "num of student is #@@num_student"
end