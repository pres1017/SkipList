For this project, I impelmented the skip lists data structure.

skiplist.h contains the actual implementation, with the following public functions:
  -constructors and destructors, including explicit constructors and copy constructors
  -insert(Comparable obj), inserts desired templated object, returns true if successful and false if the object already exists
  -remove(Comparable obj), removes desired objects, returns true if the object is present and false otherwise
  -contains(Comparable obj), returns true if the list contains the object and false otherwise
  -elements(), returns the number of elements in the data structure
  -printLayer(size_t layer, std::ostream& os), prints the elements at the desired layer to the desired output stream
  -printElements(std::ostream& os), prints all elements in the list layer-by-layer
  
 skiptests.cpp contains a testing suite verifying everything from basic 
 functionality to more specific edge cases, and demonstrates how to properly use the data structure.
  

The skip list functions similarly to a Linked List, except it can perform searches, deletions, and insertions in logarithmic time. This is accomplished by having multiple "layers," where each layer holds its own smaller linked list. 
The searching, deletion, and insertion algorithms start with a pointer at the top layer and 
moves down as certain conditions are met. In addition, the skip list is inserted at all times.

This project was developed independently. 
