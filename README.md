# Gaming 

## Course Information

- **Course Name:** Algorithmic Problem Solving
- **Course Code:** 23ECSE309
- **Student Name:** Gokul G G
- **University:** KLE Technological University, Hubballi-31

---

## Tagline
> Changing the world of gaming

## Editor's Note:


## Contents
1. [Introduction](#introduction)
2. [Why Portfolio](#why-portfolio)
3. [Objectives](#objectives)
4. [Design](#design)
5. [Challenges](#challenges)
6. [To-Do List](#to-do-list)

---

## Introduction
 World of gaming is full of maths and algorithms. From path finding to move unit towards user specified destination to complex AI npcs that react to player's play style. Algorithms help create most elements in gaming world, so designing better algorithms / replacing existing algorithms with more suitable becomes a must for game developers.

Problems faced:
1. Device Contraints
2. Time of reaction (Of NPC/ of elements in games)
3. Realistic reaction of elements (More realistic == More complexities)

## Why Portfolio
 

## Objectives
  1. Exploring agorithms employed
  2. Designing/ modifying bits of algorithm
  3. Implementation of different algorithm and discussion of experimentation


### Search functionality in mobile games

Searching in mobile games is very slow and especially when there we are searching through huge list of inventory items or huge list of cities you manage (In civilization/kingdom based games). In case of mobile games **space** plays an important role. 

We make 2 step modifications to solve this problem. First trie to radix tree then replacing standard arrays for storing pointer to Maps/hash-maps

Use of 2 modified Radix tree algorithms
##### 1. Radix tree + Maps
 - **Modification**: Each node in a Radix Tree + Maps uses a map  to store pointers to its child nodes. The keys in the map are character sequences, and the values are pointers to child nodes.
 - **Memory Wise**: More efficient memory usage compared to a basic radix tree due to the space optimization from both the radix tree structure and the map's dynamic allocation.
- **Time Complexity**:
	- **Insertion**: O(m * log(n)), where m is the length of the string and n is the number of distinct characters.
	- **Search**: O(m * log(n)), where m is the length of the string and n is the number of distinct characters.
- **Space Complexity**: O(N * K), where N is the number of nodes and K is the pointer/reference size.
    
##### 2. Radix tree + Hash-maps
- **Modification**: Each node in a Radix Tree + Hash-Maps uses a hash-map  to store pointers to its child nodes. The keys in the hash-map are character sequences, and the values are pointers to child nodes.
- **Memory wise**: Efficient memory usage with additional overhead for hash table metadata. Similar to Radix Tree+Maps, but with the dynamic allocation of hash-maps.
- **Time Complexity**:
	- **Insertion**: O(m), where m is the length of the string. Hashmap operations (insert and search) are generally O(1) on average.
	- **Search**: O(m), where m is the length of the string.
- **Space Complexity**: O(N * K), where N is the number of nodes and K is the pointer/reference size.



### In-App Bundle (New Approach for creating bundles of items)

This method was developed to create customized bundles of in-game items based on user spending behavior and preferences. The first step involves collecting detailed statistics on how much users spend on each item within the game. By analyzing this data, we can determine the ratio of spending for each item, which we then scale to a standard value of 100. Any items that have a value of zero after scaling are discarded, as they do not hold significant perceived value to the users.

Next, we evaluate the real-world value of these in-game items. In this context, the scaled perceived values serve as the costs, while the real-world values act as the weights. This dual analysis allows us to generate a set of items and their respective quantities, which can be bundled together and presented to the users in a way that maximizes their appeal and utility.

To ensure these bundles are range of casual user's range, we set the maximum weight as the average daily spending of users. This constraint ensures that the bundles are both attractive to users and acceptable limits of their spending budget. 

Algorithm used
- Knapsack Algorithm


### Advanced Collision Detection in Large 2D Spaces Using Quad-Trees

Collision detection in large 2D spaces with too many objects presents big computational challenges. Utilizing Quad-Trees for this purpose offers a more efficient solution compared to using  Red-Black Trees/ hash-maps, specifically in cases which has many objects distributed across large spaces.

**Data structure**
 1. Quad-Trees: It is a tree data structure that stores information related to each layer. Each layer then gets subdivided into 4 quadrants if information exceeds the capacity of each layer.

**Comparison with**
1. **Red-Black trees**: It stores in a order of creation but doesn't maintain data about objects based on its spatial position.
2. **Hash-Maps**: It doesn't store object data in order of creation/ based on spatial location but is faster in insertion, query and deletion.

**Working of Quad-Tree**
Quad-Trees works by dividing the 2D space into 4 quadrants, recursively subdividing each quadrant depending on capacity. This hierarchical partitioning allows for efficient organization and retrieval of spatial data. When an object is added to a QuadTree, it is placed into the appropriate quadrant based on its coordinates. This spatial partitioning significantly reduces the number of comparisons needed to detect collisions, as objects are only compared with others within the same or neighboring quadrants.



### Lazy rendering/loading (Static objects)

Lazy rendering/loading is a process where only the visible distance based on the player's current position is rendered. This technique helps save RAM and GPU by rendering only what is important for the player's experience in the game.

**Proposed Algorithm:**
- Use Quad-trees to store the spatial location of objects.

**Functionality:**
- The algorithm will return the objects to be rendered based on the range of the query.
- By querying a range (x, y, w, h), we can get all objects present within that range.




### Level wise rendering (Static objects)

This type of rendering prioritizes loading high-priority objects first. For example, in games like the GTA series, high-priority objects include houses, roads, and barriers. Low-priority objects might be pebbles, insects, etc.

**Proposed Algorithm:**
- Quad-trees
- Oct-trees (for 3D environments)

**Limitation:** 
- To achieve this rendering method, we can use quad-trees by manually storing important objects at higher levels and lower-priority objects at lower levels.


### Level wise rendering (Static object) + Objects randomly generated

To handle the randomly generated objects (Not generated sequentially based on priority) we need the algorithm to automatically sort of objects based on priority, This implies we need to modify the algorithm to accommodate automated sorting.

eg: If high priority object was added at end. It should be loaded into top level instead of subdivided lower levels.

**Modification Proposed:**
- Quad-Trees + Priority Vector (Priority Queue)
- Oct-Trees + Priority Vector (Priority Queue)

**Limitations:**
- **Increased Time Complexity:** Sorting the priority list will increase insertion time complexity to O(n * log(n)), where n is the maximum capacity of a layer.

**Alternative Modification (Not recommended):**

- Quad-Tree + Using Simple Vector and Finding Minimum Element Directly

**Limitation:**

- **Unsorted List:** Objects will remain unsorted at every level, which may impact performance and retrieval efficiency.


### Pathfinding for NPCs (Following a static destination)

Pathfinding in games involves finding the shortest path between a source and a destination. While Dijkstra's algorithm is efficient, it lacks the ability to explore and adapt to different scenarios. Therefore, we use the A* algorithm for its good performance.

**Proposed Solution:**

- Use the A* algorithm.
- Set the heuristic to the Euclidean distance between available nodes and the destination.

**Details:**

- **A* Algorithm**: Combines the benefits of Dijkstra's algorithm and heuristics to efficiently find the shortest path.
- **Heuristic:** Euclidean distance ensures that the algorithm considers the closest position to destination




### Pathfinding for NPCs (Following a moving object)

In this scenario, Dijkstra's algorithm is highly inefficient as it will keep recalculating the path every time the object being followed changes its current position. On the other hand, using the A* algorithm with Euclidean distance as its heuristic allows the algorithm to dynamically choose the next move based on the current position of the object.

**Advantages of A* Algorithm**:

- **Dynamic Pathfinding:** A* can continuously update its pathfinding based on the object's current position, ensuring efficient and adaptive movement.
- **Heuristic Function:** The Euclidean distance heuristic helps the algorithm prioritize nodes that are closer to the destination, enhancing performance and reducing unnecessary calculations.

By leveraging the A* algorithm with an appropriate heuristic, pathfinding in dynamic scenarios becomes more efficient and responsive.



### 2D shooter games aiming system, Bullet holes

This technique allows you to find intersection point between 2 line segments.
    Uses:
          1. Smoothly move randomly moving NPC
          2. NPCs based on Neural network models

Same technique can be extended to find intersection between polygon and a line segment. This is used in simple 2d games.
