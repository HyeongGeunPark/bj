/*#pragma GCC optimize("O3")*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char* RBUF;
char* rp;
char* rpb;
char* rpe;

char* string;
char* sp;
char* streak;
char* strp;

static inline int is_char(char* p) {
  return (*p <= '9' && *p >= '0') || (*p <= 'z' && *p >= 'a') ||
         (*p <= 'Z' && *p >= 'A');
}

static inline size_t mymmap() {
  struct stat stat;
  fstat(STDIN_FILENO, &stat);
  RBUF = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
  rp = RBUF;
  return stat.st_size;
}

int main(void) {
  char bomb[40];
  size_t bomblen;
  size_t stringlen;
  size_t filesize;
  size_t st;
  filesize = mymmap();
  string = malloc(1000009 * sizeof(char));
  sp = string + 1;
  streak = malloc(1000009 * sizeof(char));
  strp = streak + 1;
  streak[0] = 0;

  rp = RBUF + filesize - 1;
  while (!is_char(rp)) {
    rp--;
  }
  rpe = rp;
  while (is_char(rp)) {
    rp--;
  }
  bomblen = rpe - rp;
  memcpy(bomb, rp + 1, bomblen);
  while (!is_char(rp)) {
    rp--;
  }
  rpe = rp + 1;
  while (!is_char(RBUF)) {
    RBUF++;
  }
  rpb = rp = RBUF;
  st = 0;

  /*    printf("%s %ld\n%s %ld\n", RBUF, rpe-rp, bomb, bomblen);*/

  while (rp < rpe) {
    if (*rp != bomb[st]) {
      if (st != 0) {
        st = 0;
        continue;
      }
      rpb = rp;
      while (*rp != bomb[0] && rp < rpe) {
        rp++;
      }
      memcpy(sp, rpb, rp - rpb);
      sp += (rp - rpb);
      strp += (rp - rpb);
      *(strp - 1) = 0;
      rpb = rp;
    }
    // compare
    while (st < bomblen && rp < rpe) {
      if (*rp == bomb[st]) {
        *(sp++) = *(rp++);
        *(strp++) = (++st);
      } else {
        break;
      }
    }
    if (st == bomblen) {
      sp -= bomblen;
      strp -= bomblen;
      st = *(strp - 1);
    }
  }

  *sp = '\n';
  if (sp == string + 1) {
    write(STDOUT_FILENO, "FRULA\n", 6);
  } else {
    fwrite(string + 1, sizeof(char), sp - string - 1, stdout);
    /*        write(STDOUT_FILENO, string+1, sp-string);*/
  }

  free(string);
  free(streak);

  return 0;
}
