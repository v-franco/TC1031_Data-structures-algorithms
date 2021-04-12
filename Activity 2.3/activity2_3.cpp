//Made by Victor Franco & Miguel Santamaría
//November 14th 2020
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//Node class defines Node for linked list
class Node{
public:
    string info;
    Node *next;
    Node(string data){
        info = data;
        next = nullptr;
    }
};

// list class contains all methods to manipulate the linked list
class List{
      
public:
    Node *first = nullptr;

    //createStart method creates node at the beginning of the list
    //Complexity: O(1)
    void createStart(string data){
        Node *p = new Node(data);
        p->next = first;
        first = p;
    }

    //createEnd ethod creates node at the end of the list
    ///Complexity: O(n)
    void createEnd(string data){
        if (first == NULL){
            createStart(data);
            return;
        }
        Node *p = new Node(data);
        Node *ptr = this->first;
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = p;
    }

    //read method reads data stored at a given position
    //Complexity: O(n)
    string read(int pos){
        int i = 0;
        Node *p = first;
        while(p != NULL){
            if(i == pos){
                return p->info;
            }
            i++;
            p = p->next;
        }
        cout << "Index not found" << endl;
        return "np";
    }

    //startList method starts complete list
    //Complexity: O(n)
    void startList(){
        Node *p;
        p = first;
        while (p != nullptr){
            cout << p->info << endl;
            p = p->next;
        }
        cout << endl;
    }

    //getSize method gets the linked list size
    //Complexity: O(n)
    int getSize(){
        int size = 0;
        Node* p = first;
        while (p != NULL){
            size++;
            p = p->next;
        }
        return size;
    }
};

//Ordo class contains sorting algorithms
class Ordo{

public:
    //myList object is used to access List methods
	List myList;
    string str;

    //ipIndex creates an index for each entry of the log file
    string ipIndex(string str){
        string ip, strA, strB, strC, strD, strE;
        int posA, posB, posC, posD;
        ip=str;

        if(str.size() > 18){
            if (str.substr(14,1) == " "){
                ip = str.substr(15,18);
            }
            else {
                ip = str.substr(16,18);
            }
        }

        posA = ip.find(".");
        posB = ip.find(".", posA+1);
        posC = ip.find(".", posB+1);
        posD = ip.find(":");
        /*format
        aaa.bb.ccc.dd:eeee
        strA*/
        if(posA == 3){
            strA = ip.substr(0,3);
        }
        else if(posA == 2){
            strA = "0" + ip.substr(0,2);
        }
        else if(posA == 1){
            strA = "00" + ip.substr(0,1);
        }
        // strB
        if((posB-posA) == 3){
            strB = ip.substr(posA+1,2);
        }
        else if((posB-posA) == 2){
            strB = "0" + ip.substr(posA+1,1);
        }
        // strC
        if((posC-posB) == 4){
            strC = ip.substr(posB+1,3);
        }
        else if((posC-posB) == 3){
            strC = "0" + ip.substr(posB+1,2);
        }
        else if((posC-posB) == 2){
            strC = "00" + ip.substr(posB+1,1);
        }
        // strD
        if((posD-posC) == 3){
            strD = ip.substr(posC+1,2);
        }
        else if((posD-posC) == 2){
            strD = "0" + ip.substr(posC+1,1);
        }
        // strE
        strE = ip.substr(posD+1,4);
        ip = strA+"."+strB+"."+strC+"."+strD+":"+strE;
        return ip;
    }
    
    //readFile method stores all contents of the txt file in a linked list
    void readFile(string file){
        ifstream in(file.c_str());
        if(!in){
            cerr << "Can't open file: "<< file << endl;
        }
        while (getline(in, str)){
        	if(str.size() > 0){
				myList.createEnd(string(str));
			}	
        }
        in.close();
    }

    //outputFile method creates a txt file with the ordered data
    void outputFile(){
        ofstream outputfile("log_in_order.txt");
        mergeSort();
        for(int i=0; i<myList.getSize(); i++)
        outputfile<<myList.read(i)<<"\n";
    }
    
    //Merge method joins two sections of the linked list in order
    Node* Merge(Node* start1, Node* start2){
        string a;
        Node *last1 = new Node(a);
        Node *last2 = new Node(a);
        Node *temp = new Node(a);
        if(start1 == NULL){
            return start2;
        }
        if(start2 == NULL){
            return start1;
        }
        last1 = start1;
        while(start2 != NULL){
            last2 = start2;
            start2 = start2->next;
            last2->next = NULL;
            if(ipIndex(start1->info) > ipIndex(last2->info)){
                last2->next=start1;
                start1=last2;
                last1=start1;
            }
            while(last1->next != NULL && ipIndex((last1->next)->info) <= ipIndex(last2->info)){
                last1 = last1->next;
            }
            if(last1->next == NULL){
                last1->next = last2;
                last1 = last1->next;
            }
             else{
                temp = last1->next;
                last1->next = last2;
                last2->next = temp;
            }
        }
        return start1;
    }

    //mergeS method orders linked list using merge sort
    //Complexity: O(nlog(n))
    void mergeS(Node **start){
        string a;
        Node *first = new Node(a);
        Node *second  = new Node(a);
        Node *temp  = new Node(a);
        first = *start;
        temp = *start;

        if(first == NULL || first->next == NULL){
            return;
        }
        else{
            while(first->next != NULL){
                first = first->next;
                if(first->next != NULL){
                    temp = temp->next;
                    first = first->next;
                }
            }
            second = temp->next;
            temp->next = NULL;
            first = *start;
        }
        mergeS(&first);
        mergeS(&second);
        *start=Merge(first, second);
    }

    //mergesort helper method to use merge sort
    void mergeSort(){
        mergeS(&myList.first);
    }

    //linearSearch method searches a date stored in the linked list
    //Worst case complexity: O(n)
    int linearSearch(string k){
        int pos = -1;
        for (int i=0; i < myList.getSize(); i++){
            if (ipIndex(myList.read(i)) == ipIndex(k)){
                pos = i;
                break;
            }
        }
        return pos;
   }

    //userSelect method prints a section of the ordered data, limited by two given IP adresses
   void userSelect(){
       int startDate, endDate;
       string key, inicio, last;
       cout << "Input initial IP: " << endl;
       cin >> inicio;
       startDate = linearSearch(inicio);
       cout << "Input final IP: " << endl;
       cin >> last;
       endDate = linearSearch(last);

       if (inicio > last){
           cout << "Error" <<endl;
       }
       else{
           while (endDate >= startDate){
               cout << myList.read(startDate) <<endl;
               startDate++;
           }
       }
   }
};

int main(){
    //Comments in main help to use de code
    //Open file
    Ordo log;
    log.readFile("log.txt");

    //Sorts and creates sorted log file
    log.outputFile();

    //Orders log - not necessary if output file is used
    //log.mergeSort();

    //Prints selected IPs
    log.userSelect();

    //Prints complete linked list
	//log.myList.startList();
}