DynQueue(int mi) {
         maxArrItems = mi;
         arr = (T[])new Object[maxArrItems];
     }

     // TODO: Implement enqueue with array and linked list as specified
     /**
      * Add an item to the queue
      * @param x Item to add to the queue
      */
     public void enqueue(T x) {
         if(arrItems == maxArrItems){
             isArrayMode = false;
 
             //transfers queue variables to linked list
             while(arrItems != 0){
                 if(isEmpty()) {
                     linkFront = new Node(arr[arrFront], null);
                     linkRear = linkFront;
                 } else {
                     linkRear.next = new Node(arr[arrFront], null);
                     linkRear = linkRear.next;
                 }
                 arrFront++;
                 arrItems--;
             }
             //releases variables from queue
             arr = null;
             arrFront = 0;
             arrRear = 0;
         }
 
         if(isArrayMode){
             if(isEmpty()) {
                 arr[arrRear] = x;
                 arrItems++;
             } else if((arrRear + 1) == maxArrItems) {
                 arrRear = 0;
                 arr[arrRear] = x;
                 arrItems++;
             } else {
                 arrItems ++;
                 arrRear ++;
                 arr[arrRear] = x;
             }
         } else {
             // Linked list mode
             linkRear.next = new Node(x, null);
             linkRear = linkRear.next;
         }
    }
 
 
     // TODO: Implement dequeue using array and linked list as specified
     /**
      * Remove an item from the queue
      * @return Item removed from the queue
      * @throws Exception Exception when queue is empty
      */
     public T dequeue() throws Exception {
         T item;
         if(isArrayMode){
             item = look();
             arr[arrFront] = null;
             arrFront ++;
             arrItems --;
         } else {
             item = linkFront.item;
             linkFront = linkFront.next;
             if (linkFront == null)
                 linkRear = null;
         }
         return item;
     }
 
     // TODO: Implement queue look with array or linked list as specified
     /**
      * Item at the end of the queue (next outgoing item)
      * @return Next item to be removed from the queue
      * @throws Exception Exception when queue is empty
      */
     public T look() throws Exception {
         if (isEmpty()){
             System.out.println("Queue is empty");
         }
         return arr[arrFront];
     }
 
     // TODO: Implement queue isEmpty with array or linked list as specified
     /**
      * Whether or not the queue is empty
      * @return True if queue is empty, false otherwise
      */
     public boolean isEmpty() {
         if(isArrayMode)
             return arrItems == 0;
         else
             return linkFront == null;
     }
 
 }
