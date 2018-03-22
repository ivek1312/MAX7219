/* naložimo knjižnico s funkcijami */
#include "LedZaslon.h"

/* čas čakanja preden se izvede naslednja vrstica */
#define casCakanja 100 /* 1000 je ena sekunda, čas je v milisekundah */

#define DIN 12 /*DIN z zaslona povežemo na pin 12 arduina */
#define CS  11 /*CS  z zaslona povežemo na pin 11 arduina */
#define CLK 10 /*CLK z zaslona povežemo na pin 10 arduina */

#define CHIP_POZICIJA LEVO /* možnosti so: LEVO, ZGORAJ, DESNO, SPODAJ */
#define SVETLINA_ZASLONA 0  /* od 0 do 15 */

/* inicializacija, izvede se samo enkrat */
void setup() {
  inicializacija(DIN, CS, CLK, CHIP_POZICIJA, SVETLINA_ZASLONA);
}

/* koda, ki se ponavlja zanki (ang. loop) */
void loop() {
  prizgiLucko(0,0);
  pavza(casCakanja);
  ugasniLucko(0,0);
  pavza(casCakanja);  
test();
}




/* 
 Priziga lucke po vrsticah. Ko je vrstica polna
 gre v naslednjo vrstico
 */
void test() {
  while (true) {
    for(int vrstica=0;vrstica<8;vrstica++) {
      for(int stolpec=0;stolpec<8;stolpec++) {
        delay(casCakanja);
        nastaviLucko(vrstica,stolpec,true);
        delay(casCakanja);
      }
    }
    if (rotacija==SPODAJ)
      rotacija=LEVO;
    else rotacija++;
    pobrisiZaslon();
  }
}

void nal1() {
//1) Prižgi 1 lučko - s to nalogo pokažemo kaj je/kako se rabi funkcija prizgiLucko()
  prizgiLucko(0, 0);
}

void nal2() {
//2) Prižgi zadnjo lučko - rešijo sami
  prizgiLucko(7, 7);
}

void nal3() {
//3) Prižgi 3 lučke po svoji izbiri - rešijo sami
  prizgiLucko(0,0);
  prizgiLucko(1,1);
  prizgiLucko(2,2);
}

void nal4() {
//4) Prižgi poljubno lučko, počakaj 1 sekundo, ugasni to lučko ter spet počakaj 1 sekundo.
  prizgiLucko(0,0);
  pavza(casCakanja);
  ugasniLucko(0,0);
  pavza(casCakanja);
}

//PODATKOVNI TIPI
//INT
void nal5() {
//5) Prižgi drugo lučko z uporabo 2 spremenljivk - prvo pokažemo deklaracijo int spremenljivke, nato rešijo nalogo
  int x = 0;
  int y = 1;
  prizgiLucko(x, y);
}

void nal6() {
//6) Dodelaj prejšnjo nalogo tako, da ustvariš 2 novi spremenljivki. Prva je za 1 večja od spremenljivke x, druga pa za 2 večja od spremenljivke y.
//Nato prižgi novo lučko s tema dvema novima spremenljivkoma.
  int x = 0;
  int y = 1;
  int a = 4;
  int b = 7;
  prizgiLucko(x, y);
  prizgiLucko(a, b);
}

//BOOL
void nal7() {
//7) Prižgi 1 lučko z uporabo 3 spremenljivk - prvo pokažemo deklaracijo bool spremenljivke, nato rešijo nalogo
  int x = 0;
  int y = 1;
  bool sveti = true;
  nastaviLucko(x, y, sveti);
}

void nal8() {
//8) Prižgi 1 lučko, počakaj 1 sekundo, ugasni to lučko ter počakaj 1 sekundo - pokažemo funkcijo pavza(), nato rešijo nalogo
  bool sveti = true;
  nastaviLucko(0, 0, sveti);
  pavza(1000);
  sveti = false;
  nastaviLucko(0, 0, sveti);
  pavza(1000);
  
}

//IF-ELSE STAVEK
void nal9() {
//9) Če je prva lučka ugasnjena, jo prižgi. - pokažemo strukturo if stavka
  if (jeLuckaUgasnjena(0,0)){
    prizgiLucko(0,0);
  }  
}

void nal10() {
//10) Prižgi drugo lučko. Če je druga lučka prižgana, prižgi zadnjo lučko v zadnji vrstici.
  prizgiLucko(0,1);
  if (jeLuckaPrizgana(0,1)){
    prizgiLucko(7,7);
  }
}

void nal11() {
//11) Če je prva lučka prižgana, jo ugasni, drugače jo prižgi. Na koncu počakaj 1 sekundo. - pokažemo strukturo if-else stavka, rešijo sami
  if (jeLuckaPrizgana(0,0)){
    ugasniLucko(0,0);
  }
  else {
    prizgiLucko(0,0);
  }
  pavza(1000);
}

void nal12() {
//12) Če je prva lučka prižgana in je druga lučka ugasnjena, prižgi drugo lučko. Drugače prižgi prvo lučko. - razložimo zakaj sta obe prižgani (najprej se izvede else, potem if)
  if (jeLuckaPrizgana(0,0) && jeLuckaUgasnjena(0,1)){
    prizgiLucko(0,1);
  }
  else{
    prizgiLucko(0,0);
  }  
}

//WHILE ZANKA
void nal13() {
//13) Prižgi vse lučke v prvi vrstici - najprej na 1. način, potem na drugi; pokažemo strukturo for zanke, jo napišemo na tablo in skupaj rešimo nalogo
  prizgiLucko(0, 0);
  pavza(1000);
  prizgiLucko(0, 1);
  pavza(1000);
  prizgiLucko(0, 2);
  pavza(1000);
  prizgiLucko(0, 3);
  pavza(1000);
  prizgiLucko(0, 4);
  pavza(1000);
  prizgiLucko(0, 5);
  pavza(1000);
  prizgiLucko(0, 6);
  pavza(1000);
  prizgiLucko(0, 7);
  pavza(1000);
  pobrisiZaslon();
}

void nal13a() {
  //2. način
  int stevec = 0;
  while (stevec < 8){
    prizgiLucko(0,stevec);
    stevec = stevec+1;
    pavza(1000);
  }
}

void nal14() {
//14) Prižgi vse lučke v prvem stolpcu - rešijo sami
  int stevec = 0;
  while (stevec < 8){
    prizgiLucko(stevec,0);
    stevec = stevec+1;
    pavza(1000);
  }
}

void nal15() {
//15) Prižgi 2., 3., 4. in 5. lučko v prvi vrstici - rešijo sami
  int stevec = 2;
  while (stevec < 6){
    prizgiLucko(0,stevec);
    stevec = stevec+1;
    pavza(1000);
  }
}

void nal16() {
//16) Prižgi vsako drugo lučko v prvi vrstici - rešijo sami  
  int stevec = 0;
  while (stevec < 8){
    prizgiLucko(0,stevec);
    stevec = stevec+2;
    pavza(1000);
  }  
}

void nal17() {
//17) Prižgi vse lučke v prvi vrstici in prvem stolpcu - rešijo sami
  int stevec = 0;
  while (stevec < 8){
    prizgiLucko(0,stevec);
    stevec = stevec+1;
    pavza(1000);
  }
  stevec = 0;
  while (stevec < 8){
    prizgiLucko(stevec,0);
    stevec = stevec+1;
    pavza(1000);
  }
}

void nal18() {
//18) Prižgi lučke po diagonali od prve do zadnje - rešimo skupaj (mogoče od konca nazaj? ("kaj dobimo, če napišemo (stevec,stevec)?"))
  int stevec;
  while (stevec < 8){
    prizgiLucko(stevec,stevec);
    stevec = stevec+1;
    pavza(1000);
  }  
}

//TABELA
//Obrazložimo kaj je tabela in strukturo tabele:
//Tabela je kot seznam, v katerem hranimo podatke. Posamezen podatek dobimo s številko, ki pove kateri po vrsti je ta podatek v tabeli.
//  (narišemo na tablo tabelo, dodamo številke kot elemente, napišemo indekse)
//Važno je le vedeti, da morajo biti vsi podatki iste vrste - ali število, ali logična vrednost,...
//Tabelo bomo sedaj potrebovali, da si shranimo katere lučke v vrstici bodo prižgane, in katere ugasnjene.

void nal19() {
//19) Prižgi črko 'a' - kaj pomeni npr. 'B00111000' (povemo zgolj to, da se prižgejo 3., 4. in 5. lučka, ostale so zaprte) in skupaj rešimo nalogo. Nato povežemo z while zanko.
  byte tabela[8]={
    B00000000,
    B00111000,
    B01000100,
    B01000100,
    B01111100,
    B01000100,
    B01000100,
    B00000000};
  prizgiVrstico(0, tabela[0]);
  prizgiVrstico(1, tabela[1]);
  prizgiVrstico(2, tabela[2]);
  prizgiVrstico(3, tabela[3]);
  prizgiVrstico(4, tabela[4]);
  prizgiVrstico(5, tabela[5]);
  prizgiVrstico(6, tabela[6]);
  prizgiVrstico(7, tabela[7]);
}
void nal19a() {
  byte tabela[8]={
    B00000000,
    B00111000,
    B01000100,
    B01000100,
    B01111100,
    B01000100,
    B01000100,
    B00000000};
  int stevec = 0;
  while (stevec < 8){
    prizgiVrstico(stevec, tabela[stevec]);
    stevec = stevec+1;
  }
}
void nal20() {
//20) Prižgi kvadrat - rešimo skupaj
  byte tabela[8]={
    B00000000,
    B01111110,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01111110,
    B00000000};
  prizgiVrstico(0, tabela[0]);
  prizgiVrstico(1, tabela[1]);
  prizgiVrstico(2, tabela[2]);
  prizgiVrstico(3, tabela[3]);
  prizgiVrstico(4, tabela[4]);
  prizgiVrstico(5, tabela[5]);
  prizgiVrstico(6, tabela[6]);
  prizgiVrstico(7, tabela[7]);
}

void nal21() {
//21) Prižgi trikotnik - rešimo skupaj
  byte tabela[8]={
    B00000001,
    B00000011,
    B00000101,
    B00001001,
    B00010001,
    B00100001,
    B01000001,
    B11111111};
  prizgiVrstico(0, tabela[0]);
  prizgiVrstico(1, tabela[1]);
  prizgiVrstico(2, tabela[2]);
  prizgiVrstico(3, tabela[3]);
  prizgiVrstico(4, tabela[4]);
  prizgiVrstico(5, tabela[5]);
  prizgiVrstico(6, tabela[6]);
  prizgiVrstico(7, tabela[7]);
}

void nal22() {
//22) Prižgi krog - rešimo skupaj
  byte tabela[8]={
    B00000000,
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B00100100,
    B00011000,
    B00000000};
  prizgiVrstico(0, tabela[0]);
  prizgiVrstico(1, tabela[1]);
  prizgiVrstico(2, tabela[2]);
  prizgiVrstico(3, tabela[3]);
  prizgiVrstico(4, tabela[4]);
  prizgiVrstico(5, tabela[5]);
  prizgiVrstico(6, tabela[6]);
  prizgiVrstico(7, tabela[7]);
}

void nal23() {
//23) Prižgi srce - rešimo skupaj
  byte tabela[8]={
    B00000000,
    B00100100,
    B01011010,
    B01000010,
    B01000010,
    B00100100,
    B00011000,
    B00000000};
  prizgiVrstico(0, tabela[0]);
  prizgiVrstico(1, tabela[1]);
  prizgiVrstico(2, tabela[2]);
  prizgiVrstico(3, tabela[3]);
  prizgiVrstico(4, tabela[4]);
  prizgiVrstico(5, tabela[5]);
  prizgiVrstico(6, tabela[6]);
  prizgiVrstico(7, tabela[7]);
}

void nal24() {
//24) Prižgi napis 'nona' - jim damo črke, dopolnijo sami
  byte n[8]={
    B00000000,
    B01000010,
    B01100010,
    B01010010,
    B01001010,
    B01000110,
    B01000010,
    B00000000};
  byte o[8]={
    B00000000,
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B00100100,
    B00011000,
    B00000000};
  byte a[8]={
    B00000000,
    B00111000,
    B01000100,
    B01000100,
    B01111100,
    B01000100,
    B01000100,
    B00000000};
  
  int stevec = 0;
  while (stevec < 8){
    prizgiVrstico(stevec, n[stevec]);
    stevec = stevec+1;
  }
  
  pavza(1000);
  pobrisiZaslon();
  
  stevec = 0;
  while (stevec < 8){
    prizgiVrstico(stevec, o[stevec]);
    stevec = stevec+1;
  }
  
  pavza(1000);
  pobrisiZaslon();
  
  stevec = 0;
  while (stevec < 8){
    prizgiVrstico(stevec, n[stevec]);
    stevec = stevec+1;
  }
  
  pavza(1000);
  pobrisiZaslon();
  
  stevec = 0;
  while (stevec < 8){
    prizgiVrstico(stevec, a[stevec]);
    stevec = stevec+1;
  }
  pavza(1000);
  pobrisiZaslon();
}
//DODATNE NALOGE
//-izpiše svoje ime
//-izpiše poljuben text
//-izriše poljuben lik
//-po lastnih željah
  

//void loop() {
////  nal24();
//  test();
////  pobrisiZaslon();
//}




