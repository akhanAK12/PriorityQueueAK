/*
 Project 4:  Priority Queue Project 
 File name: test.cpp Author: Arij Khan  NetId: akhan342  Course: CS 251
 System: Visual Studio
*/

#include <gtest/gtest.h>
#include "priorityqueue.h"
#include <vector>

TEST(priorityqueue, defaultConstructor)
{
    priorityqueue<int> pq; 
     EXPECT_EQ(pq.Size(), 0); 
     EXPECT_EQ(pq.getRoot(), nullptr); 
     priorityqueue<string> jq; 
     EXPECT_EQ(jq.Size(), 0);
     EXPECT_EQ(jq.getRoot(), nullptr);

}


TEST(priorityqueue, toString) {

map<int, vector<int> > map;
int n = 9;
int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
priorityqueue<int> pq;
for (int i = 0; i < n; i++) {
    pq.enqueue(vals[i], prs[i]);
    map[prs[i]].push_back(vals[i]);
}
EXPECT_EQ(pq.Size(), 9);
stringstream ss;
for (auto e: map) {
    int priority = e.first;
    vector <int> values = e.second;
    for (size_t j = 0; j < values.size(); j++){
        ss << priority << " value: " << values[j] << endl;
    }
}
EXPECT_EQ(pq.toString(), ss.str());


}

TEST(priorityqueue, equality){
     priorityqueue<int>pq;
    int n = 30; 
    vector<int> vals; 
    vector<int> prs;
 for(int i = 0; i < 100; i++){
   
    for(int i = 0; i < n; i++)
    {
        vals.push_back(1 + (rand() % 15)); 
        prs.push_back(1 + (rand() % 15)); 

    }
    for(int i = 0; i < n; i++)
    {
        pq.enqueue(vals[i], prs[i]); 
    }
    priorityqueue<int> gq; 

    gq = pq; 
    for(int i = 0; i < n; i++)
    {
        EXPECT_EQ(pq.Size(), gq.Size()); 
        EXPECT_EQ(pq.toString(), gq.toString()); 
    }
    
 }
}

TEST(priorityqueue, clear){
    priorityqueue<int>pq;
    int n = 30; 
    vector<int> vals; 
    vector<int> prs;
 for(int j = 0; j < 100; j++)
 {
    for(int i = 0; i < n; i++)
    {
        vals.push_back(1 + (rand() % 15)); 
        prs.push_back(1 + (rand() % 15)); 

    }
    for(int i = 0; i < n; i++)
    {
        pq.enqueue(vals[i], prs[i]); 
    }
    pq.clear(); 
    EXPECT_EQ(pq.Size(), 0); 
 }
}

TEST(priorityqueue, enqueue){
    map<int, vector<string>> map;
    priorityqueue<string> mp; 
    string value = ""; 
    int priority = 0; 
    
    string vals[] = {"Kareem", "Magic", "Tim", "Rondo", "Cade", "Melo", "Curry", "Ad", "Russ", "PatBev", "Kd", "Kyrie", "Ben", "Lebron", "Luka", "Trae", "Kat", "Nash", "Klay", "Draymond", "Jordan", "Dejonte", "cp", "DBook", "Giannis", "Kris", "Kawhi", "PG"}; 
    int prs[] = {12,10,18,11,17,22,8,9,5,3,6,7,4,1,2,14,16,13,15,21,23,12,12,18,18,18,1,8}; 

    int n = 28; 

     for(int i = 0; i < n; i++)
     {
        mp.enqueue(vals[i], prs[i]); 
        map[prs[i]].push_back(vals[i]);
     }
     
    stringstream ss;
    for (auto e: map) {
        int priority = e.first;
        vector <string> values = e.second;
        for (size_t j = 0; j < values.size(); j++){
        ss << priority << " value: " << values[j] << endl;
        }
    }

    EXPECT_EQ(mp.toString(), ss.str());
    EXPECT_EQ(mp.Size(), 28); 
    EXPECT_EQ(mp.peek(), "Lebron"); 


}

TEST(priorityqueue, dequeue){
    
    priorityqueue<string> mp; 
    string value = ""; 
    int priority = 0; 
    
    string vals[] = {"Ben", "Jack", "Mario", "Cade", "Bella"}; //mario->ben->jack->cade->bella
    int prs[] = {2, 3, 1, 3, 4}; 


    for(int i = 0; i < 5; i++)
     {
        mp.enqueue(vals[i], prs[i]); 
     }

     mp.dequeue();
     mp.dequeue();   


    priorityqueue<string> jp; 
    string vals2[] = {"Ben", "Jack", "Mario", "Cade", "Bella"}; //jack->cade->bella
    int prs2[] = {2, 3, 1, 3, 4}; 
     
    for(int i = 0; i < 5; i++)
     {
        jp.enqueue(vals2[i], prs2[i]); 
     }

     jp.dequeue();
     jp.dequeue(); 

     EXPECT_EQ(mp.toString(), jp.toString()); 
     EXPECT_EQ(mp.peek(), jp.peek());
     EXPECT_EQ(mp.Size(), 3);

  
}

TEST(priorityqueue, peek){
    priorityqueue<string> pq;   
    string value = ""; 
    int priority = 0; 
    
    string vals[] = {"Kareem", "Magic", "Tim", "Rondo", "Cade", "Melo", "Curry", "Ad", "Russ", "PatBev", "Kd", "Kyrie", "Ben", "Lebron", "Luka", "Trae", "Kat", "Nash", "Klay", "Draymond", "Jordan", "Dejonte", "cp", "DBook", "Giannis", "Kris", "Kawhi", "PG"}; 
    int prs[] = {12,10,18,11,17,22,8,9,5,3,6,7,4,1,2,14,16,13,15,21,23,12,12,18,18,18,1,8}; 

    int n = 28; 


      for(int i = 0; i < 28; i++)
     {
        pq.enqueue(vals[i], prs[i]); 
     }

     EXPECT_EQ(pq.peek(), "Lebron");
     EXPECT_EQ(pq.peek(), "Lebron");
     pq.dequeue(); //delete lebron
     EXPECT_EQ(pq.peek(), "Kawhi"); 
     pq.dequeue(); //delete kawhi
     EXPECT_EQ(pq.peek(), "Luka"); 

}

