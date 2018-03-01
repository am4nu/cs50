import cs50
from stu import Student
studentList=[]

for i in  range(2):
    
    
    print("name",end=":")
    name=cs50.get_string()
    
    print("dorm",end=":")
    dorm=cs50.get_string()
    
    
    
    studentList.append(Student(name,dorm))


for i in studentList:
    print("{} is in {}".format(i.name,i.dorm))

