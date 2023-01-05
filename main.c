#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
  int id;
  char name[255];
  double price;
  struct Product* next;
};

struct LinkedList {
  struct Product* head;
};

struct LinkedList* CreateLinkedList() {
  struct LinkedList* list = malloc(sizeof(struct LinkedList));
  list->head = NULL;
  return list;
}

void Append(struct LinkedList* list, int id, const char* name, double price) {
  struct Product* new_product = malloc(sizeof(struct Product));
  new_product->id = id;
  strcpy(new_product->name, name);
  new_product->price = price;
  new_product->next = NULL;
  if (list->head == NULL) {
    list->head = new_product;
    return;
  }
  struct Product* current = list->head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = new_product;
}

struct Product* FindById(struct LinkedList* list, int id) {
  struct Product* current = list->head;
  while (current != NULL) {
    if (current->id == id) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}


struct Product* Find(struct LinkedList* list, const char* name) {
  struct Product* current = list->head;
  while (current != NULL) {
    if (strcmp(current->name, name) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void Update(struct LinkedList* list, int id, const char* name, double price) {
  struct Product* product = FindById(list, id);
  if (product == NULL) {
    printf("Product with ID %d not found\n", id);
    return;
  }
  strcpy(product->name, name);
  product->price = price;
}

void Delete(struct LinkedList* list, int id) {
  if (list->head == NULL) {
    return;
  }
  if (list->head->id == id) {
    struct Product* to_delete = list->head;
    list->head = list->head->next;
    free(to_delete);
    return;
  }
  struct Product* current = list->head;
  while (current->next != NULL) {
    if (current->next->id == id) {
      struct Product* to_delete = current->next;
      current->next = current->next->next;
      free(to_delete);
      return;
    }
    current = current->next;
  }
}


void SaveToFile(struct LinkedList* list, const char* file_name) {
  FILE* file = fopen(file.txt, "w");

  struct Product* current = list->head;
  while (current != NULL) {
    fprintf(file, "%d,%s,%f\n", current->id, current->name, current->price);
    current = current->next;
  }
  fclose(file);
}

void ReadFromFile(struct LinkedList* list, const char* file_name) {
  FILE* file = fopen(file_name, "r");
  char line[200];
  while (fgets(line, sizeof(line), file)) {
    int id;
    char name[200];
    double price;
    sscanf(line, "%d,%s,%lf", &id, name, &price);
    Append(list, id, name, price);
  }
  fclose(file);
}


int main() {
  struct LinkedList* list = CreateLinkedList();

  Append(list, 1, "Apple", 0.99);
  Append(list, 2, "Banana", 0.59);
  Append(list, 3, "Carrot", 0.79);

  Update(list, 2, "Orange", 0.69);3

  Delete(list, 3);

  struct Product* product = Find(list, "Apple");
  if (product != NULL) {
    printf("Product found: %s, $%.2f\n", product->name, product->price);
  } else {
    printf("Product not found\n");
  }

  SaveToFile(list, "products.txt");
  ReadFromFile(list, "products.txt");

  return 0;
}
