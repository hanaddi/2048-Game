#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "2048.h"

int main(){
	char pil;
	char q;
	hs user;
	createhs();
	loadhs();
	srand (time(NULL));
	do{
		ShowMenu();
		setBufferedInput(false);
		pil=getchar();
		setBufferedInput(true);
		switch (pil) {
			case '1' : {
				play();
				savehs();
				break;
			}
			case '2' : {
				loadhs();
				tulishs();
				printf("Press Enter to Continue...\n");
				scanf("%c",&q);
				break;
			}
			case '3' : {
				HowToPlay();
				printf("Press Enter to Continue...\n");
				scanf("%c",&q);
				break;
			}
			case '4' : {
				About();
				printf("Press Enter to Continue...\n");
				scanf("%c",&q);
				break;
			}
			case '5' : {
				system("clear");
				printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"); usleep(50000);
				printf("░░░░░       ░░░░░░  ░░░  ░░░░        ░░░░░\n"); usleep(50000);
				printf("░░░░░  ░░░░  ░░░░░  ░░░  ░░░░  ░░░░░░░░░░░\n"); usleep(50000);
				printf("░░░░░       ░░░░░░       ░░░░      ░░░░░░░\n"); usleep(50000);
				printf("░░░░░  ░░░░░  ░░░░░░░ ░░░░░░░  ░░░░░░░░░░░\n"); usleep(50000);
				printf("░░░░░        ░░░░░░░░ ░░░░░░░        ░░░░░\n"); usleep(50000);
				printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"); usleep(50000);
				printf("░      ░░░░        ░░░░  ░░░  ░░░░       ░\n"); usleep(50000);
				printf("░░░░░  ░░░░  ░░░░  ░░░░  ░░░  ░░░░  ░░░  ░\n"); usleep(50000);
				printf("░      ░░░░  ░░░░  ░░░░       ░░░░       ░\n"); usleep(50000);
				printf("░  ░░░░░░░░  ░░░░  ░░░░░░░░░  ░░░░  ░░░  ░\n"); usleep(50000);
				printf("░      ░░░░        ░░░░░░░░░  ░░░░       ░\n"); usleep(50000);
				printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"); usleep(50000);
				break;
			}
			default :
				printf("\x1b[31mINPUT SALAH!! ULANGI!!\x1b[0m");
		}
	}while(pil!='5');

	return 0;
}
