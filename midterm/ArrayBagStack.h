# ifndef ArrayBagStack
# define ArrayBagStack
# define MAX_SIZE 100

# define TYPE int
# define EQ(a, b) (a == b)

struct arrayBagStack {
  TYPE data [MAX_SIZE];
  int count;
};

/* Interface for Bag */
void initBag (struct arrayBagStack * b);
void addBag (struct arrayBagStack * b, TYPE v);
int containsBag (struct arrayBagStack * b, TYPE v);
void removeBag (struct arrayBagStack * b, TYPE v);
int sizeBag (struct arrayBagStack * b);
/* Interface for Stack */
void pushStack (struct arrayBagStack * b, TYPE v);
int topStack (struct arrayBagStack * b);
void popStack (struct arrayBagStack * b);
int isEmptyStack (struct arrayBagStack * b);
# endif