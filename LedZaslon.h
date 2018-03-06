

#ifndef LedZaslon_h
#define LedZaslon_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define LEVO 0 //MAX7219 je levo od zaslona
#define ZGORAJ 1 //MAX7219 je zgoraj zaslona, tako valentin hoce :P
#define DESNO 2  //MAX7219 je desno od zaslona
#define SPODAJ 3 //MAX7219 je spodaj zaslona

extern byte stanje[8]; //en zaslon je 8 bytov, shranjujejo trenutno stanje

extern byte SPI_CS;
extern byte SPI_CLK;
extern byte SPI_MOSI;

extern byte rotacija;

void poslji(byte opcode, byte data);
void inicializacija(byte SPI_CS, byte SPI_CLK, byte SPI_MOSI, byte rotacija, byte svetlina);
void pobrisiZaslon();
void pavza(int cas);
void nastaviLucko(byte vrstica, byte stolpec, boolean vklopi);
void prizgiLucko(byte vrstica, byte stolpec);
void ugasniLucko(byte vrstica, byte stolpec);
boolean jeLuckaPrizgana (byte vrstica, byte stolpec);
boolean jeLuckaUgasnjena (byte vrstica, byte stolpec);
void prizgiVrstico (byte vrstica, byte vrednost);
void prizgiStolpec (byte vrstica, byte vrednost);
void invertiraj();
void nastaviZaslon(byte vrednost[], byte st_vrstic);


#endif	//LedZaslon.h



