//Created by Victor Franco and Miguel Santamaría

//October 18th, 2020
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Ordo{
    //Following methods are private, for internal use, not to be used in main

    vector< pair<string, string> > myvector;
    string str;

    //dateIndex method creates an index for each line from de txt file, using the following format:
    //Format: MMDDhh:mm:ss
    string dateIndex(string str){
        string month, day, time;

        if (str.substr(0,3) == "Jun"){
            month = "06";
        }
        else if (str.substr(0,3) == "Jul"){
            month = "07";
        }
        else if (str.substr(0,3) == "Aug"){
            month = "08";
        }
        else if (str.substr(0,3) == "Sep"){
            month = "09";
        }
        else if (str.substr(0,3) == "Oct"){
            month = "10";
        }
        else{
            month = "13";
        }

        if (str.substr(5,1) == " "){
            day  = "0" + str.substr(4,1);
            time = str.substr(6,8);
        }
        else {
            day = str.substr(4,2);
            time = str.substr(7,8);
        }
        return month + day + time;
    }

    //pivot method separates vector in two, and orders it using quicksort
    int pivot(vector< pair <string, string> >&myvector, int first, int last){
       int pivPos = first + (last - first) / 2;
       string pivValue = myvector[pivPos].first;
       int i = first, j = last;
       string aux, aux2;
       while(i <= j){
           while(myvector[i].first<pivValue){
               i++;
           }
           while(myvector[j].first>pivValue){
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

    //quick method orders array using quicksort, uses pivot method
    //Worst case complexity: O(n^2)
    //Average complexity: O[nlog(n)]
   void quick(vector< pair <string, string> >&myvector, int first, int last){
       if(first < last){
           int pivPos = pivot(myvector,first,last);
           quick(myvector,first, pivPos-1);
           quick(myvector, pivPos,last);
        }
    }

    //linearSearch method searches a date stored in the vector
    //Worst case complexity: O(n)
    int linearSearch(string k){
        int pos = -1;
        for (int i=0; i < myvector.size(); i++){
            if (myvector[i].first.substr(0,4) == k){
                pos = i;
                break;
            }
        }
        return pos;
   }

    //userIndex method formats user given date to fit with txt file
   int userIndex(){
       string key, month, day;
       cout << "Input month (Following .txt file format): ";
       cin >> month;
       cout << "Input day (Following .txt file format): ";
       cin >> day;
       key = dateIndex(month+" "+day+" "+"00:00:00");
       key = key.substr(0,4);
    return linearSearch(key);
   }

public:
    //Following methods are public and to be used in the main()

    //readFile method stores all contents of the txt file in a vector

    void readFile(string file){
        ifstream in(file.c_str());
        if(!in){
            cerr << "file can't be opened: "<< file << endl;
        }
        while (getline(in, str)){
        if(str.size() > 0)
            myvector.push_back( make_pair(dateIndex(str),str));
        }
        in.close();
    }

    //printVector method prints in console all contents of vector
    void printVector(){
        for(int i = 0; i < myvector.size(); i++){
            cout << myvector[i].second << endl;
        }
        cout << endl;
    }

    //quicksort helper method to sort vector with quicksort
    void quickSort(){
        quick(myvector,0,myvector.size()-1);
    }

    //bubbleSort method sorts vector contents using bubble sort
    //Worst case complexity: O(n^2)
    void bubbleSort(){
        int i, j;
        string aux, aux2;
        for (i=1; i<myvector.size(); i++){
           for (j=0; j < myvector.size() - i; j++){
                if(myvector[j].first > myvector[j+1].first){
                    aux = myvector[j].first;
                    aux2 = myvector[j].second;
                    myvector[j].first = myvector[j+1].first;
                    myvector[j+1].first = aux;
                    myvector[j].second = myvector[j+1].second;
                    myvector[j+1].second = aux2;
                }
           }
        }
    }

    //insertionSort method sorts vector contents using insertion sort
    //Worst case complexity: O(n^2)
    void insertionSort(){
        int i, j;
        string aux, aux2;
        for (i=1; i < myvector.size(); i++){
            for (j=i; j > 0; j--){
                if (myvector[j].first < myvector[j-1].first){
                  aux = myvector[j].first;
                  aux2 = myvector[j].second;
                  myvector[j].first = myvector[j-1].first;
                  myvector[j-1].first = aux;
                  myvector[j].second = myvector[j-1].second;
                  myvector[j-1].second = aux2;
                }
            }
        }
    }

    //userSelect method prints a section of the ordered data, limited by two given dates
   void userSelect(){
       int start, end;
       string key;
       cout << "Input start date: " << endl;
       start = userIndex();
       
       cout << "Input end date: " << endl;
       end = userIndex();
       key = myvector[end].first.substr(0,4);

       if (start > end){
           cout << "Error" <<endl;
       }
       else{
            for (int i=start; i<=end; i++ ){
                cout << myvector[i].second << endl; //print 
            }
            for (int i=end; i<myvector.size(); i++){
                if (myvector[i].first.substr(0,4) == key){
                cout << myvector[i].second << endl;
                }
                else {
                    break;
                }
            }
            cout << endl;
       }
   }

    //outputFile method creates a txt file with the ordered data
    void outputFile(){
        ofstream outputfile("log_in_order.txt");
        quickSort();
        for(int i=0; i<myvector.size(); i++)
        outputfile<<myvector[i].second<<"\n";
    }
};

int main(){
    //Los comentarios en esta sección sirven para orientar al usuario para comentar o descomentar el método que quieran utilizar en el main
    Ordo log;

    //iopen file
    log.readFile("log.txt");

    //sort vector with quicksort
    log.quickSort();

    //sort vector with bubble sort
    //log.bubbleSort();

    //sort vector with insertion sort
    //log.insertionSort();

    //print vector
    //log.printVector();

    //ask for dates to print data
    log.userSelect();

    //create new txt with ordered data
    log.outputFile();
}
