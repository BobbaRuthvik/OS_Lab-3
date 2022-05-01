#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
extern int errno;
using namespace std;

bool run = true;
char global_username[100] = "";

int getWords(char *base, char target[1024][1024]){
	int n = 0, i, j = 0;
	for(i=0; 1; i++){
		if(base[i] != ' '){
			target[n][j++] = base[i];
		}
		else{
			target[n][j++] = '\0'; //insert NULL
			n++;
			j = 0;
		}
		if(base[i] == '\0')
			break;
	}
	return n;
}

int compare(char a[], char b[]){
	int flag = 0, i = 0;
	while(a[i] != '\0' && b[i] != '\0'){
		if(a[i]!=b[i]){
			flag = 1;
			break;
		}
		i++;
	}
	if(flag==0) return 0;
	else return 1;
}

void INThandler(int sig){
	char c;
	signal(sig, SIG_IGN);
	cout << endl;
	cout << "OUCH, did you hit Ctrl-C" << endl;
	cout << "Do you really want to quit? [y/n]: ";
	cin >> c;
	if(c == 'y' or c == 'Y'){
		/*
		char cmd2[100];
		sprintf(cmd2, "echo %s | sudo -S chmod 600 marksheet.txt", global_username);
		int ret = system(cmd2);
		if(ret==0)
			printf("Permissions of read removed from marksheet.txt\n");
		else
			printf("Unable to remove read permissions to marksheet.txt\n");
		*/
		exit(0);
	}
	else{
		signal(SIGINT, INThandler);
	}
}

int main(){
signal(SIGINT, INThandler);
while(run){
	//char terminal_buffer[100];
	char command[100];
	char *username = getlogin();
	strcpy(global_username, username);
	printf("Username: %s\n", username);
	strcpy(command, "groups ");
	int idx = 7;
	//printf("Part command: %s\n", command);
	//printf("Username length: %d\n", strlen(username));
	for(int i=0; i<strlen(username); i++){
		command[idx++] = username[i];
	}
	username[strlen(username)] = '\0';
	command[idx] = '\0';
	//printf("Part here: %s\n", command);
	strcat(command, " >> terminal_output.txt");
	//printf("final command: %s\n", command);
	system(command);
	//printf("Reached out of command\n");
	int fd1;
	if((fd1 = open("terminal_output.txt", O_RDONLY)) == -1){
		printf("Error Number: %d\n", errno);
		perror("Couldn't open file terminal_output.txt\n");
		exit(1);
	}
	char pc[1024];
	char words[1024][1024];
	char student[100] = "student";
	char teacher[100] = "teacher";
	char admin[100] = "admin";
	while(read(fd1, pc, 1024)){
		
		int ret = 0;
		char cmd1[100];
		sprintf(cmd1, "echo %s | sudo -S chmod 666 marksheet.txt", username);
		ret = system(cmd1);
		if(ret==0)
			printf("Read permission given to marksheet.txt\n");
		else
			printf("Unable to give read permission to marksheet.txt\n");

		int fd2;
		if((fd2 = open("marksheet.txt", O_RDONLY)) == -1){
			printf("Error Number %d\n", errno);
			perror("Couldn't open file marksheet.txt\n");
			exit(1);
		}
		char c;
		int len = 0;
		int line = 0;
		int count_line = 0;
		char score[1024][1024];
		while(read(fd2, &c, 1) == 1){
			if(c == '\n'){
				score[line][len] = '\0';
				count_line++;
				//printf("%s\n", score[line]);
				line++;
				len = 0;
			}
			else{
				score[line][len++] = c;
			}
		}
		if(close(fd2) < 0){
			printf("Error Number %d\n", errno);
			perror("Unable to close file marksheet.txt\n");
			exit(1);
		}
			
		// get teacher in array
		char teacher_list[1024][1024];
		int teacher_count = getWords(score[0], teacher_list);
		/*
		printf("i ");
		for(int i=1; i<=teacher_count; i++){
			printf("%s ", teacher_list[i]);
		}
		printf("\n");
		*/
		// similarly make a student list
		int group_count = getWords(pc, words);
		/*
		for(int i=0; i<=group_count; i++){
			printf("Group: %s\n", words[i]);
		}
		*/
		//run = false;
		
		for(int i=0; i<=group_count; i++){
			//printf("Group: %s\n", words[i]);
			if(compare(words[i], admin) == 0){
				//printf("iam admin\n");
				for(int i=0; i<count_line; i++){
					printf("%s\n", score[i]);
				}
				cout << "OPTION PANEL: " << endl;
				cout << "1 --> Add Student" << endl;
				cout << "2 --> Add Teacher" << endl;
				cout << "3 --> View Marksheet" << endl;
				cout << "4 --> Edit Marks" << endl;
				cout << "Anything else --> EXIT" << endl;
				int opt;
				cout << "Select output opt: ";
				cin >> opt;
				if(opt==1){
					cout << "Please add student to wheel, student and read  groups" << endl;
					cout << "Loading setup..." << endl;
					sleep(1);
					int add_ret = 0;
					char add_cmd[100];
					//sprintf(add_cmd, "echo %s | sudo -S adduser", username);
					//add_ret = system(add_cmd);
					add_ret = system("sudo adduser");
					if(add_ret==0)
						printf("adduser ran successfully\n");
					else
						printf("adduser failed to run\n");
					//system("adduser");
					cout << "Create a slot for student in marksheet.txt..." << endl;
					cout << "Loading setup..." << endl;
					sleep(1);
					//system("vim marksheet.txt");
					char echo_cmd[50];
					sprintf(echo_cmd, "echo \"%d " , line);
					for(int j=0; j<teacher_count-1; j++){
						strcat(echo_cmd, "N ");
					}
					strcat(echo_cmd, "N\" >> marksheet.txt");
					printf("Command to run: %s\n", echo_cmd);
					system(echo_cmd);
					char kilo_cmd[50];
					sprintf(kilo_cmd, "./a.out %d 0 1", teacher_count);
					system(kilo_cmd);
		/////////////////////////////////////////////////

					cout << "Student setup complete." << endl;
				}
				else if(opt==2){
					cout << "Please add teacher to wheel, teacher and read groups" << endl;
					cout << "Loading setup..." << endl;
					sleep(1);
					system("sudo adduser");
					cout << "Create a slot for teacher in marksheet.txt" << endl;
					cout << "Loading setup..." << endl;
					sleep(1);
					char kilo_cmd[50];
					sprintf(kilo_cmd, "./a.out %d 0 2", teacher_count);
					system(kilo_cmd);
					//system("vim marksheet.txt");
					cout << "Teacher setup complete." << endl;
				}
				else if(opt==3){
					cout << "View student scores loading setup..." << endl;
					sleep(2);
					char cmd[50];
					sprintf(cmd, "./a.out %d %d %d", teacher_count, 0, 0);
					system(cmd);
				}
				else if(opt==4){
					cout << "Edit student scores, loading setup..";
					sleep(2);
					char cmd[50];
					sprintf(cmd, "./a.out %d %d %d", teacher_count, 0, 1);
					system(cmd);
				}
				else{
					run = false;
				}
			}
			else if(compare(words[i], student)==0){
				//printf("Iam student\n");
				int num_len = strlen(username)-1;
				//printf("Numeric part length: %d\n", num_len);
				char userid[3];
				memcpy(userid, &username[1], num_len);
				userid[num_len] = '\0';
				//printf("User id string format: %s\n", userid);
				int row = atoi(userid);
				//printf("User id in numeric form: %d\n", row);
				printf("i ");
				for(int k=1; k<=teacher_count; k++){
					printf("%s ", teacher_list[k]);
				}
				printf("\n");
				printf("%s\n", score[row]);
				run = false;
			}
			else if(compare(words[i], teacher) == 0){
				//printf("Iam teacher\n");
				int num_len = strlen(username)-1;
				//printf("Numeric part length: %d\n", num_len);
				char userid[3];
				memcpy(userid, &username[1], num_len);
				userid[num_len] = '\0';
				//printf("User id string format: %s\n", userid);
				int t_col = atoi(userid);
				printf("User id in numeric form: %d\n", t_col);
				////////////////////////////
				printf("Marks alloted:\n");
				int sid=0;	
				for(int k=0; k<count_line; k++){
					char target[1024][1024];
					int word_count = getWords(score[k], target);
					if(sid==0){
						printf("i: ");
						sid++;
					}
					else{
						printf("%d: ", sid);
						sid++;
					}
					printf("%s\n", target[t_col]);
				}
				printf("OPTION PANEL:\n");
				printf("1 --> Update Score of Student\n");
				printf("Anything other --> Exit\n");
				int opt;
				printf("Enter option opt: ");
				cin >> opt;
				printf("Opted: %d\n", opt);
				if(opt==1){
					char cmd[50];
					sprintf(cmd, "./a.out %d %d %d", teacher_count, 1, 2*t_col);
					system(cmd);
				/*
					printf("Selected 1\n");
					int student_id;
					printf("Student ID No.: ");
					cin >> student_id;
					printf("ID NUM: %d\n",student_id);
					char new_score[1024];
					printf("New score: ");
					scanf("%[^\n]%*c", new_score);
					printf("New score: %s\n", new_score);
					//new_score[strlen(new_score)-1] = '\0';
					printf("Score length: %d\n", strlen(new_score));
					int fd4 = open("marksheet.txt", O_RDWR);
					int row_skip = 10;
					int curr_skip = 0;
					for(int k=0; k<student_id; k++){
						curr_skip += row_skip;
					}
					curr_skip += (t_col*2);
					int fd5 = lseek(fd4, curr_skip, SEEK_SET);
					printf("Pointer is at %d position\n", fd5);
					char temp[10] = "%";
					write(fd4, temp, 1);
				*/
					printf("Updated score\n");
				}
				else{
					//cout << "Will exit" << endl;
					run = false;
				}
			}
		}
		
		char cmd2[100];	
                sprintf(cmd2, "echo %s | sudo -S chmod 600 marksheet.txt", username);
		ret = system(cmd2);
                if(ret==0)
                	printf("Permissions of read removed from marksheet.txt\n");
                else
                	printf("Unable to remove read permissions to marksheet.txt\n");





	}
	//printf("here out: %s\n", pc);
	
	int fd3 = open("terminal_output.txt", O_WRONLY | O_CREAT | O_TRUNC | 644);
	if(fd3 < 0){
		perror("r1");
		exit(1);
	}
	int sz = write(fd3, "", strlen(""));
	close(fd3);
	
	if(close(fd1) < 0){
		printf("Error Number %d\n", errno);
		perror("Wrong user permissions given. UNABLE TO CLOSE THE FILE\n");
		exit(1);
	}
}
	return 0;
}
