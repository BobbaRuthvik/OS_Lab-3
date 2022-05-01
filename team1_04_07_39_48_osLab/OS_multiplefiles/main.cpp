#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
using namespace std;


int main(){

	char *username = getlogin();
	printf("username: %s\n",username);
	
	//for S1 user, username = S1
	int noOfFaculty = 2;
	char filename[10];
	if(strcmp(username,"S1")==0){
		for(int i=1; i<=noOfFaculty; i++){
			strcpy(filename,"f");
			//concatenate i to filename
			strcat(filename,"s1");
			//command: open f1s1.txt; then read it and print to command line.
		}

	}
	/*else if{
		//other users
	}*/
	else{
		cout << "user other than root" << endl;
	}

	return 0;

}
