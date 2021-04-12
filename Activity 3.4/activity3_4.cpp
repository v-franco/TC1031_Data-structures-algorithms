//Made by Victor Franco & Miguel Santamaría
//November 25th 2020
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//TreeNode class defines node for BST
class TreeNode{
public:
    string info;
    int count = 1;
    TreeNode *hLeft;
    TreeNode *hRight;
    TreeNode(string data){
        info = data;
        hLeft = nullptr;
        hRight = nullptr;
    }
};

class Ordo{
private:
    //indexIP method creates an index for each entry from the log file, using an IP for each line
    string indexIP(string str){
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
        // Formatting IP 
        posA = ip.find(".");
        posB = ip.find(".", posA+1);
        posC = ip.find(".", posB+1);
        posD = ip.find(":");
        // aaa.bb.ccc.dd:eeee
        // strA
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

    //save method saves de contents from the BST into a vector to order the data by no. of accesses
    void save(TreeNode *p, vector< pair<string, string> >&myvector){
        if(p != nullptr){
            save(p->hLeft, myvector);
            myvector.push_back( make_pair(to_string(p->count), p->info));
            save(p->hRight, myvector);
        }
    }

    //pivot method splits vector and orders it using quicksort
    int pivot(vector< pair <string, string> >&myvector, int first, int last){
       int pivPos = first + (last - first) / 2;
       string pivValue = myvector[pivPos].first;
       int i = first, j = last;
       string aux, aux2;
       while(i <= j){
           while(myvector[i].first>pivValue){
               i++;
           }
           while(myvector[j].first<pivValue){
               j--;
           }
           if( i<=j ){
               aux = myvector[i].first;
               myvector[i].first = myvector[j].first;
                myvector[j].first = aux;
                aux2 = myvector[i].second;
                myvector[i].second = myvector[j].second;
                myvector[j].second = aux2;
                i++;
                j--;
           }
       }
       return i;
   }

    //quickSort method orders vector using quicksort, uses pivot method
    //Worst case complexity: O(n^2)
    //Average complexity: O[nlog(n)]
   void quickSort(vector< pair <string, string> >&myvector, int first, int last){
       if(first < last){
           int pivPos = pivot(myvector,first,last);
           quickSort(myvector,first, pivPos-1);
           quickSort(myvector, pivPos,last);
        }
    }

    //recursiveInsertion  method inserts a new node with data into the BST 
    TreeNode* recursiveInsertion(TreeNode *p, string data){
        if (p == nullptr){
            p = new TreeNode(data);
        }
        else{
            if (indexIP(data) == indexIP(p->info)){
                (p->count)++;
                return p;
            }
            if (indexIP(data) < indexIP(p->info)){
                p->hLeft = recursiveInsertion(p->hLeft,data);
            }
            else if (indexIP(data) > indexIP(p->info)){
                p->hRight = recursiveInsertion(p->hRight,data);
            }
        }
        return p;
    }

    //insert method is a helper to insert data into the BST
    void insert(string data){
        root = recursiveInsertion(root, data);
    }

    //height method obtains BST height
    //Complexity: O(n)
     int height(TreeNode *p){ 
        if (p == NULL){
            return 0;
        } 
        else{ 
            int leftHeight = height(p->hLeft); 
            int rightHeight = height(p->hRight); 
            if (leftHeight > rightHeight){
                return(leftHeight + 1); 
            }
            else{
                return(rightHeight + 1);
            }  
        }
    }
  
    //printLevel method prints a level from the BST
    void printLevel(TreeNode *p, int nivel) { 
        if (p == NULL) {
            return; 
        }
        if (nivel == 0){
            cout << "First IP access: " << p->info << " || Total accesses: " << p->count << " ";
        }

        else if (nivel > 0){ 
            printLevel(p->hLeft, nivel-1); 
            printLevel(p->hRight, nivel-1); 
        } 
    }
    
public:
    TreeNode *root = nullptr;
    vector< pair<string, string> > myvector;
    string str;

    //printTopAccesses method prints the IPs with the most accesses in the log file
    void printTopAccesses(){
        save(root, myvector);
        quickSort(myvector,0,myvector.size()-1);
        for(int i = 0; i < 5; i++){
            cout << "IP: " << indexIP(myvector[i].second) << " || No. of accesses:  " <<  myvector[i].first << endl;
        }
        cout << endl;
    }

    //readFile stores the log data into the BST
    void readFile(string file){
        ifstream in(file.c_str());
        if(!in){
            cerr << "Cannot open file: "<< file << endl;
        }
        while (getline(in, str)){
        	if(str.size() > 0){
				insert(string(str));
			}	
        }
        in.close();
    }
    
    //levelByLevel method prints the BST level by level
    //Complexity: O(n)
    void levelByLevel(TreeNode *p){ 
        for (int i=0; i<=height(p); i++){ 
            printLevel(p, i);
            cout << "\n"; 
        } 
    } 

    //inOrder method prints the BST inOrder: Left, root, right
    //Complexity: O(n)
    void inOrder(TreeNode *p){
        if (p != nullptr){
            inOrder(p->hLeft);
            cout << "IP: " << indexIP(p->info) << " || No. of accesses: " << p->count << "\n";
            inOrder(p->hRight);
        }
    }
};

int main(){
    Ordo log;
    //Open file with registries
    log.readFile("log.txt");

    //print top 5 accesses by IP
    log.printTopAccesses();

    //print BST level by level
    log.levelByLevel(log.root);

    //print BST inOrder
    log.inOrder(log.root);

}