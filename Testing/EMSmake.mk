Ems: user.o student.o pagemanager.o
	gcc user.o student.o pagemanager.o -o Ems
user.o: user.c student.h pagemanager.h
	gcc -c user.c
student.o: student.c
	gcc -c student.c
pagemanager.o: pagemanager.c
	gcc -c pagemanager.c

