#ifndef DuaRibuEmpatDelapan_H
#define DuaRibuEmpatDelapan_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

#define Nmax 4 						// Kolom dan Baris maksimal
#define Nil 0						// Aamat tidak terdefinisi
#define Nol -999					// Elemen yang berisi kosong
#define savefile "save.dat"			// File eksternal menyimpan state terakhir board
#define highscore "highscore.dat"	// File eksternal menyimpan daftar 10 skor tertinggi

typedef int infotype;				
typedef struct tElmt *address;	
typedef struct tElmt {
	infotype info;
	address kanan;
	address kiri;
	address atas;
	address bawah;
} Elmt;					// Elemen tabel 2048

typedef struct {
	address kiriAtas; 
	address kanaBawah;
} tabel;				// Tabel Link List 2048

typedef struct{
	int score;
	char nama[10];
}hs;					// Elemen HighScore

typedef infotype tmatrix[Nmax][Nmax]; // Matriks
typedef struct{
	bool load;
	tmatrix T;
	int score;
} simpan;		

simpan sv;
hs topten[11];

/* Selektor */
#define info(P) (P)->info
#define atas(P) (P)->atas
#define bawah(P) (P)->bawah
#define kanan(P) (P)->kanan
#define kiri(P) (P)->kiri
#define LT(L) ((L).kiriAtas)
#define RB(L) ((L).kanaBawah)

/* ----- Konstruktor ----- */
address alokasi (infotype X);
// Menghasilkan address yang dialokasi
void init(tabel *T);
// I.S. : Sembarang 
// F.S. : Tabel T Kosong dengan ukuran Nmax x Nmax
void load(tabel *T);
// I.S. : Tabel T terdefinisi
// F.S. : Tabel T berisi elemen dalam save.dat
void save();
// I.S. : Tabel T terdefinisi
// F.S. : Tabel T disimpan dalam save.dat
void lintomat(int brs,address P);
// I.S. : Tabel terdefinisi
// F.S. : Tabel disalin ke dalam bentuk matriks
void mattolin(int brs,address P);
// I.S. : Matriks terdefinisi
// F.S. : Matriks disalin ke dalam bentuk Tabel T
void salin(address P,address Q);
// I.S. : 2 Tabel terdefinisi
// F.S. : Tabel Left Top P disalin menjadi tabel Left Top Q
void tulis(infotype P);
// I.S. : Tabel terdefinisi
// F.S. : Menulis elemen tabel dengan style tertentu
void tulisBlank(infotype P);
// I.S. : Tabel terdefinisi
// F.S. : Menulis blank berupa warna sesuai dengan nilai P
void showTabel(tabel T);
// I.S. : Tabel terdefinisi
// F.S. : Menampilkan tabel dan isi tabel

/****GESER***/
bool rataKiri(tabel *T,address LT);
// Mengembalikan nilai True jika ada gerakan ke kiri
int tambahKiri(tabel *T,address LT);
// Menambahkan pasangan elemen yang sama saat digeser ke kiri
bool geserKiri(tabel *T,int *point);
// Menggeser tabel T ke arah kiri
// point berisi score yang didapat
// Mengembalikan niali True jika ada perubahan pada tabel T

bool rataKanan(tabel *T,address LT);
// Mengembalikan nilai True jika ada gerakan ke kanan
int tambahKanan(tabel *T,address LT);
// Menambahkan pasangan elemen yang sama saat digeser ke kanan
bool geserKanan(tabel *T,int *point);
// Menggeser tabel T ke arah kanan
// point berisi score yang didapat
// Mengembalikan niali True jika ada perubahan pada tabel T

bool rataAtas(tabel *T,address LT);
// Mengembalikan nilai True jika ada gerakan ke atas
int tambahAtas(tabel *T,address LT);
// Menambahkan pasangan elemen yang sama saat digeser ke atas
bool geserAtas(tabel *T,int *point);
// Menggeser tabel T ke arah atas
// point berisi score yang didapat
// Mengembalikan niali True jika ada perubahan pada tabel T

bool rataBawah(tabel *T,address LT);
// Mengembalikan nilai True jika ada gerakan ke bawah
int tambahBawah(tabel *T,address LT);
// Menambahkan pasangan elemen yang sama saat digeser ke bawah
bool geserBawah(tabel *T,int *point);
// Menggeser tabel T ke arah bawah
// point berisi score yang didapat
// Mengembalikan niali True jika ada perubahan pada tabel T

void acak(tabel *T);
// I.S. : Tabel T terdefinisi dan ada elemen bernilai Nol
// F.S. : Mengisi elemen kosong pada tabel dengna nilai 2 atau 4 secara acak
bool IsGameOver(address P);
// Mengembalikan nilai True jika elemen tidak dapat dapat terjadi perubahan
bool Terkunci (address P);
// Mengembalikan nilai True jika elemen tidak dapat digeser
bool win(tabel T, address LT);
// Mengmbalikan nilai True jika ada elemen yang bernilai 2048

void play();
// I.S. : Sembarang
// F.S. : Menampilkan papan permainan 2048 sampai Game Over atau user keluar dari permainan
void setBufferedInput(bool enable);
// I.S. : Sembarang
// F.S. : Membaca secara otomatis input dari keyboard ketika enable bernilai False
//        Selesai membaca saat enable bernilai True

/* DISPLAY MENU */
void ShowMenu();
// I.S. : Sembarang
// F.S. : Menampilkan menu utama

/* HIGH SCORE */
void createhs();
// I.S. : Sembarang
// F.S. : Membuat tabel high score kosong
void sorths();
// I.S. : Tabel terdefinisi
// F.S. : Tabel terurut berdasarkan score dari terbesar sampai terkecil
void inserths(hs input);
// I.S. : Tabel terdefinisi
// F.S. : Memasukan score baru ke dalam tabel jika score lebih dari score terkecil dalam tabel high score
void savehs();
// I.S. : Tabel terdefinisi
// F.S. : Menyimpan tabel high score dalam file eksternal "highscore.dat"
void loadhs();
// I.S. : Tabel terdefinisi
// F.S. : Mengambil tabel high score dalam eksternal "highscore.dat"
void tulishs ();
// I.S. : Tabel terdefinisi
// F.S. : Menampilkan tabel high score pada layar

/* HOW TO PLAY */
void HowToPlay();
// I.S. : Sembarang
// F.S. : Menampilkan petunjuk cara bermain game 2048

/* ABOUT */
void About();
// I.S. : Sembarang
// F.S. : Menampilkan profil pembuat game 2048

#endif
