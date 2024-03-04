//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Tomáš Lajda <xlajdat00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"


Graph::Graph(){}

Graph::~Graph(){}

std::vector<Node*> Graph::nodes() {
    return nodes_;
}

std::vector<Edge> Graph::edges() const{
    return edges_;
}

Node* Graph::addNode(size_t nodeId) {
    for (Node* node_ : nodes_) {
        if(node_->id == nodeId){
            return nullptr;
        }
    }

    Node* newNode = new Node{nodeId, 0};
    nodes_.push_back(newNode);

    return newNode;
}

bool Graph::addEdge(const Edge& edge){
    if(edge.a == edge.b) {
        return false;
    }

    for (Edge edge_ : edges_) {
        if(edge_ == edge){
            return false;
        }
    }

    addNode(edge.a);
    addNode(edge.b);

    Node* node_A = getNode(edge.a);
    Node* node_B = getNode(edge.b);



    node_A->neigbours.push_back(node_B);
    node_B->neigbours.push_back(node_A);
    
    edges_.push_back(edge);

    return true;
}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for(Edge edge : edges) {
        addEdge(edge);
    }
}

Node* Graph::getNode(size_t nodeId){
    for (Node* node_ : nodes_) {
        if(node_->id == nodeId){
            return node_;
        }
    }

    return nullptr;
}

bool Graph::containsEdge(const Edge& edge) const{
    for (Edge edge_ : edges_) {
        if(edge_ == edge){
            return true;
        }
    }

    return false;
}

void Graph::removeNode(size_t nodeId){
}

void Graph::removeEdge(const Edge& edge){
}

size_t Graph::nodeCount() const{
    return nodes_.size();
}

size_t Graph::edgeCount() const{
    return edges_.size();
}

size_t Graph::nodeDegree(size_t nodeId) const{
    const Node *node_ = const_cast<Graph*>(this)->getNode(nodeId);

    if (node_ == nullptr) {
        throw std::out_of_range("Node doesn't exist");
    }
    
    return node_->neigbours.size();
}

size_t Graph::graphDegree() const{
    
    return ;
}

void Graph::coloring(){
}

void Graph::clear() {
}

/*** Konec souboru tdd_code.cpp ***/

