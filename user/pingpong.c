#include "kernel/types.h"
#include "user/user.h"

#define RD 0
#define WR 1

int main(int argc, char *argv[]) {
  int p_c2d[2];
  int p_d2c[2];
  int pid;
  char buf[12];
  pipe(p_d2c);
  pipe(p_c2d);

  if ((pid = fork()) == 0) {
    read(p_d2c[0], buf, 12);
    fprintf(1, "%d: received ping\n", pid);
    write(p_c2d[1], "hi, dad!", 12);

  } else {
    write(p_d2c[1], "hi, child!", 12);
    read(p_c2d[0], buf, 12);
    fprintf(1, "%d: received pong\n", pid);
  }
  exit(0);
}