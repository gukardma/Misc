public class HW<T> implements GenQueue<T> {

    // Note: Most or all member variables should be private. They are public
    // for testing purposes only, so that class internals can be inspected.

    /** True in array mode, false when switched to linked list mode */
    public boolean isArrayMode = true;

    public int maxArrItems;
    /** Maximum items for array mode */

    public T[] arr = null;
    /** Array of items for queue */
    public int arrItems = 0;
    /** Number of items in array queue */
    public int arrFront = 0;
    /** Front of array queue */
    public int arrRear = 0;
    /** Rear of array queue */

    public Node linkFront = null;
    /** Front of linked list queue */
    public Node linkRear = null;

    /** Rear of linked list queue */

    public class Node // public for testing purposes only
    {
        public T item;
        public Node next;

        Node(T i, Node n) {
            item = i;
            next = n;
        }

        Node() {
        }
    }

    // Utility method to get internal array as typed container
    public Collection<T> _arr_coll() {
        ArrayList<T> al = new ArrayList<T>(arr.length);
        // for(int i = 0; i < arr.length; i++) {
        // al.add(arr[i]);
        // }
        Collections.addAll(al, arr);
        return (Collection<T>) al;
    }

    // DONE: Implement DynQueue constructor
    @SuppressWarnings("unchecked")
    /**
     * Create a dynamic queue which will remain in array mode while it has
     * a maximum of "mi" items.
     * 
     * @param mi Maximum number of items for array mode
     */
    HW(int mi) {
        maxArrItems = mi;
        arr = (T[]) new Object[maxArrItems];
    }

    // TODO: Implement enqueue with array and linked list as specified
    /**
     * Add an item to the queue
     * 
     * @param x Item to add to the queue
     */
    public void enqueue(T x) {
        System.out.println("\nAdding Item: " + x);
        if (arrItems == maxArrItems) {
            isArrayMode = false;

            // transfers queue variables to linked list (not working)
            while (arrItems != 0) {
                // Loop back in Queue
                // if ((arrFront + 2) > arrItems)
                // arrFront = 0;
                if (isEmpty()) {
                    linkFront = new Node(arr[arrFront], null);
                    linkRear = linkFront;
                } else {
                    linkRear.next = new Node(arr[arrFront], null);
                    linkRear = linkRear.next;
                }
                arrFront++;
                arrItems--;
            }
            // releases queue variables
            arr = null;
            arrFront = 0;
            arrRear = 0;
        }

        // Queue mode //
        if (isArrayMode) {
            if (isEmpty()) {
                arr[arrRear] = x;
                arrItems++;
            } else if ((arrRear + 1) == maxArrItems) {
                arrRear = 0;
                arr[arrRear] = x;
                arrItems++;
            } else {
                arrItems++;
                arrRear++;
                arr[arrRear] = x;
            }
        }
        // Queue mode //

        // LinkedList Mode /////
        if (!isArrayMode) {
            linkRear.next = new Node(x, null);
            linkRear = linkRear.next;
        } // LinkedList Mode /////

        // Visualization
        if (isArrayMode) {
            System.out.println("\nArray Items:");
            for (int i = 0; i < maxArrItems; i++)
                System.out.println(arr[i]);
        } else {
            System.out.println("\nLink Items:");
            Node p = linkFront;
            while (p != null) {
                System.out.println(p.item);
                p = p.next;
            }
        }
    }

    // TODO: Implement dequeue using array and linked list as specified
    /**
     * Remove an item from the queue
     * 
     * @return Item removed from the queue
     * @throws Exception Exception when queue is empty
     */
    public T dequeue() throws Exception {
        // Code not complete
        T item = look();
        System.out.println("\nRemoving item: " + item);
        // if(false) {
        // throw new Exception("ERROR: dequeue() with empty queue");
        // }
        // return item;
        if (isArrayMode) {
            arr[arrFront] = null;
            arrFront++;
            arrItems--;
        } else {
            System.out.println("atempted to deque with ll");
        }

        // Visualization
        if (isArrayMode) {
            System.out.println("\nArray Items:");
            for (int i = 0; i < maxArrItems; i++)
                System.out.println(arr[i]);
        } else {
            System.out.println("\nLink Items:");
            Node p = linkFront;
            while (p != null) {
                System.out.println(p.item);
                p = p.next;
            }
        }
        return item;
    }

    // TODO: Implement queue look with array or linked list as specified
    /**
     * Item at the end of the queue (next outgoing item)
     * 
     * @return Next item to be removed from the queue
     * @throws Exception Exception when queue is empty
     */
    public T look() throws Exception {
        // T item;
        // if(false) {
        // throw new Exception("ERROR: look() with empty queue");
        // }
        if (isEmpty()) {
            System.out.println("Queue is empty");
        }
        return arr[arrFront];
    }

    // TODO: Implement queue isEmpty with array or linked list as specified
    /**
     * Whether or not the queue is empty
     * 
     * @return True if queue is empty, false otherwise
     */
    public boolean isEmpty() {
        // boolean x = false;
        // return x;
        if (isArrayMode)
            return arrItems == 0;
        else
            return linkFront == null;
    }

}
