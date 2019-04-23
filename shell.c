#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




void *myProcess(void *command) {
   
   char* cmd= NULL;
   cmd =(char*) command;
   
   char *run = strtok(cmd, "|");
   
   system(run);
  
   while( run != NULL ) {
      
      

      run = strtok(NULL, "|");
      if(run != NULL){
      system(run);
      
      }
   }
   
   pthread_exit(NULL);
   return 0;
}




int main(int argc, char *argv[]) {
   FILE *fptr;
   if(argc>2){
      printf("Incorrect number of arguments!!!\n");
      return 0;
   }
   else if(argc==2){
      
      fptr=fopen(argv[1],"r");
      if(fptr==NULL){
         printf("File couldn't found!!!\n");
         return 0;
      }
   }

   
   

   while (1){

      char input[512];
      char inputtest[1024*1024*3];
      
      
      if(argc==2){
         
         if(fgets(inputtest,512,fptr)==NULL){
            return 0;
         }
         
      }else{
         
         gets(inputtest);
        
      }
      if(strlen(inputtest)>512){
            printf("Too long command line!!!!\n");
            continue;
         }
      strcpy(input,inputtest);
      if(argc==2)
         printf("%s\n",input);
      
      if(*input=='\0')
         continue;
      int found=0;
      int quit=-1;
      do{
      if(strlen(input)==0){
         break;
      }
      char* search = input;
      quit=-1;
      for(int i = 0; i < strlen(search);i++){
         if(*(search+i)=='q'){
            quit=i;
         }else if(*(search+i)=='u' && quit!=-1){
            
            if(quit+1!=i){
               quit=-1;
            }
         }else if(*(search+i)=='i'&& quit!=-1){
            
            if(quit+2!=i){
               quit=-1;
            }
         }else if(*(search+i)=='t'&& quit!=-1){
            
            if(quit+3!=i){
               quit=-1;
            }else{
               found=1;
            }
         }

      }
      
      if(quit!=-1){
         int sub=0;
         
      for(int i = 0; i < strlen(input); i++)
      {
         if(quit==i)
         {
            i+=4;
         }
         input[sub]=input[i];
         sub++;
      }
      input[sub]='\0';

      
      }
      }while(quit!=-1);

      if(strlen(input)==0){
         if(found)
         return 0;
         else
         {
            continue;
         }
         
      }
      int istherechar=0;
      for(int k=0;k<strlen(input);k++){
         if(isalpha(input[k]))
            istherechar=1;
      }
      if(istherechar==0){
         if(found)
         return 0;
         else
         {
            continue;
         }
         }
      int spaces[strlen(input)];
      int character=0;
      for(int i=0;i<strlen(input);i++){
         if(character==1 &&input[i]!=' '){
            character=0;
         }
         if(character==1&&input[i]==' '){
            spaces[i]=1;
         }else{
            spaces[i]=0;
         }
         
         if(input[i]==';'||input[i]=='|'){
            character=1;
         }

      }
      int sub=0;
      for(int i = 0; i < strlen(input); i++)
      {

         if(spaces[i]){
            continue;
         }
         input[sub]=input[i];
         sub++;
      }
      input[sub]='\0';
      

      char* threadin[512];
      for(int i=0;i<512;i++)
         threadin[i]=NULL;
      char *command=NULL;
      command= strtok(input, ";");
      threadin[0]=(char*)malloc(512*sizeof(char));
      strcpy(threadin[0],command );
      int i =1;
      
      while( command != NULL ) {
      command= strtok(NULL,";");
      if ( command != NULL){
         threadin[i]=(char*)malloc(512*sizeof(char));
         strcpy(threadin[i],command );
         
         i++;
      }
      
      }

      pthread_t threads[i];
      
      int rc;
      long t; 
      for(int t=0;t<i;t++) {
         rc = pthread_create(&threads[t], NULL, myProcess, (void *)threadin[t]);
         if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
           exit(-1);
         }
      }

      for(int j =0;j<i;j++){
         
         pthread_join(threads[j],NULL);

      }

      for(int k=0;k<i;k++)
      free(threadin[k]);
      if(found){
         return 0;
      }

   }
 
    /*Last thing that main() should do */
   pthread_exit(NULL);
   return 0;
}
