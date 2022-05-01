#include<bits/stdc++.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;

int main(){
	char *username = getlogin();
	int ret = -1;
	char cmd1[100], cmd2[100], cmd3[100], cmd4[100], cmd5[100], cmd6[100];

	// Change owners for files
	sprintf(cmd1, "echo %s | sudo -S chown admin a.out main.cpp marksheet.txt terminal_output.txt", username);
	ret = system(cmd1);
	if(ret)
		cout << "Execution Failed!!!" << endl;

	// Change groups for files
	sprintf(cmd2, "echo %s | sudo -S chgrp read a.out main.cpp marksheet.txt terminal_output.txt", username);
	ret = system(cmd2);
	if(ret)
		cout << "Execution Failed!!!" << endl;

	// Changing file permissions
	sprintf(cmd3, "echo %s | sudo -S chmod 711 a.out", username);
	ret = system(cmd3);
	if(ret)
		cout << "Execution Failed!!!" << endl;

	sprintf(cmd4, "echo %s | sudo -S chmod 750 main.cpp", username);
	ret = system(cmd4);
	if(ret)
		cout << "Execution Failed!!!" << endl;

	sprintf(cmd5, "echo %s | sudo -S chmod 600 marksheet.txt", username);
	system(cmd5);
	if(ret)
		cout << "Execution Failed!!!" << endl;

	sprintf(cmd6, "echo %s | sudo -S chmod 660 terminal_output.txt", username);
	system(cmd6);
	if(ret)
		cout << "Execution Failed!!!" << endl;
	////////////////////////////////////////	
	return 0;
}
