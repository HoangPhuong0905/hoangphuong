/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : Student code for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */
#include "requestLib.h"
#include "dbLib.h"

/// Initialize and Finalize any global data that you use in the program

struct Data {
    AVLTree<AVLTree<VM_LAT_Record>> db_LAT;
    AVLTree<AVLTree<VM_LONG_Record>> db_LONG;
    int flag;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

bool _insertLatAVL(AVLNode<AVLTree<VM_LAT_Record>>* &pR, VRecord &key, bool &taller, int &Num_Tree) {
    if(pR == NULL) {
        VM_LAT_Record* NewData = new VM_LAT_Record(key);
        //AVLNode<VM_LAT_Record>* NewNode = new AVLNode<VM_LAT_Record>((*NewData));
        AVLTree<VM_LAT_Record>* NewTree = new AVLTree<VM_LAT_Record>();
        NewTree->insert((*NewData));
        NewTree->increaseCount();
        AVLNode<AVLTree<VM_LAT_Record>>* NewNode = new AVLNode<AVLTree<VM_LAT_Record>>((*NewTree));

        pR = NewNode;
        Num_Tree++;
        taller = true;
    }
    else {
        AVLNode<VM_LAT_Record>* pRChild = pR->_data._getpRoot();
        if(strcmp(pRChild->_data.LAT_data->id, key.id) == 0) {
            VM_LAT_Record* NewData = new VM_LAT_Record(key);
            pR->_data.insert((*NewData));
            pR->_data.increaseCount();

            taller = false;
        }
        else if(strcmp(pRChild->_data.LAT_data->id, key.id) > 0) {
            _insertLatAVL(pR->_pLeft, key, taller, Num_Tree);
            if(taller){
                if(pR->_bFactor == LH) {
                    LeftBalance<AVLTree<VM_LAT_Record>>(pR, taller);
                }
                else if(pR->_bFactor == EH) {
                    pR->_bFactor = LH;
                }
                else {
                    pR->_bFactor = EH;
                    taller = false;
                }
            }
        }
        else {
            _insertLatAVL(pR->_pRight, key, taller, Num_Tree);
            if(taller) {
                if(pR->_bFactor == LH) {
                    pR->_bFactor = EH;
                    taller = false;
                }
                else if(pR->_bFactor == EH) {
                    pR->_bFactor = RH;
                }
                else {
                    RightBalance<AVLTree<VM_LAT_Record>>(pR, taller);
                }
            }
        }
    }

    return true;
}

bool _createLatAVL(AVLTree<AVLTree<VM_LAT_Record>> &db, VRecord &key, int &Num) {
    AVLNode<AVLTree<VM_LAT_Record>>* pR = db._getpRoot();
    bool taller;
    _insertLatAVL(pR, key, taller, Num);
    db._setpRoot(pR);
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////

bool _insertLongAVL(AVLNode<AVLTree<VM_LONG_Record>>* &pR, VRecord &key, bool &taller, int &Num_Tree) {
    if(pR == NULL) {
        VM_LONG_Record* NewData = new VM_LONG_Record(key);
        //AVLNode<VM_LAT_Record>* NewNode = new AVLNode<VM_LAT_Record>((*NewData));
        AVLTree<VM_LONG_Record>* NewTree = new AVLTree<VM_LONG_Record>();
        NewTree->insert((*NewData));
        NewTree->increaseCount();
        AVLNode<AVLTree<VM_LONG_Record>>* NewNode = new AVLNode<AVLTree<VM_LONG_Record>>((*NewTree));

        pR = NewNode;
        Num_Tree++;
        taller = true;
    }
    else {
        AVLNode<VM_LONG_Record>* pRChild = pR->_data._getpRoot();
        if(strcmp(pRChild->_data.LONG_data->id, key.id) == 0) {
            VM_LONG_Record* NewData = new VM_LONG_Record(key);
            pR->_data.insert((*NewData));
            pR->_data.increaseCount();

            taller = false;
        }
        else if(strcmp(pRChild->_data.LONG_data->id, key.id) > 0) {
            _insertLongAVL(pR->_pLeft, key, taller, Num_Tree);
            if(taller){
                if(pR->_bFactor == LH) {
                    LeftBalance<AVLTree<VM_LONG_Record>>(pR, taller);
                }
                else if(pR->_bFactor == EH) {
                    pR->_bFactor = LH;
                }
                else {
                    pR->_bFactor = EH;
                    taller = false;
                }
            }
        }
        else {
            _insertLongAVL(pR->_pRight, key, taller, Num_Tree);
            if(taller) {
                if(pR->_bFactor == LH) {
                    pR->_bFactor = EH;
                    taller = false;
                }
                else if(pR->_bFactor == EH) {
                    pR->_bFactor = RH;
                }
                else {
                    RightBalance<AVLTree<VM_LONG_Record>>(pR, taller);
                }
            }
        }
    }

    return true;
}

bool _createLongAVL(AVLTree<AVLTree<VM_LONG_Record>> &db, VRecord &key, int &Num) {
    AVLNode<AVLTree<VM_LONG_Record>>* pR = db._getpRoot();
    bool taller;
    _insertLongAVL(pR, key, taller, Num);
    db._setpRoot(pR);
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
bool _CreateAVLTree(L1List<VRecord>& recList, Data* &NewData) {
    if(recList.getpHead() == NULL) {
        return false;
    }
    else {
        L1Item<VRecord>* pCurr = recList.getpHead();
        //int a = 1;
        int NumLAT = 0;
        int NumLONG = 0;
        while(pCurr != NULL) {
            bool taller;
            //cout << a++ << endl;
            _createLatAVL(NewData->db_LAT, pCurr->data, NumLAT);
            _createLongAVL(NewData->db_LONG, pCurr->data, NumLONG);
            pCurr = pCurr->pNext;
        }
        NewData->db_LAT._setCount(NumLAT);
        NewData->db_LONG._setCount(NumLONG);
    }
}


bool initVGlobalData(void** pGData) { 
    // TODO: allocate global data if you think it is necessary.
    /// pGData contains the address of a pointer. You should allocate data for the global data
    /// and then assign its address to *pGData
    static Data* pGList = new Data;
    pGList->flag = 0;
    *pGData = pGList;
    
    return true;
}
void releaseVGlobalData(void* pGData) {
    // TODO: release the data if you finish using it
}

bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
    // TODO: Your code comes here

    /// NOTE: The output of the request will be printed on one line
    /// end by the end-line '\n' character.
    Data* pGList = (Data*) pGData;
    
    L1Item<VRecord>* pCurr = recList.getpHead();
    if(pGList->flag == 0) {
        _CreateAVLTree(recList, pGList);
    }
    cout << pGList->db_LAT._getCount() << endl;
    cout << pGList->db_LONG._getCount() << endl;
    //cout << pGList->db_LAT._getpRoot()->_data._getpRoot()->_data.LAT_data->id << endl;
    //cout << pGList->db_LAT._getpRoot()->_pLeft->_data._getpRoot()->_data.LAT_data->id << endl;
    char ArrayChar[REQUEST_CODE_SIZE];
    strcpy(ArrayChar, request.code);
    void** Arr = distributeCODE(ArrayChar);
    int Num_param = strlen((char*)Arr);
    int check = 0;
    int i = 2;                              /// Đối với request NVR và NRR thì chưa kiểm tra Arr[1]
    while(i < Num_param) {
        if(!isFloat((char*)Arr[i])) {
            check = 1;
            break;
        }
        i++;
    }
    
    if(check == 0) {
        if(strcmp((char*)Arr[0], "CYR") == 0) {

        }
        else if(strcmp((char*)Arr[0], "CXR") == 0) {

        }
        else if(strcmp((char*)Arr[0], "NYR") == 0) {

        }
        else if(strcmp((char*)Arr[0], "NXR") == 0) {

        }
        else if(strcmp((char*)Arr[0], "NPR") == 0) {

        }
        else if(strcmp((char*)Arr[0], "NVR") == 0) {

        }
        else if(strcmp((char*)Arr[0], "NRR") == 0) {

        }
        else if(strcmp((char*)Arr[0], "CVP") == 0) {

        }
        else if(strcmp((char*)Arr[0], "NRP") == 0) {

        }
        else {
            cout << request.code << " : False" << endl;
        }
    }
    else {
        cout << request.code << " : False" << endl;
    }
    return true;
}

