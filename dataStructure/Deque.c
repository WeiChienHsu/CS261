struct dlink{
  TYPE value;
  struct dlink* next;
  struct dlink* prev;
};

struct linkedList {
  int size;
  struct dlink* frontSentinel;
  struct dlink* backSentinel;
}

void LinkedListLnit(struct linkedList *q) {
  q -> frontSentinel = (struct dlink *) malloc (sizeof(struct dlink));
  assert(q -> frontSentinel != NULL);
  q -> backSentinel = (struct dlink *) malloc (sizeof(struct dlink));
  assert(q -> backSentinel != NULL);
  q -> frontSentinel -> next = q -> backSentinel;
  q -> backSentinel -> next = q -> frontSentinel;
  q -> size = 0;
}

void LinkedLitFree(struct linkedList *q) {
  while(q -> size != 0) {
    linkedListRemoveFront(q);
  }
  free(q -> frontSentinel);
  free(q -> backSentinel);
  q -> frontSentinel = q -> backSentinel = NULL;
}

void _addLink(struct linkedList *q, struct dlink *lnk, TYPE e) {
    assert(q != NULL);
    struct dlink *newLink = malloc(sizeof(struct dlink));
    newLink -> value = e;

    /* Link the new sentinel */
    newLink -> prev = lnk -> prev;
    newLink -> next = lnk;

    /* Link the old sentinel */
    lnk -> prev = newLink;

    if(lnk != q -> backSentinel) {
      q -> frontSentinel -> next = newLink;
    }

    q -> size ++;

    
}

void _removeLink(struct linkedList *q, struct dlink *lnk) {
  assert(q != NULL)
  /* Remove lnk */
  lnk -> prev -> next = lnk -> next;
  lnk -> next -> prev = lnk -> prev;

  /* Unlink lnk */
  lnk -> prev = NULL;
  lnk -> next = NULL;

  /* Free Link */
  free(lnk);

  q -> size --;
}


void LinkedListAddFront (struct linkedList *q, TYPE e) { 
  _addLink(q, q -> frontSentinel->next, e); 
}

void LinkedListAddback (struct linkedList *q, TYPE e) { 
  _addLink(q, q -> backSentinel, e); 
}

void linkedListRemoveFront (struct linkedList *q) { 
  assert(! linkedListIsEmpty(q));
  _removeLink (q, q -> frontSentinal -> next);
}

void LinkedListRemoveBack (struct linkedList *q) { 
  assert(! linkedListIsEmpty(q));
  _removeLink (q, q -> backSentinel -> prev);
}
int LinkedListIsEmpty (struct linkedList *q) { 
  return q->size == 0;
}