#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    char *ptr, **pptr;
    char str[INET_ADDRSTRLEN];
    struct hostent * hptr;

    while (--argc > 0)
    {
        ptr = *++argv;
        if ((hptr = gethostbyname(ptr)) == NULL)
        {
            fprintf(stderr, "gethostbyname error for host%s : %s",
                    ptr, hstrerror(h_errno));
            continue;
        }
        printf("official hostname %s\n", hptr->h_name);
        for (pptr = hptr->h_aliases; *pptr != NULL; ++pptr)
            printf("\talials: %s\n", *pptr);
        switch (hptr->h_addrtype)
        {
            case AF_INET:
                pptr = hptr->h_addr_list;
                for (; *pptr != NULL; ++pptr)
                    printf("\taddress: %s\n",
                            inet_ntop(hptr->h_addrtype, *pptr,
                                str, sizeof(str)));
                break;
            default:
                fprintf(stderr, "unknown address type");
                exit(EXIT_FAILURE);
                break;
        }
    }
    return 0;
}
