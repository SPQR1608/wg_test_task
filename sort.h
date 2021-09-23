#pragma once

namespace wg_test_sort
{
    template<class T>
    void swap(T& A, T& B)
    {
        T t = A; A = B; B = t;
    }

    template <class T>
    void quick_sort(T aArray[], int aL, int aR)
    {
        int i, j;
        int pivot;

        i = aL; j = aR;
        pivot = aArray[(aL + aR) / 2];

        do
        {
            while ((aArray[i] < pivot) && (i < aR)) i++;
            while ((pivot < aArray[j]) && (j > aL)) j--;

            if (i <= j)
            {
                swap(aArray[i], aArray[j]);               
                i++; j--;
            }
        } while (i <= j);

        if (aL < j) quick_sort(aArray, aL, j);
        if (i < aR) quick_sort(aArray, i, aR);
    }

    template <class T>
    void make_heap(T aArray[], int root, int bottom)
    {
        int maxChild;

        while ((root * 2 <= bottom))
        {
            if (root * 2 == bottom)
            {
                maxChild = root * 2;
            }           
            else if (aArray[root * 2] > aArray[root * 2 + 1]) 
            {
                maxChild = root * 2;
            }            
            else
            {
                maxChild = root * 2 + 1;
            }           
         
            if (aArray[root] < aArray[maxChild])
            {
                swap(aArray[root], aArray[maxChild]);
                root = maxChild;
            }
            else
                break;
        }
    }

    template <class T>
    void heap_sort(T aArray[], int n)
    {
        for (int i = (n / 2); i >= 0; i--)
            make_heap(aArray, i, n - 1);
        
        for (int i = n - 1; i >= 1; i--)
        {           
            swap(aArray[0], aArray[i]);
            make_heap(aArray, 0, i - 1);
        }
    }

    namespace better {
            
        template<class T>
        void compare(T& A, T& B)
        {
            if (B < A) swap(A, B);
        }

        template <class T>
        void insertion(T aArray[], int aL, int aR)
        {
            int i;
            for (i = aR; i > aL; i--)
                compare(aArray[i - 1], aArray[i]);

            for (i = aL + 2; i <= aR; i++)
            {
                int j = i; int v = aArray[i];
                while (v < aArray[j - 1])
                {
                    aArray[j] = aArray[j - 1]; 
                    --j;
                }                   
                aArray[j] = v;
            }          
        }

        template<class T>
        int partition(T aArray[], int aL, int aR)
        {
            int i = aL - 1;
            int j = aR;
            T v = aArray[aR];
            while (true)
            {
                while (aArray[++i] < v)
                    ;

                while (v < aArray[--j])
                    if (j == aL)
                        break;

                if (i >= j)
                    break;

                swap(aArray[i], aArray[j]);
            }

            swap(aArray[i], aArray[aR]);
            return i;
        }

        static const int M = 10;

        template <class T>
        void quick_sort_median(T aArray[], int aL, int aR)
        {
            if (aR - aL <= M)
            {
                insertion(aArray, aL, aR);
                return;
            }

            swap(aArray[(aL + aR) / 2], aArray[aR - 1]);
            compare(aArray[aL], aArray[aR - 1]);
            compare(aArray[aL], aArray[aR]);
            compare(aArray[aR - 1], aArray[aR]);
            int i = partition(aArray, aL + 1, aR - 1);
            quick_sort_median(aArray, aL, i - 1);
            quick_sort_median(aArray, i + 1, aR);
        }
    }

}