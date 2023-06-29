#include<stdio.h>
#include<string.h>
#include "color.h"

#define MAX_VOTERS 100
#define MAX_CANDIDATES 5

struct Date{
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

typedef struct voter{ //Voters who will vote
    char uname[50];
    struct Date dob;
    int id;
    char password[50];
    int area; 
    int has_voted; //voted or not?
}voting;

typedef struct candidate { // Candidates who need votes
    char fname[25];
    char lname[25];
    char vote_sign[2];
    int vote_count; 
}candid;


void login(int *Verify);
void register_voter(voting *voter_arr,int* num_voters,int log);
void update_profile(voting *voter_arr,int num_voters,int log,int index);
void display_voting_date();
void insert_candid(candid *cand_arr,int* num_candid);
void display_results(candid *cand_arr, int num_candidates);
void vote(candid *cand_arr, int num_candidates,int log,int index,voting *voter_arr);
void login_logout(voting *voter_arr,int num_voters,int* log,int* index);
void display_candidates(voting *voter_arr,int log,int index);

int main() {
	int choice = 0,num_voters,num_candid; //Variable to perform Operation
	int Verify=0; // variable to check if the password entered is correct or not
    login(&Verify); // Login/Authentication
    voting voter_arr[MAX_VOTERS]; //Creating array to store details of 100 Voters
    candid cand_arr[MAX_CANDIDATES]; //Creating array to store details of 5 Candidates
    num_voters=0; //Number of voters in the database
    num_candid=0; //Number of candidates standing for election in the database
    int log=0;//Variable to check if the user is logged in or not
    int index=-1; //index where the details of the voters is stored in the database
    if (Verify==1) {
	do {
	cyan();
	printf("\n\n");
	printf("------------------------------------\n");
	printf("\tONLINE VOTING SYSTEM\n");
	printf("------------------------------------\n");
	printf("\n1. Insert Candidate\n");
	printf("2. Register Voter\n");
	printf("3. Login/Logout\n");
	printf("4. Update Profile\n");
	printf("5. Display Voting Date\n");
	printf("6. Display Profile\n");
	printf("7. Vote\n");
	printf("8. Display Results\n");
	printf("9. Quit\n");
	purple();
	printf("\nEnter your choice: ");
	scanf("%d", &choice);
	system("cls");
	switch(choice) {
	case 1:
	    insert_candid(cand_arr,&num_candid);
	    break;
        case 2:
            register_voter(voter_arr,&num_voters,log);
            break;
        case 3:
            login_logout(voter_arr,num_voters,&log,&index);
            break;
        case 4:
            update_profile(voter_arr,num_voters,log,index);
            break;
        case 5:
            display_voting_date();
            break;
        case 6:
            display_candidates(voter_arr,log,index);
            break;
        case 7:
            vote(cand_arr,num_candid,log,index,voter_arr);
            break;
        case 8:
            display_results(cand_arr,num_candid);
            break;
        case 9:
        	system("cls");
        	green();
            printf("Exiting Program. Thank You!\n");
            reset();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
} while(choice != 9);
}
	red();
    printf("You have successfully exited the program...\n\n");
    reset();
    return 0;
}

void login(int *Verify) {
    char password[15];
    blue();
    printf("\nEnter Password: ");
    scanf("%s",&password);
    system("cls");
    FILE *pass;
    pass=fopen("Password.txt","r");
    char myString[15];
    fgets(myString,15,pass); 
    fclose(pass);
    if (strcmp(password, myString) == 0) {
    	green();
        printf("Login Successful!\n\n");
        *Verify=1; //Value changed as pass is true
        reset();
    } 
	else {
		red();
        printf("Wrong Password, Login Failed. Try Again!.\n");
		reset(); //else program is closed
    }
}

void register_voter(voting *voter_arr,int* num_voters,int log) {
	if (log==2){ 
		red();
        printf("You are already logged in!\n,Try Again...\n");
        reset();
        return;
    }
    if(*num_voters >= MAX_VOTERS) {
    	red();
        printf("Sorry, Maximum number of voters reached.\n");
        reset();
        return;
    }
    yellow();
    voting new_voter; // Creating new structure and assign the details in the existing structure in the end
    printf("Enter User name: ");
    scanf("%s",&new_voter.uname);
    printf("Enter Day of Date Of Birth (DD): ");
    scanf("%d",&new_voter.dob.day);
    printf("Enter Month of Date Of Birth (MM): ");
    scanf("%d",&new_voter.dob.month);
    printf("Enter Year of Date Of Birth (YYYY): ");
    scanf("%d",&new_voter.dob.year);
    reset();
    if (new_voter.dob.year>2005)
	{
		system("cls");
		red();
        printf("Sorry, you must be 18 years or above to be eligible for voting.\n");
        reset();
        return;
	}
	yellow();
    printf("Enter Area (1, 2, 3): ");
    scanf("%d",&new_voter.area);
    if (new_voter.area!=1&&new_voter.area!=2&&new_voter.area!=3)
	{
		system("cls");
		red();
        printf("Sorry,Invalid Address\nPlease Choose address b/w 1 and 3\n");
        reset();
        return;
	}
    printf("Enter Your password: ");
    scanf("%s",&new_voter.password);
    new_voter.has_voted = 0; //Initially the user hasn't voted
	reset();

    // Generate unique voter ID
    new_voter.id=*num_voters+1;

    voter_arr[*num_voters] = new_voter;
    *num_voters=*num_voters+1; //Moving the pointer to the next memory address
    green();
    system("cls");
    printf("Registration Successful. Your voter ID is %d\n", new_voter.id);
    printf("Please remember your id and password to perform other operations in Future ...\n");
    reset();
}

void update_profile(voting *voter_arr,int num_voters,int log,int index) {
	if (log==0){ 
		red();
        printf("Log in to your ID First!\n");
        reset();
        return;
    }
	    yellow();
	    voting new_voter;
	    printf("Enter New User name: ");
	    scanf("%s",&new_voter.uname);
	    printf("Enter Day of Date Of Birth (DD): ");
	    scanf("%d",&new_voter.dob.day);
	    printf("Enter Month of Date Of Birth (MM): ");
	    scanf("%d",&new_voter.dob.month);
	    printf("Enter Year of Date Of Birth (YYYY): ");
	    scanf("%d",&new_voter.dob.year);
	    reset();
	    if (new_voter.dob.year>2005)
		{
		system("cls");
		red();
        printf("Sorry, you must be 18 years or above to be eligible for voting.\n");
        reset();
        return;
		}
		yellow();
	    printf("Enter New Area (1, 2, 3): ");
	    scanf("%d",&new_voter.area);
	    if (new_voter.area!=1&&new_voter.area!=2&&new_voter.area!=3)
	{
		system("cls");
		red();
        printf("Sorry,Invalid Address\nPlease Choose address b/w 1 and 3\n");
        reset();
        return;
	}
		reset();
		voter_arr[index] = new_voter;
		system("cls");
		green();
		printf("\n\nProfile updated successfully.\n");
		reset();	
		}
	
void display_results(candid *cand_arr, int num_candidates) {
	if (num_candidates==0){ 
		red();
        printf("Candidate List is Empty!\n");
        reset();
        return;
    }
green();
printf("Results:-\n\n");
reset();
int i;
white();
for(i = 0; i < num_candidates; i++) {
printf("Candidate %d: %s %s [%s]-> %d\n",i+1, cand_arr[i].fname,cand_arr[i].lname,cand_arr[i].vote_sign, cand_arr[i].vote_count);
}
reset();
}

void display_voting_date() {
	green();
printf("The Voting Date is 10th April 2023.\n");
reset();
}

void insert_candid(candid *cand_arr,int* num_candid){
	if(*num_candid >= MAX_CANDIDATES) {
    	red();
        printf("Sorry, Maximum number of Candidates has been reached.\n");
        reset();
        return;
    }
    yellow();
    candid new_candid; 
	int z;
    printf("Enter First name: ");
    scanf("%s",&new_candid.fname);
    printf("Enter Last name: ");
    scanf("%s",&new_candid.lname);
    printf("Enter Your Vote sign (*,^,$,#,@): ");
    scanf("%s",&new_candid.vote_sign);
    reset();
    for(z=0;z<*num_candid;z++){
    	if(strcmp(new_candid.vote_sign,cand_arr[z].vote_sign)==0){
    		system("cls");
    		red();
    		printf("Sorry, Selected Voting Symbol is already chosen by other candidate!\n");
    		reset();
    		return;
		}
	}
    new_candid.vote_count = 0;
	reset();

    cand_arr[*num_candid] = new_candid;
    *num_candid=*num_candid+1; //Moving the pointer to the next memory address
    green();
    system("cls");
    printf("\n\nCandidate values inserted Successfully.\n");
    reset();
}

void vote(candid *cand_arr, int num_candidates,int log,int index,voting *voter_arr) {
	if (log==0){ 
		red();
        printf("Log in to your ID First!\n");
        reset();
        return;
    }
		if (num_candidates==0){ 
		system("cls");
		red();
        printf("Candidate List is Empty!\n");
        reset();
        return;
    }
    if (voter_arr[index].has_voted==1){ 
		system("cls");
		red();
        printf("Sorry, You have already Voted!\n");
        reset();
        return;
    }
    system("cls");
    green();
	printf("Please Choose the Party from the below to vote:- \nParty Name\t\t Party Symbol\n");
	reset();
	white();
	int z;
	for(z=0;z<num_candidates;z++){
		printf("%d: %s %s \t %s\n",z+1,cand_arr[z].fname,cand_arr[z].lname,cand_arr[z].vote_sign);
	}
	reset();
	char sign[2];
	int found2=0; //variable to check if the party exists or not
	purple();
	printf("Please enter the symbol of the Candidate to vote: ");
	scanf("%s",&sign);
	reset();
	int j;
	for(j=0;j<num_candidates;j++){
		if(strcmp(cand_arr[j].vote_sign,sign)==0){
			found2++;
			cand_arr[j].vote_count+=1;
			voter_arr[index].has_voted=1;
			system("cls");
			green();
			printf("Your Vote has been taken successfully!\n");
			reset();
		}
	}
	
	if(found2==0){
		system("cls");
		red();
        printf("Invalid Choice, Please Try Again!\n");
        reset();
        return;
	}		
}

void login_logout(voting *voter_arr,int num_voters,int* log,int* index){
	int id;
	char pass[50];
	if (num_voters==0){ 
		red();
        printf("Registeration List is Empty!\n");
        reset();
        return;
    }
    else{
	if(*log==2){
		system("cls");
		green();
		printf("ID %d have been successfully logged out!\n",*index+1);
		*log=0;
		*index=-1;
		reset();
		return;
	}
	if(*log==0){
		purple();
		printf("Please enter your id: ");
		reset();
		scanf("%d",&id);
		int i;
		int found=0;
		for(i=0;i<num_voters;i++){
			if(voter_arr[i].id==id){
				purple();
				printf("Please enter your password to continue: ");
				scanf("%s",&pass);
				reset();
				if(strcmp(voter_arr[i].password,pass)!=0){
					red();
					system("cls");
					printf("Sorry, Wrong Password\n");
					printf("Please, Try Again!\n");
					reset();
					return;
				}
				system("cls");
				green();
				printf("User Verified :-\n\n");
				found++;
				printf("ID %d have been successfully logged in!\n\n",i+1);
				*log=2;
				*index=i;
				reset();
				return;
			}
		}
		if(found==0){
			red();
			system("cls");
			printf("Record of the user not found\nPlease Try Again!\n\n");
			reset();
			return;
		}
		}
	}
}

void display_candidates(voting *voter_arr,int log,int index){
	if (log==0){ 
		red();
        printf("Log in to your ID First!\n");
        reset();
        return;
    }
    green();
    printf("Voter Details are :-\n");
    reset();
    white();
    printf("\nID:- %d",voter_arr[index].id);
    printf("\nCurrent Password :- %s",voter_arr[index].password);
    printf("\nUsername:- %s",voter_arr[index].uname);
    printf("\nD.O.B:- %d/%d/%d",voter_arr[index].dob.day,voter_arr[index].dob.month,voter_arr[index].dob.year);
    printf("\nArea:- %d",voter_arr[index].area);
    printf("\nHas voted: %s\n\n", voter_arr[index].has_voted==1?"Yes":"No");
    reset();
}
