#include "oneElementStack.h"

#define PLAIN_CODE 1
#define COMMENT_MULTI_LINE 2    /**/
#define COMMENT_SINGLE_LINE 3   //
#define IN_STRING 4
#define IN_CHAR 5

int main(int argc, char *argv[]) {
  int c, state;
  state = PLAIN_CODE;
  while((c = getchar()) != EOF) {
    if(state == COMMENT_SINGLE_LINE) {
      if(c == '\n') {
        state = PLAIN_CODE;
        putchar(c);
      }
    } else if(state == COMMENT_MULTI_LINE) {
      if(c == '*')
        add(c);
      else if(value() == '*') {
        if(c == '/')
          state = PLAIN_CODE;
        delete();
      }
    } else if(c == '/' && state == PLAIN_CODE) {
      add(c);
      if((c = getchar()) == '/') {
        state = COMMENT_SINGLE_LINE;
        delete();
      } else if(c == '*') {
        state = COMMENT_MULTI_LINE;
        delete();
      } else {
        putchar(delete());
        if(c != EOF)
          putchar(c);
      }
    } else if(c == '"' && state != IN_CHAR) {
      if(state == PLAIN_CODE)
        state = IN_STRING;
      else if(value() == '\\')
        delete();
      else /* state == IN_STRING && value != '\\' */
        state = PLAIN_CODE;
      putchar(c);
    } else if(c == '\'' && state != IN_STRING) {
      if(state == PLAIN_CODE)
        state = IN_CHAR;
      else if(value() == '\\')
        delete();
      else
        state = PLAIN_CODE;
      putchar(c);
    } else if(c == '\\' && (state == IN_STRING || state == IN_CHAR)) {
      if(value() == '\\') /* "\\" or '\\' */
        delete();
      else
        add(c);
      putchar(c);
    } else {
      putchar(c);
      if(value() == '\\' && state == IN_STRING)   /* test 14 -->  printf("\'"); // aaa  <-- */
        delete();
    }
  }
  return 0;
}