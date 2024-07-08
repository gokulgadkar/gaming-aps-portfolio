# Gaming 

## Course Information

- **Course Name:** Algorithmic Problem Solving
- **Course Code:** 23ECSE309
- **Student Name:** Gokul G G
- **University:** KLE Technological University, Hubballi-31

---

## Tagline
> Changing the world of gaming

---

## Contents
1. [Introduction](#introduction)
2. [Objectives](#objectives)
3. [Business Cases](#business-cases)


---

## Introduction
 World of gaming is full of maths and algorithms. From path finding to move unit towards user specified destination to complex AI npcs that react to player's play style. Algorithms help create most elements in gaming world, so designing better algorithms / replacing existing algorithms with more suitable becomes a must for game developers.

Problems faced:
1. Device Contraints
2. Reaction time of a object in a game to users input/command
3. Rendering game assets.


 ---

## Objectives

  1. Exploring algorithms employed
  2. Designing/ modifying bits of algorithm
  3. Implementation of different algorithm and discussion of experimentation

---

## Business Cases
1. **Modified Algorithms**
   -  Search functionality in mobile games 
   -  Level wise rendering (Static object) + Objects randomly generated 
2. **Proposing existing technique/algorithm for a task**
   -  In-App Bundle (New Approach for creating bundles of items)
   -  Lazy rendering/loading (Static objects)
   -  Level wise rendering (Static objects)
3. **Exploring algorithms**
   -  Advanced Collision Detection in Large 2D
   -  Collision detection in large 3D space
   -  Pathfinding for NPCs (Following a static destination)
   -  Pathfinding for NPCs (Following a moving object)
   -  Event Handling

---

### Search functionality in mobile games

<img src="https://github.com/gokulgadkar/gaming-aps-portfolio/assets/92873066/68a96348-5bd3-4f3a-8842-ee48ba54d66b" height="300">



Searching in mobile games is very slow and especially when there we are searching through huge list of inventory items or huge list of cities you manage (In civilization/kingdom based games). In case of mobile games **space** plays an important role. 

**Limits on Mobile**:
- Memory on most average phones are too low and therefore there is need for optimizing 

**Task**:
- Space Optimization

**2 step modifications for space optimization**
1. First Trie[1] to Radix tree
2. Replacing standard arrays for storing pointer to Maps/hash-maps

**Radix Tree**
It is a compressed form of trie tree data structure that store a set of characters in a node untill a split takes place. Mostly useful in case of words with diverse letter sequence eg: umbrella, america, wikipedia etc.[2]

**Understanding second modification**
1. **Radix tree + Maps**
	 - **Modification**: Each node in a Radix Tree + Maps uses a map  to store pointers to its child nodes. The keys in the map are character sequences, and the values are pointers to child nodes.
	 - **Memory Wise**: More efficient memory usage compared to a basic radix tree due to the space optimization from both the radix tree structure and the map's dynamic allocation.
	- **Time Complexity**:
		- **Insertion**: O(m * log(n)), where m is the length of the string and n is the number of distinct characters.
		- **Search**: O(m * log(n)), where m is the length of the string and n is the number of distinct characters.
	- **Space Complexity**: O(N * K), where N is the number of nodes and K is the pointer/reference size.
    
 2. **Radix tree + Hash-maps**
	- **Modification**: Each node in a Radix Tree + Hash-Maps uses a hash-map  to store pointers to its child nodes. The keys in the hash-map are character sequences, and the values are pointers to child nodes.
	- **Memory wise**: Efficient memory usage with additional overhead for hash table metadata. Similar to Radix Tree+Maps, but with the dynamic allocation of hash-maps.
	- **Time Complexity**:
		- **Insertion**: O(m), where m is the length of the string. Hashmap operations (insert and search) are generally O(1) on average.
		- **Search**: O(m), where m is the length of the string.
	- **Space Complexity**: O(N * K), where N is the number of nodes and K is the pointer/reference size.

**code**
- [Radix-Tree + HashMaps](Codes/r-hash.cpp)
- [Radix-Tree + Maps](Codes/r-map.cpp)


---


### Level wise rendering (Static object) + Objects randomly generated

<img src="https://github.com/gokulgadkar/gaming-aps-portfolio/assets/92873066/f030d3f7-9692-46e7-9753-af11fc2f2f29" width="400">
<img src="https://github.com/gokulgadkar/gaming-aps-portfolio/assets/92873066/e4aff584-6df6-461f-95d5-93eb684ed9ba" width="400">

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

**Code**
- [Modified QuadTree](Codes/qtree-p.cpp)

---


### In-App Bundle (New Approach for creating bundles of items)

<img src="https://github.com/gokulgadkar/gaming-aps-portfolio/assets/92873066/b10b6ec8-5173-4aff-a852-bfac7ca3ddd4" height="300">


This method was developed to create customized bundles of in-game items based on user spending behavior and preferences. The first step involves collecting detailed statistics on how much users spend on each item within the game. By analyzing this data, we can determine the ratio of spending for each item, which we then scale to a standard value of 100. Any items that have a value of zero after scaling are discarded, as they do not hold significant perceived value to the users.

Next, we evaluate the real-world value of these in-game items. In this context, the scaled perceived values serve as the costs, while the real-world values of items act as the weights. This dual analysis allows us to generate a set of items and their respective quantities, which can be bundled together and presented to the users in a way that maximizes their appeal and utility.

To ensure these bundles are range of casual user's range, we set the maximum weight as the average daily spending of users. This constraint ensures that the bundles are both attractive to users and acceptable limits of their spending budget. 

**Time Complexity**
O(N * W * Q​) 
N- Number of items
W - Weight capacity
Q - maximum quantity

**Advantage**
- Accurately generate value based bundles. 

**Algorithm used**
- Knapsack Algorithm

**Code**
- [KnapSack](Codes/knap.cpp)


---

### Lazy rendering/loading (Static objects)

<img src="https://github.com/gokulgadkar/gaming-aps-portfolio/assets/92873066/dfb981d3-fc55-4bd6-8b43-eaf226f8a500" width="300">

Lazy rendering/loading is a process where only the visible distance based on the player's current position is rendered. This technique helps save RAM and GPU by rendering only what is important for the player's experience in the game.

**Proposed Algorithm:**
- Use Quad-trees[3] to store the spatial location of objects.

**Working of Quad-Tree**
Quad-Trees works by dividing the 2D space into 4 quadrants, recursively subdividing each quadrant depending on capacity. This hierarchical partitioning allows for efficient organization and retrieval of spatial data. 

**Functionality:**
- The algorithm will return the objects to be rendered based on the range of the query.
- By querying a range (x, y, w, h), we can get all objects present within that range.

**Code**
- [QuadTree](Codes/qtree.cpp)



---


### Level wise rendering (Static objects)

<img src="https://github.com/gokulgadkar/gaming-aps-portfolio/assets/92873066/f030d3f7-9692-46e7-9753-af11fc2f2f29" width="400">

This type of rendering prioritizes loading high-priority objects first. For example, in games like the GTA series, high-priority objects include houses, roads, and barriers. Low-priority objects might be pebbles, insects, etc.

**Proposed Algorithm:**
- Quad-trees
- Oct-trees (for 3D environments) [4]

**Limitation:** 
- To achieve this rendering method, we can use quad-trees by manually storing important objects at higher levels and lower-priority objects at lower levels.

**Code**
- [QuadTree](Codes/qtree.cpp)


---


### Advanced Collision Detection in Large 2D Spaces Using Quad-Trees

<img src="https://github.com/gokulgadkar/gaming-aps-portfolio/assets/92873066/dde707f0-e0ed-4cec-baf1-026ce1c0bcba" width="300">

<img src="https://github.com/gokulgadkar/gaming-aps-portfolio/assets/92873066/1f15388c-3e70-42a7-94c1-29463d14c5b5" height="300">

Collision detection in large 2D spaces with too many objects presents big computational challenges. Utilizing Quad-Trees for this purpose offers a more efficient solution compared to using  Red-Black Trees/ hash-maps, specifically in cases which has many objects distributed across large spaces.

**Data structure**
 1. Quad-Trees: It is a tree data structure that stores information related to each layer. Each layer then gets subdivided into 4 quadrants if information exceeds the capacity of each layer. When an object is added to a QuadTree, it is placed into the appropriate quadrant based on its coordinates. This spatial partitioning significantly reduces the number of comparisons needed to detect collisions, as objects are only compared with others within the same or neighboring quadrants.

**Comparison with**
1. **Red-Black trees**: It stores in a order of creation but doesn't maintain data about objects based on its spatial position.
2. **Hash-Maps**: It doesn't store object data in order of creation/ based on spatial location but is faster in insertion, query and deletion.

**Code**
- [QuadTree](Codes/qtree.cpp)


---



### Collision detection in large 3D space

<img src="https://github.com/gokulgadkar/gaming-aps-portfolio/assets/92873066/61390e72-68cf-4779-8145-8e376b13eb09" height="300">


Similar to quad-tree there is data structure for a 3d space which stores data in x,y,z coordinates.
This data-structure is called Oct-tree. 

This data structure handles cuboidal space and operates by dividing cuboid into 8 smaller cuboids. Each layer has specific capacity 

---








### Pathfinding for NPCs (Following a static destination)

Pathfinding in games involves finding the shortest path between a source and a destination. While Dijkstra's algorithm is efficient, it lacks the ability to explore and adapt to different scenarios. Therefore, we use the A* algorithm for its good performance.

**Proposed Solution:**

- Use the A* algorithm.
- Set the heuristic to the Euclidean distance between available nodes and the destination.

**Details:**

- **A* Algorithm**: Combines the benefits of Dijkstra's algorithm and heuristics to efficiently find the shortest path.
- **Heuristic** : Euclidean distance ensures that the algorithm considers the closest position to destination

**Code**
- [A* algorithm](Codes/a-star.cpp)

---


### Pathfinding for NPCs (Following a moving object)

In this scenario, Dijkstra's algorithm is highly inefficient as it will keep recalculating the path every time the object being followed changes its current position. On the other hand, using the A* algorithm with Euclidean distance as its heuristic allows the algorithm to dynamically choose the next move based on the current position of the object.

**Advantages of A* Algorithm**:

- **Dynamic Pathfinding:** A* can continuously update its pathfinding based on the object's current position, ensuring efficient and adaptive movement.
- **Heuristic Function:** The Euclidean distance heuristic helps the algorithm prioritize nodes that are closer to the destination, enhancing performance and reducing unnecessary calculations.

By leveraging the A* algorithm with an appropriate heuristic, pathfinding in dynamic scenarios becomes more efficient and responsive.

**Code**
- [A* algorithm](Codes/a-star.cpp)

---

### Event Handling 

In event handling for small games, arrays/lists and linked lists are commonly used. However, a more efficient data structure would be Red-Black trees, which maintain order and offer faster access times compared to lists.

**Scenario**:
When you need to access events from the middle section, a list becomes less effective.

**Advantages of Red-Black Trees** :
Ordered Data: Red-Black trees keep the data sorted, which is beneficial for event handling.
Faster Access: Compared to lists, accessing events in a Red-Black tree is more efficient.

**Time complexity**:
-  Access time : O(log n)
-  Insertion : O(Log n)
-  Deletion : O(Log n)

By using Red-Black trees, you can improve the efficiency of event handling in your game, especially when accessing or modifying events frequently.

**Code**
- [Red-Black Trees](Codes/rb.cpp)

---

## Incomplete Work


### 2D Aiming system, Bullet holes

In case of 2d shooting games. It is important for you to find intersection between 2 line segments or line segment and polygon. 

**Code to find**:
1. Line segment intersection  
2. Intersection between polygon and line segment

**Proposed Design**
Instead of directly checking all objects. Use of quad-trees to identify important local objects.


<img src="https://github.com/gokulgadkar/gaming-aps-portfolio/assets/92873066/e2e50955-1471-4871-83c7-07957bc15ee4" width="400">

In above image we need to show bullet marks on blue walls which can be done by finding if a line of fire intersects with edges of polygons


**Code**
- [Line Segment intersection](Codes/line.cpp)
- [Quad Tree](Codes/qtree.cpp)





## References
[1] https://en.wikipedia.org/wiki/Trie
[2] https://en.wikipedia.org/wiki/Radix_tree
[3] https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/quadtrees.pdf
[4] https://en.wikipedia.org/wiki/Octree
