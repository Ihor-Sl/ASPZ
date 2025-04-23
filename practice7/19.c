#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/user.h>
#include <libprocstat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    struct procstat *prstat;
    struct kinfo_proc *p;
    struct filestat_list *head;
    struct filestat *fst;
    unsigned int cnt;

    prstat = procstat_open_sysctl();
    if (prstat == NULL) {
        perror("procstat_open_sysctl");
        exit(EXIT_FAILURE);
    }

    p = procstat_getprocs(prstat, KERN_PROC_PROC, 0, &cnt);
    if (p == NULL) {
        perror("procstat_getprocs");
        procstat_close(prstat);
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < cnt; i++) {
        head = procstat_getfiles(prstat, &p[i], 0);
        if (head == NULL) continue;

        STAILQ_FOREACH(fst, head, next) {
            if (fst->fs_path != NULL)
                printf("PID %d -> %s\n", p[i].ki_pid, fst->fs_path);
        }

        procstat_freefiles(prstat, head);
    }

    procstat_freeprocs(prstat, p);
    procstat_close(prstat);
    return 0;
}
