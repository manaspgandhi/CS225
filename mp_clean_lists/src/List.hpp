/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  // @todo Graded in MP3.1
  if(length_ == 0){
    return;
  }
  
  ListNode* deNode = head_;
  ListNode* temp = deNode;
  
  while(deNode != NULL){
    temp = temp->next;
    delete deNode;
    deNode = temp;
  }

  deNode = NULL;
  temp = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  newNode->next = head_;
  newNode->prev = NULL;

  if(head_ != NULL){
    head_->prev = newNode;  
  }

  if(tail_ == NULL){
    tail_ = newNode;
  }

  head_ = newNode;

  length_++;
}


/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  newNode->next = NULL;
  newNode->prev = tail_;

  if(tail_ != NULL){
    tail_->next = newNode;
  }

  if(head_ == NULL){
    head_ = newNode;
  }

  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  if(length_ < splitPoint){
    return head_;
  }
  
  //gets you to desired node
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL && curr->prev != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if(length_ < 3){
    return;
  }

  int iterations = length_;
  if(iterations % 3 != 0){
    iterations--;
    if(iterations % 3 != 0){
      iterations--;
    }
  }

  iterations = iterations/3;

  ListNode* node1 = head_;
  ListNode* node2 = head_->next;
  ListNode* node3 = head_->next->next;
  ListNode* moving = node1;
  
  for(int i=0; i<iterations; i++){
    if(i==0){
      node1->next = node3->next;
      node3->next = node1;
      node1->prev = node3;
      node2->next = node3;
      node2->prev = NULL;
      head_ = node2;
      moving = node1;
    }
    
    else{
      node1 = moving->next;
      node2 = moving->next->next;
      node3 = moving->next->next->next;

      if(node3->next != NULL){
        node1->next = node3->next;
      }

      else{
        node1->next = NULL;
      }

      node3->next = node1;
      node3->next = node1;
      node1->prev = node3;
      node2->prev = moving;
      moving->next = node2;
      moving = node1;
    }
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint) {
    return;
  } 
  if (startPoint == NULL || endPoint == NULL){
    return;
  }

  ListNode* currentNode = startPoint;
  ListNode* previousNode = startPoint->prev;
  ListNode* nextNode = startPoint->next;

  currentNode->prev = nextNode;
  currentNode->next = endPoint->next;
  currentNode = nextNode;

  ListNode* tempNode = currentNode->next;
  
  while (currentNode != endPoint) {
    tempNode = currentNode->next;
    currentNode->next = currentNode->prev;
    currentNode->prev = tempNode;
    currentNode = tempNode;
  }

  endPoint->next = endPoint->prev;
  endPoint->prev = previousNode;
  
  if (head_ == startPoint) {
    head_ = endPoint;
  } else{
    previousNode->next = currentNode;
  }

  if (tail_ == endPoint) {
    tail_ = startPoint;
  } else{
    startPoint->next->prev = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode* headNode = head_;
  ListNode* copy = headNode;
  
  int count = 0;
  
  while((length_ - count) >= n){
    for(int i = 1; i < n; i++) {
      copy = copy->next;
    }
    
    reverse(headNode, copy);
    count += n;
    headNode = headNode->next;
    copy = headNode;
  }
  
  if(headNode != tail_ && headNode != NULL) {
    reverse(headNode, tail_);
  }
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
  head_ = merge(head_, otherList.head_);
  tail_ = head_;

  // make sure there is a node in the new list
  if (tail_ != NULL) {
    while (tail_->next != NULL){
      tail_ = tail_->next;
    }
  }

  length_ = otherList.length_ + length_;

  otherList.length_ = 0;
  otherList.head_ = NULL;
  otherList.tail_ = NULL;
    
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* headNode;

	if(first->data < second->data) {
		headNode = first;
		first = first->next;
	}
	else {
		headNode = second;
		second = second->next;
	}

	ListNode * bufuVariable = headNode;
	
  while (first != NULL && second != NULL) {
		if (second->data < first->data) {
			bufuVariable->next = second;
			second->prev = bufuVariable;
			second = second->next;
		}
		else {
			bufuVariable->next = first;
			first->prev = bufuVariable;
			first = first->next;
		}
		bufuVariable = bufuVariable->next;
	}

	if (first == NULL && second != NULL) { // first null, second data 
		bufuVariable->next = second;
		second->prev = bufuVariable;
	}
	
  if (first != NULL && second == NULL) { // first data, second null
		bufuVariable->next = first;
		first->prev = bufuVariable;
	}
	
  return headNode;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start->next == NULL) {
    return start;
  }

  ListNode* midpoint = split(start, chainLength/2);
  return merge(mergesort(start, chainLength/2), mergesort(midpoint, (chainLength%2) + (chainLength/2)));
}
