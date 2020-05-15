#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Vertex.h"
#include "Utils.h"


#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

/**
 * @file Graph.h
 * @brief File containing Graph class responsible for storing the graph of the city 
 */ 
class Graph {
private:
    vector<Vertex *> vertexSet;     /** vertex set */
    double **dist = nullptr; 		/** dist */
    int **pred = nullptr; 			/** path */ 

    friend class FloydStorage;
public:
    ~Graph();

    vector<Vertex *> getVertexSet();
    Vertex *findVertex(const ulli &in) const;
	/**
	 * @brief sorts the vertices according to the id's so that it can perform binary search to find a vertex Id 
	 */ 
    void sortVertexSet();                   
    bool addVertex(const ulli &in);
    bool addVertex(const ulli &in, const double lon, const double lat);
    /*
     * @brief Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * @return true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const ulli &sourc, const ulli &dest, double w, const string &streetName = "");
	/**
	 * @brief Finds the index of an ID in the vertexSet
	 * @param in It's the id of the vertex 
	 */ 
    inline ulli findVertexIdx(const ulli &in) const;

    /**
     * Before the execution of the proper algorithm of floyd warshall, it will check if matrix is not saved in a specific file
     * @param cityName Each city has a file called matrix_<cityName>_dest and matrix_<cityName>_pred
     */
    void handleFloydWarshall(const string& cityName);

    /**
     * @brief Application of the floydWarshall algorithm 
     */
    void floydWarshallShortestPath();
	
	/**
	 * @brief Get the path 
	 * @return Returns a vector containing the ID's of the vertexes to pass by 
	 **/ 
    vector<ulli> getFloydWarshallPath(const ulli &origin, const ulli &dest) const;


    /**
     * Calculates the path given the points of interest using the greedy strategy
     * @param origin point where the person is
     * @param poi list of the id's of the points of interest
     * @return visiting order of the points of interest
     */
    vector<ulli> trajectoryOrder(ulli origin, vector<ulli> &poi);

    /**
     * Auxiliar function to trajectoryPath. It gets the next poi to be visited
     * @param origin actual position
     * @param poi poi's left to visit
     * @return id of the next poi to be visited
     */
    ulli nextPoi(const ulli &origin, vector<ulli> &poi, vector<bool> visited);

};

#endif //GRAPH_H
