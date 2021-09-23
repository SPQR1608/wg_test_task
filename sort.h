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
        int partition(T aArray[], int lo, int hi)
        {
            int i = lo;
            int j = hi + 1;
            int v = aArray[lo];
            while (true)
            {
                while (aArray[++i] < v)
                    if (i == hi) break;

                while (v < aArray[--j])
                    if (j == lo) break;         

                if (i >= j) break;

                swap(aArray[i], aArray[j]);
            }
            swap(aArray[lo], aArray[j]);
            return j;
        }

        template <class T>
        void insertion(T aArray[], int l, int r)
        {
            int i;
            for (i = r; i > l; i--) 
                compare(aArray[i - 1], aArray[i]);

            for (i = l + 2; i <= r; i++)
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

        static const int M = 10;

        template <class T>
        void quick_sort_median(T aArray[], int l, int r)
        {
            if (r - l <= M)
            {
                insertion(aArray, l, r);
                return;
            }

            swap(aArray[(l + r) / 2], aArray[r - 1]);
            compare(aArray[l], aArray[r - 1]);
            compare(aArray[l], aArray[r]);
            compare(aArray[r - 1], aArray[r]);
            int i = partition(aArray, l, r);
            quick_sort_median(aArray, l, i - 1);
            quick_sort_median(aArray, i + 1, r);
        }

        template <class T>
        void hybrid_sort(T aArray[], int l, int r)
        {
            quick_sort_median(aArray, l, r);            
        }
    }

}