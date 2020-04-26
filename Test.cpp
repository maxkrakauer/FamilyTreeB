

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

TEST_CASE("FAMILY OF john- a case in which we keep changing the descendant's parents") {
    Tree t("john");
    t.addFather("john","rob");
    t.addMother("john","deb");
    CHECK(t.relation("rob")==string("father"));
    CHECK(t.relation("deb")==string("mother"));
    
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


TEST_CASE("FAMILY OF jane- a case in which we remove all female ancestors") {
    Tree t("jane");
    t.addFather("jane","dan");
    t.addMother("jane","deb");
    t.addFather("dan","james");
    t.addMother("dan","sarah");
    t.addFather("deb","abe");
    t.addMother("deb","leah");

    CHECK(t.relation("jane")==string("me"));
    CHECK(t.relation("dan")==string("father"));
    CHECK(t.relation("deb")==string("mother"));
    CHECK(t.relation("james")==string("grandfather"));
    CHECK(t.relation("sarah")==string("grandmother"));
    CHECK(t.relation("abe")==string("grandfather"));
    CHECK(t.relation("leah")==string("grandmother"));

    t.remove("sarah");
    t.remove("deb");

    CHECK(t.relation("jane")==string("me"));
    CHECK(t.relation("dan")==string("father"));
    CHECK(t.relation("deb")==string("unrelated"));
    CHECK(t.relation("james")==string("grandfather"));
    CHECK(t.relation("sarah")==string("unrelated"));
    CHECK(t.relation("abe")==string("unrelated"));
    CHECK(t.relation("leah")==string("unrelated"));
}


TEST_CASE("FAMILY OF george- a case in which we remove all male ancestors") {
    Tree t("george");
    t.addFather("george","dan");
    t.addMother("george","deb");
    t.addFather("dan","james");
    t.addMother("dan","sarah");
    t.addFather("deb","abe");
    t.addMother("deb","leah");

    CHECK(t.relation("george")==string("me"));
    CHECK(t.relation("dan")==string("father"));
    CHECK(t.relation("deb")==string("mother"));
    CHECK(t.relation("james")==string("grandfather"));
    CHECK(t.relation("sarah")==string("grandmother"));
    CHECK(t.relation("abe")==string("grandfather"));
    CHECK(t.relation("leah")==string("grandmother"));

    t.remove("dan");
    t.remove("abe");

    CHECK(t.relation("george")==string("me"));
    CHECK(t.relation("dan")==string("unrelated"));
    CHECK(t.relation("deb")==string("mother"));
    CHECK(t.relation("james")==string("unrelated"));
    CHECK(t.relation("sarah")==string("unrelated"));
    CHECK(t.relation("abe")==string("unrelated"));
    CHECK(t.relation("leah")==string("grandmother"));
}


TEST_CASE("Family of tim- a case where we remove each ancestor and then look for it"){

    Tree t("tim");
    t.addFather("tim","scott");
    t.addMother("tim","lana");
    t.addFather("scott","jim");
    t.addMother("scott","dana");
    t.addFather("lana","robert");
    t.addMother("lana","deb");


    CHECK(t.relation("tim")==string("me"));
    CHECK(t.relation("scott")==string("father"));
    CHECK(t.relation("lana")==string("mother"));
    CHECK(t.relation("jim")==string("grandfather"));
    CHECK(t.relation("dana")==string("grandmother"));
    CHECK(t.relation("robert")==string("grandfather"));
    CHECK(t.relation("deb")==string("grandmother"));

    t.remove("deb");
    CHECK(t.relation("deb")==string("unrelated"));

    t.remove("dana");
    CHECK(t.relation("deb")==string("unrelated"));

    t.remove("robert");
    CHECK(t.relation("robert")==string("unrelated"));

    t.remove("jim");
    CHECK(t.relation("robert")==string("unrelated"));

    CHECK_THROWS(t.find("grandmother"));
    CHECK_THROWS(t.find("grandfather"));

    t.remove("scott");
    CHECK(t.relation("scott")==string("unrelated"));

    t.remove("lana");
    CHECK(t.relation("lana")==string("unrelated"));


    CHECK_THROWS(t.find("mother"));
    CHECK_THROWS(t.find("father"));


}





    