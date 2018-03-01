import cs50
from stu import Student
import csv
studentList=[]

for i in  range(2):
    
    
    print("name",end=":")
    name=cs50.get_string()
    
    print("dorm",end=":")
    dorm=cs50.get_string()
    
    studentList.append(Student(name,dorm))

file=open("student.csv","w")
writer=csv.writer(file)

for i in studentList:
    writer.writerow((i.name,i.dorm))
    
file.close()