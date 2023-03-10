#ifndef SMARTCALC_V1_0_H_
#define SMARTCALC_V1_0_H_

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


double loan(double restSum, int month, double stavka, int type);
double loanOverpayment(double monthlyPayment, int month, double stavka, double restSum, int type);
void differential (double stavka, double ostat, double procPer);
void annuity (double stavka, double ostat, double mesProc, double procPer);

#endif
