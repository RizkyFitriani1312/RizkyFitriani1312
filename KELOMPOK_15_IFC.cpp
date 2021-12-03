#include<iostream>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<fstream>

using namespace std;
int pil=1, pildata=1, pilhari=1, no_r=0, hari=1, pilruang=1;
int tanggal=4,bulan=12,tahun=2018, dur=0, pkt=1;
int count = 0;
char x1=NULL, x2=NULL, x3=NULL;

struct fasilitas{
  string kapasitas;
  string fasilitas;
};

struct ruang{
  string  namar;
  fasilitas fas_ruang;
  int statuskunci = 1;
  ruang* next;
  ruang* prev;
};

struct peminjam{
  string namap;
  string nim;
};

struct peminjaman{
  peminjam sipeminjam;
  string namaruangan;
  string waktu;
  string hari;
  string nohp;
  string kegiatan;
  string statusk="Tidak";
  string statusp = "Belum";
  peminjaman* next;
  peminjaman* prev;
};

ruang* front=NULL;
ruang* rear=NULL;
ruang* temp=NULL;
ruang* tampil;
fstream file;
peminjaman* frontp=NULL;
peminjaman* rearp=NULL;

void insertr(ruang a){
  ruang* baru = new ruang();
  baru->namar=a.namar;
  baru->fas_ruang=a.fas_ruang;
  baru->statuskunci = a.statuskunci;
  baru->next=NULL;
  baru->prev=NULL;
  if(front==NULL){
    front = baru;
    rear = baru;  
  }
  else{
    rear->next = baru;
    temp=rear;
    rear = baru;
    rear->prev=temp;
  }
}

void insertp(peminjaman a){
  peminjaman* baru = new peminjaman();
  baru->sipeminjam=a.sipeminjam;
  baru->namaruangan=a.namaruangan;
  baru->nohp=a.nohp;
  baru->kegiatan=a.kegiatan;
  baru->waktu=a.waktu;
  baru->hari=a.hari;
  baru->statusk = a.statusk;
  baru->statusp = a.statusp;
  baru->next=NULL;
  baru->prev=NULL;
  if(frontp==NULL){
    frontp = baru;
    rearp = baru;  
  }
  else{
    rearp->next = baru;
    baru->prev = rearp;
    rearp = baru;
  }
}

void gotoxy(short x, short y){
  COORD pos = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void buffer_size(short x, short y){
  SMALL_RECT rect;
    COORD coord;
    coord.X = x;
    coord.Y = y;
    
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = coord.Y-1;
    rect.Right = coord.X-1;
    
    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(hwnd, coord);
    SetConsoleWindowInfo(hwnd, TRUE, &rect);
}

void table(int type){
  char c[1];
  if(type==1){
    for(int a=9;a<51;a++)
    {
      gotoxy(a,3);cout<<(char)220;gotoxy(a,5);cout<<(char)220;
      gotoxy(a,30);cout<<(char)220;
    }
    for(int a=4;a<31;a++)
    {
      gotoxy(9,a);cout<<(char)219;gotoxy(50,a);cout<<(char)219;
      gotoxy(17,a);cout<<(char)219;
    }
    cout<<endl<<endl;
  }
  else if(type==2){
    for(int a=59;a<101;a++)
    {
      gotoxy(a,3);cout<<(char)220;gotoxy(a,5);cout<<(char)220;
      gotoxy(a,20);cout<<(char)220;
    }
    for(int a=4;a<21;a++)
    {
      gotoxy(59,a);cout<<(char)219;gotoxy(100,a);cout<<(char)219;
    }
    cout<<endl<<endl;}
  else if(type==3){
    for(int a=6;a<26;a++)
    {
      gotoxy(a,3);cout<<(char)220;gotoxy(a,5);cout<<(char)220;
      gotoxy(a,20);cout<<(char)220;
    }
    for(int a=4;a<21;a++)
    {
      gotoxy(6,a);cout<<(char)219;gotoxy(25,a);cout<<(char)219;
    }
    cout<<endl<<endl;}
  else if(type==4){
    for(int a=35;a<100;a++)
    {
      gotoxy(a,3);cout<<(char)220;gotoxy(a,5);cout<<(char)220;
      gotoxy(a,25);cout<<(char)220;
    }
    for(int a=4;a<26;a++)
    {
      gotoxy(35,a);cout<<(char)219;gotoxy(99,a);cout<<(char)219;
      gotoxy(42,a);cout<<(char)219;
      gotoxy(68,a);cout<<(char)219;
    }
    cout<<endl<<endl;}
  else if(type==5){
    for(int a=35;a<100;a++)
    {
      gotoxy(a,26);cout<<(char)220;gotoxy(a,28);cout<<(char)220;
      gotoxy(a,37);cout<<(char)220;
    }
    for(int a=27;a<38;a++)
    {
      gotoxy(35,a);cout<<(char)219;gotoxy(99,a);cout<<(char)219;
    }
    cout<<endl<<endl;}
  else if(type==6){
    for(int a=59;a<101;a++)
    {
      gotoxy(a,21);cout<<(char)220;gotoxy(a,23);cout<<(char)220;
      gotoxy(a,33);cout<<(char)220;
    }
    for(int a=21;a<34;a++)
    {
      gotoxy(59,a);cout<<(char)219;gotoxy(100,a);cout<<(char)219;
    }
    cout<<endl<<endl;}
  else if(type==7){
    for(int a=9;a<67;a++)
    {
      gotoxy(a,3);cout<<(char)220;gotoxy(a,5);cout<<(char)220;
      gotoxy(a,30);cout<<(char)220;
    }
    for(int a=4;a<31;a++)
    {
      gotoxy(9,a);cout<<(char)219;gotoxy(66,a);cout<<(char)219;
      gotoxy(17,a);cout<<(char)219;
    }
    cout<<endl<<endl;
  }
}

void ambilDataRuang(){
  ruang a;
  fstream file;
  string trash;
  file.open("ruangan.txt", ios::in | ios::out);
  front = NULL;
  rear = NULL;
  while(!file.eof())
  {
    getline(file,a.namar);
    getline(file,a.fas_ruang.fasilitas);
    getline(file,a.fas_ruang.kapasitas);
    file>>a.statuskunci;getline(file,trash);
    getline(file,trash);
    if(a.namar!=""){
      insertr(a);  
    }
    
  }
  file.close();
}

void namaruang(){
  int y=7,no=1; 
  ruang *point = front;
  gotoxy(12,4);cout<<"No.               Ruangan ";
    while(point!=NULL){    
      if(y<32){
        gotoxy(13,y);cout<<no<<".\t\t"<<point->namar<<endl;
        point = point->next;
      }y+=2;no++;
    }
    point = front;
}

int u_detailRuang(int pildata, int y){
  if(y<32){
    if(pildata==1){
      y = 7;
      gotoxy(11,y);cout<<"[";gotoxy(46,y);cout<<"]";
      gotoxy(27,36);cout<<"Navigate: Arrow Up and Down    Select: Enter    Back: Esc";
      no_r = pildata;
    }else{
      gotoxy(11,y);cout<<"[";gotoxy(46,y);cout<<"]";
      gotoxy(27,36);cout<<"Navigate: Arrow Up and Down    Select: Enter    Back: Esc";
      no_r = pildata;
    }  
  }  
}

void detailruang(int no_r){
  
  ambilDataRuang();
  ruang *point = front;
  while(no_r){
    gotoxy(71,4);cout<<"Detail Ruangan "<<point->namar;
    point = front; for(int i=0;i<no_r-1;i++){point = point->next;}
    gotoxy(62,7);cout << "Nama Ruangan      : "<<point->namar<<endl;
    gotoxy(62,9);cout << "Fasilitas Ruangan : ";gotoxy(62,10);cout<<point->fas_ruang.fasilitas<<endl;
    gotoxy(62,13);cout << "Kapasitas Ruangan : ";gotoxy(62,14);cout<<point->fas_ruang.kapasitas<<endl;
    break;
  }
}

void userpass(){
  fflush(stdin);
  int asci=219;
  char teks1[50]="Silahkan Masukkan Username dan Password";
  gotoxy(40,11);
  for(int i=0;i<50;i++)
  {
      Sleep(50);
      printf("%c",teks1[i]);
  }
    gotoxy(45,13); 
  for(int b=1;b<=30;b++)
  {
    Sleep(15);
    printf("%c",asci);
  }
  for(int b=1;b<=5;b++)
  {
    Sleep(15);
    gotoxy(45,13+b); printf("%c",asci);
  }
  for(int b=1;b<=5;b++)
  {
    Sleep(15);
    gotoxy(74,13+b); printf("%c",asci);
  }
  gotoxy(45,19);
  for(int b=1;b<=30;b++)
  {
    Sleep(15);
    printf("%c",asci);
  }
}

void userpass1(){
  fflush(stdin);
  int asci=219;
  gotoxy(40,11);printf("Silahkan Masukkan Username dan Password");
    gotoxy(45,13); 
  for(int b=1;b<=30;b++)
  {
    printf("%c",asci);
  }
  for(int b=1;b<=5;b++)
  {
    gotoxy(45,13+b); printf("%c",asci);
  }
  for(int b=1;b<=5;b++)
  {
    gotoxy(74,13+b); printf("%c",asci);
  }
  gotoxy(45,19);
  for(int b=1;b<=30;b++)
  {
    printf("%c",asci);
  }
}

void readPass(char *); 

void readPass(char *temp) {
  fflush(stdin);
    int key = 0, index = 0;
    do {
        key = getch(); 
        switch (key) {
            case 0:
            case 224:
                break;
            case '\b':
                if (index > 0) {
                    index = index - 1; 
                    temp[index] = 0; 
 
                    printf("\b \b"); 
                }
                break;
            default:
                if (key > 31 && key < 127) {
                    temp[index] = key; 
                    index = index + 1; 
 
                    printf("*");
                }
                 break;
    }      
    } while (key != 13);
    temp[index] = '\0';
}



int countDatar(){
  ruang *point = front;
  while(point!=NULL){
    count++;
    point = point->next;
  }
  return count;
}



void u_peminjaman(string ruangp, string waktup, string harip){
  peminjaman z;
  gotoxy(40,30);cout<<"Nama: "; fflush(stdin); getline(cin,z.sipeminjam.namap);
  gotoxy(40,32);cout<<"NIM: "; fflush(stdin); getline(cin,z.sipeminjam.nim);
  gotoxy(40,33);cout<<"No. Hp: "; fflush(stdin); getline(cin,z.nohp);
  gotoxy(40,35);cout<<"Kegiatan: "; fflush(stdin); getline(cin,z.kegiatan);
  z.namaruangan = ruangp;
  z.waktu = waktup;
  z.hari = harip;
  insertp(z);
  file.open("peminjaman.txt", ios::app);
      file<<z.sipeminjam.namap<<endl;
      file<<z.sipeminjam.nim<<endl;
      file<<z.namaruangan<<endl;
      file<<z.nohp<<endl;
      file<<z.kegiatan<<endl;
      file<<z.hari<<endl;
      file<<z.waktu<<endl;
      file<<z.statusk<<endl;
      file<<z.statusp<<endl;
      file<<endl;
  file.close();
  file.open("logpeminjaman.txt", ios::app);
      file<<z.sipeminjam.namap<<endl;
      file<<z.sipeminjam.nim<<endl;
      file<<z.namaruangan<<endl;
      file<<z.nohp<<endl;
      file<<z.kegiatan<<endl;
      file<<z.hari<<endl;
      file<<z.waktu<<endl;
      file<<z.statusk<<endl;
      file<<z.statusp<<endl;
      file<<endl;
  file.close();
}



void ambilDataPeminjam(){
  peminjaman a;
  fstream file;
  string trash;
  file.open("peminjaman.txt", ios::in | ios::out);
  frontp = NULL;
  rearp = NULL;
  while(!file.eof())
  {
    getline(file,a.sipeminjam.namap);
    getline(file,a.sipeminjam.nim);
    getline(file,a.namaruangan);
    getline(file,a.nohp);
    getline(file,a.kegiatan);
    getline(file,a.hari);
    getline(file,a.waktu);
    getline(file,a.statusk);
    getline(file,a.statusp);
    getline(file,trash);
    if(a.sipeminjam.namap!=""){
      insertp(a);  
    }
  }
  file.close();
}

bool SerahkanStatusRuang(string index){
  ruang *point = front;
  while(point!=NULL){
    if(point->namar == index){
      break;
    }
    point=point->next;
  }
  if(point->statuskunci == 0){
    return false;
  }else{
    point->statuskunci = 0;
    return true;  
  }
  
}

bool KembalikanStatusRuang(string index){
  ruang *point = front;
  while(point!=NULL){
    if(point->namar == index){
      break;
    }
    point=point->next;
  }
  if(point->statuskunci == 1){
    return false;
  }else{
    point->statuskunci = 1;
    return true;  
  }
  
}

void printDataRuang(){
  ambilDataRuang();
  ruang *point = front;
  if(front==NULL){
    cout<<"Tidak ada data Ruang yang ditampilkan";
  }
  else{
    while(point !=NULL){
      cout << "Nama Ruangan      : "<<point->namar<<endl;
      cout << "Fasilitas Ruangan : "<<point->fas_ruang.fasilitas<<endl;
      cout << "Kapasitas Ruangan : "<<point->fas_ruang.kapasitas<<endl;
      if(point->statuskunci==1){
        cout << "Status Ruangan : Tersedia"<<endl;
      }else{
        cout << "Status Ruangan : Tidak Tersedia"<<endl;
      }
      point = point->next;
    }
  }
}

int printDataPeminjam(){
  ambilDataPeminjam();
  int ada = 0;
  int y=7;
  int no = 1;
  peminjaman *point = frontp;
  if(frontp==NULL){
    cout<<"Tidak ada data Data yang ditampilkan";
  }
  else{
    while(point !=NULL){
      if(point->statusk == "Tidak" && point->statusp == "Belum"){
        gotoxy(13,y);cout<<no++;
        gotoxy(22,y++);cout<<point->sipeminjam.namap<<"  -  "<<point->namaruangan<<"  -  "<<point->hari;
        ada++;
      }
      point = point->next;
    }
  }
  return ada;
}

int printDataPemegangKunci(){
  ambilDataPeminjam();
  int ada = 0;
  int y = 7;
  int no = 1;
  peminjaman *point = frontp;
  if(frontp==NULL){
    cout<<"Tidak ada data Data yang ditampilkan";
  }
  else{
    while(point !=NULL){
      if(point->statusk == "Ya" && point->statusp == "Belum"){
        gotoxy(13,y);cout<<no++;
        gotoxy(22,y++);cout<<point->sipeminjam.namap<<"  -  "<<point->namaruangan<<"  -  "<<point->hari;
        ada++;
      }
      point = point->next;
    }
  }
  return ada;
}

void hapusr(int indeks){
  int n = countDatar();
  ruang *point=front;
  ruang *temp;
  
  if(front==NULL){
    cout<<"\nTidak ada data yang dapat dihapus";
  }else{
    if(indeks > n){
      cout<<"Data tidak ada"<<endl;  
    }else{    
      for(int i=0; i<indeks-1; i++){
        point=point->next;
      }
      
      if(point==front){
        if(front->next == NULL){
          front = NULL;
          rear = NULL;
        }else{
          front = front->next;
          front->prev = NULL;  
        }
      }else if(point == rear){
        rear = rear->prev;
        rear->next = NULL;
      }else{
        temp = point->next;
        point->next = temp->next;
        temp = point->next;
        temp->prev = point;
      }  
    }  
  }
  
}

void peminjamToTxt(){
  file.open("peminjaman.txt", ios::out | ios::trunc); //trunc = ksongkan file
  file.close();
  file.open("peminjaman.txt", ios::app);
  peminjaman *point = frontp;
  while(point != NULL)
  {
    file<<point->sipeminjam.namap<<endl;
      file<<point->sipeminjam.nim<<endl;
      file<<point->namaruangan<<endl;
      file<<point->nohp<<endl;
      file<<point->kegiatan<<endl;
      file<<point->hari<<endl;
      file<<point->waktu<<endl;
      file<<point->statusk<<endl;
      file<<point->statusp<<endl;
      file<<endl;
    point = point->next;
  }
  file.close();
  
  file.open("logpeminjaman.txt", ios::out | ios::trunc); //trunc = ksongkan file
  file.close();
  file.open("logpeminjaman.txt", ios::app);
  point = frontp;
  while(point != NULL)
  {
    file<<point->sipeminjam.namap<<endl;
      file<<point->sipeminjam.nim<<endl;
      file<<point->namaruangan<<endl;
      file<<point->nohp<<endl;
      file<<point->kegiatan<<endl;
      file<<point->hari<<endl;
      file<<point->waktu<<endl;
      file<<point->statusk<<endl;
      file<<point->statusp<<endl;
      file<<endl;
    point = point->next;
  }
  file.close();
  
}

void dataToTxt(){
  file.open("ruangan.txt", ios::out | ios::trunc); //trunc = ksongkan file
  file.close();
  file.open("ruangan.txt", ios::app);
  ruang *point = front;
  while(point != NULL)
  {
    file<<point->namar<<endl;
    file<<point->fas_ruang.fasilitas<<endl;
    file<<point->fas_ruang.kapasitas<<endl;
    file<<point->statuskunci<<endl;
    file<<endl;
    point = point->next;
  }
  file.close();
}

void update_txt(int index){
  ruang *point = front;
  int i = 1;  
  int n=countDatar();
  string nama;
  if(index > n){
    cout<<"Data tidak ada";
  }else{
    for(int i=0;i<index-1;i++){
      point = point->next;
    }
    nama = point->namar;
    table(6);
    gotoxy(62,22);cout<<"Masukan Data Baru Pada Ruangan "<<endl;fflush(stdin);  
    gotoxy(62,24);cout<<"Masukkan nama ruangan      : ";
    gotoxy(62,25);getline(cin,point->namar);fflush(stdin);
    gotoxy(62,27);cout<<"Masukkan fasilitas terbaru : ";
    gotoxy(62,28);getline(cin,point->fas_ruang.fasilitas);fflush(stdin);
      gotoxy(62,30);cout<<"Masukkan kapasitas         : ";
    gotoxy(62,31);getline(cin,point->fas_ruang.kapasitas);fflush(stdin);  
  }
  
  ambilDataPeminjam();
  peminjaman *pointp = frontp;
  while(pointp!=NULL){
    if(pointp->namaruangan == nama){
      pointp->namaruangan = point->namar;
    }
    pointp = pointp->next;
  }
  peminjamToTxt();
}

void admin1(){
  char uss[15], pass[15];
    int result1, result2;
    userpass();
    ngulang:  
    userpass1();
  
    gotoxy(47,15);cout<<"Username : "; fflush(stdin); cin>>uss;
        gotoxy(47,17);cout<<"Password : "; readPass(pass);
    system("cls");
    
        result1 = strcmp (uss, "admin");
        result2 = strcmp (pass, "admin");
 
        if (result1 == 0 && result2 == 0){
        }
    else
    {
          gotoxy(45,21);cout<<"Username dan Password Salah...";
      goto ngulang;
        }
}

void sort()
{
  ambilDataPeminjam();
  system("cls");
  int y=0;
  peminjaman *temp = frontp;
  while(temp!=NULL)
  {
    temp = temp->next;
    y++;
  }
  
  temp = frontp;
  peminjaman arr[y];
  peminjaman swap;
  for(int i=0;i<y;i++)
  {
    arr[i].sipeminjam  = temp->sipeminjam;
    arr[i].namaruangan= temp->namaruangan;
    arr[i].waktu= temp->waktu;
    arr[i].hari= temp->hari;
    arr[i].statusk= temp->statusk;
    arr[i].statusp= temp->statusp;
    temp = temp->next;
  }
  int pil2;
  cout<<" Sorting Data Berdasarkan Nama Peminjam "<<endl;
  cout<<" 1. Ascending"<<endl;
  cout<<" 2. Descending"<<endl;
  cout<<" Pilihan : "; cin>>pil2;
  if(pil2 == 1)
  {
    for(int i=0;i<y-1;i++)
    {
       for(int j=0; j<y-1; j++)
      { 
        if(arr[j].sipeminjam.namap>arr[j+1].sipeminjam.namap)
        { 
          swap = arr[j]; 
          arr[j]= arr[j+1]; 
          arr[j+1] = swap; 
        } 
      } 
    }
  }
  else if(pil2 == 2)
  {
    for(int i=0;i<y-1;i++)
    { 
       for(int j=0; j<y-1; j++)
      { 
        if(arr[j].sipeminjam.namap<arr[j+1].sipeminjam.namap)
        { 
          swap = arr[j]; 
          arr[j]= arr[j+1]; 
          arr[j+1] = swap; 
        } 
      } 
    }
  }
  else
  {
    cout<<"Pilihan Tidak Ada"<<endl;
  }
  for(int i=0;i<y;i++)
  {
    cout<<" Nama Peminjam     : "<<arr[i].sipeminjam.namap<<endl;
    cout<<" Nama Ruangan      : "<<arr[i].namaruangan<<endl;
    cout<<" Waktu Peminjaman  : "<<arr[i].waktu<<endl;
    cout<<" Hari Peminjaman   : "<<arr[i].hari<<endl;
    cout<<" Status Kunci      : "<<arr[i].statusk<<endl;
    cout<<" Status Peminjaman : "<<arr[i].statusp<<endl;
    cout<<endl;
  }
}

void admin2(){
  int indeks, ada;
  char pilih;
    ruang a;
    bool kembali=true,kembali2;
    do{
      kembali = true;
      int i=0,y=7, serah;
      peminjaman *point;
    peminjaman *temp;
    system("cls");
    gotoxy(5,4); cout<<"Selamat Datang di Laman Admin";
      gotoxy(5,6); cout<<"----------------------------------"<<endl;
      gotoxy(5,7); cout<<"Menu : "<<endl;
    gotoxy(5,9); cout<<"[1.] Create Data"<<endl;   
    gotoxy(5,10); cout<<"[2.] Read Data"<<endl;
    gotoxy(5,11); cout<<"[3.] Update Data"<<endl;
    gotoxy(5,12); cout<<"[4.] Delete Data"<<endl;
    gotoxy(5,13); cout<<"[5.] Serahkan Kunci"<<endl;
    gotoxy(5,14); cout<<"[6.] Kembalikan Kunci"<<endl;
    gotoxy(5,15); cout<<"[7.] Log Peminjaman"<<endl;
    gotoxy(5,16); cout<<"[8.] Kembali"<<endl;
      gotoxy(5,18); cout<<"Masukkan pilihan Anda : ";
      cin>>pilih;
      
      switch(pilih){
      case '1' :
        table(2);
        file.open("ruangan.txt", ios::app);
        gotoxy(72,4); cout<<"Masukkan Data ";fflush(stdin);
            gotoxy(62,7); cout<<"Masukkan nama ruangan : ";
        gotoxy(62,8);getline(cin,a.namar);fflush(stdin); cout<<endl;
            gotoxy(62,11); cout<<"Masukkan fasilitas    : ";
        gotoxy(62,12);getline(cin,a.fas_ruang.fasilitas);fflush(stdin);
            gotoxy(62,15); cout<<"Masukkan kapasitas    : ";
        gotoxy(62,16);getline(cin,a.fas_ruang.kapasitas);fflush(stdin);
            
          file<<a.namar<<endl;
          file<<a.fas_ruang.fasilitas<<endl;
          file<<a.fas_ruang.kapasitas<<endl;
          file<<a.statuskunci<<endl;
          file<<endl;
            insertr(a);
          file.close();
      break;
      case '2' :
        do{
          kembali2 = false;
          system("cls");
          x2=NULL;
        
          pildata=1;namaruang();
        table(1);
        while(x2!=13){
          u_detailRuang(pildata, y);x2=getch();
          if(x2==72){
            system("CLS");namaruang();table(1);
              if(pildata==1){
                pildata=count;
                y += (count-1)*2;
              }else{pildata--; y-=2;}
          }
          else if(x2==80){
            system("CLS");namaruang();table(1);
              if(pildata==count){
                pildata=1;
                y = 7;
              }else{pildata++; y+=2;}
          }
          else if(x2==13){
          //                                               lihat detail ruangan
            table(2);
            detailruang(no_r); x2=getch();
            if(x2==27){system("CLS");pildata=1; y = 7; kembali2=true; break;}
            else if(x2==13){ system("CLS");kembali2=true; }
          }
          else if(x2==27){
            break; 
          }
        }
  
    
      }while(kembali2);
      break;

    case '3':
      do{
          kembali2 = false;
          system("cls");
          x2=NULL;
        
          pildata=1;namaruang();
        table(1);
        while(x2!=13){
          u_detailRuang(pildata, y);x2=getch();
          if(x2==72){
            system("CLS");namaruang();table(1);
              if(pildata==1){
                pildata=count;
                y += (count-1)*2;
              }else{pildata--; y-=2;}
          }
          else if(x2==80){
            system("CLS");namaruang();table(1);
              if(pildata==count){
                pildata=1;
                y = 7;
              }else{pildata++; y+=2;}
          }
          else if(x2==13){
          //                                               update ruang
            table(2);
            detailruang(no_r);
            update_txt(no_r);dataToTxt(); x2=getch();
            if(x2==27){system("CLS");pildata=1; y = 7; kembali2=true; break;}
            else if(x2==13){ system("CLS");kembali2=true; }
          }
          else if(x2==27){
            break; 
          }
        }
      }while(kembali2);
      break;
       case '4' :
           do{
            kembali2 = false;
            system("cls");
            x2=NULL;
          
            pildata=1;namaruang();
          table(1);
          while(x2!=13){
            u_detailRuang(pildata, y);x2=getch();
            if(x2==72){
              system("CLS");namaruang();table(1);
                if(pildata==1){
                  pildata=count;
                  y += (count-1)*2;
                }else{pildata--; y-=2;}
            }
            else if(x2==80){
              system("CLS");namaruang();table(1);
                if(pildata==count){
                  pildata=1;
                  y = 7;
                }else{pildata++; y+=2;}
            }
            else if(x2==13){
              hapusr(no_r); dataToTxt();
              gotoxy(40,33);cout<<"Data telah dihapus"; x2=getch();
              if(x2==27){system("CLS");pildata=1; y = 7; kembali2=true; break;}
              else if(x2==13){ system("CLS");kembali2=true; }
            }
            else if(x2==27){
              break; 
            }
          }
    
      
        }while(kembali2);
        break;
       case '5' :
         
         system("cls");
      gotoxy(12,4);cout<<"No.             Nama   -   Ruangan  -  Hari";
         table(7);
      ada = printDataPeminjam();
      point = frontp;
      if(!ada){
      gotoxy(40,33);  cout<<"Data tidak ada";
        break;
      }else{
        gotoxy(78,9);cout<<"Serahkan kunci ke : ";cin>>serah;
        if(serah > ada ){
          gotoxy(40,33);  cout<<"Inputan Salah, Kembali ke Menu";
        }else{
          while(i<=serah-1){
            if(point->statusk=="Tidak" && point->statusp == "Belum"){
              temp = point;
              i++;
            }
            point = point->next;
          }
          if(SerahkanStatusRuang(temp->namaruangan )){
            temp->statusk = "Ya";
            peminjamToTxt();
            dataToTxt();
          }else{
            gotoxy(40,33);  cout<<"Kunci Ruangan Belum Dikembalikan";
          }  
        }
        
      }      
      
      
      break;
    case '6':
         system("cls");
         table(7);
         ada = printDataPemegangKunci();
         point = frontp;
         if(!ada){
      gotoxy(40,33);  cout<<"Data tidak ada";
        break;
      }else{
        gotoxy(78,9);cout<<"Kembalikkan kunci ke : ";cin>>serah;
        if(serah > ada){
          gotoxy(40,33);  cout<<"Inputan Salah, Kembali ke Menu";
        }else{
          while(i<=serah-1){
            if(point->statusk=="Ya" && point->statusp == "Belum"){
              temp = point;
              i++;
            }
            point = point->next;
          }
          if(KembalikanStatusRuang(temp->namaruangan )){
            temp->statusk = "Tidak";
            temp->statusp = "Sudah";
            peminjamToTxt();
            dataToTxt();
          }else{
            gotoxy(40,33);  cout<<"Kunci Ruangan Sudah Dikembalikan";
          }
        }
        
      }
      break;  
    case '7':
      sort();
      break;
    case '8':
      kembali=false;
      break;
    default :
      system("cls");
              gotoxy(60,12); cout<<"\nSilahkan pilih kembali"<<endl;
    }
    gotoxy(40,35);cout<<"tekan enter untuk melanjutkan";getch();
    }while(kembali);     
}

bool cekpeminjaman(string hari, string namar, string waktu){
  peminjaman *pointp;
  pointp = frontp;
    while(pointp!=NULL){
      if(pointp->namaruangan == namar && pointp->hari == hari && pointp->statusp == "Belum" && pointp->waktu == waktu){
        return false;
      }
      pointp = pointp->next;
    }
  return true;
}

int peminjamanRuang(int pilhari){
  ambilDataPeminjam();ulang :
  gotoxy(38,32);cout<<"                                                 "; 
  int pilihRuang;
  char waktu;
  int y=7,no=1;
  ruang *point = front;
  peminjaman *pointp;
  bool ada;
  gotoxy(38,4);cout<<"No.           Ruangan                 Peminjam  ";
  switch(pilhari){
    case 1: table(4);
        while(point!=NULL){
          ada = false;
          pointp = frontp;
          gotoxy(38,y);cout<<no<<".\t"<<point->namar<<endl;
          while(pointp!=NULL){
            if(pointp->namaruangan == point->namar && pointp->hari == "Senin" && pointp->statusp == "Belum"){
              gotoxy(75,y);cout<<pointp->sipeminjam.namap;
              gotoxy(85,y);cout<<pointp->waktu;
              ada = true;
              break;
            }
            pointp = pointp->next;
          }
          if(!ada){
            gotoxy(80,y);cout<<"-";
          }
          point = point->next;no++;y+=2;
        }
        
        table(5);
        point = front;
        gotoxy(3,36);cout<<"Kembali 0 ";
        gotoxy(38,27);cout<<"Pilih Ruangan : "; cin>>pilihRuang;
        if(pilihRuang>count && pilihRuang<1 || pilihRuang == 0){
        return 1;break; 
        }
        for(int i=0;i<pilihRuang-1;i++){
          point = point->next;
        }
        if(cekpeminjaman("Senin",point->namar,"Malam")){
          u_peminjaman(point->namar,"Malam","Senin");  
        }else{
          gotoxy(38,32); cout<<"Ruang Sudah Dipinjam Silahkan Pilih Kembali"; getch();
          goto ulang;
        }
            
      break;
    case 2: table(4);
        while(point!=NULL){
          ada = false;
          pointp = frontp;
          gotoxy(38,y);cout<<no<<".\t"<<point->namar<<endl;
          while(pointp!=NULL){
            if(pointp->namaruangan == point->namar && pointp->hari == "Selasa" && pointp->statusp == "Belum"){
              gotoxy(75,y);cout<<pointp->sipeminjam.namap;
              gotoxy(85,y);cout<<pointp->waktu;
              ada = true;
              break;
            }
            pointp = pointp->next;
          }
          if(!ada){
            gotoxy(80,y);cout<<"-";
          }
          point = point->next;no++;y+=2;
        }
        table(5);
        point = front;
        gotoxy(3,36);cout<<"Kembali 0 ";
        gotoxy(38,27);cout<<"Pilih Ruangan : "; cin>>pilihRuang;
        if(pilihRuang>count && pilihRuang<1 || pilihRuang == 0){
          return 1;break; 
        }
        for(int i=0;i<pilihRuang-1;i++){
          point = point->next;
        }
        if(cekpeminjaman("Selasa",point->namar,"Malam")){
          u_peminjaman(point->namar,"Malam","Selasa");  
        }else{
          gotoxy(38,32); cout<<"Ruang Sudah Dipinjam Silahkan Pilih Kembali"; getch();
          goto ulang;
        }
      break;
    case 3: table(4);
        pointp = frontp;
        while(point!=NULL){
          ada = false;
          pointp = frontp;
          gotoxy(38,y);cout<<no<<".\t"<<point->namar<<endl;
          while(pointp!=NULL){
            if(pointp->namaruangan == point->namar && pointp->hari == "Rabu" && pointp->statusp == "Belum"){
              gotoxy(75,y);cout<<pointp->sipeminjam.namap;
              gotoxy(85,y);cout<<pointp->waktu;
              ada = true;
              break;
            }
            pointp = pointp->next;
          }
          if(!ada){
            gotoxy(80,y);cout<<"-";
          }
          point = point->next;no++;y+=2;
        }
        table(5);
        point = front;
        gotoxy(3,36);cout<<"Kembali 0 ";
        gotoxy(38,27);cout<<"Pilih Ruangan : "; cin>>pilihRuang;  
        if(pilihRuang>count && pilihRuang<1 || pilihRuang == 0){
          return 1;break; 
        }
        for(int i=0;i<pilihRuang-1;i++){
          point = point->next;
        }
        if(cekpeminjaman("Rabu",point->namar,"Malam")){
          u_peminjaman(point->namar,"Malam","Rabu");  
        }else{
          gotoxy(38,32); cout<<"Ruang Sudah Dipinjam Silahkan Pilih Kembali"; getch();
          goto ulang;
        }
      break;
    case 4: table(4);
        while(point!=NULL){
          ada = false;
          pointp = frontp;
          gotoxy(38,y);cout<<no<<".\t"<<point->namar<<endl;
          while(pointp!=NULL){
            if(pointp->namaruangan == point->namar && pointp->hari == "Kamis" && pointp->statusp == "Belum"){
              gotoxy(75,y);cout<<pointp->sipeminjam.namap;
              gotoxy(85,y);cout<<pointp->waktu;
              ada = true;
              break;
            }
            pointp = pointp->next;
          }
          if(!ada){
            gotoxy(80,y);cout<<"-";
          }
          point = point->next;no++;y+=2;
        }
        table(5);
        point = front;
        gotoxy(3,36);cout<<"Kembali 0 ";
        gotoxy(38,27);cout<<"Pilih Ruangan : "; cin>>pilihRuang;
        if(pilihRuang>count && pilihRuang<1 || pilihRuang == 0){
          return 1;break; 
        }
        for(int i=0;i<pilihRuang-1;i++){
          point = point->next;
        }
        if(cekpeminjaman("Kamis",point->namar,"Malam")){
          u_peminjaman(point->namar,"Malam","Kamis");  
        }else{
          gotoxy(38,32); cout<<"Ruang Sudah Dipinjam Silahkan Pilih Kembali"; getch();
          goto ulang;
        }
      break;
    case 5: table(4);
        while(point!=NULL){
          ada = false;
          pointp = frontp;
          gotoxy(38,y);cout<<no<<".\t"<<point->namar<<endl;
          while(pointp!=NULL){
            if(pointp->namaruangan == point->namar && pointp->hari == "Jumat" && pointp->statusp == "Belum"){
              gotoxy(75,y);cout<<pointp->sipeminjam.namap;
              gotoxy(85,y);cout<<pointp->waktu;
              ada = true;
              break;
            }
            pointp = pointp->next;
          }
          if(!ada){
            gotoxy(80,y);cout<<"-";
          }
          point = point->next;no++;y+=2;
        }
        table(5);
        point = front;
        gotoxy(3,36);cout<<"Kembali 0 ";
        gotoxy(38,27);cout<<"Pilih Ruangan : "; cin>>pilihRuang;
        if(pilihRuang>count && pilihRuang<1 || pilihRuang == 0){
          return 1;break; 
        }
        for(int i=0;i<pilihRuang-1;i++){
          point = point->next;
        }
        if(cekpeminjaman("Jumat",point->namar,"Malam")){
          u_peminjaman(point->namar,"Malam","Jumat");  
        }else{
          gotoxy(38,32); cout<<"Ruang Sudah Dipinjam Silahkan Pilih Kembali"; getch();
          goto ulang;
        }
      break;
    case 6:table(4);
        while(point!=NULL){
          ada = false;
          pointp = frontp;
          gotoxy(38,y);cout<<no<<".\t"<<point->namar<<endl;
          while(pointp!=NULL){
            if(pointp->namaruangan == point->namar && pointp->hari == "Sabtu" && pointp->statusp == "Belum" && pointp->waktu == "Siang"){
              gotoxy(75,y);cout<<pointp->sipeminjam.namap;    
              ada = true;
              break;
            }
            pointp = pointp->next;
          }
          if(!ada){
            gotoxy(80,y);cout<<"-";
          }
          gotoxy(85,y);cout<<"(Siang)";
          ada = false;
          pointp = frontp;
          while(pointp!=NULL){
            if(pointp->namaruangan == point->namar && pointp->hari == "Sabtu" && pointp->statusp == "Belum" && pointp->waktu == "Malam"){
              gotoxy(75,y+1);cout<<pointp->sipeminjam.namap;
              gotoxy(85,y+1);cout<<pointp->waktu;
              ada = true;
              break;
            }
            pointp = pointp->next;
          }
          if(!ada){
            gotoxy(80,y+1);cout<<"-";
          }
          gotoxy(85,y+1);cout<<"(Malam)";
          point = point->next;no++;y+=2;
        }
        table(5);
        point = front;
        gotoxy(3,36);cout<<"Kembali 0 ";
        gotoxy(38,27);cout<<"Pilih Ruangan : "; cin>>pilihRuang;
        if(pilihRuang>count && pilihRuang<1 || pilihRuang == 0){
          return 1;break; 
        }
        for(int i=0;i<pilihRuang-1;i++){
          point = point->next;
        }
              
        gotoxy(38,27);cout<<"                                                    "; 
        gotoxy(38,27);cout<<"1. Siang | 2. Malam | Waktu(1/2): "; cin>>waktu;
        if(waktu=='1'){
          if(cekpeminjaman("Sabtu",point->namar,"Siang")){
            u_peminjaman(point->namar,"Siang","Sabtu");  
          }else{
            gotoxy(38,27);cout<<"                                                    "; 
            gotoxy(38,32); cout<<"Ruang Sudah Dipinjam Silahkan Pilih Kembali"; getch();
            goto ulang;
          }
        }else if (waktu == '2'){
          if(cekpeminjaman("Sabtu",point->namar,"Malam")){
            u_peminjaman(point->namar,"Malam","Sabtu");  
          }else{
            gotoxy(38,27);cout<<"                                                    "; 
            gotoxy(38,32); cout<<"Ruang Sudah Dipinjam Silahkan Pilih Kembali"; getch();
            goto ulang;
          }
        }else{
          break;
        }
        
      break;
    case 7:table(4);
        while(point!=NULL){
          ada = false;
          pointp = frontp;
          gotoxy(38,y);cout<<no<<".\t"<<point->namar<<endl;
          while(pointp!=NULL){
            if(pointp->namaruangan == point->namar && pointp->hari == "Minggu" && pointp->statusp == "Belum" && pointp->waktu == "Siang"){
              gotoxy(75,y);cout<<pointp->sipeminjam.namap;    
              ada = true;
              break;
            }
            pointp = pointp->next;
          }
          if(!ada){
            gotoxy(80,y);cout<<"-";
          }
          gotoxy(85,y);cout<<"(Siang)";
          ada = false;
          pointp = frontp;
          while(pointp!=NULL){
            if(pointp->namaruangan == point->namar && pointp->hari == "Minggu" && pointp->statusp == "Belum" && pointp->waktu == "Malam"){
              gotoxy(75,y+1);cout<<pointp->sipeminjam.namap;
              gotoxy(85,y+1);cout<<pointp->waktu;
              ada = true;
              break;
            }
            pointp = pointp->next;
          }
          if(!ada){
            gotoxy(80,y+1);cout<<"-";
          }
          gotoxy(85,y+1);cout<<"(Malam)";
          point = point->next;no++;y+=2;
        }
        table(5);
        point = front;
        gotoxy(3,36);cout<<"Kembali 0 ";
        gotoxy(38,27);cout<<"Pilih Ruangan : "; cin>>pilihRuang;
        if(pilihRuang>count && pilihRuang<1 || pilihRuang == 0){
          return 1;break; 
        }
        for(int i=0;i<pilihRuang-1;i++){
          point = point->next;
        }
              
        gotoxy(38,27);cout<<"                                                    "; 
        gotoxy(38,27);cout<<"1. Siang | 2. Malam | Waktu(1/2): "; cin>>waktu;
        if(waktu=='1'){
          if(cekpeminjaman("Minggu",point->namar,"Siang")){
            u_peminjaman(point->namar,"Siang","Minggu");  
          }else{
            gotoxy(38,27);cout<<"                                                    "; 
            gotoxy(38,32); cout<<"Ruang Sudah Dipinjam Silahkan Pilih Kembali"; getch();
            goto ulang;
          }
        }else if (waktu == '2'){
          if(cekpeminjaman("Minggu",point->namar,"Malam")){
            u_peminjaman(point->namar,"Malam","Minggu");  
          }else{
            gotoxy(38,27);cout<<"                                                    "; 
            gotoxy(38,32); cout<<"Ruang Sudah Dipinjam Silahkan Pilih Kembali"; getch();
            goto ulang;
          }
        }else{
          break;
        }
      break;
  }
return 0;
}


int u_user(int pil){
  if(pil==1){
    gotoxy(39,16);cout<<"\t[\t1. Lihat Data\t  \t]";
    gotoxy(39,17);cout<<"\t\t2. Pinjam Ruangan";
    gotoxy(39,18);cout<<"\t\t3. Keluar ";gotoxy(27,30);cout<<"Navigate: Arrow Up and Down    Select: Enter    Back: Esc";
    return 1;
  }else if(pil==2){
    gotoxy(39,16);cout<<"\t\t1. Lihat Data\t  "; 
    gotoxy(39,17);cout<<"\t[\t2. Pinjam Ruangan  \t]"; 
    gotoxy(39,18);cout<<"\t\t3. Keluar ";    gotoxy(27,30);cout<<"Navigate: Arrow Up and Down    Select: Enter    Back: Esc";
    return 2;
  }else if(pil==3){
    gotoxy(39,16);cout<<"\t\t1. Lihat Data\t  "; 
    gotoxy(39,17);cout<<"\t\t2. Pinjam Ruangan  ";
    gotoxy(39,18);cout<<"\t[\t3. Keluar \t\t]"; gotoxy(27,30);cout<<"Navigate: Arrow Up and Down    Select: Enter    Back: Esc";
    return 3;
  }
}


int u_pilihruang(int pildata, int y){
  if(y<32){
    if(pildata==1){
      y = 7;
      gotoxy(11,y);cout<<"[";gotoxy(46,y);cout<<"]";
      gotoxy(27,35);cout<<"Navigate: Arrow Up and Down    Select: Enter    Back: Esc";
      no_r = pildata;
    }else{
      gotoxy(11,y);cout<<"[";gotoxy(46,y);cout<<"]";
      gotoxy(27,35);cout<<"Navigate: Arrow Up and Down    Select: Enter    Back: Esc";
      no_r = pildata;
    }  
  }
}

void namahari(){
  gotoxy(11,4);cout<<"Pilih Hari ";gotoxy(13,7);cout<<"Senin ";gotoxy(13,9);cout<<"Selasa ";
  gotoxy(13,11);cout<<"Rabu ";gotoxy(13,13);cout<<"Kamis ";gotoxy(13,15);cout<<"Jumat ";
  gotoxy(13,17);cout<<"Sabtu ";gotoxy(13,19);cout<<"Minggu ";
}

int u_pilhari(int pilhari){
  if(pilhari==1){
    gotoxy(10,7);cout<<"[";gotoxy(20,7);cout<<"]";
    gotoxy(3,25);cout<<"Navigate: Arrow Up and Down"; 
    gotoxy(3,27);cout<<"Select: Enter";gotoxy(3,29);cout<<"Back: Esc";
    return 1;}
  else if(pilhari==2){
    gotoxy(10,9);cout<<"[";gotoxy(20,9);cout<<"]";
    gotoxy(3,25);cout<<"Navigate: Arrow Up and Down"; 
    gotoxy(3,27);cout<<"Select: Enter";gotoxy(3,29);cout<<"Back: Esc";
    return 2;}
  else if(pilhari==3){
    gotoxy(10,11);cout<<"[";gotoxy(20,11);cout<<"]";
    gotoxy(3,25);cout<<"Navigate: Arrow Up and Down"; 
    gotoxy(3,27);cout<<"Select: Enter";gotoxy(3,29);cout<<"Back: Esc";
    return 3;}
  else if(pilhari==4){
    gotoxy(10,13);cout<<"[";gotoxy(20,13);cout<<"]";
    gotoxy(3,25);cout<<"Navigate: Arrow Up and Down"; 
    gotoxy(3,27);cout<<"Select: Enter";gotoxy(3,29);cout<<"Back: Esc";
    return 4;}
  else if(pilhari==5){
    gotoxy(10,15);cout<<"[";gotoxy(20,15);cout<<"]";
    gotoxy(3,25);cout<<"Navigate: Arrow Up and Down"; 
    gotoxy(3,27);cout<<"Select: Enter";gotoxy(3,29);cout<<"Back: Esc";
    return 5;}
  else if(pilhari==6){
    gotoxy(10,17);cout<<"[";gotoxy(20,17);cout<<"]";
    gotoxy(3,25);cout<<"Navigate: Arrow Up and Down"; 
    gotoxy(3,27);cout<<"Select: Enter";gotoxy(3,29);cout<<"Back: Esc";
    return 6;}
  else if(pilhari==7){
    gotoxy(10,19);cout<<"[";gotoxy(20,19);cout<<"]";
    gotoxy(3,25);cout<<"Navigate: Arrow Up and Down"; 
    gotoxy(3,27);cout<<"Select: Enter";gotoxy(3,29);cout<<"Back: Esc";
    return 7;}
}

main(){
  buffer_size(120,40); gotoxy(0,0); system("CLS");
  ambilDataRuang();countDatar();
  int pilih;
  char kembali;
    while(kembali!=13){
MENU:
  
  int y=7;
  system("cls");
  gotoxy(40,11); cout<<"SISTEM PEMINJAMAN RUANGAN UNMUL";
    gotoxy(39,12); cout<<"----------------------------------"<<endl;
    gotoxy(40,13); cout<<"Menu : "<<endl;
  gotoxy(40,15); cout<<"[1.] Admin"<<endl;   
  gotoxy(40,17); cout<<"[2.] User"<<endl;
  gotoxy(40,19); cout<<"[3.] Keluar"<<endl;
    gotoxy(40,21); cout<<"Masukkan pilihan Anda : ";
    cin>>pilih;
    switch(pilih){
    case 1 :
      system("cls");
    admin1();
    admin2();
      break;
  case 2 :
MAIN:   system("CLS");
    system("COLOR 0F");
    x1 = NULL;
    x2 = NULL;
    x3 = NULL;
    while(x1!=13){
      u_user(pil);
      x1=getch();
      if(x1==72){
        system("CLS");
          if(pil==1){
            pil=3;
          }
          else{pil--;}
      }
      else if(x1==80){
        system("CLS");
          if(pil==3){
            pil=1;
          }
          else{pil++;}
      }
      else if(x1==27){goto MENU; break;}
      else{system("CLS");}
      }
      
      switch(pil){
        case 1://1. lihat data
        B1:    pildata=1;namaruang();
            table(1);
            while(x2!=13){
              u_detailRuang(pildata, y);x2=getch();
              if(x2==72){
                system("CLS");namaruang();table(1);
                  if(pildata==1){
                    pildata=count;
                    y += (count-1)*2;
                  }else{pildata--; y-=2;}
              }
              else if(x2==80){
                system("CLS");namaruang();table(1);
                  if(pildata==count){
                    pildata=1;
                    y = 7;
                  }else{pildata++; y+=2;}
              }
            else if(x2==27){goto MAIN;}
            }
  
//                                                    lihat detail ruangan
            table(2);
            detailruang(no_r); x2=getch();
            if(x2==27){system("CLS");pildata=1; y = 7; goto B1; break;}
            else if(x2==13){ system("CLS");goto B1; }
            break;
            
        case 2://Peminjaman Ruang
B2:            namahari(); x3=NULL; pilhari=1;
            table(3);
            while(x3!=13){                          //pilih hari
            u_pilhari(pilhari);x3=getch();
            if(x3==72){
              system("CLS");namahari();table(3);
                if(pilhari==1){
                  pilhari=7;
                }else{pilhari--;}
            }
            else if(x3==80){
              system("CLS");namahari();table(3);
                if(pilhari==7){
                  pilhari=1;
                }else{pilhari++;}
            }
            else if(x3==27){system("cls");goto MAIN; break;}
            }
//                                                                                  peminjaman ruangan

            if(peminjamanRuang(pilhari)){
              system("cls"); goto B2; break;
            }  
          break;
        default: exit(1);
      }
      break;
    case 3 : exit(1);
    }
    }return EXIT_SUCCESS;
}
