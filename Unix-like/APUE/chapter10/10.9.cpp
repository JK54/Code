#include "chapter10.h"
#include <iostream>

using std::cout;
using std::endl;

void pr_mask(const char *str)
{
    sigset_t cur_mask;
    //without sigemptyset,the sigset get from current signal mask will contain unknown signal num
    sigemptyset(&cur_mask);
    // but add set before get current signal mask won't affect the signal mask.
    // sigaddset(&cur_mask, SIGBUS);
    int errno_save = errno;
    if (sigprocmask(0, nullptr, &cur_mask) < 0)
    {
        perror("");
        return;
    }
    printf("%s\n", str);
    while(!sigisemptyset(&cur_mask))
    {
        if(sigismember(&cur_mask,SIGABRT))
        {
            cout << strsignal(SIGABRT) << endl;
            sigdelset(&cur_mask, SIGABRT);
        }
        else if(sigismember(&cur_mask,SIGALRM))
        {
            cout << strsignal(SIGALRM) << endl;
            sigdelset(&cur_mask, SIGALRM);
        }        
        else if(sigismember(&cur_mask,SIGBUS))
        {
            cout << strsignal(SIGBUS) << endl;
            sigdelset(&cur_mask, SIGBUS);
        }        
        else if(sigismember(&cur_mask,SIGCHLD))
        {
            cout << strsignal(SIGCHLD) << endl;
            sigdelset(&cur_mask, SIGCHLD);
        }         
        else if(sigismember(&cur_mask,SIGCONT))
        {
            cout << strsignal(SIGCONT) << endl;
            sigdelset(&cur_mask, SIGCONT);
        }
        else if(sigismember(&cur_mask,SIGFPE))
        {
            cout << strsignal(SIGFPE) << endl;
            sigdelset(&cur_mask, SIGFPE);
        }
        else if(sigismember(&cur_mask,SIGHUP))
        {
            cout << strsignal(SIGHUP) << endl;
            sigdelset(&cur_mask, SIGHUP);
        }
        else if(sigismember(&cur_mask,SIGILL))
        {
            cout << strsignal(SIGILL) << endl;
            sigdelset(&cur_mask, SIGILL);
        }
        else if(sigismember(&cur_mask,SIGINT))
        {
            cout << strsignal(SIGINT) << endl;
            sigdelset(&cur_mask, SIGINT);
        }
        else if(sigismember(&cur_mask,SIGIO))
        {
            cout << strsignal(SIGIO) << endl;
            sigdelset(&cur_mask, SIGIO);
        }
        else if(sigismember(&cur_mask,SIGIOT))
        {
            cout << strsignal(SIGIOT) << endl;
            sigdelset(&cur_mask, SIGIOT);
        }
/*         else if(sigismember(&cur_mask,SIGKILL)) */
        // {
            // cout << strsignal(SIGKILL) << endl;
            // sigdelset(&cur_mask, SIGKILL);
        /* } */
        else if(sigismember(&cur_mask,SIGPIPE))
        {
            cout << strsignal(SIGPIPE) << endl;
            sigdelset(&cur_mask, SIGPIPE);
        }
        else if(sigismember(&cur_mask,SIGPOLL))
        {
            cout << strsignal(SIGPOLL) << endl;
            sigdelset(&cur_mask, SIGPOLL);
        }
        else if(sigismember(&cur_mask,SIGPROF))
        {
            cout << strsignal(SIGPROF) << endl;
            sigdelset(&cur_mask, SIGPROF);
        }
        else if(sigismember(&cur_mask,SIGPWR))
        {
            cout << strsignal(SIGPWR) << endl;
            sigdelset(&cur_mask, SIGPWR);
        }
        else if(sigismember(&cur_mask,SIGQUIT))
        {
            cout << strsignal(SIGQUIT) << endl;
            sigdelset(&cur_mask, SIGQUIT);
        }
        else if(sigismember(&cur_mask,SIGSEGV))
        {
            cout << strsignal(SIGSEGV) << endl;
            sigdelset(&cur_mask, SIGSEGV);
        }
        else if(sigismember(&cur_mask,SIGSTKFLT))
        {
            cout << strsignal(SIGSTKFLT) << endl;
            sigdelset(&cur_mask, SIGSTKFLT);
        }
/*         else if(sigismember(&cur_mask,SIGSTOP)) */
        // {
            // cout << strsignal(SIGSTOP) << endl;
            // sigdelset(&cur_mask, SIGSTOP);
        /* } */
        else if(sigismember(&cur_mask,SIGSYS))
        {
            cout << strsignal(SIGSYS) << endl;
            sigdelset(&cur_mask, SIGSYS);
        }
        else if(sigismember(&cur_mask,SIGTERM))
        {
            cout << strsignal(SIGTERM) << endl;
            sigdelset(&cur_mask, SIGTERM);
        }
        else if(sigismember(&cur_mask,SIGTRAP))
        {
            cout << strsignal(SIGTRAP) << endl;
            sigdelset(&cur_mask, SIGTRAP);
        }
        else if(sigismember(&cur_mask,SIGTSTP))
        {
            cout << strsignal(SIGTSTP) << endl;
            sigdelset(&cur_mask, SIGTSTP);
        }
        else if(sigismember(&cur_mask,SIGTTIN))
        {
            cout << strsignal(SIGTTIN) << endl;
            sigdelset(&cur_mask, SIGTTIN);
        }
        else if(sigismember(&cur_mask,SIGTTOU))
        {
            cout << strsignal(SIGTTOU) << endl;
            sigdelset(&cur_mask, SIGTTOU);
        }
        else if(sigismember(&cur_mask,SIGURG))
        {
            cout << strsignal(SIGURG) << endl;
            sigdelset(&cur_mask, SIGURG);
        }
        else if(sigismember(&cur_mask,SIGUSR1))
        {
            cout << strsignal(SIGUSR1) << endl;
            sigdelset(&cur_mask, SIGUSR1);
        }
        else if(sigismember(&cur_mask,SIGUSR2))
        {
            cout << strsignal(SIGUSR2) << endl;
            sigdelset(&cur_mask, SIGUSR2);
        }
        else if(sigismember(&cur_mask,SIGVTALRM))
        {
            cout << strsignal(SIGVTALRM) << endl;
            sigdelset(&cur_mask, SIGVTALRM);
        }
        else if(sigismember(&cur_mask,SIGWINCH))
        {
            cout << strsignal(SIGWINCH) << endl;
            sigdelset(&cur_mask, SIGWINCH);
        }
        else if(sigismember(&cur_mask,SIGXCPU))
        {
            cout << strsignal(SIGXCPU) << endl;
            sigdelset(&cur_mask, SIGXCPU);
        }
        else if(sigismember(&cur_mask,SIGXFSZ))
        {
            cout << strsignal(SIGXFSZ) << endl;
            sigdelset(&cur_mask, SIGXFSZ);
        }
        else
        {
            cout << "Unknown signal num" << endl;
            return;
        }
    }
    errno = errno_save;
}

int main()
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGUSR1);
    sigaddset(&sigset, SIGTERM);
    sigaddset(&sigset, SIGURG);
    sigaddset(&sigset, SIGKILL);
    sigprocmask(SIG_SETMASK, &sigset, nullptr);
    pr_mask("test");
}
