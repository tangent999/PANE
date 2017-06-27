
#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
//using namespace std;
#define numRouters 16
#define numClients 4


#define ADDR_SRC     "../../socket_src"

#define ADDR_TIMER     "../../socket_timer"
	
int fd[numRouters][numClients][5];
int sd[numRouters][numClients][5];
struct sockaddr_un saun[numRouters][numClients][5];

int fd_src;
int sd_src;
struct sockaddr_un saun_src;

int fd_timer;
int sd_timer;
struct sockaddr_un saun_timer;

const char * ADDR[numRouters][numClients][5];

int transfer_counter[numRouters][numClients][5];		//*Sarab

int getTransferCounter(int R,int C, int P) { return transfer_counter[R][C][P];}		//*Sarab

void setTransferCounter(int R,int C, int P, int value) { transfer_counter[R][C][P]=value;}	//*Sarab

//Transfer Counter
void resetTransferCounter() 
{
	for(int R = 0; R<numRouters; R++)
	{
		for(int C = 0; C<numClients; C++)
		{
			for(int P = 0; P<5; P++)
			{
				transfer_counter[R][C][P]=0;
			}
		}
	}
}

//Src
int create_socket_src()
{
	int len;
	

	if ((sd_src = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
	perror("SRC: socket");
	exit(1);
	}

	saun_src.sun_family = AF_UNIX;
	strcpy(saun_src.sun_path, ADDR_SRC);

	len = sizeof(saun_src.sun_family) + strlen(saun_src.sun_path);
	
	if (connect(sd_src, (struct sockaddr *) &saun_src, len) < 0)
	{
	perror("SRC: connect");
	exit(1);
	}
	printf("Master: Running SRC....\n");
	return sd_src;
}

void setfd_src(const int& val)
{
	fd_src = val;
}
int getfd_src()
{
        return fd_src;
}

//Timer
int create_socket_timer()
{
	int len;
	

	if ((sd_timer = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
	perror("timer: socket");
	exit(1);
	}

	saun_timer.sun_family = AF_UNIX;
	strcpy(saun_timer.sun_path, ADDR_TIMER);

	len = sizeof(saun_timer.sun_family) + strlen(saun_timer.sun_path);

	if (connect(sd_timer, (struct sockaddr *) &saun_timer, len) < 0)
	{
	perror("timer: connect");
	exit(1);
	}
	printf("Master: Running timer....\n");
	return sd_timer;
}

void setfd_timer(const int& val)
{
	fd_timer = val;
}
int getfd_timer()
{
        return fd_timer;
}


//Clients
int create_socket(int R,int C,int P)
{
	
	int len; 
	 if ((sd[R][C][P] = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	 { 
		perror("socket");
//		printf("Client[%d][%d][%d]: socket error",R,C,P);exit(1); 
	 }
//	int on=1;
//	if((setsockopt(sd[R][C][P], SOL_SOCKET,  SO_REUSEADDR,(char *)&on, sizeof(on))) < 0)		//Can remove
//	{
//		perror("setsockopt() failed");
//		exit(1);
//	}
	 saun[R][C][P].sun_family = AF_UNIX;
	 strcpy(saun[R][C][P].sun_path, ADDR[R][C][P]);
	 len = sizeof(saun[R][C][P].sun_family) + strlen(saun[R][C][P].sun_path); 
	while(1)
	{
		if (connect(sd[R][C][P], (struct sockaddr *) &saun[R][C][P], len) < 0)
			continue;
		break;
	}
//	 if (connect(sd[R][C][P], (struct sockaddr *) &saun[R][C][P], len) < 0) 
//	 { 
//		perror("connect");
//		printf("Client[%d][%d][%d]: connect error",R,C,P);
//		 exit(1); 
//	 }
	 return sd[R][C][P];
	
}

void setfd(const int& val,int R,int C, int P)
 { 
 	fd[R][C][P] = val;
 }

int getfd(int R,int C,int P)
 { 
 	return fd[R][C][P];
 }


void assignsocklist()
{
	ADDR [0][0][0] = "../../socket_r0_c0_i0";
ADDR [0][0][1] = "../../socket_r0_c0_i1";
ADDR [0][0][2] = "../../socket_r0_c0_i2";
ADDR [0][0][3] = "../../socket_r0_c0_i3";
ADDR [0][0][4] = "../../socket_r0_c0_i4";
ADDR [0][1][0] = "../../socket_r0_c1_i0";
ADDR [0][1][1] = "../../socket_r0_c1_i1";
ADDR [0][1][2] = "../../socket_r0_c1_i2";
ADDR [0][1][3] = "../../socket_r0_c1_i3";
ADDR [0][1][4] = "../../socket_r0_c1_i4";
ADDR [0][2][0] = "../../socket_r0_c2_i0";
ADDR [0][2][1] = "../../socket_r0_c2_i1";
ADDR [0][2][2] = "../../socket_r0_c2_i2";
ADDR [0][2][3] = "../../socket_r0_c2_i3";
ADDR [0][2][4] = "../../socket_r0_c2_i4";
ADDR [0][3][0] = "../../socket_r0_c3_i0";
ADDR [0][3][1] = "../../socket_r0_c3_i1";
ADDR [0][3][2] = "../../socket_r0_c3_i2";
ADDR [0][3][3] = "../../socket_r0_c3_i3";
ADDR [0][3][4] = "../../socket_r0_c3_i4";
ADDR [1][0][0] = "../../socket_r1_c0_i0";
ADDR [1][0][1] = "../../socket_r1_c0_i1";
ADDR [1][0][2] = "../../socket_r1_c0_i2";
ADDR [1][0][3] = "../../socket_r1_c0_i3";
ADDR [1][0][4] = "../../socket_r1_c0_i4";
ADDR [1][1][0] = "../../socket_r1_c1_i0";
ADDR [1][1][1] = "../../socket_r1_c1_i1";
ADDR [1][1][2] = "../../socket_r1_c1_i2";
ADDR [1][1][3] = "../../socket_r1_c1_i3";
ADDR [1][1][4] = "../../socket_r1_c1_i4";
ADDR [1][2][0] = "../../socket_r1_c2_i0";
ADDR [1][2][1] = "../../socket_r1_c2_i1";
ADDR [1][2][2] = "../../socket_r1_c2_i2";
ADDR [1][2][3] = "../../socket_r1_c2_i3";
ADDR [1][2][4] = "../../socket_r1_c2_i4";
ADDR [1][3][0] = "../../socket_r1_c3_i0";
ADDR [1][3][1] = "../../socket_r1_c3_i1";
ADDR [1][3][2] = "../../socket_r1_c3_i2";
ADDR [1][3][3] = "../../socket_r1_c3_i3";
ADDR [1][3][4] = "../../socket_r1_c3_i4";
ADDR [2][0][0] = "../../socket_r2_c0_i0";
ADDR [2][0][1] = "../../socket_r2_c0_i1";
ADDR [2][0][2] = "../../socket_r2_c0_i2";
ADDR [2][0][3] = "../../socket_r2_c0_i3";
ADDR [2][0][4] = "../../socket_r2_c0_i4";
ADDR [2][1][0] = "../../socket_r2_c1_i0";
ADDR [2][1][1] = "../../socket_r2_c1_i1";
ADDR [2][1][2] = "../../socket_r2_c1_i2";
ADDR [2][1][3] = "../../socket_r2_c1_i3";
ADDR [2][1][4] = "../../socket_r2_c1_i4";
ADDR [2][2][0] = "../../socket_r2_c2_i0";
ADDR [2][2][1] = "../../socket_r2_c2_i1";
ADDR [2][2][2] = "../../socket_r2_c2_i2";
ADDR [2][2][3] = "../../socket_r2_c2_i3";
ADDR [2][2][4] = "../../socket_r2_c2_i4";
ADDR [2][3][0] = "../../socket_r2_c3_i0";
ADDR [2][3][1] = "../../socket_r2_c3_i1";
ADDR [2][3][2] = "../../socket_r2_c3_i2";
ADDR [2][3][3] = "../../socket_r2_c3_i3";
ADDR [2][3][4] = "../../socket_r2_c3_i4";
ADDR [3][0][0] = "../../socket_r3_c0_i0";
ADDR [3][0][1] = "../../socket_r3_c0_i1";
ADDR [3][0][2] = "../../socket_r3_c0_i2";
ADDR [3][0][3] = "../../socket_r3_c0_i3";
ADDR [3][0][4] = "../../socket_r3_c0_i4";
ADDR [3][1][0] = "../../socket_r3_c1_i0";
ADDR [3][1][1] = "../../socket_r3_c1_i1";
ADDR [3][1][2] = "../../socket_r3_c1_i2";
ADDR [3][1][3] = "../../socket_r3_c1_i3";
ADDR [3][1][4] = "../../socket_r3_c1_i4";
ADDR [3][2][0] = "../../socket_r3_c2_i0";
ADDR [3][2][1] = "../../socket_r3_c2_i1";
ADDR [3][2][2] = "../../socket_r3_c2_i2";
ADDR [3][2][3] = "../../socket_r3_c2_i3";
ADDR [3][2][4] = "../../socket_r3_c2_i4";
ADDR [3][3][0] = "../../socket_r3_c3_i0";
ADDR [3][3][1] = "../../socket_r3_c3_i1";
ADDR [3][3][2] = "../../socket_r3_c3_i2";
ADDR [3][3][3] = "../../socket_r3_c3_i3";
ADDR [3][3][4] = "../../socket_r3_c3_i4";
ADDR [4][0][0] = "../../socket_r4_c0_i0";
ADDR [4][0][1] = "../../socket_r4_c0_i1";
ADDR [4][0][2] = "../../socket_r4_c0_i2";
ADDR [4][0][3] = "../../socket_r4_c0_i3";
ADDR [4][0][4] = "../../socket_r4_c0_i4";
ADDR [4][1][0] = "../../socket_r4_c1_i0";
ADDR [4][1][1] = "../../socket_r4_c1_i1";
ADDR [4][1][2] = "../../socket_r4_c1_i2";
ADDR [4][1][3] = "../../socket_r4_c1_i3";
ADDR [4][1][4] = "../../socket_r4_c1_i4";
ADDR [4][2][0] = "../../socket_r4_c2_i0";
ADDR [4][2][1] = "../../socket_r4_c2_i1";
ADDR [4][2][2] = "../../socket_r4_c2_i2";
ADDR [4][2][3] = "../../socket_r4_c2_i3";
ADDR [4][2][4] = "../../socket_r4_c2_i4";
ADDR [4][3][0] = "../../socket_r4_c3_i0";
ADDR [4][3][1] = "../../socket_r4_c3_i1";
ADDR [4][3][2] = "../../socket_r4_c3_i2";
ADDR [4][3][3] = "../../socket_r4_c3_i3";
ADDR [4][3][4] = "../../socket_r4_c3_i4";
ADDR [5][0][0] = "../../socket_r5_c0_i0";
ADDR [5][0][1] = "../../socket_r5_c0_i1";
ADDR [5][0][2] = "../../socket_r5_c0_i2";
ADDR [5][0][3] = "../../socket_r5_c0_i3";
ADDR [5][0][4] = "../../socket_r5_c0_i4";
ADDR [5][1][0] = "../../socket_r5_c1_i0";
ADDR [5][1][1] = "../../socket_r5_c1_i1";
ADDR [5][1][2] = "../../socket_r5_c1_i2";
ADDR [5][1][3] = "../../socket_r5_c1_i3";
ADDR [5][1][4] = "../../socket_r5_c1_i4";
ADDR [5][2][0] = "../../socket_r5_c2_i0";
ADDR [5][2][1] = "../../socket_r5_c2_i1";
ADDR [5][2][2] = "../../socket_r5_c2_i2";
ADDR [5][2][3] = "../../socket_r5_c2_i3";
ADDR [5][2][4] = "../../socket_r5_c2_i4";
ADDR [5][3][0] = "../../socket_r5_c3_i0";
ADDR [5][3][1] = "../../socket_r5_c3_i1";
ADDR [5][3][2] = "../../socket_r5_c3_i2";
ADDR [5][3][3] = "../../socket_r5_c3_i3";
ADDR [5][3][4] = "../../socket_r5_c3_i4";
ADDR [6][0][0] = "../../socket_r6_c0_i0";
ADDR [6][0][1] = "../../socket_r6_c0_i1";
ADDR [6][0][2] = "../../socket_r6_c0_i2";
ADDR [6][0][3] = "../../socket_r6_c0_i3";
ADDR [6][0][4] = "../../socket_r6_c0_i4";
ADDR [6][1][0] = "../../socket_r6_c1_i0";
ADDR [6][1][1] = "../../socket_r6_c1_i1";
ADDR [6][1][2] = "../../socket_r6_c1_i2";
ADDR [6][1][3] = "../../socket_r6_c1_i3";
ADDR [6][1][4] = "../../socket_r6_c1_i4";
ADDR [6][2][0] = "../../socket_r6_c2_i0";
ADDR [6][2][1] = "../../socket_r6_c2_i1";
ADDR [6][2][2] = "../../socket_r6_c2_i2";
ADDR [6][2][3] = "../../socket_r6_c2_i3";
ADDR [6][2][4] = "../../socket_r6_c2_i4";
ADDR [6][3][0] = "../../socket_r6_c3_i0";
ADDR [6][3][1] = "../../socket_r6_c3_i1";
ADDR [6][3][2] = "../../socket_r6_c3_i2";
ADDR [6][3][3] = "../../socket_r6_c3_i3";
ADDR [6][3][4] = "../../socket_r6_c3_i4";
ADDR [7][0][0] = "../../socket_r7_c0_i0";
ADDR [7][0][1] = "../../socket_r7_c0_i1";
ADDR [7][0][2] = "../../socket_r7_c0_i2";
ADDR [7][0][3] = "../../socket_r7_c0_i3";
ADDR [7][0][4] = "../../socket_r7_c0_i4";
ADDR [7][1][0] = "../../socket_r7_c1_i0";
ADDR [7][1][1] = "../../socket_r7_c1_i1";
ADDR [7][1][2] = "../../socket_r7_c1_i2";
ADDR [7][1][3] = "../../socket_r7_c1_i3";
ADDR [7][1][4] = "../../socket_r7_c1_i4";
ADDR [7][2][0] = "../../socket_r7_c2_i0";
ADDR [7][2][1] = "../../socket_r7_c2_i1";
ADDR [7][2][2] = "../../socket_r7_c2_i2";
ADDR [7][2][3] = "../../socket_r7_c2_i3";
ADDR [7][2][4] = "../../socket_r7_c2_i4";
ADDR [7][3][0] = "../../socket_r7_c3_i0";
ADDR [7][3][1] = "../../socket_r7_c3_i1";
ADDR [7][3][2] = "../../socket_r7_c3_i2";
ADDR [7][3][3] = "../../socket_r7_c3_i3";
ADDR [7][3][4] = "../../socket_r7_c3_i4";
ADDR [8][0][0] = "../../socket_r8_c0_i0";
ADDR [8][0][1] = "../../socket_r8_c0_i1";
ADDR [8][0][2] = "../../socket_r8_c0_i2";
ADDR [8][0][3] = "../../socket_r8_c0_i3";
ADDR [8][0][4] = "../../socket_r8_c0_i4";
ADDR [8][1][0] = "../../socket_r8_c1_i0";
ADDR [8][1][1] = "../../socket_r8_c1_i1";
ADDR [8][1][2] = "../../socket_r8_c1_i2";
ADDR [8][1][3] = "../../socket_r8_c1_i3";
ADDR [8][1][4] = "../../socket_r8_c1_i4";
ADDR [8][2][0] = "../../socket_r8_c2_i0";
ADDR [8][2][1] = "../../socket_r8_c2_i1";
ADDR [8][2][2] = "../../socket_r8_c2_i2";
ADDR [8][2][3] = "../../socket_r8_c2_i3";
ADDR [8][2][4] = "../../socket_r8_c2_i4";
ADDR [8][3][0] = "../../socket_r8_c3_i0";
ADDR [8][3][1] = "../../socket_r8_c3_i1";
ADDR [8][3][2] = "../../socket_r8_c3_i2";
ADDR [8][3][3] = "../../socket_r8_c3_i3";
ADDR [8][3][4] = "../../socket_r8_c3_i4";
ADDR [9][0][0] = "../../socket_r9_c0_i0";
ADDR [9][0][1] = "../../socket_r9_c0_i1";
ADDR [9][0][2] = "../../socket_r9_c0_i2";
ADDR [9][0][3] = "../../socket_r9_c0_i3";
ADDR [9][0][4] = "../../socket_r9_c0_i4";
ADDR [9][1][0] = "../../socket_r9_c1_i0";
ADDR [9][1][1] = "../../socket_r9_c1_i1";
ADDR [9][1][2] = "../../socket_r9_c1_i2";
ADDR [9][1][3] = "../../socket_r9_c1_i3";
ADDR [9][1][4] = "../../socket_r9_c1_i4";
ADDR [9][2][0] = "../../socket_r9_c2_i0";
ADDR [9][2][1] = "../../socket_r9_c2_i1";
ADDR [9][2][2] = "../../socket_r9_c2_i2";
ADDR [9][2][3] = "../../socket_r9_c2_i3";
ADDR [9][2][4] = "../../socket_r9_c2_i4";
ADDR [9][3][0] = "../../socket_r9_c3_i0";
ADDR [9][3][1] = "../../socket_r9_c3_i1";
ADDR [9][3][2] = "../../socket_r9_c3_i2";
ADDR [9][3][3] = "../../socket_r9_c3_i3";
ADDR [9][3][4] = "../../socket_r9_c3_i4";
ADDR [10][0][0] = "../../socket_r10_c0_i0";
ADDR [10][0][1] = "../../socket_r10_c0_i1";
ADDR [10][0][2] = "../../socket_r10_c0_i2";
ADDR [10][0][3] = "../../socket_r10_c0_i3";
ADDR [10][0][4] = "../../socket_r10_c0_i4";
ADDR [10][1][0] = "../../socket_r10_c1_i0";
ADDR [10][1][1] = "../../socket_r10_c1_i1";
ADDR [10][1][2] = "../../socket_r10_c1_i2";
ADDR [10][1][3] = "../../socket_r10_c1_i3";
ADDR [10][1][4] = "../../socket_r10_c1_i4";
ADDR [10][2][0] = "../../socket_r10_c2_i0";
ADDR [10][2][1] = "../../socket_r10_c2_i1";
ADDR [10][2][2] = "../../socket_r10_c2_i2";
ADDR [10][2][3] = "../../socket_r10_c2_i3";
ADDR [10][2][4] = "../../socket_r10_c2_i4";
ADDR [10][3][0] = "../../socket_r10_c3_i0";
ADDR [10][3][1] = "../../socket_r10_c3_i1";
ADDR [10][3][2] = "../../socket_r10_c3_i2";
ADDR [10][3][3] = "../../socket_r10_c3_i3";
ADDR [10][3][4] = "../../socket_r10_c3_i4";
ADDR [11][0][0] = "../../socket_r11_c0_i0";
ADDR [11][0][1] = "../../socket_r11_c0_i1";
ADDR [11][0][2] = "../../socket_r11_c0_i2";
ADDR [11][0][3] = "../../socket_r11_c0_i3";
ADDR [11][0][4] = "../../socket_r11_c0_i4";
ADDR [11][1][0] = "../../socket_r11_c1_i0";
ADDR [11][1][1] = "../../socket_r11_c1_i1";
ADDR [11][1][2] = "../../socket_r11_c1_i2";
ADDR [11][1][3] = "../../socket_r11_c1_i3";
ADDR [11][1][4] = "../../socket_r11_c1_i4";
ADDR [11][2][0] = "../../socket_r11_c2_i0";
ADDR [11][2][1] = "../../socket_r11_c2_i1";
ADDR [11][2][2] = "../../socket_r11_c2_i2";
ADDR [11][2][3] = "../../socket_r11_c2_i3";
ADDR [11][2][4] = "../../socket_r11_c2_i4";
ADDR [11][3][0] = "../../socket_r11_c3_i0";
ADDR [11][3][1] = "../../socket_r11_c3_i1";
ADDR [11][3][2] = "../../socket_r11_c3_i2";
ADDR [11][3][3] = "../../socket_r11_c3_i3";
ADDR [11][3][4] = "../../socket_r11_c3_i4";
ADDR [12][0][0] = "../../socket_r12_c0_i0";
ADDR [12][0][1] = "../../socket_r12_c0_i1";
ADDR [12][0][2] = "../../socket_r12_c0_i2";
ADDR [12][0][3] = "../../socket_r12_c0_i3";
ADDR [12][0][4] = "../../socket_r12_c0_i4";
ADDR [12][1][0] = "../../socket_r12_c1_i0";
ADDR [12][1][1] = "../../socket_r12_c1_i1";
ADDR [12][1][2] = "../../socket_r12_c1_i2";
ADDR [12][1][3] = "../../socket_r12_c1_i3";
ADDR [12][1][4] = "../../socket_r12_c1_i4";
ADDR [12][2][0] = "../../socket_r12_c2_i0";
ADDR [12][2][1] = "../../socket_r12_c2_i1";
ADDR [12][2][2] = "../../socket_r12_c2_i2";
ADDR [12][2][3] = "../../socket_r12_c2_i3";
ADDR [12][2][4] = "../../socket_r12_c2_i4";
ADDR [12][3][0] = "../../socket_r12_c3_i0";
ADDR [12][3][1] = "../../socket_r12_c3_i1";
ADDR [12][3][2] = "../../socket_r12_c3_i2";
ADDR [12][3][3] = "../../socket_r12_c3_i3";
ADDR [12][3][4] = "../../socket_r12_c3_i4";
ADDR [13][0][0] = "../../socket_r13_c0_i0";
ADDR [13][0][1] = "../../socket_r13_c0_i1";
ADDR [13][0][2] = "../../socket_r13_c0_i2";
ADDR [13][0][3] = "../../socket_r13_c0_i3";
ADDR [13][0][4] = "../../socket_r13_c0_i4";
ADDR [13][1][0] = "../../socket_r13_c1_i0";
ADDR [13][1][1] = "../../socket_r13_c1_i1";
ADDR [13][1][2] = "../../socket_r13_c1_i2";
ADDR [13][1][3] = "../../socket_r13_c1_i3";
ADDR [13][1][4] = "../../socket_r13_c1_i4";
ADDR [13][2][0] = "../../socket_r13_c2_i0";
ADDR [13][2][1] = "../../socket_r13_c2_i1";
ADDR [13][2][2] = "../../socket_r13_c2_i2";
ADDR [13][2][3] = "../../socket_r13_c2_i3";
ADDR [13][2][4] = "../../socket_r13_c2_i4";
ADDR [13][3][0] = "../../socket_r13_c3_i0";
ADDR [13][3][1] = "../../socket_r13_c3_i1";
ADDR [13][3][2] = "../../socket_r13_c3_i2";
ADDR [13][3][3] = "../../socket_r13_c3_i3";
ADDR [13][3][4] = "../../socket_r13_c3_i4";
ADDR [14][0][0] = "../../socket_r14_c0_i0";
ADDR [14][0][1] = "../../socket_r14_c0_i1";
ADDR [14][0][2] = "../../socket_r14_c0_i2";
ADDR [14][0][3] = "../../socket_r14_c0_i3";
ADDR [14][0][4] = "../../socket_r14_c0_i4";
ADDR [14][1][0] = "../../socket_r14_c1_i0";
ADDR [14][1][1] = "../../socket_r14_c1_i1";
ADDR [14][1][2] = "../../socket_r14_c1_i2";
ADDR [14][1][3] = "../../socket_r14_c1_i3";
ADDR [14][1][4] = "../../socket_r14_c1_i4";
ADDR [14][2][0] = "../../socket_r14_c2_i0";
ADDR [14][2][1] = "../../socket_r14_c2_i1";
ADDR [14][2][2] = "../../socket_r14_c2_i2";
ADDR [14][2][3] = "../../socket_r14_c2_i3";
ADDR [14][2][4] = "../../socket_r14_c2_i4";
ADDR [14][3][0] = "../../socket_r14_c3_i0";
ADDR [14][3][1] = "../../socket_r14_c3_i1";
ADDR [14][3][2] = "../../socket_r14_c3_i2";
ADDR [14][3][3] = "../../socket_r14_c3_i3";
ADDR [14][3][4] = "../../socket_r14_c3_i4";
ADDR [15][0][0] = "../../socket_r15_c0_i0";
ADDR [15][0][1] = "../../socket_r15_c0_i1";
ADDR [15][0][2] = "../../socket_r15_c0_i2";
ADDR [15][0][3] = "../../socket_r15_c0_i3";
ADDR [15][0][4] = "../../socket_r15_c0_i4";
ADDR [15][1][0] = "../../socket_r15_c1_i0";
ADDR [15][1][1] = "../../socket_r15_c1_i1";
ADDR [15][1][2] = "../../socket_r15_c1_i2";
ADDR [15][1][3] = "../../socket_r15_c1_i3";
ADDR [15][1][4] = "../../socket_r15_c1_i4";
ADDR [15][2][0] = "../../socket_r15_c2_i0";
ADDR [15][2][1] = "../../socket_r15_c2_i1";
ADDR [15][2][2] = "../../socket_r15_c2_i2";
ADDR [15][2][3] = "../../socket_r15_c2_i3";
ADDR [15][2][4] = "../../socket_r15_c2_i4";
ADDR [15][3][0] = "../../socket_r15_c3_i0";
ADDR [15][3][1] = "../../socket_r15_c3_i1";
ADDR [15][3][2] = "../../socket_r15_c3_i2";
ADDR [15][3][3] = "../../socket_r15_c3_i3";
ADDR [15][3][4] = "../../socket_r15_c3_i4";
}