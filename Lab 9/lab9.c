#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

Node *createResistor(int, char[]);
// Implement these functions
void handleInsert(LinkedList*);
void handleRemove(LinkedList*);
void handleCurrentCal(LinkedList*, int);
void handleVoltage(LinkedList*, int);
void handlePrint(LinkedList*);
void handleQuit(LinkedList*);

int main(void) {
  LinkedList circuit;
  initList(&circuit);
  char command = '\0';
  printf("Welcome to our circuit simulator\n");
  // Enter the source voltage!
  printf("What is the source of the voltage?\n");
  int voltage;
  readInputNumber(&voltage);

  while (command != 'Q') {
    command = getCommand();

    switch (command) {
      case 'I':
        handleInsert(&circuit);
        break;
      case 'R':
        handleRemove(&circuit);
        break;
      case 'C':
        handleCurrentCal(&circuit, voltage);
        break;
      case 'V':
        handleVoltage(&circuit, voltage);
        break;
      case 'P':
        handlePrint(&circuit);
        break;
      case 'Q':
        handleQuit(&circuit);
        break;
    }
  }
  return 0;
}

/*Node *createResistor(int resistance, char name[STRING_MAX]) {
  Node* resistor = malloc(sizeof(Node));
  
  if (resistor == NULL) {
    exit(EXIT_FAILURE);
  }

  resistor->value = resistance;
  for (int i = 0; name[i] != '\0'; ++i) {
    resistor->name[i] = name[i];
  }
  resistor->next = NULL;

  return resistor;
}*/


void handleInsert(LinkedList* circuit) {
  int resistance = 0;
  printf("What's the value of the resistor: ");
  readInputNumber(&resistance);
  printf("What's the label of the resistor: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);
  // TODO: Implement the insert into ordered list function
  Node* resistor = (Node*)malloc(sizeof(Node));
  
  if (resistor != NULL) {
    resistor->value = resistance;
    resistor->next = NULL;
    strcpy(resistor->name, labelName);
  }

  Node *after = circuit->head;
  Node *before = NULL;

  if (circuit->head == NULL) {
    circuit->head = resistor;
    return;
  }

  while (after != NULL && strcmp(labelName, after->name) >= 0) {
    if (strcmp(labelName, after->name) == 0) {
      printf("A resistor with %s already exists.\n", labelName);
      return;
    }
    before = after;
    after = after->next;
  }
  
  if (before == NULL) {
    resistor->next = circuit->head;
    circuit->head = resistor;
  } else {
    before->next = resistor;
    resistor->next = after;
  }
}

void handleRemove(LinkedList* circuit) {
  // TODO: Implement the remove function
  printf("What's the label of the resistor you want to remove: ");
  char resistor[STRING_MAX];
  readInputString(resistor, STRING_MAX);

  Node *previous = NULL;
  Node *present = circuit->head;
  while (present != NULL && strcmp(present->name, resistor) != 0) {//change order
    previous = present;
    present = present->next;
  }

  if (present == NULL) {
    printf("The resistor with %s label does not exist.\n", resistor);
    return;
  } else if (previous == NULL) {
    circuit->head = present->next;
  } else {
    previous->next = present->next;
  }
  free(present);

}

/*void removeResistor2(LinkedList* circuit, Node *resistor) {
  Node **present = &circuit->head;
  while (*present != resistor && *present != NULL) {
    present = &(*present)->next;
  }
  if (present == NULL) {
    printf("The resistor with %s label does not exist.", resistor->name);
  }
  *present = resistor->next;
}*/

void handleCurrentCal(LinkedList* circuit, int voltage) {
  // TODO: Implement the function that prints the value of current in the
  // circuit
  double sum = 0;
  double current;
  Node *present = circuit->head;
  while (present != NULL) {
    sum += present->value;
    present = present->next;
  }
  current = voltage / sum;
  printf("The current in the circuit is %0.6lfA\n", current);
}

void handleVoltage(LinkedList* circuit, int voltage) {
  // TODO: Implement the function that prints the potential difference across a
  // resistor
  char resistor[STRING_MAX];
  printf("What's the label of the resistor you want to find the voltage across: ");
  readInputString(resistor, STRING_MAX);
  double sum = 0;
  double volt;
  double current;
  Node *present = circuit->head;
  while (present != NULL) {
    sum += present->value;
    present = present->next;
  }
  current = voltage / sum;

  Node *search = circuit->head;
  while (strcmp(search->name, resistor) != 0 && search != NULL) {
    search = search->next;
  }
  if (search == NULL) {
    printf("The resistor with %s label does not exist.", search->name);
  } else {
    volt = search->value * current;
    printf("Voltage across resistor is %0.6lfV\n", volt);
  }

}

void handlePrint(LinkedList* circuit) {
  // TODO: they can implement the print function
  Node *present = circuit->head;
  while (present != NULL) {
    printf("%s  %d Ohms\n", present->name, present->value);
    present = present->next;
  }
}

void handleQuit(LinkedList* circuit) {
  // TODO: Implement the quit function
  printf("Removing all resistors in the circuit...\n");
  handlePrint(circuit);
  Node *present = circuit->head;
  Node *previous = NULL;
  while (present != NULL) {
    previous = present;
    present = present->next;
    free(previous);
  }
  circuit->head = NULL;
}
