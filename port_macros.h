/*
 * Duc Ngo
 */

#ifndef PORT_MACROS_H
#define PORT_MACROS_H

#define CONCAT(A,B) A##B
#define CONCAT3(A,B,C) A##B##C
#define PORT(LETTER) CONCAT(PORT,LETTER)
#define DDR(LETTER) CONCAT(DDR,LETTER)
#define PIN(LETTER) CONCAT(PIN,LETTER)
#define TOGGLE(LETTER) CONCAT(PIN,LETTER)
#define PULLUP(LETTER) CONCAT(PORT,LETTER)
#define TCCRA(NUM) CONCAT3(TCCR,NUM,A)
#define TCCRB(NUM) CONCAT3(TCCR,NUM,B)
#define OCRA(NUM) CONCAT3(OCR,NUM,A)
#define OCRB(NUM) CONCAT3(OCR,NUM,B)


#endif