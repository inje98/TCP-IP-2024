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

- lterative 기반 서버, 클라이언트 구현
    - 지금까지는 한 클라이언트의 요청에만 응답을 하고 바로 종료
    - 이젠 반복문을 통해 accept 함수를 반복 호출
    - echo_client.c 참조

## 4일차
- 소켓의 종료
    - TCP에선 연결과정보다 중요한 것이 종료과정. 종료과정은 명확해야 한다.
    - A와 B가 양방향 통신을 하고 있는 상황에서 close를 통해서 연결을 종료 --> B가 전송한걸 A가 반드시 수신해야 할 데이터라 할지라도 그냥 소멸되고 만다.
    - 두 호스트간 소켓이 연결되면, 각 호스트별로 입력 스트림과 출력 스트림이 형성된다. --> 두 스트림을 모두 끊는 것이 아니라 한쪽만 끊는것이 '우아한 종료(Half-close)'이다
        - Half-close를 위한 shutdown 함수
        ``` c
        int shutdown(int sock, int howto);
        // 성공0, 실패-1
        ```
        - 두번째 인자(howto)
            1. SHUT_RD  -> 입력 스트림 종료
            2. SHUT_WR -> 출력 스트림 종료
            3. SHUT_RDWR -> 입출력 스트림 종료

- DNS Server
    - IP주소와 도메인 이름 사이에서의 변환을 수행하는 시스템
- 소켓의 옵션
    - SOL_SOCKET
    - IPPROTO_IP
    - IPPROTO_TCP

## 5일차
- 다중접속 서버의 구현 방법
    1. 멀티프로세스 기반 서버 : 다수의 프로세스를 생성하는 방식으로 서비스 제공
    2. 멀티플렉싱 기반 서버 : 입출력 대상을 묶어서 관리하는 방식으로 서비스 제공
    3. 멀티쓰레딩 기반 서버 : 클라이언트 수만큼 쓰레드를 생성하는 방식으로 서비스 제공

- 멀티프로세스 기반 서버
    - 프로세스의 이해
        - 메모리 공간을 차지한 상태에서 실행중인 프로그램
    
    - fork 함수
    ``` c
        pid_t fork(void)
        // 성공 프로세스ID, 실패 -1
    ```
- fork 함수는 호출한 프로세스의 복사본을 생성
    - 부모 프로세스는 fork 함수의 반환값이 자식프로세스의 ID
    - 자식 프로세스는 fork 함수의 반환값이 0
- 좀비 프로세스
    - 프로세스가 생성되고 나서 할일을 다하면 사라져야 하는데 사라지지 않고 좀비가 되어 시스템의 중요한 리소스를 차지하기도 한다.
    - 해당 자식 프로세스를 생성한 부모 프로세스에게 exit 함수나 인자값이 return문의 반환값이 전달 되어야 한다
- 좀비 소멸
    - wait함수
    ``` c
        pid_t wait(int * statloc);
        // statloc에는 자식이 죽으면서 전달한값

        pid_t waitpid(pid_t pid, int * statloc, int options);
        // 성공 종료된 자식 프로세스의 ID, 실패 -1
    ```

- 시그널 함수
    ``` c
        void (*signal(int signo, void (*func)(int)))(int);
        /// 시그널 발생 시 호출되도록 이전에 등록된 함수의 포인터 반환    
    ```

    - signal(SIGCHLE, mychild);
        - SIGCHLD(자식프로세스가 종료된 상황) 이 상황에서 mychild 이 함수를 호출(like 이벤트핸들러)

- 멀티플렉싱
    - 하나의 통신채널을 통해서 둘 이상의 데이터를 전송하는데 사용되는 기술
    ``` c
        int select(int maxfd, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval * timeout);
        //성공 0, 실패 -1
    ```