#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_EXPR_LENGTH 100

char *removeAllSpaces(char *line);
int getInt(char *line, int index);
int readExpr(char *line, int index);

int main(void)
{
  char *line = malloc(sizeof(char) * MAX_EXPR_LENGTH);
  int res;

  while (1)
  {
    printf("Enter an expression (or 'quit'): ");
    fgets(line, MAX_EXPR_LENGTH, stdin);
    line[strlen(line) - 1] = '\0';

    if (strcmp(line, "quit") == 0)
    {
      printf("Goodbye!\n");

      return 0;
    }

    line = removeAllSpaces(line);

    res = readExpr(line, 0);
    printf("Result: %d\n", res);
  }

  return 0;
}

int readExpr(char *line, int index)
{
  char op;
  int number = getInt(line, index);

  // get how far we moved up after getting the number (with getInt)
  int tempNumber = number;
  int tempIndex = 0;

  while (1)
  {
    tempIndex++;

    tempNumber /= 10;

    if (tempNumber == 0)
    {
      break;
    }
  }

  int newIndex = index + tempIndex;

  if (newIndex + 1 > strlen(line))
  {
    return number;
  }

  op = line[newIndex];
  if (op == '+')
  {
    return number + readExpr(line, newIndex + 1);
  }
  else if (op == '-')
  {
    return number - readExpr(line, newIndex + 1);
  }
  else if (op == '*')
  {
    return number * readExpr(line, newIndex + 1);
  }
}

char *removeAllSpaces(char *line)
{
  char *newStr = NULL;
  int i, j = 0;

  for (i = 0; i < strlen(line); i++)
  {
    if (line[i] == ' ')
    {
      continue;
    }

    j++;

    newStr = realloc(newStr, sizeof(char) * j);
    newStr[j - 1] = line[i];
  }

  printf("%s\n", newStr);

  return newStr;
}

int getInt(char *line, int index)
{
  int res;
  char strInt[MAX_EXPR_LENGTH];
  strInt[0] = line[index];

  index++;

  while (1)
  {
    if (!isdigit(line[index]) || index > strlen(strInt))
    {
      break;
    }

    strInt[strlen(strInt)] = line[index];
    index++;
  }

  res = atoi(strInt);

  return res;
}
