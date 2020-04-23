#include <iostream>
#include "string.h"
using namespace std;

 class node{
public:
    string _name;
    node* _father;
    node* _mother;
public:
    node(string name);
public:
    void setFather(string father);

    void setMother(string mother);
    
    node* findNode(int gens,bool male);

    node* findNode(string name);

    string relation(string name, int gens,bool male);

   string display();

    void remove(string name);

    void deleteAll();
    
};


namespace family{

    class Tree{
    public:
        node* _root;
    public:
    Tree(string name);
    
    public:

    node* findNode(string name);

    Tree& addFather(string name, string father);

    Tree& addMother(string name, string mother);

    void display();

    string relation(string name);

    string find(string name);

    void remove(string name);

    };
};