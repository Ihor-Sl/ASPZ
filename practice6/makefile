CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-O2 -Wall -UDEBUG
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra -DDEBUG

CFLAGS_DBG_ASAN=${CFLAGS_DBG} -fsanitize=address
CFLAGS_DBG_MSAN=${CFLAGS_DBG} -fsanitize=memory
CFLAGS_DBG_UB=${CFLAGS_DBG} -fsanitize=undefined

mem_issues_dbg_asan.o: mem_issues.c
	${CL} ${CFLAGS_DBG_ASAN} -c mem_issues.c -o mem_issues_dbg_asan.o

mem_issues_dbg_asan: mem_issues_dbg_asan.o
	${CL} ${CFLAGS_DBG_ASAN} -o mem_issues_dbg_asan mem_issues_dbg_asan.o

mem_issues_dbg_ub.o: mem_issues.c
	${CL} ${CFLAGS_DBG_UB} -c mem_issues.c -o mem_issues_dbg_ub.o

mem_issues_dbg_ub: mem_issues_dbg_ub.o
	${CL} ${CFLAGS_DBG_UB} -o mem_issues_dbg_ub mem_issues_dbg_ub.o

mem_issues_dbg_msan.o: mem_issues.c
	${CL} ${CFLAGS_DBG_MSAN} -c mem_issues.c -o mem_issues_dbg_msan.o

mem_issues_dbg_msan: mem_issues_dbg_msan.o
	${CL} ${CFLAGS_DBG_MSAN} -o mem_issues_dbg_msan mem_issues_dbg_msan.o
