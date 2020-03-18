#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
// @author Ayþe ÖZAVCÝ 
/*-------------------------*/
struct hashTable{
	char *isim;
	int key;
};
char * karsilastir2(char *dosya_ismi){
	FILE *p1;

	char *pnt=malloc(1000*sizeof(int));
	p1=fopen(dosya_ismi,"r");					//Yeni eklenmek istenen dosyanýn karþýlaþtýrýlmasý için okunmasý
	fgets(pnt,1000,p1);
	//puts(pnt);
	fclose(p1);

return pnt;
}
char * karsilastir(char *dosya_ismi){
	FILE *p1;
	char dizin[8]="AA_Hw2\\";
	char *pnt=malloc(1000*sizeof(int));			//Adreste bulunan dosyanýn yeni eklenecek dosyayla karþýlaþtýrýlmasý için adresteki dosyanýn okunmasý
	p1=fopen(strcat(dizin,dosya_ismi),"r");
	fgets(pnt,1000,p1);
	//puts(pnt);
	fclose(p1);

return pnt;
}
/*---------------------------------------------------------------------------*/
void hashAdd(int key_toplam,char *dosya_ismi,int m,struct hashTable hash[m]){
//	printf("\nKey : %d\n",key_toplam);
//	printf("\nTablo uzunlugu : %d",m);
	int adress=key_toplam%m,kontrol=0;		//Opening adress ile adress deðerinin bulunmasý
	int deneme=0,i,ayni_mi;					//ayni_mi deðiþkeni karþýlaþtýrma iþlemi için kullandýðým deðiþken
	ayni_mi=0;
//	printf("\nDosyanin adresi : %d\n",adress);
	if(hash[adress].key==0){
		hash[adress].isim=dosya_ismi  ;		//Eðer opening adress ile bulunan adres boþsa eklenmesi
		hash[adress].key=key_toplam;
		printf("Eklenen adres  :  %d\n",adress);
		printf("\n-----------------------------------------\n");
		
		deneme++;
    	}else{
			printf("\n---------------------------------------------\n");
			printf("\nADRESTEKÝ DOSYA ISMI : %s\n",hash[adress].isim);
			printf("\nGELEN DOSYA ISMI : %s\n",dosya_ismi);
			printf("\n---------------------------------------------\n");
			
			char * pnt1=malloc(1000*sizeof(int));			//Karþýlaþtýrma iþlemi için adresteki dosya için ve eklenmek istenen dosya için dizi tanýmlamasý
			char * pnt2=malloc(1000*sizeof(int));
			pnt1=karsilastir2(dosya_ismi);
			pnt2=karsilastir(hash[adress].isim);
			if(!strcmp(pnt1,pnt2)){
				printf("Bu Dosyalar ayni");
			}else {											//strcmp ile karþýlaþtýrma iþleminin yapýlmasý
				printf("Bu dosyalar farkli");
				ayni_mi++;
			}
			if(ayni_mi!=0){
				FILE *fp;
				char *icerik=malloc(5*sizeof(int));
				char dizi[2]="\n";
				fp=fopen("AA_Hw2\\Index.txt","a");				//Eðer dosyalar farklýysa double hashing ile yerleþtirilmesi
				fprintf(fp,strcat(dizi,dosya_ismi));
				fclose(fp);
			int adress2=1+(key_toplam%(m-1));
			printf("Adress 2 : %d",adress2);
			int i;
			for(i=1;i<m;i++){
		
			if(kontrol==0 && hash[(adress+i*(adress2))%m].key==0){
				hash[(adress+i*(adress2))%m].isim=dosya_ismi;
				hash[(adress+i*(adress2))%m].key=key_toplam;
				printf("\nCakisma oldu,Hash adresi : %d\n",(key_toplam+i*(adress2))%m);
				
			kontrol++;
			}
			}
				deneme++;
		}
	}
	int s;
		for(i=0;i<m;i++){
			if(hash[i].key!=0&&s==m-1){
				printf("\nHASH DOLU!!\n");		//Hash doluluk kontrolü
				s++;
			}
		}

	printf("--------------------------------------------------------------------------------");
	for(i=0;i<m;i++){
		printf("\nKey degeri : %d" , hash[i].key );
		printf("     Dosya ismi : %s\n" , hash[i].isim );
	}
	printf("--------------------------------------------------------------------------------");
}
/*----------------------------------------------------------------*/
int hashFunction(char *kelime){	
	int R=1;
	int i;
	int key = 0, toplam=0;
	int us=strlen(kelime);
	for(i=0;i<strlen(kelime);i++){
	
		us=us-1;							//Boþluk olmadan ki key hesabý
		toplam=toplam+kelime[i];
		key=(kelime[i]*pow(R,us));
}
	key=toplam;
//	printf("\n\nKey : %d\n",key);
	return key;
}
/*----------------------------------------------------------------*/
void yeni_dos(char *dosya_ismi,int m,struct hashTable hash[m]){
	int sayac=0;
	int cikar=0;
	int key_toplam=0;
	int bosluk=0;
	sayac=sayacBul();
	int i=0;
	FILE *fp;
	printf("\nOkunmasi gereken dosya ismi : %s\n",dosya_ismi);
	char *icerik=malloc(100*sizeof(int));		
	fp=fopen(dosya_ismi,"r");
	int c,p;
	do{
		i++;
		c=fscanf(fp,"%s",icerik);			//Eklenmek istenen dosyanýn okunmasý
		p=getc(fp);
		if(p==32){
			bosluk++;
		}
	//	printf("\n%s\n",icerik);
		hashFunction(icerik);			//Key hesabý için hashFunction a gönderilmesi
		cikar=hashFunction(icerik);
	//	printf("\nCikarilacak kelime i : %d",cikar);
		key_toplam=hashFunction(icerik)+key_toplam;	  //Boþluklarla beraber toplam key
	}while(c!=EOF );
//	printf("Toplam key : %d",key_toplam);
	key_toplam=key_toplam-cikar;
	printf("Bosluk sayisi : %d",bosluk);
	printf("Toplam key : %d",key_toplam);
	bosluk=bosluk*32;					//	Boþluklarýn key hesabý
	key_toplam=key_toplam+bosluk;
	printf("Key toplami : %d",key_toplam);
	hashAdd(key_toplam,dosya_ismi,m,hash);	//Key in adrese eklenmesi için hashAdd fonksiyonna gönderilmesi
	fclose(fp);
}
void dosyaOku(char *dosya_ismi,int m,struct hashTable hash[m]){
	int sayac=0;				
	int cikar=0;
	int key_toplam=0;		//Hesaplanacak keylerin toplamý
	int bosluk=0;
	sayac=sayacBul();
	int i=0;
	FILE *fp;
	printf("\nOkunmasi gereken dosya ismi : %s\n",dosya_ismi);
	
	char dizin_adres[8]="AA_Hw2\\";		//Okunulacak dosyalarýn dizinleri
	char *adres=strcat(dizin_adres,dosya_ismi);
	char *icerik=malloc(30*sizeof(int));	//Ýçeriðin atanacaðý içerik pointerý
	fp=fopen(adres,"r");
	int c,p;
	do{
		
		i++;
		c=fscanf(fp,"%s",icerik);
		p=getc(fp);
		if(p==32){
			bosluk++;			//Boþluklarýn hesaplanmasý
		}
	//	printf("\n%s\n",icerik);
		hashFunction(icerik);		//Key in hesaplanmasý için içeriðin hashFunction a gönderilmesi
		cikar=hashFunction(icerik);
	//	printf("\nCikarilacak kelime i : %d",cikar);
		key_toplam=hashFunction(icerik)+key_toplam;	//Boþluklarla beraber toplam key
	}while(c!=EOF );
//	printf("Toplam key : %d",key_toplam);
	key_toplam=key_toplam-cikar;		//Fazla okunanlarýn silinmesi
	printf("Bosluk sayisi : %d",bosluk);
	printf("Toplam key : %d",key_toplam);
	bosluk=bosluk*32;
	key_toplam=key_toplam+bosluk;
	printf("Key toplami : %d",key_toplam);
	hashAdd(key_toplam,dosya_ismi,m,hash);		//Hash adresinin bulnup hash e eklenmesi için hashAdd e gönderilmesi
	fclose(fp);
}

/*---------------------------------------------------------------------------*/

void samplesDosAc(int m,struct hashTable hash[m]){
	int c,i=0;
	FILE *fp;
	char *f1,*f2,*f3;
	f1=malloc(20*sizeof(int));			//Veri tabanýndaki dosyalar için pointer tanýmlanmasý
	f2=malloc(20*sizeof(int));
	f3=malloc(20*sizeof(int));
	int sayac=sayacBul();
	fp=fopen("AA_Hw2\\Index.txt","r");
	do {
		
	i++;
			if(i-1==0){
			c = fscanf(fp,"%s",f1) ;
			dosyaOku(f1,m,hash); 				//Her bir dosyanýn okunmasý için fonksiyona gönderilmesi
		}
			if(i-1==1){
			c = fscanf(fp,"%s",f2) ;
			dosyaOku(f2,m,hash); 
		}
			if(i-1==2){
			c = fscanf(fp,"%s",f3) ;
			dosyaOku(f3,m,hash); 
		}
   } while (c != EOF &&i<sayac-1);      
      
   fclose(fp);
}

/*--------------------------------------*/

int sayacBul(){
	int c,sayac=0;
	FILE *fp;
	char *dosya=malloc(100*sizeof(int));
	fp=fopen("AA_Hw2\\Index.txt","r");				//Index.txt denin içinde bulunan dosya sayýsý
	do {
     	c = fscanf(fp,"%s",dosya); 
		sayac++;
   } while (c != EOF);      
      
   fclose(fp);
   return sayac;
}
/*-------------------------------------*/


int asal(int a) {
    int i;
    int sayac = 0;							//Eðer tablo uzunluðu asal deði ise en düþük asal sayinin bulunmasý
    for (i = 2; i < a; i++) {
        if (a % i == 0) {
            sayac++;
        }
    }
    if (sayac == 0)
        return 1;
    else
        return 0;
}


/*---------------------------------------*/
int dosyaSayisi() {
    FILE *fp;
    int c, sayac = 0, m, i;
    char *dosya_ismi = malloc(200 * sizeof (int));
    fp = fopen("AA_Hw2\\Index.txt", "r");			//Index.txt dosyasýnýn açýlmasý ve içinde yazan dosyalarýn çekilmesi
    do {
        c = fscanf(fp, "%s", dosya_ismi); 
        printf("%s\n",dosya_ismi);

        sayac++;
    } while (c != EOF);
    sayac = sayac / 0.6;						//Veri tabanýnda bulunan dosya_sayisi*loadFactor
    if(asal(sayac)==0){
    	return (sayac-1);
	}
	else {
    for (m = 2; m < sayac; m++) {
        if (sayac % m == 0) {
            m = 2;
            sayac--;
        }
    }
    for (i = sayac + 1; asal(i) != 1; i++) {			//Eðer tablo uzunluðu asal deði ise en düþük asal sayinin bulunmasý
        m = i;
    }
      return (m + 1);									//Tablo uzunluðunun return edilmesi
}	
  
}
/*--------------------------------------------------------*/

int main(){
	system("mkdir AA_Hw2");	//Dosyalarýn toplanacaðý directory.
	system("move A.txt AA_Hw2\\");
	system("move B.txt AA_Hw2\\");		//Dosyalarýn directory e taþýnmasý
	system("move C.txt AA_Hw2\\");
	system("move Index.txt AA_Hw2\\");
	FILE *fp=fopen("AA_Hw2\\Index.txt","w");
	fprintf(fp, "%s\n", "A.txt"); 
	fprintf(fp, "%s\n", "B.txt");			//Index.txt ye dosya isimlerinin yazýlmasý
	fprintf(fp, "%s\n", "C.txt");
	fclose(fp);
	int i;
	int m=dosyaSayisi();					//Dosya sayisi
	printf("Dosya_sayisi : %d",m);
	struct hashTable hash[m];				//Hash tanýmý
	for(i=0;i<m;i++){
		hash[i].key=0;					//Hash in ilk deðerlerinin en baþta default olarak atanmasý
		hash[i].isim=NULL;
	}
	samplesDosAc(m,hash);
	printf("\n---------------Yeni eklenmesi gereken dosyalar  : D.txt ve E.txt ------------------\n");
	yeni_dos("D.txt",m,hash);				//Eklenecek yeni dosyalar.
	yeni_dos("E.txt",m,hash);
}
