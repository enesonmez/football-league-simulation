#include <stdio.h>
#include <stdlib.h>

struct takimlar
{
    char takimUzunAd[13];
    char takimKisaAd;
    int macSayisi,galibiyet,beraberlik,maglubiyet,aGol,yGol,averaj,puan;
};
//ayarlar[0]=takım sayısı, ayarlar[1]=galibiyet, ayarlar[2]=beraberlik, ayarlar[3]=mağlubiyet
//A 2 B 1 sırasıyla bu verileri şu değişkenler tutar : birTakim birGol ikiTakim ikiGol
int birGol[200],ikiGol[200],macSayici=0,ayarlar[4],DosyadakiTakimSayisi=0;
char birTakim[100][1],ikiTakim[100][1], tkmler[50][15];

int takimSayisiAnalizi();
void takimlarDosyasiniOkuma();
void takimlarYapisiniOlusturma(struct takimlar x[]);
void ayarlarDosyasiniOkuma();
void skorislemleri(struct takimlar y[]);
int maclarDosyasiniOkuma(struct takimlar p[]);
void klavyeMaclariOkuma(struct takimlar k[]);
void buyukHarfYapma(struct takimlar v[]);
char * kucukHarfYapma(char isim[50]);
void alfabetikSiralama(int gonderilendizi[]);
void puanSiralama(struct takimlar t[],int gonderilendizi[]);
void varsayilanPuanTablosunuYazdirma(struct takimlar z[],int deger,int value);
void kosulluPuanTablosunuYazdirma(struct takimlar z[],int value);
void AnaMenu(struct takimlar m[]);
int takimvarmiyokmi(struct takimlar e[],int value,int kullanim);
int dahaOnceMacYapmismi(struct takimlar l[],int value);
void stringcopy(char * const s1, const char * const s2);
void ayarlarDosyasiniDegistirme(struct takimlar u[]);
void swap(char *str1, char *str2);

int main(){//*********************************************************************************************************************************************
    ayarlarDosyasiniOkuma();
    takimlarDosyasiniOkuma();
    struct takimlar takim[ayarlar[0]];
    takimlarYapisiniOlusturma(takim);
    AnaMenu(takim); 
}

void AnaMenu(struct takimlar m[]){//Kolay bir kullanıcı arayüzü için oluşturulmuş menü
    takimlarDosyasiniOkuma();
    int secim;
    dongu:
    printf("\n\t\t\t## Dosyadan maç girişi için                          --->     1\n");
    printf("\t\t\t## Klavyeden maç girişi için                         --->     2\n");
    printf("\t\t\t## Ekrana yazılacak puan tablosu için                --->     3\n");
    printf("\t\t\t## Dosyaya yazılacak puan tablosu için               --->     4\n");
    printf("\t\t\t## Ayarlar dosyasındaki bilgileri değiştirmek için   --->     5\n");
    printf("\t\t\t## Çıkış için                                        --->     6\n\t\t\t## Tercihiniz : ");
    scanf("%d",&secim);
    switch (secim)
    {
        case 1:
            maclarDosyasiniOkuma(m);
            takimlarYapisiniOlusturma(m);
            skorislemleri(m);
            goto dongu;
            break;
        case 2:
            klavyeMaclariOkuma(m);
            goto dongu;
            break;
        case 3:
            kosulluPuanTablosunuYazdirma(m,0);
            break;
        case 4:
            kosulluPuanTablosunuYazdirma(m,1);
            break;
        case 5:
            ayarlarDosyasiniDegistirme(m);
            break;
        case 6:
            exit(4);
            break;
        default:
            goto dongu;
            break;
    } 

}

int takimSayisiAnalizi(){ //ayarlar[0]-dosyadakitakimsayisi 0 dan buyuk olursa (ayarlar[0]-(ayarlar[0]-DosyadakiTakimSayisi)) bunu yazacak olmazsa ayarlar[0] yazacak  
    if (((ayarlar[0]-DosyadakiTakimSayisi))>=0) //takım sayısı analizi ile az ya da çok takım girdisi olduğunda bu durumu kontrol altına almak için yazılmıştır.
        return ayarlar[0]-(ayarlar[0]-DosyadakiTakimSayisi);
    else
        return ayarlar[0];  
}

void takimlarDosyasiniOkuma(){//Bu fonksiyon ile takimlar dosyasında kaç takım olduğunu öğreneceğim bu bilgiyi ise puan tabosunda kullanacağım. 
    FILE *dosya = fopen("takimlar.txt","r");//Dosya okuması için fopen fonksiyonun ve "r" modunu kullanıyoruz.
    int i=0;
    while(!feof(dosya)){
        fscanf(dosya,"%s",tkmler[i]);
        i++;
        if (ayarlar[0]<=i) {//takımlar dosyasındaki takım sayısı ayarlardaki takım sayısına eşit olduğu zaman döngüyü kıracak.
            break;
        }
    }
    DosyadakiTakimSayisi=i;
}

void takimlarYapisiniOlusturma(struct takimlar x[]){//Yapının içerisindeki elemanlara değer ataması yaptığımız fonksiyon.
    FILE *dosya = fopen("takimlar.txt","r");//Dosya okuması için fopen fonksiyonun ve "r" modunu kullanıyoruz.
    int i=0;
    char harf='A';
    if (dosya==NULL) {
        printf("\t\t\tDosya Bulunamadı");//Dosya var mı yok mu kontrolü yapıyoruz.
    }
    else
    {            
        while(i < takimSayisiAnalizi()){//struct yapısındaki değişkenlerin içini dolduruyoruz.
            fscanf(dosya,"%s",&*x[i].takimUzunAd);
            x[i].takimKisaAd=harf; x[i].macSayisi=0; x[i].galibiyet=0; x[i].beraberlik=0; x[i].maglubiyet=0; x[i].aGol=0; x[i].yGol=0; x[i].averaj=0; x[i].puan=0; 
            harf++;
            i++;
        }
        fclose(dosya);
    }
}


void ayarlarDosyasiniOkuma(){//Ayarlar dosyasındaki verileri ayarlar[] dizime çekiyorum.   
    FILE *dosya = fopen("ayarlar.txt","r");
    int i=0;
    if(dosya==NULL){
        printf("\t\t\tDosya Bulunamadı.");
    }
    else
    {
        while(!feof(dosya)){
            fscanf(dosya,"%d",&ayarlar[i]);
            i++;
        }
        fclose(dosya);  
    }  
}

int takimvarmiyokmi(struct takimlar e[],int value,int kullanim){//Ligde girilen takım var mı yok mu kontrolünü yapmaya yarayan fonksiyon
    int bayrak1=1,bayrak2=1;//bayrak sıfır dönerse takım ligde var bir dönerse ligde yok demektir.
    for(int i = 0; i < takimSayisiAnalizi(); i++)
    {
        if (birTakim[value][0]==e[i].takimKisaAd) {//Takım ligde var mı yok mu koşulu  
            bayrak1=0;
        }
        if(ikiTakim[value][0]==e[i].takimKisaAd){
            bayrak2=0;
        }     
    }
    if((bayrak1==1 || bayrak2==1)&& kullanim==1) {
        printf("\t\t\t\tGirmiş olduğunuz takım ligde yok.\n"); 
        return 1;
    }
    if((bayrak1==1 || bayrak2==1)&& kullanim==0) {
        return 1;
    }
    return 0;
}

int dahaOnceMacYapmismi(struct takimlar l[],int value){//Burada daha önce maç yapmışmı ve maçı girilen takım ligde var mi kontrolünün yapıldığı fonksiyon
    int bayrak=0;
    bayrak=takimvarmiyokmi(l,macSayici,1);//Ligde girilen takım var mı kontrolü
    for(int i = 0; i < value; i++)
    {
        if (birTakim[i][0]==birTakim[value][0] && ikiTakim[i][0]==ikiTakim[value][0]) {//Daha önce maç yapmış mmı koşulu
            printf("\t\t\t\t%c ve %c takımları daha önce maç yapmışlardır.\n",birTakim[value][0],ikiTakim[value][0]);
            return 1;
            break;
        }
    }
    return bayrak;
}

int maclarDosyasiniOkuma(struct takimlar p[]){//Dosayadaki maç skorlarının okunduğu ve dosyadan okunan maç sayısını döndüren fonksiyon   
    FILE *dosya =fopen("maclar1.txt","r");
    printf("\n");
    if (dosya==NULL) {
        printf("\t\t\tDosya bulunamadı.");
    }
    else
    {
        while(!feof(dosya)){
            fscanf(dosya,"%s %d %s %d",birTakim[macSayici],&birGol[macSayici],ikiTakim[macSayici],&ikiGol[macSayici]);//Okunan verileri dizilere atan kısım
            if (birTakim[macSayici][0]==ikiTakim[macSayici][0]) {//A 0 A 0 gibi bir maç girişinde hata verdirecek kod
                printf("\t\t\t\t%c takımı kendisi ile maç yapamaz.\n",birTakim[macSayici][0]);
            }
            dahaOnceMacYapmismi(p,macSayici);//Ligde girilen takım var mı kontrolü ve daha önce maç yapıldıysa hata mesajını ekrana yazdıran fonksiyon çalışacak.
            macSayici++;
        } 
    }
    printf("\t\t\t\t!!!Maçlarınız başarıyla kaydedildi!!!");
    macSayici++;
    return macSayici;
}

void klavyeMaclariOkuma(struct takimlar k[]){//Klavyeden girilecek maçı puan tablosuna işleyeccek kod bloğu 
    printf("\n\t\t\tMaçı giriniz     ----> ");
    scanf("\t\t\t%s%d%s%d",birTakim[macSayici],&birGol[macSayici],ikiTakim[macSayici],&ikiGol[macSayici]);//Klavyeden maçları dizilere atan kısım
    int flag=0;
    printf("\n");
    if (birTakim[macSayici][0]==ikiTakim[macSayici][0]) {
        printf("\t\t\t\t%c takımı kendisi ile maç yapamaz.\n",birTakim[macSayici][0]);
        flag=1;
    }
    flag=dahaOnceMacYapmismi(k,macSayici);//Ligde girilen takım var mı kontrolü ve daha önce maç yapıldıysa hata mesajını ekrana yazdıran fonksiyon çalışacak.
    (flag==0)? printf("\t\t\t\t!!!Maçınız başarıyla kaydedildi."):printf("\t\t\t\t!!!Maçınız kaydedilemedi!!!");
    macSayici++;  
    takimlarYapisiniOlusturma(k);
    skorislemleri(k);
}

void skorislemleri(struct takimlar y[]){//Puan durumunu güncelleme görevini yapan fonksiyon
    ayarlarDosyasiniOkuma();
    int evkonum=0,deplasmankonum=0,ASCII,flag;
    printf("\n");
    for(int i = 0; i < macSayici; i++)
    {
        if (birTakim[i][0]==ikiTakim[i][0]) {//Aynı takımı maç yaptırdıklarında puan işlemi yapmayacak
            continue;
        }
        if (takimvarmiyokmi(y,i,0)==1) {//Ligde girilen takım yoksa puan işlemi yapılmayacak
            continue;
        }
        
        flag=0;
        for(int a = 0; a < i; a++)//Takimlar daha önce maç yapmış mı onu kontrol eden döngü ve koşulu
        {
            if (birTakim[i][0]==birTakim[a][0] && ikiTakim[i][0]==ikiTakim[a][0]) {
                flag=1;
                break;
            }
        }   
        if (flag!=1) {//Bayrak 1 e eşit değilse skor işlemlerini gerçekleştirecek.
            ASCII=birTakim[i][0];
            evkonum=ASCII-65;//ASCII TABLOSUNDA 'A' 65 ile başladığından ve takma adlarda 'A' ile başladığından takma adlardan 65'i çıkarırsak galip takımın yapıdaki yerini buluruz.
            ASCII=ikiTakim[i][0];
            deplasmankonum=ASCII-65;
            
            if (birGol[i]>ikiGol[i]) {//ev sahibi takım galip gelirse uygulanacak puan işlemleri
                y[evkonum].macSayisi+=1;                y[evkonum].galibiyet+=1;                                                    y[evkonum].aGol+=birGol[i];
                y[evkonum].yGol+=ikiGol[i];             y[evkonum].averaj=y[evkonum].aGol - y[evkonum].yGol;                        y[evkonum].puan+=ayarlar[1];

                y[deplasmankonum].macSayisi+=1;         y[deplasmankonum].maglubiyet+=1;                                            y[deplasmankonum].aGol+=ikiGol[i];
                y[deplasmankonum].yGol+=birGol[i];      y[deplasmankonum].averaj=y[deplasmankonum].aGol - y[deplasmankonum].yGol;   y[deplasmankonum].puan+=ayarlar[3];
            }
            else if(birGol[i]<ikiGol[i]){//deplasman takımı galip gelirse uygulanacak puan işlemleri
                y[evkonum].macSayisi+=1;                y[evkonum].maglubiyet+=1;                                                   y[evkonum].aGol+=birGol[i];
                y[evkonum].yGol+=ikiGol[i];             y[evkonum].averaj=y[evkonum].aGol - y[evkonum].yGol;                        y[evkonum].puan+=ayarlar[3];

                y[deplasmankonum].macSayisi+=1;         y[deplasmankonum].galibiyet+=1;                                             y[deplasmankonum].aGol+=ikiGol[i];
                y[deplasmankonum].yGol+=birGol[i];      y[deplasmankonum].averaj=y[deplasmankonum].aGol - y[deplasmankonum].yGol;   y[deplasmankonum].puan+=ayarlar[1];
            }
            else{//maç berabere biterse uygulanacak puan işlemleri
                y[evkonum].macSayisi+=1;                y[evkonum].beraberlik+=1;                                                   y[evkonum].aGol+=birGol[i];
                y[evkonum].yGol+=ikiGol[i];             y[evkonum].averaj=y[evkonum].aGol - y[evkonum].yGol;                        y[evkonum].puan+=ayarlar[2];

                y[deplasmankonum].macSayisi+=1;         y[deplasmankonum].beraberlik+=1;                                            y[deplasmankonum].aGol+=ikiGol[i];
                y[deplasmankonum].yGol+=birGol[i];      y[deplasmankonum].averaj=y[deplasmankonum].aGol - y[deplasmankonum].yGol;   y[deplasmankonum].puan+=ayarlar[2];
            }
        }  
    } 
}

void buyukHarfYapma(struct takimlar v[]){//Verilen değeri büyük harfe çeviren fonksiyon
    for(int i = 0; i < takimSayisiAnalizi(); i++)
    {
        for(int s = 0; s < 12; s++)
        {
            if (v[i].takimUzunAd[s]!='\0') {
                v[i].takimUzunAd[s]-=32;                
            }  
        } 
    }
}

void alfabetikSiralama(int gonderilendizi[]){//Takım uzun adlara göre alfabetik sıralama yapılmak istenildiğinde çalışacak fonksiyon.
    int gecici=0,dizi[takimSayisiAnalizi()];
    char tutucu;
    for(int i = 0; i < takimSayisiAnalizi(); i++)
    {
        dizi[i]=i;
    }
    for(int i=0;i<takimSayisiAnalizi();i++){//Sırala algoritması olan Buble Sort algoritmasını kullandım.
        for(int j=0;j<takimSayisiAnalizi()-1;j++){
            for(int k = 0; k < 12; k++)
            {
                if (tkmler[j][k]=='\0' || tkmler[j+1][k]=='\0') {
                    break;
                }
                if ((int)tkmler[j][k] == (int)tkmler[j+1][k]) {//Karakter karakter karşılaştırma
                    continue;
                }        
                else if ((int)tkmler[j][k] > (int)tkmler[j+1][k])
                {
                    tutucu=tkmler[j][k];
                    tkmler[j][k]=tkmler[j+1][k];
                    tkmler[j+1][k]=tutucu;
                    gecici = dizi[j];
                    dizi[j]=dizi[j+1];
                    dizi[j+1]=gecici;
                }
                break;
            }
        }
    }
    for(int i = 0; i < takimSayisiAnalizi(); i++)
    {
        gonderilendizi[i]=dizi[i];//Oluşturulan indis sıralamasını döndürerek puan tablosu oluşturma da kullanacağım.
    }
}

void puanSiralama(struct takimlar t[],int gonderilendizi[]){//Takımları puan sırasına göre sıralayan fonksiyon
    int puanlar[takimSayisiAnalizi()],dizi[takimSayisiAnalizi()],averajlar[takimSayisiAnalizi()],tutucu=0,gecici=0;
    for(int i = 0; i < takimSayisiAnalizi(); i++)
    {
        puanlar[i]=t[i].puan;
        averajlar[i]=t[i].averaj;
        dizi[i]=i;
    }
    for(int i=0;i<takimSayisiAnalizi();i++){//Sırala algoritması olan Buble Sort algoritmasını kullandım.
        for(int j=0;j<takimSayisiAnalizi()-1;j++){   
            if (puanlar[j] < puanlar[j+1])//puana göre sıralama yapıyor
            {
                tutucu = puanlar[j+1];
                puanlar[j+1] = puanlar[j];
                puanlar[j] = tutucu;
                tutucu = averajlar[j+1];
                averajlar[j+1] = averajlar[j];
                averajlar[j] = tutucu;
                gecici = dizi[j+1];
                dizi[j+1]=dizi[j];
                dizi[j]=gecici;
            }
            else if(puanlar[j] == puanlar[j+1]){//puanlar eşitse averaja göre sıralama yapıyor.
                if (averajlar[j] < averajlar[j+1])
                {
                    tutucu = averajlar[j+1];
                    averajlar[j+1] = averajlar[j];
                    averajlar[j] = tutucu;
                    gecici = dizi[j+1];
                    dizi[j+1]=dizi[j];
                    dizi[j]=gecici;
                }
                else if(averajlar[j] == averajlar[j+1]){//averajlar eşitse takim kısa ada göre sıralama yapacak.
                    if (t[j].takimKisaAd < t[j+1].takimKisaAd) {
                        tutucu = averajlar[j+1];
                        averajlar[j+1] = averajlar[j];
                        averajlar[j] = tutucu;
                        gecici = dizi[j+1];
                        dizi[j+1]=dizi[j];
                        dizi[j]=gecici;
                    } 
                }
            }
        }
    }
    for(int i = 0; i < takimSayisiAnalizi(); i++)
    {
        gonderilendizi[i]=dizi[i];//Oluşturulan indis sıralamasını döndürerek puan tablosu oluşturma da kullanacağım.
    }
}

void varsayilanPuanTablosunuYazdirma(struct takimlar z[],int deger,int value){
    //Bu fonksiyon yapısı her koşullu puan tablosunu yazdırmak için klavyeden seçilen koşullu puan tablosunu buraya referans vererek ekrana veya dosyaya puan tablosunu yazdırmaya yarayan fonksiyondur.
    char buyukharf;
    int dizi[takimSayisiAnalizi()];
    if (deger==1) {//Takim kısa ada göre puan tablosu sıralaması yapıyor.(deger değişkeni kullanıcının isteğini belirten değişkendir.)
        for(int i = 0; i < takimSayisiAnalizi(); i++)
        {
            dizi[i]=i;
        }  
    }
    else if (deger==2) {//Takımların uzun isimlerine göre alfabetik puan sıralaması yapıyor.
        alfabetikSiralama(dizi);//bu fonksiyonda hem ekrana hem de dosyaya puan tablosunu yazdırmamıza yarıyor.
    }
    else if (deger==3) {
        puanSiralama(z,dizi);
    }

    dongu:
    printf("\t\t\t\t=> Takım ismini büyük harfle yazdırmak ister misiniz? (E/H)\n\t\t\t\t=> Tercihiniz : ");
    scanf("%s",&buyukharf);
    
    if (buyukharf=='e' || buyukharf=='E') {//Büyük harf olmasını istediğimizde bu kod bloğu çalışır.
        buyukHarfYapma(z);
        if(value==0){
            printf("\n\t\t\t%4s%10s%11s%20s%8s%8s%8s%8s%8s%9s%10s\n","####","KISA AD","UZUN AD","MS","G","B","M","AG","YG","AV","PUAN");
            printf("\t\t\t--------------------------------------------------------------------------------------------------------\n");
        }
        else if (value==1) {//(value değişkeni ekrana mı yoksa dosyaya mı yazılacağını belirten değikendir. Bir nevi koşul değişkenidir.)
            FILE *dosya=fopen("puantablosu.txt","w");
            fprintf(dosya,"\t\t\t%4s%10s%11s%20s%8s%8s%8s%8s%8s%9s%10s\n","####","KISA AD","UZUN AD","MS","G","B","M","AG","YG","AV","PUAN");
            fprintf(dosya,"\t\t\t--------------------------------------------------------------------------------------------------------\n");
            fclose(dosya);
        }
        for(int i = 0; i < takimSayisiAnalizi(); i++)
        {
            if (value==0) {//Ekrana yazdırma
                printf("\t\t\t%3d)%6c\t%-20s\t%5d\t%5d\t%5d\t%5d\t%5d\t%5d\t%6d\t%6d\n",i+1,z[dizi[i]].takimKisaAd,z[dizi[i]].takimUzunAd,z[dizi[i]].macSayisi,z[dizi[i]].galibiyet,z[dizi[i]].beraberlik,z[dizi[i]].maglubiyet,z[dizi[i]].aGol,z[dizi[i]].yGol,z[dizi[i]].averaj,z[dizi[i]].puan);
            }
            else if (value==1) {//Dosyaya yazdırma
                FILE *dosya=fopen("puantablosu.txt","a");
                fprintf(dosya,"\n\t\t\t%3d)%6c\t%-20s\t%5d\t%5d\t%5d\t%5d\t%5d\t%5d\t%6d\t%6d\n",i+1,z[dizi[i]].takimKisaAd,z[dizi[i]].takimUzunAd,z[dizi[i]].macSayisi,z[dizi[i]].galibiyet,z[dizi[i]].beraberlik,z[dizi[i]].maglubiyet,z[dizi[i]].aGol,z[dizi[i]].yGol,z[dizi[i]].averaj,z[dizi[i]].puan);
                fclose(dosya);
            }
            
        }
        takimlarYapisiniOlusturma(z);
        skorislemleri(z);
    }
    else if(buyukharf=='h' || buyukharf=='H'){//Büyük harf olmasını istemediğizde bu kod bloğu çalışır.
        if(value==0){
            printf("\n\t\t\t%4s%10s%11s%20s%8s%8s%8s%8s%8s%9s%10s\n","####","KISA AD","UZUN AD","MS","G","B","M","AG","YG","AV","PUAN");
            printf("\t\t\t--------------------------------------------------------------------------------------------------------\n");
        }
        else if (value==1) {
            FILE *dosya=fopen("puantablosu.txt","w");
            fprintf(dosya,"\t\t\t%4s%10s%11s%20s%8s%8s%8s%8s%8s%9s%10s\n","####","KISA AD","UZUN AD","MS","G","B","M","AG","YG","AV","PUAN");
            fprintf(dosya,"\t\t\t--------------------------------------------------------------------------------------------------------\n");
            fclose(dosya);
        }
        for(int i = 0; i < takimSayisiAnalizi(); i++)
        {
            if(value==0){//Ekrana  yazdırma
                printf("\t\t\t%3d)%6c\t%-20s\t%5d\t%5d\t%5d\t%5d\t%5d\t%5d\t%6d\t%6d\n",i+1,z[dizi[i]].takimKisaAd,z[dizi[i]].takimUzunAd,z[dizi[i]].macSayisi,z[dizi[i]].galibiyet,z[dizi[i]].beraberlik,z[dizi[i]].maglubiyet,z[dizi[i]].aGol,z[dizi[i]].yGol,z[dizi[i]].averaj,z[dizi[i]].puan);
            }
            else if (value==1) {//Dosyaya yazdırma
                FILE *dosya=fopen("puantablosu.txt","a");
                fprintf(dosya,"\t\t\t%3d)%6c\t%-20s\t%5d\t%5d\t%5d\t%5d\t%5d\t%5d\t%6d\t%6d\n\n",i+1,z[dizi[i]].takimKisaAd,z[dizi[i]].takimUzunAd,z[dizi[i]].macSayisi,z[dizi[i]].galibiyet,z[dizi[i]].beraberlik,z[dizi[i]].maglubiyet,z[dizi[i]].aGol,z[dizi[i]].yGol,z[dizi[i]].averaj,z[dizi[i]].puan);
                fclose(dosya);
            }
        }
    }
    else
    {
        goto dongu;
    }   
}

void kosulluPuanTablosunuYazdirma(struct takimlar z[],int value){
    //Skor tablosunu isteklere göre yazdıran fonksiyon(value ekrana(0) ya da dosyaya(1) yazdırmak için bir koşul değişkeni olarak tanımlanmıştır.)
    int istek;
    dongu:
    printf("\n\t\t\t\t=> Takımların takma isim sırasına göre puan durumu için    --->     1\n");
    printf("\t\t\t\t=> Takımların alfabetik sırasına göre puan durumu için     --->     2\n");
    printf("\t\t\t\t=> Puan sırasına göre puan durumu için                     --->     3\n");
    printf("\t\t\t\t=> Üst menüye gitmek için                                  --->     4\n\t\t\t\t=> Tercihiniz : ");
    scanf("%d",&istek);
    switch (istek)
    {
        case 1:
            varsayilanPuanTablosunuYazdirma(z,istek,value);
            AnaMenu(z);
            break;
        case 2:
            varsayilanPuanTablosunuYazdirma(z,istek,value);
            AnaMenu(z);
            break;
        case 3:
            varsayilanPuanTablosunuYazdirma(z,istek,value);
            AnaMenu(z);
            break;
        case 4:
            AnaMenu(z);
            break;
        default:
            goto dongu;
            break;
    } 
}

void ayarlarDosyasiniDegistirme(struct takimlar u[]){//Ayarlar dosyasındaki verileri güncellemek için kullanılan fonksiyon 
    ayarlarDosyasiniOkuma();
    int istek,degistireleceksayi;
    FILE *dosya=fopen("ayarlar.txt","w");
    dongu:
    printf("\n\t\t\t\t=> Takım sayısını değiştirmek için          --->     1\n");
    printf("\t\t\t\t=> Galibiyet puanını değiştirmek için       --->     2\n");
    printf("\t\t\t\t=> Beraberlik puanını değiştirmek için      --->     3\n");
    printf("\t\t\t\t=> Mağlubiyet puanını değiştirmek için      --->     4\n");
    printf("\t\t\t\t=> Üst menüye gitmek için                   --->     5\n\t\t\t\t=> Tercihiniz : ");
    scanf("%d",&istek);
    
    switch (istek)
    {
        case 1://takım sayısını değiştirmek için
            printf("\t\t\t\tDeğeri giriniz : ");
            scanf("%d",&degistireleceksayi);
            fprintf(dosya,"%d\n%d\n%d\n%d",degistireleceksayi,ayarlar[1],ayarlar[2],ayarlar[3]);//Dosyaya yazdırmamızı sağlayan dosya fonksiyonu
            fclose(dosya);//Açtığımız dosyayı kapatan dosya fonksiyonu
            printf("\t\t\t\tDeğişiklik başarıyla gerçekleşti.\n");
            ayarlarDosyasiniOkuma();
            AnaMenu(u);
            break;
        case 2://galibiyet sayısınnı değiştirmek için
            printf("\t\t\t\tDeğeri giriniz : ");
            scanf("%d",&degistireleceksayi);
            fprintf(dosya,"%d\n%d\n%d\n%d",ayarlar[0],degistireleceksayi,ayarlar[2],ayarlar[3]);
            fclose(dosya);
            printf("\t\t\t\tDeğişiklik başarıyla gerçekleşti.\n");
            ayarlarDosyasiniOkuma();
            AnaMenu(u);
            break;
        case 3://beraberlik sayısını değiştirmek için
            printf("\t\t\t\tDeğeri giriniz : ");
            scanf("%d",&degistireleceksayi);
            fprintf(dosya,"%d\n%d\n%d\n%d",ayarlar[0],ayarlar[1],degistireleceksayi,ayarlar[3]);
            fclose(dosya);
            printf("\t\t\t\tDeğişiklik başarıyla gerçekleşti.\n");
            ayarlarDosyasiniOkuma();
            AnaMenu(u);
            break;
        case 4://mağlubiyet sayısını değiştirmek için
            printf("\t\t\t\tDeğeri giriniz : ");
            scanf("%d",&degistireleceksayi);
            fprintf(dosya,"%d\n%d\n%d\n%d",ayarlar[0],ayarlar[1],ayarlar[2],degistireleceksayi);
            fclose(dosya);
            printf("\t\t\t\tDeğişiklik başarıyla gerçekleşti.\n");
            ayarlarDosyasiniOkuma();
            AnaMenu(u);
            break;
        case 5:
            fclose(dosya);
            AnaMenu(u);
        default:
            goto dongu;
            break;
    } 

}
