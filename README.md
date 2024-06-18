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

- bind 함수
``` c
    int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
    // 성공 0 실패 -1
    // 생성된 소켓에 IP와 Port정보 할당
```

1. 첫번째 인자에는 소켓을 만들때 그 파일디스크립터값을 담은 변수가 들어간다.
2. 두번째 인자
    - 함수 호출 전 sockaddr 구조체의 멤버를 각각 초기화 해준 후 인자로 넣어준다.
``` c
    struct sockaddr_in
    {
        sa_family_t sin_family; // 주소체계: 보통 IPv4를 의미하는 PF_INET을 많이 쓰는것 같다
        unint16_t sin_port; // 16비트 Port번호
        struct in_addr sin_addr; // 32비트 IP주소: 구조체의 멤버로 가지고있는 구조체의 멤버에다 넣어 준다.
        char sin_zero[8]; // 사용x
    }

    struct in_addr
    {
        in_addr_t s_addr; // 32비트 Ipv4 인터넷 주소
    }
```
3. 세번째 인자로는 구조체의 크기를 넣어준다. 보통 sizeof()를 쓴다


``` c
    //사용 예시
    memset(&servAddr, 0, sizeof(servAddr)); 
    servAddr.sin_family = AF_INET; // IPv4 쓰겠다
    servAddr.sin_addr.s_addr = inet_addr(argv[1]); // 입력받은 IP로 초기화 하는 모습
    servAddr.sin_port = htons(atoi(argv[2])); // 입력받은 Port번호 문자열을 정수형을 바꾼후 빅엔디안으로 쓰겠다는것 같음!
```

## 3일차
- listen 함수
``` c
    int listen(int sockfd, int backlog)
    // 성공 0 실패 -1
    // 클라이언트에서 연결요청을 할 수 있는 상태가 되게한다.
```

- bind 함수를 통해서 소켓에 주소까지 할당 했다면 , listen 함수를 통새 연결요청 대기상태로 들아간다.
- listen을 호출하면 클라이언트쪽에서 connect를 통해 연결 요청을 할 수 있다
- 두번째 인자는 클라이언트 대기큐 수이다.

- accept 함수
 ``` c
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    //성공 파일디스크립터, 실패 -1
    //  연결요청에 대한 수락을 의미. accept함수를 통새서 요청을 수락한다.
```
- accept 함수는 '연결요청 대기 큐에서 대기중인 클라이언트의 연결 요청을 수락하는 기능의 함수이다. 
- 데이터의 입출력에 사용할 소켓을 생성(clnt_sock변수), 이 소켓과 클라이언트와 소통한다.