#include "csapp.h"

void echo(int connfd);
    int normal_ticket=100;
    int deluxe_ticket=50;
    int premium_ticket=30;
    int seat_number=0;
int main(int argc, char **argv) 
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;  
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1) {
	clientlen = sizeof(struct sockaddr_storage); 
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, 
                    client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        pthread_t tid;
        Pthread_create(&tid,NULL,echo,connfd);
        Pthread_join(tid,NULL);
	Close(connfd);
    }
    exit(0);
}
void echo(int connfd) 
{
    size_t n; 
    char buf[MAXLINE]; 
    
    rio_t rio;
	int argc=0;
	char *token,*argv[20];
    Rio_readinitb(&rio, connfd);
    	
	Rio_readlineb(&rio, buf, MAXLINE);
	token=strtok(buf," ");
	while(token!=NULL)
	{
		argv[argc]=token;
		argc++;
		token=strtok(NULL," ");
	}
	int argc1=0;
	char *token1,*argv1[20];
	token1=strtok(argv[1],"'&'");
	while(token1!=NULL)
	{
		argv1[argc1]=token1;
		argc1++;
		token1=strtok(NULL,"'&'");
	}
	
	argv1[0]+=1;
	char name[100];
	strcpy(name,argv1[0]);
	//check email is empty
	if(argv1[1]==' ')
	{
		printf("%s - Invalid email address.",name);
		fflush(stdout);
		return;
	}
	char email[100];
	strcpy(email,argv1[1]);
	int quantity;
	quantity=atoi(argv1[2]);
	char ticket[100];
	strcpy(ticket,argv1[3]);
	/*printf("\nName = %s\n",name);
	printf("\nEmail = %s\n",email);
	printf("\nQuantity = %d\n",quantity);
	printf("\nTicket Type = %s\n",ticket);
	*/
	int cmd[100];
	char body[MAXLINE];
	int seats[MAXLINE];
	int seatcount;
	int booking;
	int originalq;
	
	// Check if email is valid or not
	int atrate=-1;
	int dot=-1;
	if(email[0]>='a' && email[0]<='z')
	{
		
	}
	else
	{
		printf("%s - Invalid email address.",name);
		fflush(stdout);
		return;
	}
	for(int i=0;email[i]!='\0';i++)
	{
		if(email[i]>='A' && email[i]<='Z')
		{
			printf("%s - Invalid email address.",name);
			fflush(stdout);
			return;
		}
		if(email[i]=='@')
		{
			atrate=i;
		}
		if(email[i]=='.')
		{
			dot=i;
		}
		
	}
	if(atrate!=-1 && dot!=-1 && atrate<dot)
	{
		
	}
	else
	{
		printf("%s - Invalid email address.",name);
		fflush(stdout);
		return;
	}
	if(strcmp(ticket,"Normal")==0)
	{
		fflush(stdout);
		booking=0;
		seatcount=0;
		originalq=quantity;
		if(quantity<1)
		{
			
			printf("%s - Invalid quantity requested.",name);
			fflush(stdout);
		}
		else
		{
		while(quantity--)
		{
			if(normal_ticket>0)
			{
				booking=1;
				normal_ticket-=1;
			
			
				seat_number+=1;
				seats[seatcount]=seat_number;
				seatcount+=1;
				sprintf(body,"%sTicket Booked :) \n Details:\n",body);
				sprintf(body,"%s--------------------------------------\n",body);
				sprintf(body,"%s\nName = %s\n",body,name);
				sprintf(body,"%s\nEmail = %s\n",body,email);
				sprintf(body,"%s\nSeat Number = %d\n",body,seat_number);
				sprintf(body,"%s\nTicket Type = %s\n",body,ticket);
				sprintf(body,"%s--------------------------------------\n",body);
        		
			}
			else
			{
				sprintf(body,"Not enough tickets of Normal category to satisfy given quantity\n");
			}
		
        		
		}
			if(booking==1)
        		{
        			printf("%s -The ticket booking was successful.",name);
        			printf("Ticket numbers:");
        			for(int i=0;i<seatcount;i++)
        			{
        				printf("%d ",seats[i]);
        			}
        			 printf(".Total tickets booked %d",originalq);
        			 printf(". Sent to %s\n",email);
        		}  
        		else
        		{
        			printf("%s- No sufficient tickets are available in this category.",name);
        			fflush(stdout);
        		}          
			FILE *fp = fopen("tempFile.txt","w"); 
        		fprintf(fp,"%s\n",body);       
        		fclose(fp); 
        		

        		sprintf(cmd,"ssmtp %s < tempFile.txt",email); 
        		system(cmd); 
        		sprintf(body," ");
        		}
        		
	}
	else if(strcmp(ticket,"Deluxe")==0)
	{
		fflush(stdout);
		booking=0;
		seatcount=0;
		originalq=quantity;
		if(quantity<1)
		{
			
			printf("%s - Invalid quantity requested.",name);
			fflush(stdout);
		}
		else
		{
		while(quantity--)
		{if(deluxe_ticket>0)
		{
			deluxe_ticket-=1;
			booking=1;
				
			
			
				seat_number+=1;
				seats[seatcount]=seat_number;
				seatcount+=1;
			
				
				sprintf(body,"%sTicket Booked :) \n Details:\n",body);
				sprintf(body,"%s--------------------------------------\n",body);
				sprintf(body,"%s\nName = %s\n",body,name);
				sprintf(body,"%s\nEmail = %s\n",body,email);
				sprintf(body,"%s\nSeat Number = %d\n",body,seat_number);
				sprintf(body,"%s\nTicket Type = %s\n",body,ticket);
				sprintf(body,"%s--------------------------------------\n",body);
			
			
			
			

        		
		}
		else
		{
			sprintf(body,"Not enough tickets of Deluxe category to satisfy given quantity\n");
			
		}
		}
		if(booking==1)
        		{
        			printf("%s -The ticket booking was successful.",name);
        			printf("Ticket numbers:");
        			for(int i=0;i<seatcount;i++)
        			{
        				printf("%d ",seats[i]);
        			}
        			 printf(".Total tickets booked %d",originalq);
        			 printf(". Sent to %s\n",email);
        		}  
        		else
        		{
        			printf("%s- No sufficient tickets are available in this category.",name);
        			fflush(stdout);
        		}          
			FILE *fp = fopen("tempFile.txt","w"); 
        		fprintf(fp,"%s\n",body);       
        		fclose(fp); 
        		

        		sprintf(cmd,"ssmtp %s < tempFile.txt",email); 
        		system(cmd); 
        		sprintf(body," ");
        		}
	}
	else if(strcmp(ticket,"Premium")==0)
	{
		fflush(stdout);
		booking=0;
		seatcount=0;
		originalq=quantity;
		if(quantity<1)
		{
			
			printf("%s - Invalid quantity requested.",name);
			fflush(stdout);
		}
		else
		{
		while(quantity--)
		{if(premium_ticket>0)
		{
			premium_ticket-=1;
			
			
				booking=1;
				
			
			
				seat_number+=1;
				seats[seatcount]=seat_number;
				seatcount+=1;
				sprintf(body,"%sTicket Booked :) \n Details:\n",body);
				sprintf(body,"%s--------------------------------------\n",body);
				sprintf(body,"%s\nName = %s\n",body,name);
				sprintf(body,"%s\nEmail = %s\n",body,email);
				sprintf(body,"%s\nSeat Number = %d\n",body,seat_number);
				sprintf(body,"%s\nTicket Type = %s\n",body,ticket);
				sprintf(body,"%s--------------------------------------\n",body);
			
			
			
			

        		
		}
		else
		{
			sprintf(body,"Not enough tickets of Premium category to satisfy given quantity\n");
			fflush(stdout);
			
		}
		}
		if(booking==1)
        		{
        			printf("%s -The ticket booking was successful.",name);
        			printf("Ticket numbers:");
        			for(int i=0;i<seatcount;i++)
        			{
        				printf("%d ",seats[i]);
        			}
        			 printf(".Total tickets booked %d",originalq);
        			 printf(". Sent to %s\n",email);
        		}  
        		else
        		{
        			printf("%s- No sufficient tickets are available in this category.",name);
        		}          
			FILE *fp = fopen("tempFile.txt","w"); 
        		fprintf(fp,"%s\n",body);       
        		fclose(fp); 
        		

        		sprintf(cmd,"ssmtp %s < tempFile.txt",email); 
        		system(cmd); 
        		sprintf(body," ");
        		}
	}
	Rio_writen(connfd, argv[1], n);
}

