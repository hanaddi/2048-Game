#include "2048.h"

/* ----- Konstruktor ----- */
void init(tabel *T) {
	//KAMUS
	address P,Q,R,S;
	int i,j;
	//ALGORITMA
	P=alokasi(Nol);
	LT(*T)=P;
	for(i=1;i<Nmax;i++){
		Q=alokasi(Nol);
		kanan(P)=Q;
		kiri(Q)=P;
		P=Q;
	}
	P=LT(*T);
	for(i=1;i<Nmax;i++){
		Q=alokasi(Nol);
		bawah(P)=Q;
		atas(Q)=P;
		S=kanan(P);
		for(j=1;j<Nmax;j++){
			R=alokasi(Nol);
			kanan(Q)=R;
			kiri(R)=Q;
			atas(R)=S;
			bawah(S)=R;
			Q=kanan(Q);
			S=kanan(S);
		}
		P=bawah(P);
	}
	RB(*T)=R;
}
void load(tabel *T) {
	//KAMUS
	FILE *f;
	//ALGORITMA
	f=fopen(savefile,"r");
	if(f!=NULL){
		fread(&sv,sizeof(sv),1,f);
		if(sv.load==true){
			mattolin(0,LT(*T));
		}
		fclose(f);
	}else{
		sv.load=false;
	}
}
void save() {
	//KAMUS
	FILE *f;
	//ALGORITMA
	f=fopen(savefile,"w");
	fwrite(&sv,sizeof(sv),1,f);
	fclose(f);
}
address alokasi (infotype X) {
	//KAMUS
	address P;
	//ALGORITMA
	do{
		P = (address) malloc (sizeof (Elmt));
	}while(P==Nil);
	info(P)		= X;
	kanan(P)	= Nil;
	kiri(P)		= Nil;
	atas(P)		= Nil;
	bawah(P)	= Nil;
	return P;
}
void showTabel(tabel T) {
	//KAMUS
	address P,Q;
	int i;
	//ALGORITMA
	P=LT(T);
	//Menulis border
	printf("    ╔");
	for(i=1;i<Nmax;i++){
		printf("════════╦");
	}
	printf("════════╗\n");
	Q=P;
	printf("    ║");
	tulisBlank(info(Q));
	printf("║");
	while(kanan(Q)!=Nil){
		Q=kanan(Q);
		tulisBlank(info(Q));
		printf("║");
	}
	printf("\n");
	Q=P;
	printf("    ║");
	tulis(info(Q));
	printf("║");
	while(kanan(Q)!=Nil){
		Q=kanan(Q);
		tulis(info(Q));
		printf("║");
	}
	printf("\n");
	Q=P;
	printf("    ║");
	tulisBlank(info(Q));
	printf("║");
	while(kanan(Q)!=Nil){
		Q=kanan(Q);
		tulisBlank(info(Q));
		printf("║");
	}
	printf("\n");

	while(bawah(P)!=Nil){
		P=bawah(P);

		//menulis border
		printf("    ╠");
		for(i=1;i<Nmax;i++){
			printf("════════╬");
		}
		printf("════════╣");

		Q=P;
		printf("\n    ║");
		tulisBlank(info(Q));
		printf("║");
		while(kanan(Q)!=Nil){
			Q=kanan(Q);
			tulisBlank(info(Q));
			printf("║");
		}
		Q=P;
		printf("\n    ║");
		tulis(info(Q));
		printf("║");
		while(kanan(Q)!=Nil){
			Q=kanan(Q);
			tulis(info(Q));
			printf("║");
		}
		Q=P;
		printf("\n    ║");
		tulisBlank(info(Q));
		printf("║");
		while(kanan(Q)!=Nil){
			Q=kanan(Q);
			tulisBlank(info(Q));
			printf("║");
		}
		printf("\n");


	}
	printf("    ╚");
	for(i=1;i<Nmax;i++){
		printf("════════╩");
	}
	printf("════════╝\n");
}
void lintomat(int brs,address P) {
	//KAMUS
	int kol=0;
	address Q;
	//ALGORITMA
	Q = P;
	while (kanan(Q)!= Nil)
	{
		sv.T[brs][kol]=info(Q);
		Q = kanan(Q);
		kol++;
	}
	sv.T[brs][kol]=info(Q);

	if (bawah(P)!= Nil)
	{
		lintomat(brs+1,bawah(P));
	}
}
void mattolin(int brs,address P) {
	//KAMUS
	int kol=0;
	address Q;
	//ALGORITMA
	Q = P;
	while (kanan(Q)!= Nil)
	{
		info(Q)=sv.T[brs][kol];
		Q = kanan(Q);
		kol++;
	}
	info(Q)=sv.T[brs][kol];

	if (bawah(P)!= Nil && brs<Nmax-1)
	{
		mattolin(brs+1,bawah(P));
	}
}
void salin(address P,address Q) {
	//KAMUS
	address P1,Q1;
	//ALGORITMA
	P1=P;
	Q1=Q;
	while(kanan(P1)!=Nil && kanan(Q1)!=Nil){
		info(Q1)=info(P1);
		P1=kanan(P1);
		Q1=kanan(Q1);
	}
	info(Q1)=info(P1);
	if(bawah(P)!=Nil && bawah(Q)!=Nil){
		salin(bawah(P), bawah(Q));
	}
}
void tulis(infotype P) {
	//ALGORITMA
	if(P==Nol)printf("\x1b[0m");
	else if(P<=2)printf("\x1b[90m\x1b[103m");
	else if(P<=4)printf("\x1b[90m\x1b[101m");
	else if(P<=8)printf("\x1b[41m");
	else if(P<=16)printf("\x1b[42m");
	else if(P<=32)printf("\x1b[90m\x1b[102m");
	else if(P<=64)printf("\x1b[46m");
	else if(P<=128)printf("\x1b[44m");
	else if(P<=256)printf("\x1b[45m");
	else printf("\x1b[93m\x1b[40m");

	if(P==Nol)printf("        ");
	else if(P<10)printf("    %d   ",P);
	else if(P<100)printf("   %d   ",P);
	else if(P<1000)printf("  %d   ",P);
	else if(P<10000)printf("  %d  ",P);
	else if(P<100000)printf(" %d  ",P);
	else if(P<1000000)printf(" %d ",P);
	else if(P<10000000)printf(" %d",P);
	else if(P<100000000)printf("%d",P);

	printf("\x1b[0m");
}
void tulisBlank(infotype P) {
	//ALGORITMA
	if(P==Nol)printf("\x1b[0m");
	else if(P<=2)printf("\x1b[90m\x1b[103m");
	else if(P<=4)printf("\x1b[90m\x1b[101m");
	else if(P<=8)printf("\x1b[41m");
	else if(P<=16)printf("\x1b[42m");
	else if(P<=32)printf("\x1b[90m\x1b[102m");
	else if(P<=64)printf("\x1b[46m");
	else if(P<=128)printf("\x1b[44m");
	else if(P<=256)printf("\x1b[45m");
	else printf("\x1b[93m\x1b[40m");

	printf("        ");
	printf("\x1b[0m");
}

/* Geser Kotak */
bool rataKiri(tabel *T, address LT) {
	//KAMUS
	address P,Q;
	bool diam=true;
	//ALGORITMA
	Q=LT;
	while(kanan(Q)!=Nil){
		if(info(Q)==Nol){
			P=kanan(Q);
			if(info(P)!=Nol){
				diam=false;
				info(Q)=info(P);
				info(P)=Nol;
			}else{
				while(kanan(P)!=Nil && info(P)==Nol){
					P=kanan(P);
				}
				if(info(P)!=Nol){
					diam=false;
					info(Q)=info(P);
					info(P)=Nol;
				}
			}
		}
		Q=kanan(Q);
	}
	if(bawah(LT)!=Nil){
		diam=rataKiri(T,bawah(LT)) && diam;
	}
	return diam;
}
int tambahKiri(tabel *T, address LT) {
	//KAMUS
	address P;
	int point=0;
	//ALGORITMA
	P=LT;
	while(kanan(P)!=Nil){
		if(info(P)!=Nol && info(P)==info(kanan(P))){
			info(P)*=2;
			point+=info(P);
			info(kanan(P))=Nol;
		}
		P=kanan(P);
	}
	if(bawah(LT)!=Nil){
		point+=tambahKiri(T,bawah(LT));
	}
	return point;
}
bool geserKiri(tabel *T,int *point) {
	//KAMUS
	bool diam=true;
	//ALGORITMA
	diam=rataKiri(T,LT(*T));
	*point=tambahKiri(T,LT(*T));
	diam=rataKiri(T,LT(*T)) && diam && (*point==0);
	return diam;
}
bool rataKanan(tabel *T, address RB) {
	//KAMUS
	address P,Q;
	bool diam=true;
	//ALGORITMA
	Q=RB;
	while(kiri(Q)!=Nil){
		if(info(Q)==Nol){
			P=kiri(Q);
			if(info(P)!=Nol){
				diam=false;
				info(Q)=info(P);
				info(P)=Nol;
			}else{
				while(kiri(P)!=Nil && info(P)==Nol){
					P=kiri(P);
				}
				if(info(P)!=Nol){
					diam=false;
					info(Q)=info(P);
					info(P)=Nol;
				}
			}
		}
		Q=kiri(Q);
	}
	if(atas(RB)!=Nil){
		diam=rataKanan(T,atas(RB)) && diam;
	}
	return diam;
}
int tambahKanan(tabel *T, address RB) {
	//KAMUS
	address P;
	int point=0;
	//ALGORITMA
	P=RB;
	while(kiri(P)!=Nil){
		if(info(P)!=Nol && info(P)==info(kiri(P))){
			info(P)*=2;
			point+=info(P);
			info(kiri(P))=Nol;
		}
		P=kiri(P);
	}
	if(atas(RB)!=Nil){
		point+=tambahKanan(T,atas(RB));
	}
	return point;
}
bool geserKanan(tabel *T,int *point) {
	//KAMUS
	bool diam=true;
	//ALGORITMA
	diam=rataKanan(T,RB(*T));
	*point=tambahKanan(T,RB(*T));
	diam=rataKanan(T,RB(*T))&& diam && (*point==0);
	return diam;
}
bool rataAtas(tabel *T, address LT) {
	//KAMUS
	address P,Q;
	bool diam=true;
	//ALGORITMA
	Q=LT;
	while(bawah(Q)!=Nil){
		if(info(Q)==Nol){
			P=bawah(Q);
			if(info(P)!=Nol){
				diam=false;
				info(Q)=info(P);
				info(P)=Nol;
			}else{
				while(bawah(P)!=Nil && info(P)==Nol){
					P=bawah(P);
				}
				if(info(P)!=Nol){
					diam=false;
					info(Q)=info(P);
					info(P)=Nol;
				}
			}
		}
		Q=bawah(Q);
	}
	if(kanan(LT)!=Nil){
		diam=rataAtas(T,kanan(LT)) && diam;
	}
	return diam;
}
int tambahAtas(tabel *T, address LT) {
	//KAMUS
	address P;
	int point=0;
	//ALGORITMA
	P=LT;
	while(bawah(P)!=Nil){
		if(info(P)!=Nol && info(P)==info(bawah(P))){
			info(P)*=2;
			point+=info(P);
			info(bawah(P))=Nol;
		}
		P=bawah(P);
	}
	if(kanan(LT)!=Nil){
		point+=tambahAtas(T,kanan(LT));
	}
	return point;
}
bool geserAtas(tabel *T,int *point) {
	//KAMUS
	bool diam=true;
	//ALGORITMA
	diam=rataAtas(T,LT(*T));
	*point=tambahAtas(T,LT(*T));
	diam=rataAtas(T,LT(*T)) && diam && (*point==0);
	return diam;
}
bool rataBawah(tabel *T, address RB) {
	//KAMUS
	address P,Q;
	bool diam=true;
	//ALGORITMA
	Q=RB;
	while(atas(Q)!=Nil){
		if(info(Q)==Nol){
			P=atas(Q);
			if(info(P)!=Nol){
				diam=false;
				info(Q)=info(P);
				info(P)=Nol;
			}else{
				while(atas(P)!=Nil && info(P)==Nol){
					P=atas(P);
				}
				if(info(P)!=Nol){
					diam=false;
					info(Q)=info(P);
					info(P)=Nol;
				}
			}
		}
		Q=atas(Q);
	}
	if(kiri(RB)!=Nil){
		diam=rataBawah(T,kiri(RB)) && diam;
	}
	return diam;
}
int tambahBawah(tabel *T, address RB) {
	//KAMUS
	address P;
	int point=0;
	//ALGORITMA
	P=RB;
	while(atas(P)!=Nil){
		if(info(P)!=Nol && info(P)==info(atas(P))){
			info(P)*=2;
			point+=info(P);
			info(atas(P))=Nol;
		}
		P=atas(P);
	}
	if(kiri(RB)!=Nil){
		point+=tambahBawah(T,kiri(RB));
	}
	return point;
}
bool geserBawah(tabel *T,int *point) {
	//KAMUS
	bool diam=true;
	//ALGORITMA
	diam=rataBawah(T,RB(*T));
	*point=tambahBawah(T,RB(*T));
	diam=rataBawah(T,RB(*T)) && diam && (*point==0);
	return diam;
}

void acak(tabel *T) {
	//KAMUS
	address P;
	//ALGORITMA
	int i, barisdituju, kolomdituju;
	int seconds = 1;

	barisdituju = (rand()*seconds)%Nmax;
	kolomdituju = (rand()*seconds)%Nmax;	
	P = LT(*T);
	for (i = 0; i< barisdituju; i++)
	{
		P=bawah(P);
	}
	for (i = 0; i< kolomdituju; i++)
	{
		P=kanan(P);
	}
	if(info(P) == Nol)
	{
		info(P) = rand()*seconds;
		if(info(P)%5==0)info(P)=4;
		else info(P)=2;		
	}else{
		acak(T);
	}
}
bool IsGameOver(address P) {
	//KAMUS
	bool Over = true;	
	address Q;
	//ALGORITMA
	Q = P;
	while (kanan(Q)!= Nil)
	{
		Over = Terkunci(Q) && Over;
		Q = kanan(Q);
	}
	Over = Terkunci(Q) && Over;

	if (bawah(P)!= Nil)
	{
		Over = IsGameOver(bawah(P)) && Over;
	}
	return Over;
}
bool Terkunci(address P) {
	//ALGORITMA
	if (kiri(P)!=Nil)
	{
		if (info(kiri(P)) == Nol)
		{return false;}
		else
		{
			if (info(kiri(P)) == info(P))
			{return false;}
		}	
	}
	if (kanan(P)!=Nil)
	{
		if (info(kanan(P)) == Nol)
		{return false;}
		else
		{
			if (info(kanan(P)) == info(P))
			{return false;}
		}	
	}
	if (bawah(P)!=Nil)
	{
		if (info(bawah(P)) == Nol)
		{return false;}
		else
		{
			if (info(bawah(P)) == info(P))
			{return false;}
		}	
	}
	if (atas(P)!=Nil)
	{
		if (info(atas(P)) == Nol)
		{return false;}
		else
		{
			if (info(atas(P)) == info(P))
			{return false;}
		}	
	}
	return true;
}
bool win(tabel T, address LT) {
	//KAMUS
	address P;
	bool found;
	//ALGORITMA
	found = false;
	P = LT;
	while((found==false) && (kanan(P)!=Nil))
	{
		if(info(P)>= 2048){
			return true;
		}
		else
		{
			P = kanan(P);
			found == false;
		}
	}
	if(info(P)>= 2048){
		return true;
	}

	if(bawah(LT)!=Nil)
	{
		found = win(T, bawah(LT));		
	}
	return found;
}

void play() {
	//KAMUS
	tabel T,U,UTemp;
	int i,j, bantu;
	char pil, lanjut, rst;
	int score, scoreTemp;
	bool isdiam;
	hs user;
	//ALGORITMA
	//Inisialisasi
	init(&T);
	init(&U);
	init(&UTemp);
	system("clear"); 	//clear screen
	lanjut='y';
	sv.load=false;
	load(&T);
	if(sv.load==false){
		acak(&T);
		acak(&T);
		score = 0;
	}else{
		score=sv.score;
	}
	salin(LT(T),LT(U));
	scoreTemp=score;

	if(win(T,LT(T))){
		bantu = 1; 		// Variabel bantu untuk kemunculan 2048 hanya sekali
	}else{
		bantu=0;
	}

	printf ("Score : %d \n", score);
	if(score>topten[1].score)
	{
		printf ("Highscore : %d \n",score);
	}
	else
	{
		printf ("Highscore : %d \n", topten[1].score);		
	}
	showTabel(T);

	do
	{
		setBufferedInput(false); 	// Membaca input secara otomatis
		pil=getchar();				// Menerima input
		setBufferedInput(true);		// Selesai membaca input
		switch(pil)
		{
			case 'a' :
			case 'A' :
			// Gerakan ke kiri
			{
				salin(LT(T),LT(UTemp));
				scoreTemp=score;
				isdiam=geserKiri(&T,&i);
				score= score +i;
				break;				
			}
			case 'd' :
			case 'D' :
			// Gerakan ke kanan
			{
				salin(LT(T),LT(UTemp));
				scoreTemp=score;
				isdiam=geserKanan(&T,&i);
				score= score +i;
				break;				
			}
			case 'w' :
			case 'W' :
			// Gerakan ke atas
			{
				salin(LT(T),LT(UTemp));
				scoreTemp=score;
				isdiam=geserAtas(&T,&i);
				score= score +i;
				break;
			}
			case 's' :
			case 'S' :
			// Gerakan ke bawah
			{
				salin(LT(T),LT(UTemp));
				scoreTemp=score;
				isdiam=geserBawah(&T,&i);
				score= score +i;				
				break;
			}
			case 'u' :
			case 'U' :
			// Undo
			{
				salin(LT(U),LT(T));
				score=scoreTemp;
				isdiam=true;
				break;
			}
			case 'r' :
			case 'R' :
			// Reset
			{
				printf("Apakah anda yakin ingin reset? [Y/N] : ");
				scanf("%c", &rst);
				if((rst=='Y')||(rst=='y'))
				{
					init(&T);			
					score = 0;
					acak(&T);
					isdiam=false;
				}else isdiam=true;
				break;
			}
			default :
			{
				isdiam=true;
			}
			
		}
		system("clear");	// clear screen
		printf ("Score : %d \n", score);
		if(score>topten[1].score){
			printf ("Highscore : %d \n",score);
		}else{
			printf ("Highscore : %d \n", topten[1].score);		
		}
		showTabel(T);
		if ((win(T, LT(T))==true) && bantu==0)
		{
			printf("Melanjutkan? [Y/n] ? ");
			lanjut = getchar();
			bantu ++;
			if(lanjut!='y' && lanjut!='Y'){
				init(&T);
			}
		}		
		if(IsGameOver(LT(T))==false){
			usleep(100000);
			system("clear");

			if(isdiam==false){
				acak(&T);
				salin(LT(UTemp),LT(U));
				scoreTemp=score-i;
			}

			printf ("Score : %d \n", score);
			if(score>topten[1].score)
			{
				printf ("Highscore : %d \n",score);
			}
			else
			{
				printf ("Highscore : %d \n", topten[1].score);		
			}
			showTabel(T);
			sv.load=true;
			lintomat( 0,LT(T));
			sv.score=score;
			save();
		}
	}
	while((IsGameOver(LT(T))== false)&&(pil !='q') && (pil !='Q')
		&&(lanjut=='y' || lanjut=='Y'));

	if (IsGameOver(LT(T)))
	{		
			printf("Kalah\n");
			user.score=score;
			if(user.score>topten[10].score){
				printf("Masukkan Nama (10):");
				fgets(user.nama,sizeof(user.nama),stdin);
				while(strlen(user.nama)>10){
					printf("Nama terlalu panjang, ulangi :");
					fgets(user.nama,sizeof(user.nama),stdin);
				}
				inserths(user);
			}else{
				printf("Press Enter to Continue...\n");
				//scanf("%c",&user.nama);
			}
			sv.load=false;
			save();
	}
}
void setBufferedInput(bool enable) {
	// KAMUS
	static bool enabled = true;
	static struct termios old;
	struct termios new;
	//ALGORITMA
	if (enable && !enabled) {
		// restore the former settings
		tcsetattr(STDIN_FILENO,TCSANOW,&old);
		// set the new state
		enabled = true;
	} else if (!enable && enabled) {
		// get the terminal settings for standard input
		tcgetattr(STDIN_FILENO,&new);
		// we want to keep the old setting to restore them at the end
		old = new;
		// disable canonical mode (buffered i/o) and local echo
		new.c_lflag &=(~ICANON & ~ECHO);
		// set the new settings immediately
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		// set the new state
		enabled = false;
	}
}
void createhs() {
	//KAMUS
	int i;
	//ALGORITMA
	for(i=1; i<11; i++)
	{
		topten[i].score = 0;
	}
}
void sorths() {
	//KAMUS
	int i,j;
	hs temp;
	//ALGORITMA
	for(i=1; i<10; i++)
	{
		for(j = i +1; j<=10; j++)
		{
			if (topten[j].score>topten[i].score)
			{
				temp = topten[j];
				topten[j] = topten[i];
				topten[i] = temp; 
			}
		}
	}	
}
void inserths(hs input) {
	//KAMUS
	int i,j;
	i =10;
	//ALGORITMA
	while((input.score>topten[i].score)&&(i>=1))
	{
		i--;
	}
	i= i+1;
	if(i<11)
	{
		for(j=10;j>i; j--)
		{
			topten[j] = topten[j-1];
		}
		topten[i] = input;
	}
}
void savehs() {
	//KAMUS
	FILE *f;
	//ALGORITMA
	f=fopen(highscore,"w");
	fwrite(&topten,sizeof(topten),1,f);
	fclose(f);
}
void loadhs() {
	//KAMUS
	FILE *fi;
	//ALGORITMA
	fi=fopen(highscore,"r");
	if(fi!=NULL){
		fread(&topten,sizeof(topten),1,fi);
		fclose(fi);
	}
}
void tulishs () {
	//KAMUS
	int i,j;
	//ALGORITMA
	system("clear");
	printf("\n");
	printf("  ║ ║║╔══ ║ ║╔══╗╔══╗╔══╗╔══╗╔══\n");
	printf("  ╠═╣║║ ═╗╠═╣╚══╗║   ║  ║╠═╦╝╠═\n");
	printf("  ║ ║║╚══╝║ ║╚══╝╚══╝╚══╝║ ╚ ╚══\n");
	printf("     ╔════════════╦════════╗\n");
	printf("     ║NAME        ║ SCORE  ║\n");
	printf("     ╠════════════╬════════╣\n");
	for (i=1; i<11; i++) {
		//menghapus new line
		for (j=0;j<strlen(topten[i].nama);j++){
			if(topten[i].nama[j]=='\n'){
				topten[i].nama[j]=' ';
			}
		}
		printf("     ║%s", topten[i].nama);
		for(j=strlen(topten[i].nama);j<=11;j++){
			printf(" ");
		}
		printf("║ %d", topten[i].score);
		if(topten[i].score<10)printf(" ");
		if(topten[i].score<100)printf(" ");
		if(topten[i].score<1000)printf(" ");
		if(topten[i].score<10000)printf(" ");
		if(topten[i].score<100000)printf(" ");
		if(topten[i].score<1000000)printf(" ");
		printf("║\n");
	}
	printf("     ╚════════════╩════════╝\n");
}
void HowToPlay () {
	//ALGORITMA
	system("clear");
	printf("                            ║ ║╔══╗║ ║ ║ ══╦══╔══╗ ╔══╗║  ╔═╗║ ║\n");
	printf("                            ╠═╣║  ║║ ║ ║   ║  ║  ║ ║══╝║  ╠═╣╚═╣\n");
	printf("                            ║ ║╚══╝╚═╩═╝   ║  ╚══╝ ║   ╚══║ ║══╝\n");
	
	printf("╔═════════════════════════════════════════════════════════════════════════════════════════════╗\n"); usleep(100000);
	printf("║ 2048 dimainkan di papan persegi berukuran 4×4. Di atasnya terdapat beberapa kotak dengan    ║\n"); usleep(100000);
	printf("║ warna berbeda yang bergeser ketika pemain menekan empat tombol arah di keyboard. Kotaknya   ║\n"); usleep(100000);
	printf("║ dapat bergerak sejauh mungkin sampai bertemu kotak lain atau pinggir papan. Apabila dua     ║\n"); usleep(100000);
	printf("║ kotak bernomor sama bergabung saat bergeser, keduanya akan bergabung dan menghasilkan kotak ║\n"); usleep(100000);
	printf("║ baru yang nomornya merupakan hasil penjumlahan nomor di dua kotak yang bergabung tadi. Kotak║\n"); usleep(100000);
	printf("║ yang baru ini tidak bisa bergabung dengan kotak lain dengan arah yang sama. Kotak dengan    ║\n"); usleep(100000);
	printf("║ nomor tertinggi memancarkan sinar di sekitarnya. Di setiap pergeseran akan ada satu kotak   ║\n"); usleep(100000);
	printf("║ baru bernomor 2 atau 4 yang muncul secara acak pada ruang kosong di papan. Papan skor di    ║\n"); usleep(100000);
	printf("║ kanan atas terus memperbarui skor pemain. Skor pemain berawal di angka nol, lalu bertambah  ║\n"); usleep(100000);
	printf("║ ketika dua kotak bergabung dan membentuk kotak bernomor baru. Seperti permainan arkade lain ║\n"); usleep(100000);
	printf("║ nya, skor terbaik pemain ditampilkan bersandingan dengan skor saat ini. Pemain baru menang  ║\n"); usleep(100000);
	printf("║ ketika sebuah kotak bernomor 2048 muncul di papan. Setelah mencapai skor target, pemain bisa║\n"); usleep(100000);
	printf("║ terus bermain dalam mode kotak pasir melewati angka 2048. Saat pemain tidak bisa bergerak   ║\n"); usleep(100000);
	printf("║ lagi (tidak ada ruang kosong dan kotak bernomor sama di sekitarnya), permainan berakhir.    ║\n"); usleep(100000);
	printf("╚═════════════════════════════════════════════════════════════════════════════════════════════╝\n"); usleep(100000);
	printf("      ╔═══╗                   ╔═══╗                ╔═══╗              ╔═══╗\n"); usleep(100000);
	printf("      ║ w ║                   ║ r ║                ║ u ║              ║ q ║\n"); usleep(100000);
	printf("      ╚═══╝                   ╚═══╝                ╚═══╝              ╚═══╝\n"); usleep(100000);
	printf("      Atas                    Reset                Undo           back to menu\n"); usleep(100000);
	printf("╔═══╗ ╔═══╗ ╔═══╗ \n"); usleep(100000);
	printf("║ a ║ ║ s ║ ║ d ║ \n"); usleep(100000);
	printf("╚═══╝ ╚═══╝ ╚═══╝ \n"); usleep(100000);
	printf("Kiri  Bawah  Kanan\n"); usleep(100000);
}
void About () {
	//ALGORITMA
	system("clear");
	printf("                                  ╔═╗╔═╗ ╔══╗║  ║══╦══\n"); usleep(100000);
	printf("                                  ╠═╣╠═╩╗║  ║║  ║  ║  \n"); usleep(100000);
	printf("                                  ║ ║╚══╝╚══╝╚══╝  ║  \n"); usleep(100000);
	printf("                ╔═══════════════════════════════════════════════════╗\n"); usleep(100000);
	printf("                ║---------------------JavaScript--------------------║\n"); usleep(100000);
	printf("                ║░░░░░░░░░Andreas Ekadinata Widodo/18214033░░░░░░░░░║\n"); usleep(100000);
	printf("                ║░░░░░░░░░░░░Arsi Amallah Binhaq/18214013░░░░░░░░░░░║\n"); usleep(100000);
	printf("                ║░░░░░░░░░░░░░░Fat Han Nuraddin/18214046░░░░░░░░░░░░║\n"); usleep(100000);
	printf("                ║░░░░░░░░░░░░░░░░Santo Wijaya/18214028░░░░░░░░░░░░░░║\n"); usleep(100000);
	printf("                ╚═══════════════════════════════════════════════════╝\n"); usleep(100000);		
}
void ShowMenu () {
	//ALGORITMA
	system("clear");
		printf("\n");
		printf("╔═══════╗░╔═══════╗░╔═╗░░░╔═╗░╔═══════╗\n"); usleep(10000);
		printf("║░╔═══╗░║░║░╔═══╗░║░║░║░░░║░║░║░╔═══╗░║\n"); usleep(10000);
		printf("╚═╝░░░║░║░║░║░░░║░║░║░║░░░║░║░║░╚═══╝░║\n"); usleep(10000);
		printf("╔═════╝░║░║░║░░░║░║░║░╚═══╝░║░║░╔═══╗░║\n"); usleep(10000);
		printf("║░╔═════╝░║░║░░░║░║░╚═════╗░║░║░║░░░║░║\n"); usleep(10000);
		printf("║░╚═════╗░║░╚═══╝░║░░░░░░░║░║░║░╚═══╝░║\n"); usleep(10000);
		printf("╚═══════╝░╚═══════╝░░░░░░░╚═╝░╚═══════╝\n"); usleep(10000);
		printf("                ╔══════╗\n"); usleep(10000);
		printf("                ║1 Play║\n"); usleep(10000);
		printf("                ╚══════╝\n"); usleep(10000);
		printf("             ╔════════════╗\n"); usleep(10000);
		printf("             ║2 High Score║\n"); usleep(10000);
		printf("             ╚════════════╝\n"); usleep(10000);
		printf("            ╔══════════════╗\n"); usleep(10000);
		printf("            ║3 How to Play ║\n"); usleep(10000);
		printf("            ╚══════════════╝\n"); usleep(10000);
		printf("                ╔═══════╗\n"); usleep(10000);
		printf("                ║4 About║\n"); usleep(10000);
		printf("                ╚═══════╝\n"); usleep(10000);
		printf("                ╔═══════╗\n"); usleep(10000);
		printf("                ║5 Quit ║\n"); usleep(10000);
		printf("                ╚═══════╝\n"); usleep(10000);
}
