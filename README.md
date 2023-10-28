# 리눅스 키로거 프로그램

### 실행 방법
```swift
gcc -o main keylogger.c
su
./main
```
이후 키보드에 입력하는 것들이 log 파일에 저장됩니다.  
**프로그램 종료는 Ctrl + C** 를 눌러 해주시면 됩니다.

##### NOTE
* readlink 명령어 : 심볼릭 링크가 연결되어 있는 파일의 경로를 가져온다.
* /dev/input/by-path 에서 전체 입력장치 볼 수 있다.
