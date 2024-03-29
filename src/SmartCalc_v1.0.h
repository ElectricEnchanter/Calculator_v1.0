#ifndef SMARTCALC_V1_0_H_
#define SMARTCALC_V1_0_H_

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

enum operatorPrior { LOW, MID, HIGH, ULTRA };

typedef struct Numbers {
  double number;
  struct Numbers *next;
} Numbers;

typedef struct Operations {
  char Operator;
  struct Operations *next;
} Operations;

int Validator(char *string, char *output);
double Count(char *output, Numbers **NumHead, Operations **OpHead, double X);
void counting(char pop, Numbers **NumHead);
void conditions(Operations **OpHead, Numbers **NumHead, char *output);
int checkPriority(char token);

void pushNum(Numbers **head, double data);
void pushOp(Operations **head, char data);
double popNum(Numbers **head);
char popOp(Operations **head);

int ymd_to_mord(char *data);

#endif
