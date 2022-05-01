#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	//printf("hi\n");
	if(argc!=4){
		printf("Invalid input arguments\n");
	}
	int teacher_count = atoi(argv[1]);
	int userType = atoi(argv[2]);
	int rw_permissions = atoi(argv[3]);
	char command[50];
	sprintf( command, "./kilo marksheet.txt %d %d %d", teacher_count, userType, rw_permissions );
	system(command);
	int n;
	//scanf("%d", &n);
	printf("Output\n");
	printf("%s\n", command);
	int fd2;
	if((fd2 = open("marksheet.txt", O_RDONLY)) == -1){
		printf("Error Number %d\n", errno);
		perror("Couldn't open file test.txt\n");
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
	
	for(int i=0; i<count_line; i++){
		printf("%s\n", score[i]);
	}
	printf("\n");
	return 0;
}
