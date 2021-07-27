# MetroNavigator
This is basic application of Djikstra's Algorithm which finds shortest paths between two metro stattions

AIM
The aim of the project is used to save the time of a user by suggesting the shortest possible route with reference to Delhi Metro Map. 
It can also compute the cost incurred in travelling from Destination A to Destination B 

Abstract: 
For people living in big cities, imagining lives without the Metro would be difficult. This method of transport allows people to travel major distances much faster while it simultaneously helps us to skip the road traffic and greater exposure to pollution.
 In this project, we will try to show the basic features of a Metro Map Navigator, which tells us the shortest and the most efficient route to reach our destination. In this case the source and the destination will be entered by the user. Then the program will suggest the optimum path for metro travelling. 

Tools & Techniques Used  
1.	GRAPHS:  consists of a finite set of vertices (or nodes) and set of edges which connect a pair of nodes.
2.	VECTORS : Vectors are same as dynamic arrays with the ability to resize itself automatically when an element is inserted or deleted
3.	MAP: Maps are associative containers that store elements in a mapped fashion. Each element has a key value and a mapped value. No two mapped values can have same key values.
4.	PAIR : The pair container is a simple container defined in <utility> header consisting of two data elements or objects.
5.	DJIKSTRA ALGORITHM:  is an algorithm for finding the shortest paths between nodes in a graph, which may represent, for example, road networks. It was conceived by computer scientist Edsger W. Dijkstra in 1956 
6.	Language Used :   C++ 14.0

DATASET DESCRIPTION : Delhi Metro Map Stations www.delhimetrorail.info/delhi-metro-stations , www.mapsofindia.com/maps/delhi/delhi-metro-map.html
Input Code for Metro Database: https://pastebin.com/4VHbkZHk

DESIGN & BASIC IMPLEMENTATION OF THE PROJECT: 

INPUT: 

A ->(B, 1) (C, 4) (D,7) 
B->(A, 1) (C, 1) 
C->(A, 4) (B, 1) (D, 2) 
It means that distance from A to B is 1 and A to C is 4 and A to D is 7 
Similarly in the next line the distance from B to A is 1 and from B to C is 1 and simultaneously in the next line distance from C to A is 4 and from C to B is 1 and from C to D is 2

Implementation
Using make_graph() function ,We have created a graph. The inputs have been taken from “djikstra.txt” file which makes our code user friendly. User can paste the inputs from any source and graph will be generated on its own. 
We have implemented graphs using adjacency list .Throughout the program we have used concepts of hashing to map the values of different places with their destination. 
Dijkstra() :- This is our main function ,which provides the shortest route from source to all other destinations. This is based on the famous djikstra’s algorithm which calculates the shortest path between given pair of nodes.
Kthsmallest(src,k) : This function calculates all nodes which are at various distance from given source and returns the kth smallest among them.
This can be used if we want to survey a particular area and we need to cover some places at once.
calculateCost(src,destination) : It calculates the cost incurred in travelling from source to destination based on some simple if else condition.


 

 
 
 
 
 
 

