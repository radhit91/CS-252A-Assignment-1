/* credit @Daniel Scocco */

/****************** SERVER CODE ****************/

#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>


char buffer[10000];

int write_image_to_buffer(char* file)
{
    char* name=malloc(19*sizeof(char));
    char st1[]={'i','m','a','g','e','s','/'};
    strcpy(name,st1);
    strcat(name,file);
    FILE *fp = fopen(name,"rb+");
    long lsize;
    //char *buffer;
    size_t result;

    fseek(fp , 0 ,SEEK_END);
    lsize = ftell(fp);
    //printf("%ld",lsize);
    rewind(fp);
    //buffer = (char*)malloc(sizeof(char)*lsize);
   
    result=fread(buffer,1,lsize,fp);

    /*result = fread(buffer+k,1,lsize,fp);
    k=lsize;
    *(buffer+k)="?";
    k++;*/
    //int k=0;
    /*FILE *fp1 = fopen("i.jpg","w");
    do{
            fputc(buffer[k],fp1);
    }while(buffer[k++]!=EOF);
    printf("!*!%d\n",k);*/
  return lsize;
}

int main(){
  int welcomeSocket, newSocket, total, temp;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5432);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("I'm listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
printf("!! I am here\n");
  while(1){
  addr_size = sizeof serverStorage;
  printf("@@ WAITING FOR CONNECTION\n");
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  printf("## WAITING FOR PACKET\n");
  recv(newSocket,buffer,1024,0);
  printf("&& RECEIVED\n");
  printf("@@ %s\n",buffer);
  
  /*---- Process the data ----*/
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
  /* The values num_cats,num_dogs,num_cars,num_trucks contain the
     number of photos required by the client */
  /*---- Send message to the socket of the incoming connection ----*/
  printf("%d %d %d %d\n",num_cats,num_dogs,num_cars,num_trucks);
  //strcpy(buffer,"Hello World\n");
 /* printf("$$ SENDING\n");
  buffer[0]=num_cats+48;buffer[1]=num_dogs+48;buffer[2]=num_cars+48;
  buffer[3]=num_trucks+48;buffer[4]='\n';buffer[5]='\0';
  //send(newSocket,buffer,strlen(buffer)+1,0);
  printf("$$ SENT\n");*/
  

  // ** Retrieving the required images and placing them in buffer ** //
  
  total=num_cats+num_dogs+num_cars+num_trucks;
  int count[4][4];
  int lsize;
   for(int i=0;i<4;i++)
{
   for(int j=0;j<4;j++)
 {
   count[i][j]=0;
 }
} 

  while(total!=0)
{ printf("%d %d %d %d %d\n",total,num_cats,num_dogs,num_cars,num_trucks);
     while(num_cats!=0)
  {printf("reached1");
      temp=rand()%4; 
      while(count[0][temp]!=0)
    {
      temp=rand()%4;
    }
     
     char str[]={'c','a','t','-',(temp+1)+48,'.','j','p','g','\0'};
     
    
      lsize=write_image_to_buffer(str);   
 int num = htonl(lsize);
      write(newSocket,&num,sizeof(num));
      send(newSocket,buffer,lsize,0);   
      recv(newSocket,buffer,lsize,0);   
      count[0][temp]=1;
      num_cats--;
  }
     while(num_dogs!=0)
  {printf("reached2");
      temp=rand()%4; 
      while(count[1][temp]!=0)
    {
      temp=rand()%4;
    }
    
     char str[]={'d','o','g','-',(temp+1)+48,'.','j','p','g','\0'};
     
     
      lsize=write_image_to_buffer(str);   
 int num = htonl(lsize);
      write(newSocket,&num,sizeof(num));
      send(newSocket,buffer,lsize,0);   
      recv(newSocket,buffer,lsize,0);   
      count[1][temp]=1;
      num_dogs--;
  }

     while(num_cars!=0)
  { printf("reached");
      temp=rand()%4; 
      while(count[2][temp]!=0)
    {
      temp=rand()%4;
    }
     //char* res=malloc(10*sizeof(char));
     char str[]={'c','a','r','-',(temp+1)+48,'.','j','p','g','\0'};
     //char *str2;
     //*str2=(temp+1)+48;
     //char str3[]={'.','j','p','g','\0'};
     //strcpy(res,str1);
     //strcat(res,str2);
     //strcat(res,str3);
      printf("%s\n",str);
      printf("qw");
      lsize=write_image_to_buffer(str);  
       printf("**%d",lsize);
       printf("rw");
       printf("!!!%d\n",strlen(buffer)+1);
      int num = htonl(lsize);
      write(newSocket,&num,sizeof(num));
      send(newSocket,buffer,lsize,0);   
      recv(newSocket,buffer,lsize,0);   
      
      count[2][temp]=1;
      num_cars--;
  }
     while(num_trucks!=0)
  {
	printf("reached3");
      temp=rand()%4; 
      while(count[3][temp]!=0)
    {
      temp=rand()%4;
    }
     char str[]={'t','r','u','c','k','-',(temp+1)+48,'.','j','p','g','\0'};
    
      lsize=write_image_to_buffer(str);   
 int num = htonl(lsize);
      write(newSocket,&num,sizeof(num));
      send(newSocket,buffer,lsize,0);   
      recv(newSocket,buffer,lsize,0);   
      count[3][temp]=1;
      num_trucks--;
  }


  total--;
printf("%d\n",total);
}
 
 
}  
  








  return 0;
}
