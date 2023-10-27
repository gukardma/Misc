public class test {
    /**
     * @param args
     */
    public static void main(String[] args) {
        String[] arr = { "bob", "joe", "sarah" };
        int arrSize = arr.length;
        int arrPointer = 2;

        String[] arr2 = new String[3];

        for (int i = 0; i < arrSize; i++) {
            if ((arrPointer + 1) > arrSize)
                arrPointer = 0;
            arr2[i] = arr[arrPointer];
            arrPointer++;
        }

        for (int i = 0; i < arr2.length; i++)
            System.out.println(arr2[i]);
    }
}