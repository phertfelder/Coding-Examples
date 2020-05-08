#include "vertex.h"

using namespace std;

int main()
{
    Vertex* gHead=nullptr; //The entry point of the graph.

    addVertex(gHead, 'A');
    addVertex(gHead, 'B');
    addVertex(gHead, 'C');
    addVertex(gHead, 'D');
    addVertex(gHead, 'E');
    addVertex(gHead, 'F');

    addArc(gHead, 'A', 'B');
    addArc(gHead, 'B', 'C');
    addArc(gHead, 'B', 'E');
    addArc(gHead, 'C', 'E');
    addArc(gHead, 'C', 'D');
    addArc(gHead, 'E', 'D');
    addArc(gHead, 'E', 'F');
    addArc(gHead, 'D', 'C');
    addArc(gHead, 'D', 'E');



    printGraph(gHead);

   
    //remArc(gHead, 'E', 'F');
    //remArc(gHead, 'C', 'A');

    printGraph(gHead);

    remVertex(gHead, 'G');
    printGraph(gHead);

    return 0;
}