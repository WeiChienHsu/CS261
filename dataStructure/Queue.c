struct link {
  TYPE value;
  struct link *next;
};

struct listQueue {
  struct link *firstLink;
  struct link *lastLink; 
};

void listQueueInit(struct listQueue *q) {
  struct link *lnk = (struct link*) malloc(sizeof(struct link));
  assert(lnk != NULL); /* lnk is the sentinel */
  lnk -> next = NULL;
  q -> firstLink = q -> lastLink = lnk;
}

void listQueueAddBack(struct listQueue *q, TYPE e) {
  struct link *newLink = (struct link*) malloc(sizeof(struct link));
  assert(newLink != NULL);
  newLink -> value = e;
  newLink -> next = NULL;

  if(lnk -> next == NULL) {
    lnk.next = newList;
    q -> firstLink = newLink;
    q -> lastLink = newLink;
  } else {
    q -> lastLink -> next = newLink;
    q -> lastLink = q -> lastLink.next;
  }
}

TYPE listQueueFront(struct listQueue *q) {
  if(listQueuIsEmpty(q)) {
    return NULL;
  } else {
    return q -> firstLink -> value;
  }
}

TYPE listQueueRemoveFront(struct listQueue *q) {
  if(!listQueueIsEmpty(q)) {
    struct link * temp = (struct link *) malloc(sizeof(struct link));
    temp = q -> firstLink;
    q -> firstLink = q -> firstLink -> next;
    temp -> next = NULL;

    free(temp);
  }
}

int listQueueIsEmpty(struct listQueue *q) {
  if(q -> firstLink == q -> lastLink) {
    return 1;
  } else {
    return 0;
  }
}