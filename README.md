# TCP-IP-2024
소켓 프로그래밍

## 1일차
- 네트워크 프로그래밍
    - 네트워크로 연결되어 있는 서로 다른 두 컴퓨터가 데이터를 주고받을 수 있도록 하는 것

- 소말리아 : 서버를 만들기위한 함수
    - Socket 함수
    ``` c
    int socket(int domain, int type, int protocol);
    // 성공 1, 실패 -1
    // 소켓 함수가 소켓을 생성
    ```
    
    
    - bind 함수
    ``` c
    int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
    // 성공 0 실패 -1
    // 생성된 소켓에 IP와 Port정보 할당
    ```
        
    
    - listen 함수
    ``` c
    int listen(int sockfd, int backlog)
    // 성공 0 실패 -1
    // 클라이언트에서 연결요청을 할 수 있는 상태가 되게한다.
    ```
        

    - accept 함수
    ``` c
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    //성공 파일디스크립터, 실패 -1
    //  연결요청에 대한 수락을 의미. accept함수를 통새서 요청을 수락한다.
    ```
        

- connect 함수 : 클라이언트
    - 클라이언트 프로그램에서는 socket 함수 호출을 통한 소켓 생성과 connect 함수 호출을 통한 연결 요청 과정이 존재한다.

    ``` c
    int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
    // 성공 0, 실패 -1
    ```

- 컴파일 및 실행
    - gcc hello_server.c -o hserver
        - hello_server.c 파일을 컴파일 해서 hserver라는 이름의 실행파일을 만드는 문장
    - ./hserver
        - 현재 디렉토리에 있는 hserver라는 이름의 파일을 실행 시키는 문장


## 2일차
- 프로토콜
    - 컴퓨터 상호간 대화에 필요한 통신규약
    - 쉽게 말해 데이터를 주고 받기위해서 정의해놓은 약속을 뜻한다

- socket 함수 
``` c
    int socket(int domain, int type, int protocol);
    // 1. domain : 프로토콜 체계
    // 2. type : 소켓의 타입
    // 3.. protocol : 0    
    ```
1. 첫번째 인자 : 프로토콜 체계
    - 다양하지만 PF_INET와 PF_INET6만 알아두자
    - PF_INET은 IPv4를 의미하고 PF_INET6는 IPv6다.
2. 두번째 인자 : 소켓의 타입
    - SOCK_STREAM
        - 연결지향형 소켓이다.
        - TCP
    - SOCK_DGRAM
        - 비연결지향형 소켓이다.
        -UDP
3. 세번째 인자
    - 일단 얘는 0을 쓴다고 알고 있자

