// C coding
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct clip {
  int views;
  char *user;
  char *id;
  char *dur;
  char *title;
  struct clip *next;
};

struct clip * head=NULL;

//Function Prototypes
void print();
void getdata();
void split_line(char * line);

int main(int argc, char *argv[])
{
	getdata();
	print();
}

void getdata(){
    FILE * file=fopen("youtube.csv", mode);
	char * mode="r";
	char line[255]="";

	if (file==NULL){
		printf("File could not be open");	
	}else{
		while (fgets(line, sizeof(line), file)){
			//printf("%s", line);
			split_line(line);
		}
	}
}

void split_line(char * line){
	int pos=0, views=0, len=0;
	char * token=NULL;
	char * tmp_string=NULL;
	struct clip * tmp=NULL;
	struct clip * current=NULL;
	tmp=malloc(sizeof(struct clip));
	
	//views
	token=strtok(line,",");
	tmp->views=atoi(token);
	//user
	token=strtok(NULL,",");
	tmp_string=malloc(sizeof(char)*strlen(token));
	strcpy(tmp_string,token);
	tmp->user=tmp_string;
	//dur
	token=strtok(NULL,",");
	tmp_string=malloc(sizeof(char)*strlen(token));
	strcpy(tmp_string,token);
	tmp->dur=tmp_string;
	//title
	token=strtok(NULL,",");
	tmp_string=malloc(sizeof(char)*strlen(token));
	strcpy(tmp_string,token);
	tmp->title=tmp_string;
	//id
	token=strtok(NULL,",");
	tmp_string=malloc(sizeof(char)*strlen(token));
	strcpy(tmp_string,token);
	tmp->id=tmp_string;
	tmp->next=NULL;

	if (head==NULL){
		head=tmp;
	}else{
		current=head;
		while(current->next){
			current=current->next;
		}
		current->next=tmp;
	}
}

void print(){
	struct clip * current=head;
	while(current)
	{	
		printf("%d %s, %s, %s, %s \n",current->views,current->user,current->dur,current->title,current->id);	
		current=current->next;
	}
}








