#include <stdio.h>
#include <signal.h>
#include <string.h>

int waitSignal = 0;

struct sigaction {
    void (*sa_handler)(int);
    void (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};

void handler(int signum, siginfo_t * siginfo, void * notuse)
{
    printf("%s, value %d is received\n", strsignal(signum), signum);
    waitSignal = 1;
}

siginfo_t {
    int si_signo;
    int si_errno;
    int si_code;
    int si_trapno;
    pid_t si_pid;
    uid_t si_uid;
    int si_status;
    clock_t si_utime;
    clock_t si_stime;
    sigval_t si_value;
    int si_int;
    void *si_ptr;
    int si_overrun;
    int si_timerid;
    void *si_addr;
    long si_band;
    int si_fd;
    short si_addr_lsb;
}

int main(void)
{
    struct sigaction act;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGINT);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handler;
    act.sa_mask = set;
    sigaction(SIGUSR1, &act, NULL);
    printf("This is my pid: %d\n", getpid());

    while(!waitSignal) {
        sleep(3);
    }
return 0;
}