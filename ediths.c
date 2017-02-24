#include <stdio.h>
#include <string.h>
#include "2048.h"

int main(){
	int pil,i;
	
	loadhs();
	do{
		printf("\n***HIGHSCORE EDITOR***");
		printf("\n1. Show HighScore");
		printf("\n2. Edit Name");
		printf("\n3. Edit Score");
		printf("\n4. Save HighScore");
		printf("\n5. Exit");
		printf("\nInput :");
		scanf("%d",&pil);
		
		system("clear");
		if(pil==1){
			sorths();
			tulishs();
		}else tulishs();
		if(pil==2){
			printf("\nInput index (1-10) :");
			scanf("%d",&i);
			if(i>=1 && i<=10){
				printf("Old Name : %s",topten[i].nama);
				printf("\nNew Name : ");
				scanf("%s",&topten[i].nama);
//				fgets(topten[i].nama,sizeof(topten[i].nama),stdin);
			}else{
				printf("\nWrong input");
			}
		}else
		if(pil==3){
			printf("\nInput index (1-10) :");
			scanf("%d",&i);
			if(i>=1 && i<=10){
				printf("Old Score : %d",topten[i].score);
				printf("\nNew Score : ");
				scanf("%d",&topten[i].score);
//				fgets(topten[i].nama,sizeof(topten[i].nama),stdin);
			}else{
				printf("\nWrong input");
			}
		}else
		if(pil==4){
			savehs();
			printf("\nHighScore Saved.\n");
		}
	}while(pil!=5);
	return 0;
}
