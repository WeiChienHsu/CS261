# Graphs and Matrices

A graph is composed of vertices (or nodes) and edges (or arcs). Either may carry additional information. If a graph is being used to model real-world objects, such as a roadmap, the value of a vertex might represent the name of a city, whereas an edge could represent a road from one city to another.


The two most common representations for a graph are an adjacency matrix and an edge list. 

## Two ways to store a graph: Adjancency Matrix vs Edges List

For Adjancency Matrix, here a 1 value in position (i, j) indicates that there is a link between city i and j, and zero value indicates no such link. By convention, a node is always considered to be connected to itself. The adjacency matrix representation has the disadvantage that it always requires O(v^2) space to store a matrix with v verticies, regardless of the number of edges. 

```c
#define N 3

int adjacency[N][N] = {{1, 0, 0},
                       {0, 1, 1},
                       {1, 0, 0}};
```

For Edges List, stores only the edges and is thus advantageous if the graph is
relatively sparse. This edge list can easily be stored in a dictionary, where the index is the vertex (say, the city named), and the value is a list of adjacent cities. If the graph is weighted the list is replaced by a second dictionary, again indexed by verticies, which contains the weight for each edge.

***

## Single Source Reachability

```
findReachable(graph a, vertex start) {
  create a set of reachable vertices, initially empty. CALL this r.
  create a container for vertices known to be reachable. CALL this c.
  add start vertex to container c
  while the container c is not empty {
    remove first entry from the contatiner c, assign to v
    if v is not already in the set of reachable vertices r {
      add v to the reachable set r
      add the neighbors of v, not already reachable, to the container c
    }
  }
  return r 
}
```


### Use Stack as our Container (DFS)

- Reachable: Any Bag Implementation (Array, Dynamic Array, LinkedList, AVL tree - faster check for contains, HashTable)

- Stack: Dynamic array, Deque, LL Deque

- Graph Representation: Dynamic array of LinkedLists / HashMap of LinkedList (key: name of node, value: list of neighbors)

```
Initialize set of reachable vertices and add vi to a STACK
While STACK is not empty {
  Get and Pop last vertex v from STACK
  if vertex v is not in reachable {
    add it to reachable
    For all its nieghbors vj of v, if vj is NOT reachable
      add to STACK
  }
}
```

### Use Queue as our Container (BFS)

```
Initialize set of reachable vertices and add vi to a QUEUE
While QUEUE is not empty {
  Get and pop first vertex v from Queue
  if vertex v is not in reachable {
    add it to reachable
    For all its neighbors vj of v, if vj is NOT reachable
      add to the end of QUEUE
  } 
}
```

***

## Depth-First-Search (Implement by Stack)
- DFS like a single person working a maze.
- DFS can take an unfortunate route and have to backtrack a long way, and multiple times.
- DFS can get lucky and find the solution very quickly.
- What if there's one inifinite path DFS may go dwon it and stuck in it.

```java
public static void showThePathByDFS(HashMap<Integer, List<Integer>> edgesList) {
    Deque<Integer> stack = new ArrayDeque<>();
    List<Integer> reachable = new ArrayList<>();

    /* Add the first Node into the stack */
    stack.offerFirst(1);

    while(!stack.isEmpty()) {
        int currentNode = stack.pollFirst();
        reachable.add(currentNode);

        if(currentNode == 25) {
            break;
        }

        /* Add all neighbors of current node into the Stack */
        List<Integer> neighbors = edgesList.get(currentNode);

        for(int i = 0; i < neighbors.size(); i++) {
            int neighbor = neighbors.get(i);
            /* Check the neighbor is not in the reachable array */
            if(!reachable.contains(neighbor) && !stack.contains(neighbor)) {
                /* Push it into the Stack */
                stack.offerFirst(neighbor);
            }
        }
    }
}
```

***

## Breadth-First-Search (Implement by Queue)
- BFS like a wave flowing through a maze.
- BFS may not find it as quickly, but will always find it.
- BFS first checks all paths of length 1, then of lenth 2, then of length 3, etc. It'g guaranteed to find a path containing the least steps from start to goal.

```java
public static void showThePathByBFS(HashMap<Integer, List<Integer>> edgesList) {
    Deque<Integer> queue = new ArrayDeque<>();
    List<Integer> reachable = new ArrayList<>();

    queue.offerFirst(1);

    while(!queue.isEmpty()) {
        int currentNode = queue.pollLast();
        reachable.add(currentNode);

        if(currentNode == 25) {
            break;
        }

        /* Add all neighbors of current node into the Queue */
        List<Integer> neighbors = edgesList.get(currentNode);
        for(int neighbor : neighbors) {
            if(!reachable.contains(neighbor) && !queue.contains(neighbor)) {
                queue.offerFirst(neighbor);
            }
        }
    }
}
```

***

## Dijkstra's Shortest Path Algorithm (Implement by PriorityQueue)

O(E LogE) : Inner loop runs at most E times and Time to add / remove from priority Queue is bounded by LogE.

```
Need a Reachable HashMap to record <"Name" : "Shortest Distance">
Need a Priortiy Queue to Put the toCity Class
Add source vertex to PQ with distance 0

while PQ is not empty
  Get and Remove vertex v with shortest distance from PQ
  If v is known to be reachable, discard
  Otherwise, add v with given cost to reachable dictionary 
  For all neighbors vj of v
    if vj is not in reachable dictionary, update cost of reaching v 
    with cost to travel from v to vj, and add it into PQ
```

```java
class toCity {
  String name;
  int dist;
  public toCity(String name, int dist) {
    this.name = name;
    this.dist = dist;
  }
}

public static void Dijkstra(HashMap<String, HashMap<String, Integer>> source, String startCity) {

    /* Set a reachable HashMap to record the shortest distance with City */
    LinkedHashMap<String, Integer> reachable = new LinkedHashMap<>();

    /* Set a Priority Queue to get the currently shortest path */
    /* Write a Comparator for a min Heap return values base on dist in class*/
    PriorityQueue<toCity> pq = new PriorityQueue<>(new Comparator<toCity>() {
        @Override
        public int compare(toCity o1, toCity o2) {
            return o1.dist - o2.dist;
        }
    });

    /* Add the Start City into Priority Queue */
    pq.add(new toCity(startCity, 0));

    while(!pq.isEmpty()) {
        /* Get the shortest city form the top of PQ */
        toCity currentCity = pq.poll();

        /* If current city is in the reachable, discard */
        if(reachable.containsKey(currentCity.name)) {
            continue;
        } else {
            /* add v with given cost to reachable dictionary */
            reachable.put(currentCity.name, currentCity.dist);
        }

        /* Get the HashMap which has recorded all neighbors of current City */
        HashMap<String, Integer> neighbors = source.get(currentCity.name);

        for(String neighbor : neighbors.keySet()) {
            /* Check if the neighbor of current city has been put into reachable map */
            if(!reachable.containsKey(neighbor)) {
                /* Updated the new Distance by adding up: */
                    /* Current Distance : currentCity.dist */
                    /* Distance of current city to its neighbor: neighbors.get(neighbor) */
                pq.add(new toCity(neighbor, currentCity.dist + neighbors.get(neighbor)));
            }
        }
    }
}
```

## Heap Sort is an in-place sorting algorithm 
Since it could implement in place by an array.

## Tree Sort is built by AVL binary Search Tree
So it need an additional space building up a Tree.