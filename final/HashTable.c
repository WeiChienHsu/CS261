struct openHashTable {
  TYPE **table; /* Points to pointer stored in the array */
  int tableSize;
  int count;
}

void initOpenHashTable(struct openHashTable *ht, int size) {
  ht -> table = (TYPE **) malloc(size * sizeof(TYPE *));
  ht -> tableSize = size;
  ht -> count = 0;
  /*  Fill in the array */
  for(int i = 0; i < size; i++) {
    ht ->table[i] = 0; /* Points to the 0 means there is no stored value */
  }
}

void openHashTableSize(struct openHashTable *ht) {
  return ht -> tableSize;
}

void openHashTableAdd(struct openHashTable *ht, TYPE *newValue) {
  if((ht -> count / (double) ht -> tableSize) > 0.75) {
    _resizeOpenHashTable(ht);
  }
  ht -> count ++;

  int index = HASH(newValue) * ht -> tableSize;
  if(index < 0) index += ht -> tableSize;

  while(index >= 0) {
    /* If index exceed */
    if(index == ht -> tableSize) {
      index = 0;
    }
    /* Meet empty space */
    if(ht -> table[index] == 0) {
      ht -> table[index] = newValue;
      index = -1;
    }
    else {
      index ++;
    }
  } 
}

int openHashTableContains(struct openHashTable *ht, TYPE* newValue) {
  int index = HASH(newValue) % ht -> tableSize;
  if(index < 0) index += ht -> tableSize;

  while(ht -> table[index] != 0) {
    if(index == ht ->tableSize) {
      index = 0;
    }
    if(compare(ht -> table[index], newValue) == 0) {
      return 1;
    } else {
      index ++;
    }
  }

  return 0;
}

void _resizeOpenHashTable(struct openHashTable *ht) {
  int originalSize = ht -> tableSize;
  TYPE **temp = ht -> table;
  initOpenHashTable(ht, originalSize * 2);
  for(int i = 0; i < originalSize; i++) {
    if(temp[i] != 0) {
      openHashTableAdd(ht, temp[i]);
    } 
  }
  free(temp);
}