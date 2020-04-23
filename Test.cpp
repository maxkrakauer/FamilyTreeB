

#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>
using namespace std;
using namespace family;

#include <iostream>
#include "string.h"
#include <stdexcept>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <exception>
#include <bits/stdc++.h>


TEST_CASE("Family of Jim") {
    Tree t("jim");
    CHECK(t.relation("jim") == string("me"));
    CHECK_THROWS(t.find("father"));
    t.addFather("jim","dan");
    t.addFather("dan","tim");
    t.addMother("tim","dana");
    CHECK(t.relation("dan") == string("father"));
    CHECK(t.relation("tim") == string("grandfather"));
    CHECK(t.relation("dana") == string("great-grandmother"));
    CHECK(t.relation("netanel")==string("unrelated"));
}

TEST_CASE("Family of robert") {
    Tree t("robert");
    t.addFather("robert","tommy");
    t.remove("tommy");
    CHECK(t.relation("tommy") == string("unrelated"));
    t.addFather("robert","joe");
    t.addFather("robert","thomas");
    t.addMother("robert","tommy");
    CHECK(t.find("mother") == string("tommy"));
    CHECK(t.relation("joe") == string("unrelated"));
    CHECK(t.find("father") == string("thomas"));
    t.display();
    //t.remove("robert");
}

TEST_CASE("Family of thomas") {
    Tree t("thomas");
    t.addFather("thomas","james");
    CHECK(t.find("father") == string("james"));
    t.addFather("james","nate");
    CHECK(t.find("grandfather") == string("nate"));
    t.addFather("nate","don");
    CHECK(t.find("great-grandfather") == string("don"));
    t.addFather("don","ben");
    CHECK(t.find("great-great-grandfather") == string("ben"));
    t.addFather("ben","jon");
    CHECK(t.find("great-great-great-grandfather") == string("jon"));
    t.addFather("jon","sam");
    CHECK(t.find("great-great-great-great-grandfather") == string("sam"));

    t.remove("sam");
    CHECK_THROWS(t.addFather("sam","moshe"));
    CHECK(t.relation("sam") == string("unrelated"));
    t.addMother("jon","jane");
    t.remove("jon");
    CHECK_THROWS(t.addFather("jane","moshe"));
    CHECK(t.find("great-great-grandfather") == string("ben"));



    t.addFather("ben","sam");
    CHECK(t.relation("sam") == string("great-great-great-grandfather"));

    t.display();

    t.remove("ben");



    CHECK(t.relation("sam") == string("unrelated"));
    CHECK(t.relation("ben") == string("unrelated"));


    t.addMother("don","miriam");
    t.addFather("miriam","mort");
    t.addMother("miriam","tova");
    t.remove("miriam");
    CHECK(t.relation("mort") == string("unrelated"));
    CHECK(t.relation("tova") == string("unrelated"));

    t.remove("don");
    CHECK(t.relation("nate") == string("grandfather"));

    
}

TEST_CASE("FAMILY OF john- a case in which multiple users with the same name") {

}

TEST_CASE("Family of jack- a case of incest"){
    
    Tree t("jack");

    t.addFather("jack","mat");
    t.addMother("jack","deb");

    t.addFather("mat","tod");
    t.addMother("mat","sarah");
    t.addMother("deb","sarah");
    t.addFather("deb","tom");

    t.display();
 
    CHECK(t.relation("sarah")==string("grandmother"));
    CHECK(t.relation("tod")==string("grandfather"));
    CHECK(t.relation("tom")==string("grandfather"));

    t.remove("tod");

    CHECK(t.relation("tod")==string("unrelated"));

    CHECK(t.find("grandmother")==string("sarah"));
    CHECK(t.find("grandfather")==string("tom"));
    
    t.remove("mat");
  
    CHECK(t.relation("sarah")==string("grandmother"));   //one sarah was removed. There should still be one left

}

    