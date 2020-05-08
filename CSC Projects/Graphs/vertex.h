#ifndef VERTEX_H
#define VERTEX_H

struct Vertex;
struct Arc;
#include <iostream>

struct Vertex
{
    char data;
    Vertex* vNext;
    Arc* aHead;
};
struct Arc
{
    Vertex* dest; //short for destination
    Arc* aNext;
};

void addVertex(Vertex*& vHead, char label);
void remVertex(Vertex*& vHead, char label);
void addArc(Vertex* vHead, char from, char to);
void remArc(Vertex* vHead, char from, char to);
Vertex* findVertex(Vertex* vHead, char key);
void printGraph(Vertex* vHead);
void remArc_Vert(Vertex* vHead, char from, char to);
#endif