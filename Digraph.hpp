// Digraph.hpp
//
// ICS 46 Spring 2021
// Project #5: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>



//// Any comments with four forward slashes will be mine


// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.
template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.
template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    ////
    ////ALL EDGES
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    ////
    //// ONLY OUTGOING EDGES
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.

    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> digraphMap;


    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
};




//// Default Constructor
template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{
    //// digraphMap variable is already initialized to be empty
}



//// Copy Constructor (separate copies from source)
template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
    : digraphMap{d.digraphMap}
{
}



//// Move Constructor
template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
{
    digraphMap.clear();
    std::swap(digraphMap,d.digraphMap);
}


//// Deconstructor
template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
}



//// Self Assignment Operator
template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    if (this != &d)
    {
        digraphMap.clear();
        digraphMap = d.digraphMap;
    }
    return *this;
}



//// Move Assignment Operator
template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    if (this != &d)
    {
        digraphMap.clear();
        std::swap(digraphMap,d.digraphMap);
    }
    return *this;
}


//// Returns a vector of all the vertices
template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    //// If map is empty, return an empty vector.
    if (digraphMap.size() == 0)
    {
        return std::vector<int>{};
    }
    //// If map is NOT empty, for loop through all the pairs to get
    //// the key values to store into a new vector.
    else
    {
        std::vector<int> allVertices{};

        for (auto &vertex : digraphMap)
        {
            //// not modifying vertex reference so can use "."
            allVertices.push_back(vertex.first);
        }
        return allVertices;
    }
}



//// Returns vector of all edges (from and to)
template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    if (digraphMap.size() == 0)
    {
        return std::vector<std::pair<int, int>>{};
    }
    else
    {
        std::vector<std::pair<int, int>> allEdges;

        for (auto &vertex : digraphMap)
        {
            //// &vertex.second.edges is the list of edges in DigraphVertex
            //// &edge is each DigraphEdge within the list
            for (auto &&edge : vertex.second.edges) /// might need &&
            {
                int fromV = edge.fromVertex;  
                int toV = edge.toVertex; //  might need to use ->

                std::pair<int, int> edgePair(fromV, toV);

                allEdges.push_back(edgePair);
            }
        }
        return allEdges;
    }
}



//// Return all outgoing edges from specific vertex
template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    try
    {
        if (digraphMap.find(vertex)->first != vertex)
        {
            throw DigraphException{"Vertex does NOT exist."};
        }
        // for (auto &v : digraphMap)
        // {
        //     if (v.first == vertex)

        // }
        else
        {
            std::vector<std::pair<int, int>> allEdges{};

            //// only get outgoing edges from specific vertex
            for (auto &edge : digraphMap.find(vertex)->second.edges)
            {
                int fromV = edge.fromVertex;  
                int toV = edge.toVertex; //  might need to use ->

                std::pair<int, int> edgePair(fromV, toV);

                allEdges.push_back(edgePair);
            }
            return allEdges;
        }
        throw;
    }
    catch(...)
    {
        throw DigraphException{"Vertex does NOT exist."};
    }
}



template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    try
    {
        if (digraphMap.find(vertex)->first != vertex)
        {
            throw DigraphException{"Vertex not found."};
        }
        else
        {
            return digraphMap.find(vertex)->second.vinfo;

        }
        ////return digraphMap.find(vertex)->second.vinfo;
        throw;
    }
    catch(...)
    {
        throw DigraphException{"Vertex not found."};
    }
}



template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    try
    {
        if (digraphMap.count(fromVertex) == 0 || digraphMap.count(toVertex) == 0)
        {
             throw DigraphException{"Vertices or edge does not exist."};
        }
        else
        {
            //// Check edge existence
            if (digraphMap.find(fromVertex)->second.edges.size() == 0)
            {
                throw DigraphException{"Vertices or edge does not exist."};
            }
            else
            {
                for (auto &edge : digraphMap.find(fromVertex)->second.edges)
                {
                    if (edge.fromVertex == fromVertex && edge.toVertex == toVertex)
                    {
                        return edge.einfo;
                    }
                }
            }
            throw DigraphException{"Vertices or edge does not exist."};
        }
        throw DigraphException{"Vertices or edge does not exist."};
    }
    catch(...)
    {
        throw DigraphException{"Vertices or edge does not exist."};
    }
}



template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    try
    {
        //// Check to see if vertex already exists in digraphMap and if so,
        //// throw an exception.
        if (digraphMap.find(vertex)->first == vertex)
        {
            throw;
        }

        //// If vertex does not exist in digraphMap, then add it to the map
        //// with a new struct.
        DigraphVertex<VertexInfo, EdgeInfo> newStruct;
        newStruct.vinfo = vinfo;

        digraphMap.insert({vertex, newStruct});
    }
    catch(...)
    {
        throw DigraphException{"Vertex already exists."};
    }
}



template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    //// Use .find() memember function that will throw an exception if neither the from
    //// or to vertices exist OR if the edge within the graph already exists.
    try
    {
        //// Check vertices' existents before edge
        if (digraphMap.find(fromVertex)->first == fromVertex && digraphMap.find(toVertex)->first == toVertex)
        {
            //// Check edge existence
            if (digraphMap.find(fromVertex)->second.edges.size() == 0)
            {
                //// Initialize a new edge if list is empty and add it
                DigraphEdge<EdgeInfo> newEdge{fromVertex, toVertex, einfo};
                digraphMap.find(fromVertex)->second.edges.push_back(newEdge);
            }
            else
            {
                //// Check each edge struct in the list to see if the edge already exists
                for (auto &edge : digraphMap.find(fromVertex)->second.edges)
                {
                    if (edge.fromVertex == fromVertex && edge.toVertex == toVertex)
                    {
                        throw DigraphException{"Vertex may does not exist or edge already exists."};

                    }
                }
                //// If the throw was not activated then edge does NOT already exist so insert it into the list
                DigraphEdge<EdgeInfo> newEdge{fromVertex, toVertex, einfo};
                digraphMap.find(fromVertex)->second.edges.push_back(newEdge);
            }
        }
        else
        {
            throw DigraphException{"Vertex may does not exist or edge already exists."};
        }
    }
    catch(...)
    {
        throw DigraphException{"Vertex may does not exist or edge already exists."};
    }
}



template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    try
    {
        if (digraphMap.count(vertex) == 0)
        {
            throw DigraphException{"Vertex already exists."};
        }
        else
        {
            //// Erases the vertex itself from the map and all of its outgoing edges.
            // digraphMap.erase(vertex);
            
            

            digraphMap.erase(vertex);
            //// Remove all incoming edges in other vertices so check toVertex
            for (auto v = digraphMap.begin(); v != digraphMap.begin(); v++)
            {
                std::list<DigraphEdge<EdgeInfo>> edgesWithoutVertex;
                //// edges are the structs
                for (struct DigraphEdge<EdgeInfo> &edge : v->second.edges)
                {
                    if (edge.toVertex != vertex)
                    {
                        edgesWithoutVertex.push_back(edge);
                    }
                }
                v->second.edges = edgesWithoutVertex;
            }

            return;
        }        
    }
    catch(...)
    {
        throw DigraphException{"Vertex already exists."};
    }
}


//// Remove specific edge within "fromVertex"
template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    try
    {
        if (digraphMap.count(fromVertex) == 0 || digraphMap.count(toVertex) == 0)
        {
            throw DigraphException{"Vertex already exists."};
        }
        else
        {
            std::list<DigraphEdge<EdgeInfo>> edgesWithoutVertex;
            //// edges are the structs
            for (struct DigraphEdge<EdgeInfo> &edge : digraphMap.find(fromVertex)->second.edges)
            {
                //// Don't add the edge we want to remove
                if (edge.fromVertex != fromVertex && edge.fromVertex != toVertex)
                {
                    edgesWithoutVertex.push_back(edge);
                }
            }

            //// Check if edge never existed in the first place
            int originalSize = digraphMap.find(fromVertex)->second.edges.size();
            int newSize = edgesWithoutVertex.size();
            
            if (originalSize == newSize)
            {
                throw DigraphException{"At least one vertex is not found OR edge does not exist."};
            }
            else
            {
               digraphMap.find(fromVertex)->second.edges = edgesWithoutVertex;
            }
        }
    }
    catch(...)
    {
        throw DigraphException{"At least one vertex is not found OR edge does not exist."};
    }
}


//// Returns the amount of vertices in the map
template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    if (digraphMap.size() == 0)
    {
        return 0;
    }
    else
    {
        return digraphMap.size();
    }
}


//// Returns the total amount of all edges across all vertices
template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    if (digraphMap.empty() == true)
    {
        return 0;
    }
    else
    {
        int totalEdgeCount = 0;
        for (auto &vertex : digraphMap)
        {
            totalEdgeCount += vertex.second.edges.size();
        }
        return totalEdgeCount;
    }
}


//// Returns total amount of outgoing edges for a specific vertex
template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    try
    {
        return digraphMap.find(vertex)->second.edges.size();   
    }
    catch(...)
    {
        throw DigraphException{"Vertex does not exist."};
    }
}



template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    return false;
}



template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
    return std::map<int, int>{};
}



#endif

