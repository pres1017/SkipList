#include "skiplist.h"
#include <vector>
#include <time.h>

int main(){
    // A random number generator 
    // Using std::clock_t for time tracking
    // Stuck with the srand for time because it's fun, even if it is inefficient sometimes

    std::cout << "Test Suite\n";
    std::cout << "CONTAINS TEST means that the list is being checked for all the elements that were inserted. If the list contains elements it shouldn't\nor is missing elements it should have, it fails.\n";
    std::cout << "SIZE TEST is for a counter variable. This variable keeps track of the number of elements that should be in the list, \nthen compares that to the actual number of elements in the list.\n\n";
    { // TEST 1: Forwards and backwards
        std::cout << "TEST 0: INSERTING 30 ELEMENTS HALF FORWARDS AND HALF BACKWARDS\n";
        size_t count = 0;
        SkipList<int> skpList;
        for(int x = 0; x < 15; x++){
            skpList.insert(x);
            count++;
        }
        for(int x = 30; x >= 15; x--){
            skpList.insert(x);
            count++;
        }
        bool containsElems = true;
        for(int x = 0; x < 30; x++){
            if(!skpList.contains(x)) containsElems = false;
        }
        if(containsElems == false){
            std::cout << "\tCONTAINS TEST: FAILED\n";
        }else{
            std::cout << "\tCONTAINS TEST: PASSED\n";
        }

        if(count != skpList.elements()){
            std::cout << "\tSIZE TEST: FAILED\n";
        }else{
            std::cout << "\tSIZE TEST: PASSED\n";
        }
    }
    std::cout <<"\n";
    {
        std::cout << "TEST 1: INSERTING 15 ODD ELEMENTS, 15 EVENS, THEN REMOVING THE ODDS\n";
        size_t count = 0;
        SkipList<int> skpList;
        for(int x = 0; x < 30; x++){
            if(x%2 == 0){
                skpList.insert(x);
                count++;
            }
        }

        for(int x = 0; x < 30; x++){
            if(x%2 != 0){
                skpList.insert(x);
                count++;
            }
        }

        for(int x = 0; x < 30; x++){
            if(x%2 != 0){
                skpList.remove(x);
                count--;
            }
        }

        bool containsElems = true;
        for(int x = 0; x < 30; x++){
            if((x%2 != 0 && skpList.contains(x)) || (x%2 == 0 && !skpList.contains(x))) containsElems = false;
        }
        if(containsElems == false){
            std::cout << "\tCONTAINS TEST: FAILED\n";
        }else{
            std::cout << "\tCONTAINS TEST: PASSED\n";
        }

        if(count != skpList.elements()){
            std::cout << "\tSIZE TEST: FAILED\n";
        }else{
            std::cout << "\tSIZE TEST: PASSED\n";
        }
    }

    std::cout << "\n";

    {
        std::cout << "TEST 2: INSERTING AND REMOVING 100 ELEMENTS\n";
        SkipList<int> skpList;
        size_t count = 0;
        for(int x = 0; x < 100; x++){
            skpList.insert(x);
            count++;
        }

        for(int x = 0; x < 100; x++){
            skpList.remove(x);
            count--;
        }
        bool containsElems = true;

        for(int x = 0; x < 100; x++){
            if(skpList.contains(x)) containsElems = false;
        }

        if(containsElems == false){
            std::cout << "\tCONTAINS TEST: FAILED\n";
        }else{
            std::cout << "\tCONTAINS TEST: PASSED\n";
        }

        if(count != skpList.elements()){
            std::cout << "\tSIZE TEST: FAILED\n";
        }else{
            std::cout << "\tSIZE TEST: PASSED\n";
        }
    }

    std::cout << "\n";

    {
        std::cout << "TEST 3: TIMING INSERTING AND REMOVING OF 10000 ELEMENTS WITH 3 LAYERS\n";
        SkipList<int> skpList;
        size_t count = 0;
        long double duration1;
        long double duration2;
        long double duration3;

        clock_t start1 = clock();
        for(int x = -5000; x < 5000; x++){
            skpList.insert(x);
            count++;
        }
        clock_t end1 = clock();
        duration1 = (end1 - start1) / (long double) CLOCKS_PER_SEC;

        clock_t start2 = clock();
        for(int x = 5000 - 1; x > -5000; x--){
            skpList.remove(x);
            count--;
        }
        clock_t end2 = clock();
        duration2 = (end2 - start2) / (long double) CLOCKS_PER_SEC;
        duration3 = duration1 + duration2;

        bool containsElems = true;

        for(int x = 2500; x < -2500; x++){
            if(skpList.contains(x)) containsElems = false;
        }

        if(containsElems == false){
            std::cout << "\tCONTAINS TEST: FAILED\n";
        }else{
            std::cout << "\tCONTAINS TEST: PASSED\n";
        }

        if(count != skpList.elements()){
            std::cout << "\tSIZE TEST: FAILED\n";
        }else{
            std::cout << "\tSIZE TEST: PASSED\n";
        }
        std::cout << "\tTIME TO INSERT 10000 ELEMENTS IN ORDER: " << duration1 << "s\n";
        std::cout << "\tTIME TO REMOVE 10000 ELEMENTS IN REVERSE ORDER: " << duration2 << "s\n";
        std::cout << "\tTOTAL TIME: " << duration3 << "s\n";
    }

    std::cout << "\n";

    {
        std::cout << "TEST 4: TIMING INSERTING AND REMOVING OF 10000 ELEMENTS WITH 10 LAYERS\n";
        SkipList<int> skpList(10);
        size_t count = 0;
        long double duration1;
        long double duration2;
        long double duration3;

        clock_t start1 = clock();
        for(int x = -5000; x < 5000; x++){
            skpList.insert(x);
            count++;
        }
        clock_t end1 = clock();
        duration1 = (end1 - start1) / (long double) CLOCKS_PER_SEC;

        clock_t start2 = clock();
        for(int x = 5000 - 1; x > -5000; x--){
            skpList.remove(x);
            count--;
        }
        clock_t end2 = clock();
        duration2 = (end2 - start2) / (long double) CLOCKS_PER_SEC;
        duration3 = duration1 + duration2;

        bool containsElems = true;

        for(int x = 2500; x < -2500; x++){
            if(skpList.contains(x)) containsElems = false;
        }

        if(containsElems == false){
            std::cout << "\tCONTAINS TEST: FAILED\n";
        }else{
            std::cout << "\tCONTAINS TEST: PASSED\n";
        }

        if(count != skpList.elements()){
            std::cout << "\tSIZE TEST: FAILED\n";
        }else{
            std::cout << "\tSIZE TEST: PASSED\n";
        }
        std::cout << "\tTIME TO INSERT 10000 ELEMENTS IN ORDER: " << duration1 << "s\n";
        std::cout << "\tTIME TO REMOVE 10000 ELEMENTS IN REVERSE ORDER: " << duration2 << "s\n";
        std::cout << "\tTOTAL TIME: " << duration3 << "s\n";
    }

    std::cout << "\n";

    {
        std::cout << "TEST 5: INSERTING 5000 ELEMENTS AND REMOVING EVERY THIRD ELMENT\n";
        SkipList<int> skpList;
        size_t count = 0;
        clock_t start1 = clock();
        for(int x = -2500; x < 2500; x++){
            skpList.insert(x);
            count++;
        }
        clock_t end1 = clock();
        long double duration1 = (end1 - start1) / (long double) CLOCKS_PER_SEC;

        clock_t start2 = clock();
        for(int x = -2500; x < 2500; x++){
            if(x%3 == 0){
                skpList.remove(x);
                count--;
            }
        }
        clock_t end2 = clock();
        long double duration2 = (end2 - start2) / (long double) CLOCKS_PER_SEC;
        long double duration3 = duration1 + duration2;

        if(count != skpList.elements()){
            std::cout << "\tSIZE TEST: FAILED\n";
        }else{
            std::cout << "\tSIZE TEST: PASSED\n";
        }
        std::cout << "\tTIME TO INSERT 10000 ELEMENTS IN ORDER: " << duration1 << "s\n";
        std::cout << "\tTIME TO REMOVE 10000 ELEMENTS IN REVERSE ORDER: " << duration2 << "s\n";
        std::cout << "\tTOTAL TIME: " << duration3 << "s\n";
    }
    
    std::cout << "\n";

    {
        std::cout << "TEST 6: INSERTING 15 DOUBLES AND PRINTING THEM\n";
        SkipList<double> skpList;
        for(int x = 0; x < 15; x++){
            skpList.insert(((double)x)/3);
        }
        skpList.printElements();
    }

    std::cout << "\n";

    {
        std::cout << "TEST 7: INSERTING T VALUES AND REMOVING EVERY U ONE WITH V LAYERS (change variables in code)\n";
        int T = 100;
        int U = 2;
        int V = 3;
        std::cout << "\tT: " << T << " || U: " << U << " || V: " << V << "\n";
        SkipList<int> skpList(V);
        size_t count = 0;
        clock_t start1 = clock();
        for(int x = -T/2; x <= T/2; x++){
            skpList.insert(x);
            count++;
        }
        clock_t end1 = clock();
        long double duration1 = (end1 - start1) / (long double) CLOCKS_PER_SEC;
        if(skpList.contains(0)){
            std::cout << "\tCONTAINS 0: YES\n";
        }else{
            std::cout << "\tCONTAINS 0: NO\n";
        }
        clock_t start2 = clock();
        for(int x = T/2; x >= -T/2; x--){
            if(x%V == 0){
                skpList.remove(x);
                count--;
            }
        }
        clock_t end2 = clock();
        if(skpList.elements() == count){
            std::cout << "\tSIZE TEST: PASSED\n";
        }else{
            std::cout << "\tSIZE TEST: FAILED\n";
        }
        long double duration2 = (end2 - start2) / (long double) CLOCKS_PER_SEC;
        long double duration3 = duration1 + duration2;
        std::cout << "\tINSERTION TIME: " << duration1 << "s\n";
        std::cout << "\tREMOVAL TIME: " << duration2 << "s\n";
        std::cout << "\tTOTAL TIME: " << duration3 << "s\n";
    }

    std::cout << "\n";

    {
        std::cout << "TEST 8: INSERTING 5 VALUES AND USING THE COPY CONSTRUCTOR\n";
        SkipList<int> skpList1;
        for(int x = 0; x <= 5; x++){
            skpList1.insert(x);
        }
        SkipList<int> skpList2 = skpList1;
        bool containsSame = true;
        for(int x = 0; x <= 5; x++){
            if(!skpList2.contains(x)) containsSame = false;
        }
        if(containsSame == true) std::cout << "\tCONTAINS THE SAME ELEMENTS\n";
        else std::cout << "\tDOES NOT CONTAIN THE SAME ELEMENTS\n";

        if(skpList1.elements() == skpList2.elements()) std::cout << "\tSIZE MATCHES\n"; 
        else std::cout << "\tSIZE DOES NOT MATCH\n";
    }

    std::cout << "\n";

    {
        std::cout << "TEST 9: SETTING A SKIP LIST WITH SOME VALUES EQUAL TO ANOTHER SKIP LIST\n";
        SkipList<int> skpList1;
        SkipList<int> skpList2;
        for(int x = 0; x <= 5; x++){
            skpList1.insert(x);
        }
        for(int x = 6; x <= 10; x++){
            skpList2.insert(x);
        }
        skpList2 = skpList1;
        bool containsSame = true;
        for(int x = 0; x <= 5; x++){
            if(!skpList2.contains(x)) containsSame = false;
        }
        if(containsSame == true) std::cout << "\tCONTAINS THE SAME ELEMENTS\n"; 
        else std::cout << "\tDOES NOT CONTAIN THE SAME ELEMENTS\n";

        if(skpList1.elements() == skpList2.elements()) std::cout << "\tSIZE MATCHES\n"; 
        else std::cout << "\tSIZE DOES NOT MATCH\n";
    }

    std::cout << "\n";

    {
        std::cout << "TEST 10: USING A SKIPLIST COPY CONSTRUCTOR ON ITSELF AND PERFORMING INSERTIONS/REMOVALS\n";
        SkipList<int> skpList = skpList;
        size_t count = 0;
        for(int x = 0; x <= 100; x++){
            skpList.insert(x);
            count++;
        }

        bool containsWorks = true;
        for(int x = 0; x <= 100; x++){
            if(!skpList.contains(x)) containsWorks = false;
        }

        std::cout << "\tPRE-REMOVAL TESTS\n";
        if(skpList.elements() == count) std::cout << "\t\tSIZE TEST: PASSED\n";
        else std::cout << "\t\tSIZE TEST: FAILED\n";
        if(containsWorks == true) std::cout << "\t\tCONTAINS TEST: PASSED\n";
        else std::cout << "\t\tCONTAINS TEST: FAILED\n";

        for(int x = 0; x <= 100; x++){
            if(x%2 == 0){
                skpList.remove(x);
                count--;
            }
        }

        bool containsWorks2 = true;
        for(int x = 0; x <= 100; x++){
            if(x%2 == 0 && skpList.contains(x)) containsWorks2 = false;
        }
        std::cout << "\tPOST-REMOVAL TESTS\n";
        if(skpList.elements() == count) std::cout << "\t\tSIZE TEST: PASSED\n";
        else std::cout << "\t\tSIZE TEST: FAILED\n";
        if(containsWorks2 == true) std::cout << "\t\tCONTAINS TEST: PASSED\n";
        else std::cout << "\t\tCONTAINS TEST: FAILED\n";
    }

    std::cout << "\n";

    {
        std::cout << "TEST 11: INSERTING MANY NUMBERS IN REVERSE ORDER\n";
        // Consistent best-time insertions and removes, as they all happen at the front
        int T = 10000;
        SkipList<int> skpList;
        clock_t start1 = clock();
        for(int x = T; x >= 0; x--){
            skpList.insert(x);
        }
        clock_t end1 = clock();
        long double duration1 = (end1 - start1) / (long double) CLOCKS_PER_SEC;

        clock_t start2 = clock();
        for(int x = 0; x < T; x++){
            skpList.remove(x);
        }
        clock_t end2 = clock();
        long double duration2 = (end2 - start2) / (long double) CLOCKS_PER_SEC;

        std::cout << "\tBEST CASE INSERTION FOR: " << T << " VALUES: " << duration1 << "\n";
        std::cout << "\tBEST CASE REMOVAL FOR: " << T << " VALUES: " << duration2 << "\n";
    }
}
