#include "vertex.h"

using namespace std;



void addVertex(Vertex*& vHead, char label)
{
    Vertex* newVertex = new Vertex;
    newVertex->data = label;
    newVertex->vNext = nullptr;
    newVertex->aHead = nullptr;

    if (vHead == nullptr)
    {
        vHead = newVertex;
        return;
    }
    if (vHead->data > label)
    {
        newVertex->vNext = vHead;
        vHead = newVertex;
        return;
    }

    Vertex* curVertex = vHead;

    while (curVertex->vNext != nullptr && curVertex->vNext->data < label)
    {
        curVertex = curVertex->vNext;

    }
    //Determine if curVertex is null or not
    if (curVertex->vNext == nullptr)
    {
        curVertex->vNext = newVertex;
    }

    else
    {
        newVertex->vNext = curVertex->vNext;
        curVertex->vNext = newVertex;

    }

    
}

//Homework Assignment.
    //Remove all incoming arcs as well as 
    // vertex itself and its outgoing arcs.
//Label is vertex that needs to be deleted.
void remVertex(Vertex*& vHead, char label)
{
    Vertex* curVer = vHead;
    Vertex* dltVer;
    Arc* currArc;
    Arc* dltArc;
    dltVer = findVertex(vHead, label);
    if (dltVer == nullptr)
    {
        cout << "Cannot find vertex " << label << " to delete." << endl;
        return;
    }
    //Go through all vertices delete incoming arcs.
    while (curVer != nullptr)
    {
           remArc_Vert(vHead, curVer->data, label);
           curVer= curVer->vNext;
    }
    
    //Need to take previous vertex connect it to the remaining vertex.

    curVer = vHead;
    currArc = dltVer->aHead;
    char to = currArc->dest->data;
    while (currArc != nullptr)
    {
        char to = currArc->dest->data;

        remArc(vHead, label, to);
        currArc = dltVer->aHead;
    }
    
    
    
    while (curVer->vNext != dltVer)
    {
        curVer = curVer->vNext;
    }
    //curVer contains previous to dlt vertex.
    curVer->vNext = dltVer->vNext;
    // dlt vertex is not in the list of vertices.

    delete dltVer;
    return;

}

void addArc(Vertex* vHead, char from, char to)
{
    //1st step: traverse to "from" vertex.
    Vertex* fromVer = vHead;
    while (fromVer != nullptr && fromVer->data< from)
    {
        fromVer = fromVer->vNext;

    }

    if (fromVer == nullptr||fromVer->data > from)
    {
        cout << "Starting vertex is not in the list.";
        return;
    }
    Vertex* toVer = vHead;

    while (toVer != nullptr && toVer->data < to)
    {
        toVer = toVer->vNext;

    }

    if (toVer == nullptr || toVer->data > to)
    {
        cout << "Destination vertex is not in the list.";
        return;
    }
    Arc* newArc = new Arc;
    newArc->dest = toVer;
    newArc->aNext = nullptr;


    if (fromVer->aHead == nullptr)
    {
        fromVer->aHead = newArc;
        return;
    }
    if (fromVer->aHead->dest->data > to)
    {
        newArc->aNext = fromVer->aHead;
        fromVer->aHead = newArc;
        return;
    }

    Arc* curArc = fromVer->aHead;
    while (curArc->aNext != nullptr && curArc->aNext->dest->data < to)
    {
        curArc = curArc->aNext;

    }
    //Determine if curArc is null or not
    if (curArc->aNext == nullptr)
    {
        curArc->aNext = newArc;
    }

    else
    {
        newArc->aNext = curArc->aNext;
        curArc->aNext = newArc;

    }
}

void remArc(Vertex* vHead, char from, char to)
{
    Vertex* fromVer = vHead;

    //Finding Vertex. Function
    while (fromVer != nullptr && fromVer->data < from)
    {
        fromVer = fromVer->vNext;

    }

    if (fromVer == nullptr || fromVer->data > from)
    {
        cout << "Starting vertex is not in the list." << endl;;
        return;
    }
    //
    Arc* curArc = fromVer->aHead;

    if (curArc == nullptr)
    {
        cout << "Arc head is null. There is no connection between vertices." << endl;
        return;
    }
    if (curArc->dest->data == to)
    {
        Arc* dltPtr = curArc;
        fromVer->aHead = curArc->aNext;
        delete dltPtr;
        return;
    }
    while (curArc->aNext != nullptr && curArc->aNext->dest->data < to)
    {
        curArc = curArc->aNext;

    }
    if (curArc->aNext == nullptr || curArc->aNext->dest->data > to)
    {
        cout << "There is no connection between vertices." << endl;
        return;
    }
    else
    {
        Arc* dltPtr;
        dltPtr = curArc->aNext;
        curArc->aNext = curArc->aNext->aNext;
        delete dltPtr;

    }
}

Vertex* findVertex(Vertex* vHead, char key)
{
    Vertex* currVer = vHead;
    //look through vertices
    while (currVer != nullptr)
    {
        //Found vertex
        if (currVer->data == key)
            return currVer;
        currVer = currVer->vNext;
    }
    //Not found.
    return nullptr;
}

void printGraph(Vertex* vHead)
{
    //Just implement vert LL to start with.
    Vertex* currentVertex = vHead;
    Arc* curArc;

    while (currentVertex != nullptr)
    {
        cout << currentVertex->data;
        if (currentVertex->aHead != nullptr)
        {
            cout <<  " -> ";

        }
        curArc = currentVertex->aHead;
        while (curArc != nullptr)
        {
            cout << curArc->dest->data;
            if (curArc->aNext != nullptr)
            {
                cout << " -> ";
            }
            curArc = curArc->aNext;
        }
        currentVertex = currentVertex->vNext;
        cout << endl;
    }
    cout << endl;
}

void remArc_Vert(Vertex* vHead, char from, char to)
{
    Vertex* fromVer = vHead;

    //Finding Vertex. Function
    while (fromVer != nullptr && fromVer->data < from)
    {
        fromVer = fromVer->vNext;

    }

    if (fromVer == nullptr || fromVer->data > from)
    {
        return;
    }
    //
    Arc* curArc = fromVer->aHead;

    if (curArc == nullptr)
    {
        return;
    }
    if (curArc->dest->data == to)
    {
        Arc* dltPtr = curArc;
        fromVer->aHead = curArc->aNext;
        delete dltPtr;
        return;
    }
    while (curArc->aNext != nullptr && curArc->aNext->dest->data < to)
    {
        curArc = curArc->aNext;

    }
    if (curArc->aNext == nullptr || curArc->aNext->dest->data > to)
    {
        return;
    }
    else
    {
        Arc* dltPtr;
        dltPtr = curArc->aNext;
        curArc->aNext = curArc->aNext->aNext;
        delete dltPtr;

    }
}
