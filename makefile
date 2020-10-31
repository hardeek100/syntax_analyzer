#I would strongly recommend NOT changing any lines below except the CC and MYFILE lines.
#Before running this file, run the command:   module load gnu


EXECS=danc_parser

#Replace the g++ with gcc if using C
CC=gcc

#Replace with the name of your C or C++ source code file.
MYFILE=Hardik_Poudel_R11645072_Assignment4.c parser.c


all: ${EXECS}

${EXECS}: ${MYFILE}
	${CC} -o ${EXECS} ${MYFILE}

clean:
	rm -f ${EXECS}
