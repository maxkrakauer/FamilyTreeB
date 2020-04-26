#include <iostream>
#include "string.h"
#include "FamilyTree.hpp"
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <exception>
#include <bits/stdc++.h>
using namespace std;
using namespace family;


bool _male;
int _gens=0;
bool _found=false;


/*
struct noRelation : std::exception {
   string what()  noexcept 
  {return "unrelated\n";}
};
*/



    node::node(string name){
         std::printf("start of node, adding name: %s\n", name.c_str());
        _name=name;
        std::printf("end of node, adding name: %s\n", name.c_str());
    }

    void node::setFather(string father){
         std::printf("start of setfather, setting name: %s\n", father.c_str());
        _father=new node(father);
    }

    void node::setMother(string mother){
         std::printf("start of setfather, setting name: %s\n", mother.c_str());
        if(_mother==NULL){
            _mother=new node(mother);
        }
        _mother->_name=mother;
   }

    
    node* node::findNode(int gens,bool male){
        std::printf("start of node::findNode(string name, int gens), gens: %d\n", gens);
        if(gens==0)
        return NULL;
        else gens=gens-1;
        if(gens==0 && _male==male){
            return this;
        }
        else{
            if(_father!=NULL){
             node* person=_father->findNode(gens,true);
             if(person!=NULL)
             return person;
            }
            if(_mother!=NULL)
            return _mother->findNode(gens,false);
        }
        return NULL;
    }


node* node::findNode(string name){
    std::printf("start of node::findNode(string name), finding name: %s\n", name.c_str());
        if(strcmp(name.c_str(),_name.c_str())==0){
            return this;
        }
        else{
            if(_father!=NULL){
             node* person=_father->findNode(name);
             if(person!=NULL)
             return person;
            }
            if(_mother!=NULL){
             node* person=_mother->findNode(name);
             if(person!=NULL)
             return person;
            }
            
        }
        return NULL;
}

    

void tokenize(string str)
{
     std::printf("start of tokensize,  name: %s\n", str.c_str());
    const char delim='-';
    vector<string> out;
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
//if(strcmp(name.c_str(),_father->_name.c_str())==0){
    for(int i=0; i<out.size()-1;i++){
        if(strcmp(out[i].c_str(),"grand")==0)
        throw "invalid relation";
    }

    if(out.size()==1){
         if(strcmp(out[0].c_str(),"father")!=0 && strcmp(out[0].c_str(),"mother")!=0 &&
         strcmp(out[0].c_str(),"grandfather")!=0 && strcmp(out[0].c_str(),"grandmother")!=0)
         throw "invalid relation";
    }

    if(out.size()>1){
        int len=out.size()-1;
        if(strcmp(out[len].c_str(),"grandfather")!=0 && strcmp(out[len].c_str(),"grandmother")!=0)
        throw "invalid relation";
    }

    _gens=out.size();
    printf("_gens at first is %d\n",_gens);
    
    /*
    if(strcmp("mother",out[out.size()-1]) || 
    strcmp("grandmother",out[out.size()-1]))
    _male=false;
    */
   if(out[out.size()-1].compare("mother")==0 || out[out.size()-1].compare("grandmother")==0){
   _male=false;
   std::printf("male is false\n");
   }
    else{
        _male=true;
        std::printf("males is true\n");
    }
    if(out[out.size()-1].compare("grandmother")==0||
    out[out.size()-1].compare("grandfather")==0)
    _gens++;

    std::printf("gens is: %d\n",_gens);
}

Tree::Tree(string name){
     std::printf("start of Tree,  name: %s\n", name.c_str());
    _root=new node(name);
}


node* Tree::findNode(string name){
     std::printf("start of Tree::findnode(string name), finding name: %s\n", name.c_str());
        if(strcmp(name.c_str(),_root->_name.c_str())==0){
            return NULL;
        }
        else{

        }
        return _root;
    }

Tree& Tree::addFather(string name, string father){
    std::printf("start of addfather, adding name: %s\n", name.c_str());
    node * node=_root->findNode(name);
    if(node!=NULL && node->_father==NULL)
    node->setFather(father);
    else if(node!=NULL && node->_father!=NULL)
    throw "already has father";
    else throw "no"+name;
    return *this;
}

Tree& Tree::addMother(string name, string mother){
    std::printf("start of addfather, adding name: %s\n", name.c_str());
    node * node=_root->findNode(name);
    if(node!=NULL && node->_mother==NULL)
    node->setMother(mother);
    else if(node!=NULL && node->_mother!=NULL)
    throw "already has mother";
    else throw "no"+name;
    return *this;
    
}

string Tree::find(string relation){
    std::printf("start of tree::find,  name: %s\n",relation.c_str());
    tokenize(relation);
    int gens=_gens;
    node* node;
    if(gens==1){
        if(_male==true && _root->_father!=NULL){
            node=_root->_father->findNode(1,true);
            return node->_name;
        }
        else if(_male==false && _root->_mother!=NULL){
            node=_root->_mother->findNode(1,false);
            return node->_name;
        }
    }
    else if(gens>1){
        if(_root->_father!=NULL){
            node=_root->_father->findNode(gens,true);
            if(node!=NULL)
            return node->_name; 
        }
        if(_root->_mother!=NULL){
            node=_root->_mother->findNode(gens,false);
            if(node!=NULL)
            return node->_name; 
        }
    }
    printf("throwing no such relation\n");
    throw "no such relation";

}


string ancestor(int gens,bool male){
     std::printf("start of ancestor,  name: \n");
    string str="";
    for(int i=1; i<gens-1; i++){
        str="great-"+str;
    }
    if(gens>1)
    str+="grand";
    if(male)
    str+="father";
    else
    {
        str+="mother";
    }
    return str;
}


string Tree::relation(string name){
     if(strcmp(name.c_str(),_root->_name.c_str())==0)
        return "me";

    std::printf("start of tree::relation,  name: %s\n", name.c_str());
    if(_root!=NULL && _root->_father!=NULL){
    string pat=_root->_father->relation(name,1,true);
    if(strcmp(pat.c_str(),"")!=0){
    printf("the father's side");
    return pat;
    }
    }

    if(_root!=NULL && _root->_mother!=NULL){
    string mot=_root->_mother->relation(name,1,false);
    if(strcmp(mot.c_str(),"")!=0){
    printf("the mother's side");
    return mot;
    }
    printf("not found\n");
    return "unrelated";
}
return "unrelated";
}

string node::relation(string name, int gens,bool male){
    std::printf("start of node::relation,  name: %s and gens is:%d\n", name.c_str(),gens);
    if(strcmp(name.c_str(),_name.c_str())==0)
        return ancestor(gens,male);

    else{
    gens++;
    if(_father!=NULL){
    string pat=_father->relation(name,gens,true);
    if(strcmp(pat.c_str(),"")!=0)
    return pat;
    }
    
    if(_mother!=NULL){
    string mot=_mother->relation(name,gens,false);
    if(strcmp(mot.c_str(),"")!=0)
    return mot;
    }
    }
    return ""; 
}

string node::display(){
    std::printf("start of node::display \n");
    string str=_name+"\n";
    if(_father!=NULL){
        //str=str+_name+"'s father is: "+_father->display()+"\n";
        string father=_father->display();
        printf("%s's father's name is: %s\n",_name.c_str(),father.c_str());
    }
    if(_mother!=NULL){
        //str=str+_name+"'s mother is: "+_mother->display()+"\n";
        string mother=_mother->display();
        printf("%s's mother's name is: %s\n",_name.c_str(),mother.c_str());
    }
    return _name;
}

void Tree::display(){
    std::printf("start of tree::display \n");
    string str="";
    if(_root!=NULL){
        printf("the descendant's name is: %s\n ",_root->_name.c_str());
        //str=str+"the descendant's name is: "+_root->_name;
        if(_root->_father!=NULL){
           //str=str+"\n"+_root->_name+"'s father is: "
           //+_root->_father->display()+"\n"; 
           string father=_root->_father->display();
           printf("%s's father's name is: %s\n",_root->_name.c_str(),father.c_str());
        }
        if(_root->_mother!=NULL){
           //str=str+"\n"+_root->_name+"'s mother is: "
           //+_root->_mother->display()+"\n"; 
           string mother=_root->_mother->display();
           printf("%s's mother's name is: %s\n",_root->_name.c_str(),mother.c_str());
        }
    }
}

void node::deleteAll(){
    printf("start of delete all\n");
    if(_father!=NULL){
        _father->deleteAll();
    }
    if(_mother!=NULL){
        _mother->deleteAll();
    }
    printf("before delete all's delete(this)\n");
    //delete(this);
    if(_father!=NULL){
    delete(_father);
    _father=NULL;
    }
    if(_mother!=NULL){
    delete(_mother);
    _mother=NULL;
    }
    printf("after delete all's delete(this)\n");
}

void node::remove(string name){
    std::printf("start of node::remove,  name: %s\n", name.c_str());
    if(_father!=NULL){
        if(strcmp(name.c_str(),_father->_name.c_str())==0){
            _found=true;
            printf("deleting node with name: %s\n",_father->_name.c_str());
            _father->deleteAll();
            printf("before delete(father)\n");
            //delete(_father);
            printf("after delete(father)\n");
            //_father=NULL;
            delete(_father);
            _father=NULL;
        }
        else
        _father->remove(name);
    }
    if(_mother!=NULL){
        if(strcmp(name.c_str(),_mother->_name.c_str())==0){
            _found=true;
            printf("deleting node with name: %s\n",_mother->_name.c_str());
            _mother->deleteAll();
            delete(_mother);
            _mother=NULL;
            //_mother=NULL;
        }
        else
        _mother->remove(name);
    }
}

void Tree::remove(string name){
    _found=false;
    if(strcmp(name.c_str(),_root->_name.c_str())==0){
        _found=true;
        throw "trying to remove descendant";
    }
     std::printf("start of tree::remove,  name: %s\n", name.c_str());
     if(strcmp(name.c_str(),_root->_name.c_str())==0){
         printf("delete root\n");
         _found=true;
        _root->deleteAll();
        delete(this);
     }
     else{
     if(_root->_father!=NULL){
         if(strcmp(name.c_str(),_root->_father->_name.c_str())==0){
             _found=true;
             _root->_father->deleteAll();
             printf("deleting father\n");
            delete(_root->_father);
            _root->_father=NULL;
         }
         else _root->_father->remove(name);
     }
     if(_root->_mother!=NULL){
         if(strcmp(name.c_str(),_root->_mother->_name.c_str())==0){
             _found=true;
             _root->_mother->deleteAll();
             printf("deleting mother\n");
             delete(_root->_mother);
             _root->_mother=NULL;
         }
         else _root->_mother->remove(name);
     }
     }
     if(_found==false)
     throw "removing a non-existant person";
}




