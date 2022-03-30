#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
void signUp();
void signIn();
void printMenu();
void enterChoice();
void dashboard(char activeUser[]);
void maskpassword(char mskpw[]);
void adminDashboard();
FILE *fptr;
struct userdata {
	char name[50];
	char email[50];
	char password[50];
	int status;
}receive,send;
int main(){
	while(1){
		printMenu();
		enterChoice();
		getch();
		system("cls");
	}
	return 0;
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
			dashboard(receive.name);
			goto loginclose;
		}
	}
	printf("password and email do not match");
	loginclose:
	fclose(fptr);
}
void signUp() {
	char retype[50];
	printf("Enter your full name:\n");
	fflush(stdin);
	gets(send.name);
	emailExists:
	printf("Enter your email:\n");
	fflush(stdin);
	gets(send.email);
	fptr = fopen("userdata.txt","r");
	while(fread(&receive,sizeof(struct userdata),1,fptr)){
		if(strcmp(send.email,receive.email)==0){
			printf("Email already exists.\n");
			goto emailExists;
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
		fptr=fopen("userdata.txt","a+");
		fwrite(&send,sizeof(struct userdata),1,fptr);
		fclose(fptr);
		char* extention = ".txt";							//this creates a file //
		fptr=fopen(strcat(send.email,extention),"a+");
		fclose(fptr);
	}else{
		printf("\nPassword do not match\n Please retype\n");
		goto passwordIncorrect;
	}
}
void printMenu(){
	printf("\n\tMENU DEMONSTRATION");
	printf("\n\t------------------------------");
	printf("\n\n\t Choose your opetion:\n");
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

void dashboard(char activeUser[]){
	fclose(fptr);
	adminDashboard();
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
void adminDashboard(){
	printf("Welcome to the admin dashboard");
	
}
