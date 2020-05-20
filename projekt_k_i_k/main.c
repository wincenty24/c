#include <stdio.h>/// dopisz debil reset
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>////////////// if scanf(imie nr 2 == BOT) grasz z botem
#include "biblioteka.h"
struct struktura
{
    char imie_nr1[20];
    char imie_nr2[20];
    char imie_wygranego[20];
};
struct struktura myk;
FILE *plik_zapis;
//int *wskaznik = &menu;
char *str;
bool kto_teraz_gra=true;// czy jest ruch kolka czy krzyzyka
bool gra_trwa=true;
bool gra_trwa_z_botem=true;
bool gra_bot_czy_ty=true;
bool mozesz_przejsc_dalej=false;/// przydatne przy losowaniu
char kto_zaczyna[20];////// on gra krzyzykiem
char imie_osoby_grajacej_kolkiem[20];

char tablica[]={"123456789"};


char zaczyna_bot_czy_ty[20];
char nazwa_bota[]={"bot"};//// żeby grać z botem to trzeba w drugim imieniu wpiszać "bot"
char remis[20]={"remis"};
char lotto_nazwa[]={"lotto"};
int menu=0;
int random_liczba=0;
int zmienna_poocnicza_random=0;
char czytaj_co_wpisuje[1];
void sprawdzanie_poprawnosci()
{
   if(strcmp( kto_zaczyna, myk.imie_nr1 ) == 0 || strcmp( kto_zaczyna, myk.imie_nr2 ) ==0){

   }else{
    printf("\n");
   printf("To imie nie pasuje do poprzednich imion, popyliles sie wpisz jeszcze raz!");
   abc();
   }
}
void reset()
{
tablica[0]='1';
tablica[1]='2';
tablica[2]='3';
tablica[3]='4';
tablica[4]='5';
tablica[5]='6';
tablica[6]='7';
tablica[7]='8';
tablica[8]='9';
gra_trwa=true;
kto_teraz_gra=true;
gra_trwa_z_botem=true;
gra_bot_czy_ty=true;

}

void abc()
{
reset();

printf("\n");
printf("Kto gra X?");
printf("\n");
scanf("%s", &kto_zaczyna);
sprawdzanie_poprawnosci();
if(strcmp( kto_zaczyna, myk.imie_nr1) == 0 ){/// ta komenda s³uzy do porównania charów
    strcpy( imie_osoby_grajacej_kolkiem, myk.imie_nr2);
}
if(strcmp( kto_zaczyna, myk.imie_nr2) == 0 ){
    strcpy( imie_osoby_grajacej_kolkiem, myk.imie_nr1);
}
if(gra_trwa==true){
    for(;;){
        pokaz_to();
        czytaj_znaki_dla_X();
        if(gra_trwa==false){
            break;
        }
    }
}
if(gra_trwa==false){
    system("cls");
    printf("ta osoba wygrala: %s  Brawo!", myk.imie_wygranego);
}
printf("\n");
printf("jesli chcesz zresetowac gre wybierz  '1' ");
printf("\n");
printf("jesli chcesz zagrac z innym graczem wybierz  '2' ");
printf("\n");
printf("jesli chcesz wylaczyc gre wybierz '3' ");
scanf("%d", &menu);
switch(menu)
{
    case 1:
        abc();
        reset();
        break;
    case 2:
        main();
        reset();
        break;
    case 3:
        return 0;// wylącza caly program
        break;
 }


}

void losowanie_liczb()
{

    int los_x;
    int los_y;
printf("wybierz 2 liczby <1;10>, pamietaj ee liczby nie moge sie powtarzae :D\n");
scanf("\n%d", &los_x);
scanf("\n%d", &los_y);
int x=funkcja_biblioteka1();
int y=funkcja_biblioteka2();
printf("%d\n", x);
printf("%d\n", y);
if(los_x==x && los_y!=y){
    printf("trafizel pierwszą liczbz, ale drugiej juz nie  ");
}
if(los_x!=x && los_y==y){
    printf("trafiles druga liczbe, ale pierwszej juz nie  ");
}
if(los_x!=x && los_y!=y){
    printf("nie trafiles zadnej ");
}
if(los_x==x && los_y==y){
    printf("brawo");
}
 printf("\n");
    printf("jesli chcesz zresetowac gre z botem zwybierz  '1' ");
    printf("\n");
    printf("powrot do menu '2' ");
    printf("\n");
    printf("jesli chcesz wylaczyc gre wybierz '3' ");
    scanf("%d",&menu);
    switch(menu)
    {
    case 1:
        system("cls");
        losowanie_liczb();
        break;
    case 2:
        main();
        system("cls");
        break;
    case 3:
        return 0;
        break;

    }

}


int main()
{

//printf("wpisz imie pierwszego Gracza");
str = (char *) malloc(50);
strcpy(str, "wpisz imie pierwszego Gracza");
printf("\n %s,  Adres = %u", str, str);
printf("\n");
scanf("%s", &(myk.imie_nr1));

/*
//printf("wpisz imie drugiego Gracza");
str = (char *) realloc(str, 51);
strcat(str, "wpisz imie drugiego Gracza");
printf("\n %s,  Adres = %u", str, str);

*/
free(str);
printf("wpisz imie drugiego Gracza");
printf("\n");
scanf("%s", &(myk.imie_nr2));
if(strcmp(nazwa_bota , myk.imie_nr2) == 0 ){
    gra_z_botem();
}
if(strcmp(lotto_nazwa , myk.imie_nr2) == 0 ){
      losowanie_liczb();
}
else{
    abc();
}
}
void pokaz_to()
{
printf("%c   %c   %c", tablica[0],tablica[1],tablica[2]);
printf("\n\n");
printf("%c   %c   %c", tablica[3],tablica[4],tablica[5]);
printf("\n\n");
printf("%c   %c   %c", tablica[6],tablica[7],tablica[8]);
printf("\n\n");
}
void czytaj_znaki_dla_X()
{
    printf("\n");
    if(kto_teraz_gra==true){
         printf("teraz jest kolej X ===> %s", kto_zaczyna);
         //printf("\n");
         //printf("%s", kto_zaczyna);
    }else{
        printf("teraz jest kolej O ===> %s", imie_osoby_grajacej_kolkiem);
        //printf("\n");
        //printf("%s", imie_osoby_grajacej_kolkiem);
    }
    printf("\n");
    scanf("%c",&czytaj_co_wpisuje);
//////////////////////////////////////////////////////////////////// czytaj znaki dla X
if(kto_teraz_gra==true){
    if(tablica[0]!='O'){
        if(czytaj_co_wpisuje[0]=='1'){
            tablica[0]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[1]!='O'){
        if(czytaj_co_wpisuje[0]=='2'){
            tablica[1]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[2]!='O'){
        if(czytaj_co_wpisuje[0]=='3'){
            tablica[2]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[3]!='O'){
        if(czytaj_co_wpisuje[0]=='4'){
            tablica[3]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[4]!='O'){
        if(czytaj_co_wpisuje[0]=='5'){
            tablica[4]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[5]!='O'){
        if(czytaj_co_wpisuje[0]=='6'){
            tablica[5]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[6]!='O'){
        if(czytaj_co_wpisuje[0]=='7'){
            tablica[6]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[7]!='O'){
        if(czytaj_co_wpisuje[0]=='8'){
            tablica[7]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[8]!='O'){
        if(czytaj_co_wpisuje[0]=='9'){
            tablica[8]='X';
            kto_teraz_gra=false;
        }
    }
}
///////////////////////////////////////////////////////////////////////////// czytanie znaku dla O
    if(kto_teraz_gra==false){
        if(tablica[0]!='X'){
            if(czytaj_co_wpisuje[0]=='1'){
            tablica[0]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[1]!='X'){
            if(czytaj_co_wpisuje[0]=='2'){
            tablica[1]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[2]!='X'){
            if(czytaj_co_wpisuje[0]=='3'){
            tablica[2]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[3]!='X'){
            if(czytaj_co_wpisuje[0]=='4'){
            tablica[3]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[4]!='X'){
            if(czytaj_co_wpisuje[0]=='5'){
            tablica[4]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[5]!='X'){
            if(czytaj_co_wpisuje[0]=='6'){
            tablica[5]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[6]!='X'){
            if(czytaj_co_wpisuje[0]=='7'){
            tablica[6]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[7]!='X'){
            if(czytaj_co_wpisuje[0]=='8'){
            tablica[7]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[8]!='X'){
            if(czytaj_co_wpisuje[0]=='9'){
            tablica[8]='O';
            kto_teraz_gra=true;
            }
        }

    }

if((tablica[0]=='O' && tablica[1]=='O' && tablica[2]=='O') || (tablica[3]=='O' && tablica[4]=='O' && tablica[5]=='O') || (tablica[6]=='O' && tablica[7]=='O' && tablica[8]=='O') || (tablica[0]=='O' && tablica[3]=='O' && tablica[6]=='O') || (tablica[1]=='O' && tablica[4]=='O' && tablica[7]=='O') || (tablica[2]=='O' && tablica[5]=='O' && tablica[8]=='O') || (tablica[0]=='O' && tablica[4]=='O' && tablica[8]=='O') || (tablica[2]=='O' && tablica[4]=='O' && tablica[6]=='O')){
    gra_trwa=false;
    //kolko_wygralo=true;
    strcpy( myk.imie_wygranego,  imie_osoby_grajacej_kolkiem);
     plik_zapis=fopen("plik.txt", "a+");
   fprintf (plik_zapis, " \n pojedynek pomiędzy %s a %s wygrywa %s ", myk.imie_nr1 ,myk.imie_nr2,myk.imie_wygranego);
     fclose(plik_zapis);

}
if((tablica[0]=='X' && tablica[1]=='X' && tablica[2]=='X') || (tablica[3]=='X' && tablica[4]=='X' && tablica[5]=='X') || (tablica[6]=='X' && tablica[7]=='X' && tablica[8]=='X') || (tablica[0]=='X' && tablica[3]=='X' && tablica[6]=='X') || (tablica[1]=='X' && tablica[4]=='X' && tablica[7]=='X') || (tablica[2]=='X' && tablica[5]=='X' && tablica[8]=='X') || (tablica[0]=='X' && tablica[4]=='X' && tablica[8]=='X') || (tablica[2]=='X' && tablica[4]=='X' && tablica[6]=='X')){
    gra_trwa=false;
    //krzyzyk_wygral=true;

    strcpy( myk.imie_wygranego,  kto_zaczyna);
      plik_zapis=fopen("plik.txt", "a+");
      fprintf (plik_zapis, " \n pojedynek pomiędzy %s a %s wygrywa %s ", myk.imie_nr1 ,myk.imie_nr2,myk.imie_wygranego);
     fclose(plik_zapis);

}
if( (tablica[0]=='O' || tablica[0]=='X') && (tablica[1]=='O' || tablica[1]=='X') && (tablica[2]=='O' || tablica[2]=='X') && (tablica[3]=='O' || tablica[3]=='X') && (tablica[4]=='O' || tablica[4]=='X') && (tablica[5]=='O' || tablica[5]=='X') && (tablica[6]=='O' || tablica[6]=='X') && (tablica[7]=='O' || tablica[7]=='X') && (tablica[8]=='O' || tablica[8]=='X') )
{
    gra_trwa=false;
    strcpy( myk.imie_wygranego,  remis);
    plik_zapis=fopen("plik.txt", "a+");
            fprintf (plik_zapis, " \n &s pomiedzy %s i %s", myk.imie_wygranego,myk.imie_nr1 ,myk.imie_nr2);
            fclose(plik_zapis);

}
system("cls");

}

void gra_z_botem()
{
    reset();
    printf("wybrales opcje grania z botem powodzeni:D");
    printf("\n");
    printf("kto zaczyna?");
    printf("\n");
    scanf("%s", &zaczyna_bot_czy_ty);
    if(zaczyna_bot_czy_ty=='bot')
    {
        gra_bot_czy_ty=true;/// GRE ZACZYNA BOT
        kto_teraz_gra=true;
    }

    if(strcmp( zaczyna_bot_czy_ty, myk.imie_nr1) == 0)
    {
        gra_bot_czy_ty=false;/// GRE ZACZYNA GRACZ
        kto_teraz_gra=false;
    }

    if(gra_trwa_z_botem==true)
    {
        for(;;){
            gra_z_botem_kod();
            printf("\n");
            printf("%d", zmienna_poocnicza_random);
            printf("\n");
            pokaz_to();
            if(gra_trwa_z_botem==false){
                break;
            }

       // printf("\n%d", random_liczba);
        }
    }
    if(gra_trwa_z_botem==false)
    {
        system("cls");
        printf("ta osoba wygrala: %s   Brawo!", myk.imie_wygranego);
    }
    printf("\n");
    printf("jesli chcesz zresetowac gre botem zwybierz  '1' ");
    printf("\n");
    printf("jesli chcesz zagrac z innym graczem wybierz  '2' ");
    printf("\n");
    printf("jesli chcesz wylaczyc gre wybierz '3' ");
    scanf("%d",&menu);
    switch(menu)
    {
    case 1:
        gra_z_botem();
        break;
    case 2:
        main();
        break;
    case 3:
        return 0;
        break;

    }
}
int losuj_liczbe()
{
    srand((unsigned int)time(NULL));
   return 1+rand() %9;
}
void gra_z_botem_kod()
{

zmienna_poocnicza_random=losuj_liczbe();



if(gra_bot_czy_ty==true){/////////////////////zaczyna grać bot
    if(kto_teraz_gra==true){

    if(tablica[0]!='O' && tablica[0]!='X' && zmienna_poocnicza_random==1){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==1){
            tablica[0]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[0]=='O' && tablica[0]=='X' && zmienna_poocnicza_random==1)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[1]!='O' && tablica[1]!='X' && zmienna_poocnicza_random==2){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==2){
            tablica[1]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[1]=='O' && tablica[1]=='X' && zmienna_poocnicza_random==2)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[2]!='O' && tablica[2]!='X' && zmienna_poocnicza_random ==3){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==3){
            tablica[2]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[2]=='O' && tablica[2]=='X' && zmienna_poocnicza_random==3)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[3]!='O' && tablica[3]!='X' && zmienna_poocnicza_random== 4){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==4){
            tablica[3]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[3]=='O' && tablica[3]=='X' && zmienna_poocnicza_random==4)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[4]!='O' && tablica[4]!='X' && zmienna_poocnicza_random==5){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==5){
            tablica[4]='X';
            kto_teraz_gra=false;
        }
     if(tablica[4]=='O' && tablica[4]=='X' && zmienna_poocnicza_random==5)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    }
    if(tablica[5]!='O' && tablica[5]!='X' && zmienna_poocnicza_random ==6){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==6){
            tablica[5]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[5]=='O' && tablica[5]=='X' && zmienna_poocnicza_random==6)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[6]!='O' && tablica[6]!='X' && zmienna_poocnicza_random==7){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==7){
            tablica[6]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[6]=='O' && tablica[6]=='X' && zmienna_poocnicza_random==7)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[7]!='O' && tablica[7]!='X' && zmienna_poocnicza_random==8){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==8){
            tablica[7]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[7]=='O' && tablica[7]=='X' && zmienna_poocnicza_random==8)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[8]!='O' && tablica[8]!='X' && zmienna_poocnicza_random==9){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==9){
            tablica[8]='X';
            kto_teraz_gra=false;
        }
    }
    if(tablica[8]=='O' && tablica[8]=='X' && zmienna_poocnicza_random==9)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    }



    if(kto_teraz_gra==false){
        printf("\n");
        printf("teraz jest kolej O ===> %s", myk.imie_nr1);
        printf("\n");
        scanf("%c",&czytaj_co_wpisuje);
        if(tablica[0]!='X'){
            if(czytaj_co_wpisuje[0]=='1'){
            tablica[0]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[1]!='X'){
            if(czytaj_co_wpisuje[0]=='2'){
            tablica[1]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[2]!='X'){
            if(czytaj_co_wpisuje[0]=='3'){
            tablica[2]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[3]!='X'){
            if(czytaj_co_wpisuje[0]=='4'){
            tablica[3]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[4]!='X'){
            if(czytaj_co_wpisuje[0]=='5'){
            tablica[4]='0';
            kto_teraz_gra=true;
            }
        }
        if(tablica[5]!='X'){
            if(czytaj_co_wpisuje[0]=='6'){
            tablica[5]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[6]!='X'){
            if(czytaj_co_wpisuje[0]=='7'){
            tablica[6]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[7]!='X'){
            if(czytaj_co_wpisuje[0]=='8'){
            tablica[7]='O';
            kto_teraz_gra=true;
            }
        }
        if(tablica[8]!='X'){
            if(czytaj_co_wpisuje[0]=='9'){
            tablica[8]='O';
            kto_teraz_gra=true;
            }
        }

    }
}

if(gra_bot_czy_ty==false)
{
if(kto_teraz_gra==true){
    if(tablica[0]!='O' && tablica[0]!='X' && zmienna_poocnicza_random==1){
        if(random_liczba==1){
            tablica[0]='O';
            kto_teraz_gra=false;
        }
    }
    if(tablica[0]=='O' && tablica[0]=='X' && zmienna_poocnicza_random==1)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[1]!='O' && tablica[1]!='X' && zmienna_poocnicza_random==2){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==2){
            tablica[1]='O';
            kto_teraz_gra=false;
        }
    }
    if(tablica[1]=='O' && tablica[1]=='X' && zmienna_poocnicza_random==2)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[2]!='O' && tablica[2]!='X' && zmienna_poocnicza_random ==3){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==3){
            tablica[2]='O';
            kto_teraz_gra=false;
        }
    }
    if(tablica[2]=='O' && tablica[2]=='X' && zmienna_poocnicza_random==3)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[3]!='O' && tablica[3]!='X' && zmienna_poocnicza_random== 4){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==4){
            tablica[3]='O';
            kto_teraz_gra=false;
        }
    }
    if(tablica[3]=='O' && tablica[3]=='X' && zmienna_poocnicza_random==4)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[4]!='O' && tablica[4]!='X' && zmienna_poocnicza_random==5){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==5){
            tablica[4]='O';
            kto_teraz_gra=false;
        }
     if(tablica[4]=='O' && tablica[4]=='X' && zmienna_poocnicza_random==5)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    }
    if(tablica[5]!='O' && tablica[5]!='X' && zmienna_poocnicza_random ==6){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==6){
            tablica[5]='O';
            kto_teraz_gra=false;
        }
    }
    if(tablica[5]=='O' && tablica[5]=='X' && zmienna_poocnicza_random==6)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[6]!='O' && tablica[6]!='X' && zmienna_poocnicza_random==7){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==7){
            tablica[6]='O';
            kto_teraz_gra=false;
        }
    }
    if(tablica[6]=='O' && tablica[6]=='X' && zmienna_poocnicza_random==7)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[7]!='O' && tablica[7]!='X' && zmienna_poocnicza_random==8){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==8){
            tablica[7]='O';
            kto_teraz_gra=false;
        }
    }
    if(tablica[7]=='O' && tablica[7]=='X' && zmienna_poocnicza_random==8)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    if(tablica[8]!='O' && tablica[8]!='X' && zmienna_poocnicza_random==9){
        random_liczba=zmienna_poocnicza_random;
        if(random_liczba==9){
            tablica[8]='O';
            kto_teraz_gra=false;
        }
    }
    if(tablica[8]=='O' && tablica[8]=='X' && zmienna_poocnicza_random==9)
        {
            zmienna_poocnicza_random=losuj_liczbe();
     }
    }



    if(kto_teraz_gra==false){
        printf("\n");
        printf("teraz jest kolej O ===> %s", myk.imie_nr1);
        printf("\n");
        scanf("%c",&czytaj_co_wpisuje);
        if(tablica[0]!='0'){
            if(czytaj_co_wpisuje[0]=='1'){
            tablica[0]='X';
            kto_teraz_gra=true;
            }
        }
        if(tablica[1]!='O'){
            if(czytaj_co_wpisuje[0]=='2'){
            tablica[1]='X';
            kto_teraz_gra=true;
            }
        }
        if(tablica[2]!='0'){
            if(czytaj_co_wpisuje[0]=='3'){
            tablica[2]='X';
            kto_teraz_gra=true;
            }
        }
        if(tablica[3]!='0'){
            if(czytaj_co_wpisuje[0]=='4'){
            tablica[3]='X';
            kto_teraz_gra=true;
            }
        }
        if(tablica[4]!='O'){
            if(czytaj_co_wpisuje[0]=='5'){
            tablica[4]='X';
            kto_teraz_gra=true;
            }
        }
        if(tablica[5]!='O'){
            if(czytaj_co_wpisuje[0]=='6'){
            tablica[5]='X';
            kto_teraz_gra=true;
            }
        }
        if(tablica[6]!='O'){
            if(czytaj_co_wpisuje[0]=='7'){
            tablica[6]='X';
            kto_teraz_gra=true;
            }
        }
        if(tablica[7]!='O'){
            if(czytaj_co_wpisuje[0]=='8'){
            tablica[7]='X';
            kto_teraz_gra=true;
            }
        }
        if(tablica[8]!='O'){
            if(czytaj_co_wpisuje[0]=='9'){
            tablica[8]='X';
            kto_teraz_gra=true;
            }
        }

    }

}



    if((tablica[0]=='O' && tablica[1]=='O' && tablica[2]=='O') || (tablica[3]=='O' && tablica[4]=='O' && tablica[5]=='O') || (tablica[6]=='O' && tablica[7]=='O' && tablica[8]=='O') || (tablica[0]=='O' && tablica[3]=='O' && tablica[6]=='O') || (tablica[1]=='O' && tablica[4]=='O' && tablica[7]=='O') || (tablica[2]=='O' && tablica[5]=='O' && tablica[8]=='O') || (tablica[0]=='O' && tablica[4]=='O' && tablica[8]=='O') || (tablica[2]=='O' && tablica[4]=='O' && tablica[6]=='O')){
        gra_trwa_z_botem=false;
        if(gra_bot_czy_ty==true)
        {
            strcpy( myk.imie_wygranego,  myk.imie_nr1);
        }
        if(gra_bot_czy_ty==false)
        {
             strcpy( myk.imie_wygranego, nazwa_bota);
        }
    }
    if((tablica[0]=='X' && tablica[1]=='X' && tablica[2]=='X') || (tablica[3]=='X' && tablica[4]=='X' && tablica[5]=='X') || (tablica[6]=='X' && tablica[7]=='X' && tablica[8]=='X') || (tablica[0]=='X' && tablica[3]=='X' && tablica[6]=='X') || (tablica[1]=='X' && tablica[4]=='X' && tablica[7]=='X') || (tablica[2]=='X' && tablica[5]=='X' && tablica[8]=='X') || (tablica[0]=='X' && tablica[4]=='X' && tablica[8]=='X') || (tablica[2]=='X' && tablica[4]=='X' && tablica[6]=='X')){
        gra_trwa_z_botem=false;
        if(gra_bot_czy_ty==false){
            strcpy( myk.imie_wygranego,  myk.imie_nr1);
             plik_zapis=fopen("plik.txt", "a+");
            fprintf (plik_zapis, " \n pojedynek pomiędzy %s a %s wygrywa %s ", myk.imie_nr1 ,nazwa_bota,myk.imie_wygranego);
            fclose(plik_zapis);
        }
        if(gra_bot_czy_ty==true)
        {
             strcpy( myk.imie_wygranego, nazwa_bota);
             plik_zapis=fopen("plik.txt", "a+");
            fprintf (plik_zapis, " \n pojedynek pomiędzy %s a %s wygrywa %s ", myk.imie_nr1 ,nazwa_bota,myk.imie_wygranego);
            fclose(plik_zapis);
        }


    }

    if( (tablica[0]=='O' || tablica[0]=='X') && (tablica[1]=='O' || tablica[1]=='X') && (tablica[2]=='O' || tablica[2]=='X') && (tablica[3]=='O' || tablica[3]=='X') && (tablica[4]=='O' || tablica[4]=='X') && (tablica[5]=='O' || tablica[5]=='X') && (tablica[6]=='O' || tablica[6]=='X') && (tablica[7]=='O' || tablica[7]=='X') && (tablica[8]=='O' || tablica[8]=='X') )
{
    gra_trwa_z_botem=false;
    strcpy( myk.imie_wygranego, remis);

    plik_zapis=fopen("plik.txt", "a+");
            fprintf (plik_zapis, " \n %s pomiedzy %s i %s", remis,myk.imie_nr1 ,nazwa_bota);
            fclose(plik_zapis);
}

system("cls");
}

