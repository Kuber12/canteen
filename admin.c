#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
void signUp();
void signIn();
void printMenu();
void enterChoice();
void dashboard();
void maskpassword(char mskpw[]);
char activeUserName[50];
char activeUserEmail[50];
char emailBeforeA[50];
int dashboardChoice();
void menuCreator();
void viewMenu();
void adminInterface();
void userInterface();
char* extention = ".txt";
char *ptr;
FILE *fptr;
struct userdata {
	char name[50];
	char email[50];
	char password[50];
	int status;
}receive,send;
struct menu{
	char item[10];
	char price[10];	
}r;
int main(){
	printf("Are you a admin or a user?\n1. F");
	return 0;
}
void adminInterface(){
	while(1){
		printMenu();
		enterChoice();
		getch();
		system("cls");
	}
}

void signIn() {
	char userEmail[50];
	char userPassword[50];
	printf("Enter your email:\n");
	fflush(stdin);
	gets(userEmail);
	printf("Enter your password:\n");
	fflush(stdin);
	maskpassword(userPassword);
	fptr = fopen("userdata.txt","r");
	while(fread(&receive,sizeof(struct userdata),1,fptr)){
		if(strcmp(userEmail,receive.email)==0 && strcmp(userPassword,receive.password)==0){
			strcpy(activeUserEmail,receive.email);
			strcpy(activeUserName,receive.name);
			ptr = strchr(activeUserEmail, '@');  //this removes @
			if (ptr != NULL) {
			    *ptr = '\0';
			}
			strcat(activeUserEmail,extention);
			getch();
			dashboard();
			goto loginclose;
		}
	}
	printf("password and email do not match");
	loginclose:
	fclose(fptr);
}
void signUp() {
	int i,count;
	char retype[50];
	char temp[50];
	printf("Enter your full name:\n");
	fflush(stdin);
	gets(send.name);
	retypeEmail:
	printf("Enter your email:\n");
	fflush(stdin);	
	strcpy(temp,gets(send.email));
	i=0;
	count=0;
	for(i;i<=strlen(temp);i++){					//email validator for now//
		if(temp[i]=='@'){
			count++;
		}
	}
	if(count == 1){									
		printf("its a valid email noice man\n");
	}else{
		printf("envter a valid email you noob\n");
		goto retypeEmail;
	}
	
	fptr = fopen("userdata.txt","r");
	while(fread(&receive,sizeof(struct userdata),1,fptr)){
		if(strcmp(send.email,receive.email)==0){
			printf("Email already exists.\n");
			goto retypeEmail;
		}
	}
	passwordIncorrect:
	printf("Enter your password:\n");
	fflush(stdin);
	maskpassword(send.password);
	printf("\nRetype your password\n");
	maskpassword(retype);
	if(strcmp(send.password,retype)==0){
		puts("\nYou are now registered.\n");
		strcpy(activeUserEmail,send.email);
		strcpy(activeUserName,send.name);
		
		fptr=fopen("userdata.txt","a+");
		
		fwrite(&send,sizeof(struct userdata),1,fptr);
		fclose(fptr);
		ptr = strchr(activeUserEmail, '@');  //this removes @
		if (ptr != NULL) {
		    *ptr = '\0';
		}
		
		fptr=fopen(strcat(activeUserEmail,extention),"a+");//this creates a file //
		printf("%s",activeUserEmail);
		fclose(fptr);
	}else{
		printf("\nPassword do not match\n Please retype\n");
		goto passwordIncorrect;
	}
}
void printMenu(){
	printf("\n\tADMIN PANEL");
	printf("\n\t------------------------------");
	printf("\n\n\t Choose your option:\n");
	printf("\n\t r to register:");
	printf("\n\t s to sign in:");
	printf("\n\t w to view all user data:");
	printf("\n\t e EXIT\n");
}
void enterChoice(){
	char ch;
	scanf("%c", &ch);
	switch(ch) {
	    case 'r' :
        	signUp();
            break;
	    case 's' :
	     	signIn();
	        break;
	    case 'e':
	    	printf("Thank you for using our application");
	    	exit(0);
	    	break;
	    case 'w':
	    	puts("\tAll user data:");
	    	puts("\tName\t\t\t\t|\tEmail\t\t\t|\tPassword\n\n");
	    	fptr=fopen("userdata.txt","r");
			while(fread(&receive,sizeof(struct userdata),1,fptr)){
				printf("\t%s\t\t\t\t|\t%s\t\t\t|\t%s \n",receive.name,receive.email,receive.password);
			}
			fclose(fptr);
			break;
		case '\n':
			puts("Press any key to Continue");
			break;
	    default:
	    	printf("Invalid character\n");
	    	break;
		}
}

void dashboard(){
	fclose(fptr);
	int e = 1;
	while(e){
		system("cls");
		printf("Welcome to the dashboard, %s\n",activeUserName);
		printf("Enter your choice:\n");
		puts("Press 1 to add menu\nPress2 for ...\nPress 0 to exit to mainmenu");
		e = dashboardChoice();
	}
}
void maskpassword(char mskpw[]){
	int i=0;
	char pw;
	while(1){
		pw=getch();
		if(pw==13 || pw==9){	//ASCII Enter=13 , Tab=9 , Backspace=8
			mskpw[i] = '\0';
			break;
		}
		else if(pw==8 && i>0){
			i--;
			printf("\b \b");
		}
		else{
			mskpw[i++]=pw;
			printf("*");
		}
	}
}
void menuCreator(){
	system("cls");
	char yn;
	fptr=fopen(activeUserEmail,"a+");
	printf("Welcome to Menu Generator %s,\n",activeUserName);
	addMore:
	puts("Enter your item: ");
	fflush(stdin);
	gets(r.item);
	puts("Enter the price for your item: ");
	fflush(stdin);
	gets(r.price);
	fwrite(&r,sizeof(struct menu),1,fptr);
	printf("press y if you want to continue adding more items\n");
	scanf("%c",&yn);
	if(yn == 'y' || yn=='Y'){
		goto addMore;
	}else{
		printf("Items added successfully");
	}
	fclose(fptr);
}
void viewMenu(){
	system("cls");
	fptr = fopen(activeUserEmail,"r");
	printf("\nHi %s, this is our menu today. Looks good?\n",activeUserName);
	printf("\n\t------------------------------\n");
	while(fread(&r,sizeof(struct menu),1,fptr)){
		printf("\t%s\t|\t%s\n",r.item,r.price);
	}
}
int dashboardChoice(){
	char ch;
	ch = getchar();
	switch(ch){
		case '1':
			menuCreator();
			getch();
			break;
		case '2':
			viewMenu();
			getch();
			break;
		case '0':
			return 0;
			break;
		case '\n':
			printf("Press any key to continue");
			getch();
			break;
		default:
			printf("Invalid choice");
			break;
	}
	
}
