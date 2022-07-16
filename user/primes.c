#include "kernel/types.h"
#include "user/user.h"

#define INT_LEN sizeof(int)

int primes_helper(int div,int *last_p){
    close(last_p[1]);
    int num;
    int p[2];

    if(read(last_p[0],&num,INT_LEN)==INT_LEN){
    fprintf(1,"prime %d\n",num);

    pipe(p);

    if(fork()==0){ 
        primes_helper(div+1,p);
    }else{
        while(read(last_p[0],&num,INT_LEN)){
            if(num%div!=0){ 
                write(p[1],&num,INT_LEN);
            }
        }
        close(p[1]);
        close(last_p[0]);
        wait(0);
    }
    }
    exit(0);
}

int main(int argc, char *argv[]){
    fprintf(1,"prime 2\n",2);
    int num=2;
    int div=2;
    int p[2];
    pipe(p);
    if(fork()==0){ 
        read(p[0],&num,INT_LEN);
        fprintf(1,"prime %d\n",num);
        primes_helper(div+1,p);
    }else{
        while(num<=35){
            if(num%div!=0){ 
                write(p[1],&num,INT_LEN);
            }
            num++;
        }
        close(p[1]);
        close(p[0]);
        wait(0);
    }
    exit(0);
}