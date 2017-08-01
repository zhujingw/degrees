=========================ReadMe.md=============================
By: Zhu Jing Wang
Data: April 25, 2016

Purpose: This program is aimed to find the paths between two students.The 
	 program first reads in two files: one students file, which contains
	 students' names and the courses they've taken, one ta file, which 
	 contains tas' names and the courses they've taed.Then the program 
	 stores the two files and creates a graph to represent the connections 
	 among all students and tas exist in the two files. Then the program 
	 can find all the paths between any given two people, as well as the 
	 shortest path between those two people.
	 
Files:   main.cpp          main function and a bunch of functions that supports 
	 	           read-in, take-in commands,and calling other functions 
	 	           in other files

	 HashTable.h       header file of the HashTable class
	 
	 HashTable.cpp     actual implementation of HashTable class, this class
	 		   hash the key first, then store the key together with 
	 		   its value to the bucket it belongs.

	 Graph.h	   header file of the Graph class
	 
	 Graph.cpp	   actual implementation of Graph class, this class 
	 	 	   creates an adjacency list to represent the graph of 
	 	 	   the connections among people 
	 
Compile instruction: use include Makefile

Run instruction: type ./hw6degrees file1 file2 (press enter)
		 (replace file1 with student file, file2 with ta file)

		 type in command 'ls' for list of all students and tas' names

		                 'lc' for list of all courses either students
		                      have taken or tas have taed

		                 'roster coursename'
		                      for roster of that course

		                 'taed ta's name'
		                      for list of courses that ta has taed

		                 'paths name1 name2'
		                      for all paths between the two people

		                 'shortestpath name1 name2'
		                      for the shortest path between the two 

Data Structure: 1.I use two lists to store list of names and list of courses. I
		  use standard vector of strings to implement the lists

		2.I use two chained hashtables, one to map a student to the 
		  courses he/she has taed, the other to map a course to the 
		  students who have taken this course. And I use linked list
		  inside each bucket of the table to implement chained table

		3.I use graph to represent the connections among people, and I 
		  use adjacency list to represent the graph

		  	a.I use a dynamic array of structs to store the 
		  	  adjacency list. Each element of the array is one 
		  	  vertex and the a list of vertices connected to that
		  	  vertex.

		  	b.I use a dynamic array of strings to store the paths
		  	  I find between two vertices

Algorithm: 
	Chained Hash Table  
		1.hash the key so we get the index of the bucket the key should
		  go to
		  
		2.go to that bucket
		
		3.check if there's already things in the bucket
		
		4.if not just insert the key and its value. 
		
		  if there is, and the key has not yet been added to the table
		  collision takes place, we traverse to the end of the chain in 
		  that bucket, link the key and its value to the end of the 
		  chain. 
		  
		  if the key already exists in the table, we traverse to that 
		  key and just update the value of that key
	
	Adjacency list
		1.look at each vertices
		
		2.look at each neighbor of the vertex we looking at, add them to 
		  the list of neighbors of the vertex we looking at
		  
	DFS search(recursive)
		* mark the vertex as not visited and store it in current path
		
                * if current vertex is same as destination, then store current
		   path (base case)
		
		* if current vertex is not destination, 
			recurse for all the vertices adjacent to current vertex
		   
		* remove current vertex from path and mark it as unvisited
		
		(for corner cases when the source vertex is the destination 
		 vertex, in the base case we make sure entering recursion 
		 despite current vertex is destination if we have never entered
		 recursion)
		 
	Shortest path
		I did not use dijkstra algorithm or BFS this time, the way for
		me to find the shortest path is that each time I create a path,
		I calculate the length of that path, since I create path piece
		by piece(each piece represents a person). Then I use a find min
		function to find the path with the shortest length. So
		for large data set, I can find all paths, but when finding the
		shortest path, it might took a long while. (I guess that's why 
		I got time out on the large data shortest path test)

*** I failed some valgrind tests when using big data, and I'm sure they resulted 
    from the same source. 10 tas looked at my code and could not figure out why
    it's only leaking memory for big data. I'm very confused. I checked that 
    every time I use a new operator, I delete it when done using it. And my 
    destructor is working. Plzzzzz don't take all points off for failed valgrind
    tests that are actually resulted from the same source. Thanksss so much.
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	          	
