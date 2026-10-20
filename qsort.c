#include "my_qsort.h"

/*
  quicksort эрэмбэлэх аргын цааш хуваагдах ёсгүй хэмжээ
*/
#ifndef CUTOFF
#define CUTOFF 10
#endif

static int init_seed = 0;  // Random seed 1 удаа эхлүүлнэ

/*
  Оруулан эрэмбэлэх функц.
  [lo, hi] завсрах тоонуудыг оруулан эрэмбэлэх аргаар эрэмбэлнэ.
*/
static void insertion_sort(int a[], int lo, int hi)
{
        int i, j, key;

        for (i = lo + 1; i <= hi; i++) {
                key = a[i];
                j = i - 1;

                while (j >= lo && a[j] > key) {
                        a[j + 1] = a[j];
                        j--;
                }

                a[j + 1] = key;
        }
}

/*
  Хоёр утгыг хооронд солих функц
*/
static void swap(int *a, int *b)
{
        int tmp = *a;
        *a = *b;
        *b = tmp;
}

/*
  [lo, hi] завсрыг санамсаргүйгээр холих функц.
*/
static void random_shuffle(int a[], int lo, int hi)
{
        if (init_seed == 0) {
                srand(time(NULL));
                init_seed = 1;
        }
        int i, j;
        for (i = lo; i <= hi; i++) {
                j = rand() % (hi - lo) + lo;
                swap(&a[i], &a[j]);
        }
}

/*
  1-pivot хурдан эрэмбэлэх функц.
*/
static void _single_pivot_qsort(int a[], int lo, int hi)
{
        if (hi <= lo)
                return;

        if (hi - lo <= CUTOFF) {
                insertion_sort(a, lo, hi);
                return;
        }

        int pivot = a[lo];
        int i = lo + 1;
        int j = hi;

        while (1) {
                while (i <= hi && a[i] < pivot)
                        i++;

                while (j > lo && a[j] > pivot)
                        j--;

                if (i >= j)
                        break;

                swap(&a[i], &a[j]);
                i++;
                j--;
        }

        swap(&a[lo], &a[j]);

        _single_pivot_qsort(a, lo, j - 1);
        _single_pivot_qsort(a, j + 1, hi);
}

/*
  wrapper function for _single_pivot_qsort
  _single_pivot_qsort-ыг дуудахад ашиглах функц
 */
void single_pivot_qsort(int a[], int lo, int hi)
{
        if (lo >= hi)
                return;

        random_shuffle(a, lo, hi);
        _single_pivot_qsort(a, lo, hi);
}

/*
  Dual-pivot хурдан эрэмбэлэх функц
*/
static void _dual_pivot_qsort(int a[], int lo, int hi)
{
        /*
          Энд dual-pivot quicksort хэрэгжүүл
        */

        if (hi <= lo)
                return;

        if (hi - lo <= CUTOFF) {
                insertion_sort(a, lo, hi);
                return;
        }

        if (a[lo] > a[hi])
                swap(&a[lo], &a[hi]);

        int pivot1 = a[lo];
        int pivot2 = a[hi];

        int lt = lo + 1;
        int gt = hi - 1;
        int i = lo + 1;

        while (i <= gt) {
                if (a[i] < pivot1) {
                        swap(&a[i], &a[lt]);
                        lt++;
                } else if (a[i] > pivot2) {
                        while (i < gt && a[gt] > pivot2)
                                gt--;

                        swap(&a[i], &a[gt]);
                        gt--;

                        if (a[i] < pivot1) {
                                swap(&a[i], &a[lt]);
                                lt++;
                        }
                }

                i++;
        }

        lt--;
        gt++;

        swap(&a[lo], &a[lt]);
        swap(&a[hi], &a[gt]);

        _dual_pivot_qsort(a, lo, lt - 1);
        _dual_pivot_qsort(a, lt + 1, gt - 1);
        _dual_pivot_qsort(a, gt + 1, hi);
}

/*
  wrapper function for _dual_pivot_qsort
  _dual_pivot_qsort-ыг дуудахад ашиглах функц
*/
void dual_pivot_qsort(int a[], int lo, int hi)
{
        if (lo >= hi)
                return;

        random_shuffle(a, lo, hi);
        _dual_pivot_qsort(a, lo, hi);
}
