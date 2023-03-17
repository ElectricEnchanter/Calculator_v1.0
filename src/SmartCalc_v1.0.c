#include "SmartCalc_v1.0.h"

double Count(char *output, Numbers **NumHead, Operations **OpHead, double X) {
  char pop, *end, num[256] = {};
  int minus = 0;
  while (*output) {
    if (*output == ' ') {
      output++;
      continue;
    }
    if (isdigit(*output) == 1 || *output == 'x' || *output == '.' ||
        *output == '~') {
      if (*output == '~') {
        minus++;
        output++;
      }
      if (*output == 'x') {
        sprintf(num, "%.7f", X);
      }
      while (isdigit(*output) == 1 || *output == '.') {
        strncat(num, output, 1);
        output++;
      }
      if (minus == 1) {
        pushNum(NumHead, -strtold(num, &end));
        minus = 0;
      } else
        pushNum(NumHead, strtold(num, &end));
      memset(num, 0, 100);
    }
    switch (*output) {
      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
      case '^':
      case 's':
      case 'c':
      case 't':
      case 'o':
      case 'i':
      case 'a':
      case 'q':
      case 'n':
      case 'l':
        if (*OpHead == NULL)
          pushOp(OpHead, *output);
        else
          conditions(OpHead, NumHead, output);
        break;
      case '(':
        pushOp(OpHead, *output);
        break;
      case ')':
        pop = popOp(OpHead);
        while (pop != '(') {
          counting(pop, NumHead);
          pop = popOp(OpHead);
        }
        break;
    }
    output++;
  }
  while ((*OpHead) != NULL) {
    pop = popOp(OpHead);
    counting(pop, NumHead);
  }
  double number = popNum(NumHead);
  return number;
}

void conditions(Operations **OpHead, Numbers **NumHead, char *output) {
  char pop = popOp(OpHead);
  if (checkPriority(pop) > checkPriority(*output) ||
      checkPriority(pop) == checkPriority(*output)) {
    pushOp(OpHead, *output), counting(pop, NumHead);
  } else {
    pushOp(OpHead, pop);
    pushOp(OpHead, *output);
  }
}

void counting(char pop, Numbers **NumHead) {
  double num = 0;
  double num2 = 0;
  if (pop == 's') pushNum(NumHead, sin(popNum(NumHead)));
  if (pop == 'c') pushNum(NumHead, cos(popNum(NumHead)));
  if (pop == 't') pushNum(NumHead, tan(popNum(NumHead)));
  if (pop == 'o') pushNum(NumHead, acos(popNum(NumHead)));
  if (pop == 'i') pushNum(NumHead, asin(popNum(NumHead)));
  if (pop == 'a') pushNum(NumHead, atan(popNum(NumHead)));
  if (pop == 'q') pushNum(NumHead, sqrt(popNum(NumHead)));
  if (pop == 'n') pushNum(NumHead, log(popNum(NumHead)));
  if (pop == 'l') pushNum(NumHead, log10(popNum(NumHead)));
  if (pop == '+') pushNum(NumHead, popNum(NumHead) + popNum(NumHead));
  if (pop == '-') {
    num = popNum(NumHead);
    num2 = popNum(NumHead);
    pushNum(NumHead, num2 - num);
  }
  if (pop == '*') pushNum(NumHead, popNum(NumHead) * popNum(NumHead));
  if (pop == '/') {
    num = popNum(NumHead);
    pushNum(NumHead, popNum(NumHead) / num);
  }
  if (pop == '%') {
    num = popNum(NumHead);
    num2 = popNum(NumHead);
    pushNum(NumHead, fmodl(num2, num));
  }
  if (pop == '^') {
    num = popNum(NumHead);
    pushNum(NumHead, pow(popNum(NumHead), num));
  }
}

int Validator(char *string, char *output) {
  int err = 0, DotFlag = 0, open = 0, close = 0;

  if (*string == '-') {
    strncat(output, "~", 1);
    string++;
  }
  if (*string == '+') {
    strncat(output, " ", 1);
    string++;
  }
  while (*string) {
    while (isdigit(*string) || *string == '.') {
      if (*string == '\0') break;
      if (isdigit(*string))
        strncat(output, string, 1);
      else if (*string == '.') {
        if (DotFlag > 1) {
          err = 1;
          break;
        } else {
          strncat(output, string, 1);
          DotFlag++;
        }
      }
      if (DotFlag > 1) err = 1;
      string++;
    }

    while (!isdigit(*string)) {
      strncat(output, " ", 1);
      DotFlag = 0;
      if (*string == '\0') break;
      switch (*string) {
        case 'x':
          strncat(output, "x", 1);
          break;
        case 'a':
          string++;
          if (*string == 'c')
            strncat(output, "o", 1);
          else if (*string == 's')
            strncat(output, "i", 1);
          else if (*string == 't')
            strncat(output, "a", 1);
          string += 2;
          break;
        case 'l':
          string++;
          if (*string == 'o') {
            strncat(output, "l", 1);
            string++;
          } else if (*string == 'n')
            strncat(output, "n", 1);
          break;
        case 's':
          string++;
          if (*string == 'i') {
            strncat(output, "s", 1);
            string++;
          } else if (*string == 'q') {
            strncat(output, "q", 1);
            string += 2;
          }
          break;
        case 'c':
          string++;
          if (*string == 'o') {
            strncat(output, "c", 1);
            string++;
          }
          break;
        case 't':
          string++;
          if (*string == 'a') {
            strncat(output, "t", 1);
            string++;
          }
          break;
        case '+':
          string--;
          if (*string == '(') {
            strncat(output, " ", 1);
            string++;
          } else if (*string == '+' || *string == '-' || *string == '*' ||
                     *string == '/' || *string == '%')
            err = 4;
          else {
            strncat(output, "+", 1);
            string++;
          }
          string++;
          if (*string == '+' || *string == '-' || *string == '*' ||
              *string == '/' || *string == '%' || *string == '\0') {
            err = 4;
          }
          string--;
          break;
        case '-':
          string--;
          if (*string == '+' || *string == '-' || *string == '*' ||
              *string == '/' || *string == '%')
            err = 4;
          else if (*string == '(') {
            strncat(output, "~", 1);
          } else
            strncat(output, "-", 1);
          string++;

          break;
        case '*':
        case '/':
        case '%':
        case '^':
          string++;
          if (*string == '\0') {
            err = 4;
          } else if (*string == '+' || *string == '-' || *string == '*' ||
                     *string == '/' || *string == '%')
            err = 4;
          else if (*string == '(')
            string--;
          else
            string--;
          strncat(output, string, 1);
          break;
        case '(':
          string--;
          if (isdigit(*string) == 1) {
            strncat(output, "* ", 2);
            string++;
          } else
            string++;
          strncat(output, "(", 1);
          open++;
          string++;
          if (*string == '+' || *string == '*' || *string == '^' ||
              *string == '/' || *string == '%' || *string == '.')
            err = 6;
          string--;
          break;
        case ')':
          string--;
          if (*string == '(') err = 3;
          string++;
          if (*string == ')') {
            strncat(output, ")", 1);
            close++;
          }
          if (*string == '\0') break;
          break;
      }
      string++;
      if (err != 0) break;
    }
  }
  if (open != close)
    err = 2;
  else {
    int tmperr = err;
    while (*output != '\0') {
      if ((isdigit(*output) || *output == 'x') && tmperr == 0) {
        err = 0;
        break;
      } else if (*output == ' ')
        err = 6;
      else
        err = 6;
      output++;
    }
  }
  return err;
}

int checkPriority(char token) {
  int priority = 0;
  if (token == '(')
    priority = LOW;
  else if (token == ')')
    priority = LOW;
  else if (token == '-')
    priority = MID;
  else if (token == '+')
    priority = MID;
  else if (token == '*')
    priority = HIGH;
  else if (token == '/')
    priority = HIGH;
  else if (token == '%')
    priority = HIGH;
  else if (token == '^')
    priority = ULTRA;
  else
    priority = ULTRA;
  return priority;
}

void pushNum(Numbers **head, double data) {
  Numbers *tmp = (Numbers *)malloc(sizeof(Numbers));
  tmp->number = data;
  tmp->next = *head;
  *head = tmp;
}

void pushOp(Operations **head, char data) {
  Operations *tmp = (Operations *)malloc(sizeof(Operations));
  tmp->Operator = data;
  tmp->next = *head;
  *head = tmp;
}

double popNum(Numbers **head) {
  if (*head == NULL) exit(-1);
  Numbers *prev = NULL;
  double res;
  prev = (*head);
  res = prev->number;
  (*head) = (*head)->next;
  free(prev);
  return res;
}

char popOp(Operations **head) {
  if (*head == NULL) exit(-1);
  Operations *p = *head;
  char res = p->Operator;
  *head = p->next;
  free(p);
  return res;
}

int ymd_to_mord(char *data) {
    
    int y1, m1, d1;
    if (sscanf(data, "%d.%d.%d", &y1, &m1, &d1) != 3) {
      return -1;
    }

    int a = (14 - m1) / 12;
    int y = y1 - a;  /* лет с 1 марта 0-го года */
    int m = m1 + 12*a - 3;  /* месяцев -"- */
    return d1 + (153*m + 2)/5 + 365*y + y/4 - y/100 + y/400;

}

