#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include "BST.h"
#include "AVL.h"
using namespace std;
using namespace std::chrono;

// Replace this code once you have determined that your Trees work as expected

int main() {
    // Store the sizes of the elements/ vertices of the trees
    vector<int> sizes;
    sizes.push_back(1000);
    sizes.push_back(10000);
    sizes.push_back(100000);
    /*
     Things to learn, how to use the chrono library from the C++ STL to record the loop execution time
     3 important things to learn
     Durations
     Time points
     Clocks
     
     */
    
    for (int id = 0; id < sizes.size(); id++) {
        // 1000 , 10000, 100000
        int n = sizes[id];
        
        cout << "========================" << endl;
        
        cout << "n = " << n << endl;
        
        // Worst-case: sorted insert
        BST bst1;
        for (int i = 0; i < n; i++) bst1.insert(i);
        
        AVL avl1;
        for (int i = 0; i < n; i++) avl1.insert(i);
        
        // we have to write the getHeight() function ourselves, count the edges and not the nodes in the tree
        
        cout << " Sorted Insert " << endl;
        // why is the height zero here?
        cout << "BST Height: " << bst1.getHeight() << endl;
        cout << "AVL Height: " << avl1.getHeight() << endl;
        
        auto t_bst_s = high_resolution_clock::now();
        
        for (int i = 0; i < n; i++) bst1.search(i);
        
        auto t_bst_e = high_resolution_clock::now();
        
        // duration_cast returns an integral type
        
        double bst_succ = duration_cast<microseconds>(t_bst_e-t_bst_s).count() / double(n);
        
        cout << " This is the time taken by the searching algorithm implemented in the BST class: " << duration_cast<microseconds>(t_bst_e-t_bst_s).count() << endl;
        
        auto t_avl_s = high_resolution_clock::now();
        
        for (int i = 0; i < n; i++) avl1.search(i);
        
        auto t_avl_e = high_resolution_clock::now();
        
        // time taken to search for 1000,10000,100000 keys in the avl tree. worst case should be O(log n)
        
        double avl_succ = duration_cast<microseconds>(t_avl_e-t_avl_s).count() / double(n);
        
        // what exactly is printed here??
        
        cout << "BST avg successful search (us): " << bst_succ << endl;
        cout << "AVL avg successful search (us): " << avl_succ << endl;
        
        cout << " This is the time taken by the searching algorithm implemented in the AVL class: " <<duration_cast<microseconds>(t_avl_e-t_avl_s).count() << endl;
        
        BST bst_ev;
        AVL avl_ev;
        
        for (int i = 0; i < n; i += 2) { bst_ev.insert(i); avl_ev.insert(i); }
        
        vector<int> odds;
        
        for (int i = 1; i < n; i += 2) odds.push_back(i);
            
        
        // the data type deduced here will be double
        
        auto t_bst_us = high_resolution_clock::now();
        // we can't print a time point, the duration has to be the difference between the two time points, so end - start or something similar
        // cout << "Before the loop runs " << duration_cast<microseconds>(t_bst_us).count() << endl;
        
        for (int i = 0; i < odds.size(); i++) bst_ev.search(odds[i]);
        
        auto t_bst_ue = high_resolution_clock::now();
        // why isn'tthis statement working?
        // cout << "After the loop runs " << duration_cast<microseconds>(t_bst_ue).count() << endl;
        
        double bst_unsucc = duration_cast<microseconds>(t_bst_ue-t_bst_us).count() / double(odds.size());
        
        auto t_avl_us = high_resolution_clock::now();
        
        for (int i = 0; i < odds.size(); i++) avl_ev.search(odds[i]);
        
        auto t_avl_ue = high_resolution_clock::now();
        
        double avl_unsucc = duration_cast<microseconds>(t_avl_ue-t_avl_us).count() / double(odds.size());
        
        //the average time for an unsuccessful search
        // (us) micro seconds 
        cout << "BST avg unsuccessful search (us): " << bst_unsucc << endl;
        cout << "AVL avg unsuccessful search (us): " << avl_unsucc << endl;
        
        
                // Random insert (average case)
                BST bst2;
                AVL avl2;
                vector<int> randoms;
                for (int i = 0; i < n; i++) randoms.push_back(i);
                shuffle(randoms.begin(), randoms.end(), mt19937(random_device()()));
        
                for (int i = 0; i < n; i++) {
                    bst2.insert(randoms[i]);
                    avl2.insert(randoms[i]);
                }
        
                cout << " Random Insert " << endl;
                cout << "BST Height: " << bst2.getHeight() << endl;
                cout << "AVL Height: " << avl2.getHeight() << endl;
        
                auto t_bst_s2 = high_resolution_clock::now();
                for (int i = 0; i < n; i++) bst2.search(randoms[i]);
                auto t_bst_e2 = high_resolution_clock::now();
                double bst_succ2 = duration_cast<microseconds>(t_bst_e2-t_bst_s2).count() / double(n);
        
                auto t_avl_s2 = high_resolution_clock::now();
                for (int i = 0; i < n; i++) avl2.search(randoms[i]);
                auto t_avl_e2 = high_resolution_clock::now();
                double avl_succ2 = duration_cast<microseconds>(t_avl_e2-t_avl_s2).count() / double(n);
        
                cout << "BST avg successful search (us): " << bst_succ2 << endl;
                cout << "AVL avg successful search (us): " << avl_succ2 << endl;
        
                BST bst_ev2;
                AVL avl_ev2;
                for (int i = 0; i < n; i += 2) { bst_ev2.insert(i); avl_ev2.insert(i); }
                auto t_bst_us2 = high_resolution_clock::now();
                for (int i = 0; i < odds.size(); i++) bst_ev2.search(odds[i]);
                auto t_bst_ue2 = high_resolution_clock::now();
                double bst_unsucc2 = duration_cast<microseconds>(t_bst_ue2-t_bst_us2).count() / double(odds.size());
        
                auto t_avl_us2 = high_resolution_clock::now();
                for (int i = 0; i < odds.size(); i++) avl_ev2.search(odds[i]);
                auto t_avl_ue2 = high_resolution_clock::now();
                double avl_unsucc2 = duration_cast<microseconds>(t_avl_ue2-t_avl_us2).count() / double(odds.size());
        
                cout << "BST avg unsuccessful search (us): " << bst_unsucc2 << endl;
                cout << "AVL avg unsuccessful search (us): " << avl_unsucc2 << endl;
    }
    
    
    return 0;
}
// Done !!! ugghhhghghsuyfvuasbisrvbiupevurbpdvyuwsd
