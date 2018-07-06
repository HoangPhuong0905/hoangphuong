/*
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : Library for Assignment 2 - Data structures and Algorithms - Spring 2018
 *               This library contains functions used for database management
 * =========================================================================================
 */

#ifndef A02_DBLIB_H
#define A02_DBLIB_H

#include <string.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>

#include "dsaLib.h"
#include "requestLib.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define VDB_HEADER_TEXT     "VRecord data"
#define VDB_HEADER_SIZE     12

#define ID_MAX_LENGTH   16

struct VRecord {
    char    id[ID_MAX_LENGTH];
    time_t  timestamp;
    double  x, y;

    VRecord() {// default constructor
        id[0] = 0;
    }
    VRecord(const char* vID) {
        strcpy(id, vID);
    }
    VRecord(VRecord& vR) : timestamp(vR.timestamp),
                           x(vR.x), y(vR.y) {
        strcpy(id, vR.id);
    }
    VRecord(VRecord&& vR): timestamp(vR.timestamp),
                           x(vR.x), y(vR.y) {
        strcpy(id, vR.id);
    }

    bool operator==(VRecord& b) {
        return  strcmp(id, b.id) == 0 &&
                timestamp == b.timestamp;
    }

    VRecord& operator = (VRecord& b) {
        strcpy(id, b.id);
        timestamp = b.timestamp;
        x =b.x;
        y = b.y;
        return *this;
    }

};

struct VM_LAT_Record {
    VRecord *LAT_data = NULL;
    VM_LAT_Record(VRecord &b) {
        LAT_data = &b;
    }
    bool operator < (VM_LAT_Record &b) {
        if(LAT_data->y < b.LAT_data->y) return true;
        else return false;
    }
};

struct VM_LONG_Record {
    VRecord *LONG_data = NULL;
    VM_LONG_Record(VRecord &b) {
        LONG_data = &b;
    }
    bool operator < (VM_LONG_Record &b) {
        if(LONG_data->x < b.LONG_data->x) return true;
        else return false;
    }
};
/*
struct VM_Record {
    AVLTree<VM_LAT_Record>* Latitude;
    AVLTree<VM_LONG_Record>* Longitude;
    int count;
    
    VM_Record() {
        Latitude = NULL;
        Longitude = NULL;
        count = 0;
    }
    VM_Record(VRecord &b) {
        VM_LAT_Record LAT(b);
        Latitude->insert(LAT);
        VM_LONG_Record LONG(b);
        Longitude->insert(LONG);

        count++;
    }
    
};
*/
a(key)
AVLTree<a> insert key
struct NodeLarge{ //lat/long/ID
    AVLTree<VM_LAT_Record>* a;
    AVLTree<VM_LONG_Record>* b;
    VRecord*
    NodeLarge + NodeLarge{
        AVLTree<Lat> + AVLTree<LAt>
        AVLTre + AVLTree
        ID = ID
    }
    NodeLarge == NodeLarge{
        this->VRRecord == that->VRRecord
    }
    NodeLarge(&VRRecord){
        this->VRRecod = *that->VRRecord
    }
}
VRRECORD{
    VRRecord == VRRecord{
        this->ID == that->ID
    }
}
AVL<T>{
    AVL + AVL{
        this->AVL->insert(that->data)
    }
}
Lat{
    Lat < Lat{
        this->lat < that->lat
    }
}
 if data = Tree->Data {Data + Data}
void    printVRecord(VRecord& vR);
void    strPrintTime(char* des, time_t& t);
void    loadVDB(char* fName, L1List<VRecord> &db);

#define __deg2rad(deg) (deg * pi / 180.0)
#define __rad2deg(rad) (rad * 180.0 / pi)

double  distanceVR(double lat1d, double lon1d, double lat2d, double lon2d);


#endif //A02_DBLIB_H

quan(b) {
    void *pR = b
    AVLtree *a = NULL
}
