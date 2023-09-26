#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n; //size of array
    int arr1[n];
    //input in arr1
    for(int i=0; i<n; i++){
        cin>>arr1[i];
    }
    //declare new array and assign with 1 element
    int arr2[n];
    arr2[0]=arr1[0];
    int temp=1;

    for(int i=1; i<n; i++){
        bool checker;
        //check if arr1 has duplicate elemnt or not
        for(int j=0; j<temp; j++){
            if(arr1[i] == arr2[j]){
                checker = true;
                break; }
             else   checker = false;
                  
        } 
        //if checker is false then assign arr1 unique elemnt in arr2
        if(!checker){
        arr2[temp]=arr1[i];
        temp++;
        }
    }
    //print arr2 unique elements
    for(int i=0; i<temp;i++){
        cout<<arr2[i]<<" ";
    }
    
    
}
//end