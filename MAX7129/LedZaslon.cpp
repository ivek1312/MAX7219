
#include "LedZaslon.h"

//ukazi za MAX7219
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

byte stanje[8];
byte SPI_CS;
byte SPI_CLK;
byte SPI_MOSI;
byte rotacija;

void inicializacija(byte DIN, byte CS, byte CLK, byte _rotacija, byte svetlina) {   

    SPI_MOSI=DIN;
    SPI_CS=CS;
    SPI_CLK=CLK;

    pinMode(SPI_MOSI,OUTPUT);
    pinMode(SPI_CLK,OUTPUT);
    pinMode(SPI_CS,OUTPUT);
    digitalWrite(SPI_CS,HIGH);

    rotacija = _rotacija;
    
    poslji(OP_DISPLAYTEST,0);
    poslji(OP_SCANLIMIT,7);
    poslji(OP_DECODEMODE,0);
    pobrisiZaslon();

    if(svetlina>=0 && svetlina<16) 
        poslji( OP_INTENSITY,svetlina);
    
    poslji(OP_SHUTDOWN,1);        
}

void pobrisiZaslon() {
    for(int i=0;i<8;i++) {
        stanje[i]=0;
        poslji(i+1,stanje[i]);
    }
}


void nastaviLucko(byte vrstica, byte stolpec, boolean vklopi) {
    
    if(vrstica<0 || vrstica>7 || stolpec<0 || stolpec>7)
        return;
    
    if (rotacija == LEVO) {
        // MAX7219 je levo
        bitWrite(stanje[vrstica], 7-stolpec, vklopi);
        poslji(vrstica+1,stanje[vrstica]);
    }
    else if (rotacija == ZGORAJ) {
        // MAX7219 je zgoraj    
        bitWrite(stanje[stolpec], 7-vrstica, vklopi);
        poslji(8-stolpec,stanje[stolpec]);
    }
    else if (rotacija == DESNO) {
        // MAX7219 je desno
        bitWrite(stanje[7-vrstica], stolpec, vklopi);
        poslji(8-vrstica,stanje[7-vrstica]);
    }
    else if (rotacija == SPODAJ) {
        // MAX7219 je spodaj    
        bitWrite(stanje[stolpec], vrstica, vklopi);
        poslji(stolpec+1,stanje[stolpec]);
    }

}

void prizgiLucko (byte vrstica, byte stolpec) {
    nastaviLucko(vrstica,stolpec, true);
}

void ugasniLucko (byte vrstica, byte stolpec) {
    nastaviLucko(vrstica,stolpec, false);
}

boolean jeLuckaPrizgana (byte vrstica, byte stolpec) {
    if(vrstica<0 || vrstica>7 || stolpec<0 || stolpec>7)
        return false;

    
    if (rotacija == LEVO)
        // MAX7219 je levo
        return bitRead(stanje[vrstica], 7-stolpec);
    else if (rotacija == ZGORAJ)
        // MAX7219 je zgoraj    
        return bitRead(stanje[stolpec], 7-vrstica);
    else if (rotacija == DESNO)
        // MAX7219 je desno
        return bitRead(stanje[7-vrstica], stolpec);
    else if (rotacija == SPODAJ)
        // MAX7219 je spodaj    
        return bitRead(stanje[stolpec], vrstica);
    return false;
}

boolean jeLuckaUgasnjena (byte vrstica, byte stolpec) {
    return !(jeLuckaPrizgana(vrstica, stolpec));
}

void prizgiVrstico (byte vrstica, byte vrednost) {
    for(int i=0;i<8;i++)
        nastaviLucko(vrstica, i, bitRead(vrednost, 7-i));
}

void prizgiStolpec (byte stolpec, byte vrednost) {
    for(int i=0;i<8;i++)
        nastaviLucko(i, stolpec, bitRead(vrednost, 7-i));
}

void invertiraj () {
    for(int i=0;i<8;i++) {
        stanje[i] = ~stanje[i];
        poslji(i+1,stanje[i]);
    }
}

//nastavi cel zaslon, index tabele je vrstica, vrednost je vrednost byta 
//ker je c imamo samo pointer namest tabele, zato moramo podati tudi dolzino, oz st. vrstic
void nastaviZaslon(byte vrednost[], byte st_vrstic) {
    for(int i=0;i<st_vrstic; i++) {
        prizgiVrstico(i,vrednost[i]); 
    }
}


void pavza(int cas){
	delay(cas);
}

void poslji(volatile byte ukaz, volatile byte podatki) {
    digitalWrite(SPI_CS,LOW);
    
    shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,ukaz);
    shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,podatki);
    
    digitalWrite(SPI_CS,HIGH);
}    


