struct hlink {
  TYPE value;
  struct hlink *next;
}

struct HashTable {
  struct hlink **table;
  int tableSize;
  int count;
}

void initHashTable(struct HashTable *ht, int size) {
  assert(size > 0);
  /* Allocate a memory space for size * pointers */
  ht -> table = (struct hlink **) malloc (size * sizeof(struct hlink *)); 
  for(int i = 0; i < size; i++) {
    ht -> table[i] = 0;
  }
  ht -> tableSize = size;
  ht -> count = 0;
}

void HashTableAdd(struct HashTable *ht, TYPE newValue) {
  int index = HASH(newValue) % ht -> tableSize;
  if(index < 0) index += ht -> tableSize;

  struct hlink *newLink = malloc(sizeof(struct hlink*));
  assert(newLink != 0);
  newLink -> value = newValue;
  newLink -> next = ht -> table[index];
  ht -> table[index] = newLink;
  ht -> count ++;

  if((ht -> count / (double) ht -> tableSize) > 8.0) {
    _HashTableResize(ht);
  }
  
}

int HashTableConatins(struct HashTable *ht, TYPE target) {
  int index = HASH(newValue) % ht -> tableSize;
  if(index < 0) index += ht -> tableSize;

  struct *hlink current = ht -> table[index];
  while(current != 0) {
    if(current -> value == target) {
      return 1;
    }
    current = current -> next;
  }
  return 0;
}

void HashTableRemove(struct HashTable *ht, TYPE value) {
  int index = HASH(value) * ht -> tableSize;
  if(index < 0) index += ht -> tableSize;

  struct *hlink current = ht -> table[index];
  struct *hlinl prev = 0;

  while(current != 0) {
    if(compare(current -> value, value) == 0) {
      /* Remove the current value */
      /* Target is the HEAD */
      if(current == ht -> table[index]) {
        ht -> table[index] = current -> next;
      } else {
        /* There is a previous hlink */
        prev -> next = current -> next;
      }
      break;
    }
    else {
      /* Find the next position */
      prev = cur;
      cur = cur -> next;
    }
  }
}

void _HashTableResize(struct HashTable *ht) {
  struct hlink **tempTable = ht -> table;
  initHashTable(ht, ht -> tableSize * 2);
  
  /* Reassign value into new Hash Map */
  for(int i = 0; i < tempTable -> tableSize; i++) {
    struct hlink* temp = tempTable -> table[i];
    while(temp != 0) {
      HashTableAdd(ht, temp -> value);
      struct hlink* last = temp;
      temp = temp -> next;
      free(last);
    }
  }
  free(tempTable);
}