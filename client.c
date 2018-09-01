
/* credit @Daniel Scocco */

/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
  int clientSocket;
  char buffer[10000];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5432);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  char c;int k=0;
  scanf("%c",&c);
  while(c!='\n'){
  	buffer[k++]=c;
	scanf("%c",&c);
  }
  buffer[k]='\0';
  send(clientSocket,buffer,strlen(buffer)+1,0);
  //####### Processed Data#####################
  int num_dogs,num_cats,num_cars,num_trucks;
  num_dogs=0;num_cats=0;num_cars=0;num_trucks=0;
  int index=0;
  while(buffer[index]!='\0')
  {
    char arr[100];
        int size=0;
        int x=buffer[index]-48;
        printf("**%d**\n",x);
        index=index+2;
        while(buffer[index]!=' ' && buffer[index]!='\0'){
    arr[size++]=buffer[index++];
  }
  
        arr[size]='\0';
  if(strcmp(arr,"cats\0")==0 || strcmp(arr,"cat\0")==0)
    num_cats=x;
  if(strcmp(arr,"dogs\0")==0 || strcmp(arr,"dog\0")==0)
    num_dogs=x;
  if(strcmp(arr,"cars\0")==0 || strcmp(arr,"car\0")==0)
    num_cars=x;
  if(strcmp(arr,"trucks\0")==0 || strcmp(arr,"truck\0")==0)
    num_trucks=x;
        if(buffer[index]==' ')
    index++;
  }
  int total = num_trucks+num_cars+num_dogs+num_cats;
  //##################recieving for multiple images##############
  FILE *fp;
  char filename[20];
  for(int i=0;i<total;i++){
    int size=0;
    read(clientSocket, &size, sizeof(size));
    size=ntohl(size);
    printf("**%d",size);
    recv(clientSocket, buffer, 10000, 0);
    if(i<num_cats){
      sprintf(filename ,"cat%d.jpg",i+1);
      fp = fopen(filename,"w");
      int i=0;
      while(i<=size)
	fputc(buffer[i++],fp);
    }
    else if(i<num_cats+num_dogs && i>=num_cats){
      sprintf(filename ,"dog%d.jpg",i+1-num_cats);
      fp = fopen(filename,"w");
      int i=0;
      while(i<=size)
	fputc(buffer[i++],fp);

    }
    else if(i<num_cats+num_dogs+num_cars && i>=num_cats+num_dogs){
      sprintf(filename ,"car%d.jpg",i+1-(num_cats+num_dogs));
      fp = fopen(filename,"w");
      /*for(int i=0;i<10000;i++)
          printf("%c",buffer[i]); */
      int i=0;
      while(i<=size)
	fputc(buffer[i++],fp);
    }
    else if(i<total && i>=num_cats+num_dogs+num_cars){
      sprintf(filename ,"truck%d.jpg",i+1-(num_cats+num_dogs+num_cars));
      fp = fopen(filename,"w");
      int i=0;
      while(i<=size)
	fputc(buffer[i++],fp);

    }
    send(clientSocket,"Hello",6,0);
  }
  /*---- Read the message from the server into the buffer ----*/
  //recv(clientSocket, buffer, 1024, 0);
  /*---- Print the received message ----*/

  //printf("Data received: %s",buffer);

  return 0;
}
