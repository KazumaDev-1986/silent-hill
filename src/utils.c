#include "includes/utils.h"
#include <stdlib.h>

__AC__ void addElementList(struct List **list, void *value) {
  if (list && *list) {
    struct List *tmp = (*list);
    while (tmp->next) {
      tmp->next = tmp->next;
    }

    tmp->next = (struct List *)malloc(sizeof(struct List));
    tmp->next->next = NULL;

  } else {
    *list = (struct List *)malloc(sizeof(struct List));
    (*list)->value = value;
    (*list)->next = NULL;
  }
}
__AC__ void clearList(struct List **const ptr) {
  if (ptr && *ptr) {
    struct List *tmp = NULL;
    while (*ptr) {
      tmp = (*ptr);
      (*ptr) = (*ptr)->next;
      free(tmp);
      tmp = NULL;
    }
  }
}
