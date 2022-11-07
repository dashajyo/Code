#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define MOVIE_NAME 50
#define BOOKING_DETAILS 100


void debug(char *str){printf("%s\n",str);}
void init();
void list_movies();
void list_bookings();
void display_movies();
void display_bookings();
void book_tickets();
void cancel_tickets();
void remove_booking();
void add_bookings(char *);
void sort_booking();

struct movie_list
{
    char movie_name[MOVIE_NAME];
    struct movie_list *next;
};
struct movie_list *movie_list_head=NULL;


struct booking_list
{
    char booking_name[BOOKING_DETAILS];
    struct booking_list *next;
};
struct booking_list *booking_list_head=NULL;

void init()
{
    printf("\033[0;32mInitialising....Please wait... \033[0m\n\n");
    //sleep(2);
    list_movies(&movie_list_head);
    list_bookings();
}

void sort_booking()
{
    int flag=1,res;
    struct booking_list *head=NULL;
    struct booking_list *temp=NULL;
    char *name=(char *)malloc(BOOKING_DETAILS);
    while(flag)
    {
       flag=0;
       head=booking_list_head;
       while(head->next != temp)
       {
            res=strcmp(head->booking_name,head->next->booking_name);
            if ( res > 0 )
            {
                strcpy(name,head->booking_name);
                strcpy(head->booking_name,head->next->booking_name);
                strcpy(head->next->booking_name,name);
                memset(name,'\0',strlen(name));
                flag=1;
            }
            head=head->next;
       }
       temp = head;
    }
    free(name);
}
void list_movies(struct movie_list **head)
{
   FILE *fptr=NULL;
   struct movie_list *node=NULL;
   struct movie_list *temp=*head;
   char *movie=(char *)malloc(MOVIE_NAME);
   
   fptr=fopen("movie_list.txt","r");
   if(fptr == NULL)
   {
       printf("ERROR: Reading file movie_list.txt\n");   
   }
   while(fgets(movie,MOVIE_NAME,fptr))
   {
        temp=*head;
        node=(struct movie_list*)malloc(sizeof(struct movie_list));
        strcpy(node->movie_name,movie);
        node->next=NULL;
        if (*head == NULL)
        {
            *head=node;
        }
        else
        {
            while (temp->next != NULL) temp=temp->next;
            temp->next=node;
        }
        memset(movie,'\0',strlen(movie));
   }
   fclose(fptr);
   free(movie);
}

void list_bookings()
{
    FILE *fptr=NULL;
    char book[BOOKING_DETAILS];
    struct booking_list *first=NULL;
    struct booking_list *temp=NULL;

    fptr=fopen("booking_list.txt","r");
    if(fptr == NULL)
    {
        printf("ERROR: Reading file booking_list.txt\n");
    }
    while(fgets(book,BOOKING_DETAILS,fptr))
    {
        temp=booking_list_head;
        first=malloc(sizeof(struct booking_list));
        strcpy(first->booking_name,book);
        first->next=NULL;
        if (booking_list_head == NULL)
        {
            booking_list_head=first;
        }
        else
        {
            while (temp->next != NULL) temp=temp->next;
            temp->next=first;
        }
        memset(book,'\0',strlen(book));
    }
    fclose(fptr);
}

void display_movies(struct movie_list *head)
{
    char *token;
    char *name=(char *)malloc(MOVIE_NAME);
    char opt='n',junk;
    if ( head == NULL )
    {
        printf("OOPS! NO MOVIES ON SCREEN\n");
    }
    else
    {
        printf("\n\tMOVIES ON SCREEN\n");
        printf("SI.NO\tMOVIE_NAME\tSHOW_TIME\n");
        while(head != NULL)
        {
            strcpy(name,head->movie_name);
            token=strtok(name,"|");
            while(token != NULL)
            {
                printf("%s\t",token);
                token=strtok(NULL,"|");
            }
            printf("\r");
            head = head->next;
            memset(name,'\0',strlen(name));
        }
    }
    scanf("%c",&junk);
    printf("\nReturn to Dashboard?(y/n):");
    scanf("%c",&opt);
    while(opt != 'y')
    {
        scanf("%c",&junk);
        printf("Return to Dashboard?(y/n):");
        scanf("%c",&opt);
    }

}

void display_bookings()
{
    char *token;
    char *book=(char *)malloc(BOOKING_DETAILS);
    char opt='n',junk;
    int si_no=1;
    struct booking_list *head=NULL;
    head=booking_list_head;
    if ( booking_list_head == NULL )
    {
        printf("NO TICKETS ARE BOOKED YET!!\n");
    }
    else
    {
        printf("\n\t\t\t\tBOOKED DETAILS\n");
        printf("SI.ID\tBOOKING_NAME\tMOVIE_NAME\tTICKET_COUNT\tBOOKING_DATE\tSHOW_TIME\n");
        sort_booking();
        while(head != NULL)
        {
            printf("%d\t",si_no++);
            strcpy(book,head->booking_name);
            token=strtok(book,"|");
            while(token != NULL)
            {
                printf("%s\t\t",token);
                token=strtok(NULL,"|");
            }
            printf("\r");
            head = head->next;
            memset(book,'\0',strlen(book));
        }
    }
    scanf("%c",&junk);
    printf("\nReturn to Dashboard?(y/n):");
    scanf("%c",&opt);
    while(opt != 'y')
    {
        scanf("%c",&junk);
        printf("Return to Dashboard?(y/n):");
        scanf("%c",&opt);
    }
}

void book_tickets()
{
    char m_name[MOVIE_NAME];
    int s_count;

    char b_name[MOVIE_NAME];
    int b_day,b_month,b_year;
    char b_time[6];
    char junk;
    char *booking_detail=malloc(BOOKING_DETAILS);

    printf("\nEnter Movie Name\t\t:");
    scanf("%c",&junk);
    scanf("%[^\n]", m_name);
    printf("Choose Booking Date(DD MM YYYY)\t:");
    scanf("%d%d%d", &b_day,&b_month,&b_year);
    printf("Enter Movie Time(24hrs 00:00)\t:");
    scanf("%s", b_time);
    printf("Enter Seat Count\t\t:");
    scanf("%d", &s_count);
    printf("Enter Booking Name\t\t:");
    scanf("%c",&junk);
    scanf("%[^\n]", b_name);
    sprintf(booking_detail,"%s|%s|%d|%d-%d-%d|%s\n",b_name,m_name,s_count,b_day,b_month,b_year,b_time);
    add_bookings(booking_detail);
    free(booking_detail);
}

void add_bookings(char *booking_detail)
{
    struct booking_list *head=NULL;
    struct booking_list *node=malloc(sizeof(struct booking_list));
    strcpy(node->booking_name,booking_detail);
    node->next=NULL;
    head=booking_list_head;
    if ( booking_list_head == NULL)
    {
        booking_list_head=node;
    }
    else
    {
        while(head->next != NULL) head=head->next;
        head->next=node;
    }
}

void remove_booking(struct booking_list **head,char *book)
{
    struct booking_list *node=*head;
    struct booking_list *prev;
    
    if ( node != NULL && !strcmp(node->booking_name,book))
    {
        *head = node->next;
        free(node);
    }
    else
    {
        while (node != NULL && strcmp(node->booking_name,book))
        {
            prev = node;
            node = node->next;
        }
        if (node == NULL)
        {
            printf("NOT DELETED");
        }
        else
        {
            prev->next = node->next;
        }
        free(node);
    }
}
void cancel_tickets()
{
    int si_id,si_id_org=1;
    char opt='n',junk;
    struct booking_list *head=NULL;
    head=booking_list_head;
    printf("\nPLEASE ENTER YOUR BOOKING SI.ID TO CANCEL:");
    scanf("%d",&si_id);
    if ( booking_list_head == NULL )
    {
        printf("NO TICKETS ARE BOOKED WITH SI.ID: %d!!\n",si_id);
    }
    else
    {
        while(head != NULL)
        {
            if ( si_id_org == si_id )
            {
                printf("DELETED: %s\n",head->booking_name);
                remove_booking(&booking_list_head,head->booking_name);
                break;
            }
            else
            {
                head = head->next;
                si_id_org++;
            }
        }                                                                       
    } 
}

void deinit()
{
    FILE *fptr=NULL;
    struct booking_list *head=NULL;
    fptr=fopen("booking_list.txt","w");
    head=booking_list_head;
    if(fptr==NULL)
    {
        printf("ERROR: Writing to file booking_list.txt\n");
    }
    else
    {
        while(head != NULL)
        {
            printf("%s",head->booking_name);
            fprintf(fptr,"%s",head->booking_name);
            head = head->next;
        }
    }
    fclose(fptr);
}

int main(void)
{
    int option;
    char junk;
    printf("\033[0;31m\n<<<-<-<-<-<-<-<-<-<\tWELCOME TO DJ CINEMAS\t>->->->->->->->->->>>\033[0m\n\n");
    init();
    while(1)
    {
        printf("\n======================================================================\n");
        printf("                            D A S H B O A R D\n");
        printf("======================================================================\n\n");
        printf("---------------------\n");
        printf("OPTION.NO\tOPTION\n");
        printf("---------------------\n");
        printf("1\t\tMOVIES\n");
        printf("2\t\tYOUR BOOKING\n");
        printf("3\t\tBOOK A TICKET\n");
        printf("4\t\tCANCEL A TICKET\n");
        printf("5\t\tEXIT\n");
        printf("\nENTER YOUR OPTION:");
        printf("\e[5m |\e[0m");
        scanf("%d",&option);
        if ( (option >= 1) && (option <=5))
        {
            switch(option)
            {
                case 1:display_movies(movie_list_head);break;
                case 2:display_bookings();break;
                case 3:book_tickets();break;
                case 4:cancel_tickets();break;
                case 5:deinit();return 0;break;
                default:printf("\nERROR: INVALID OPTION!! PLEASE ENTER THE OPTION FROM THE MENU.\n");break;
            }
        }
        else
        {
            scanf("%c",&junk);
            printf("\nERROR: INVALID OPTION!! PLEASE ENTER THE OPTION FROM THE MENU.\n");
        }
    }
    return 0;
}
