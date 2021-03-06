#include <bits/stdc++.h>
#include <fstream>
#include <chrono>

using namespace std;

ifstream fin("date.in");

int n, *v, *copie, baza, nmax, *aux;

void citire_elemente() {
    int i;
    fin >> n >> nmax >> baza;
    v = new int[n];
    copie = new int[n];
    srand((unsigned) time(NULL));
    for (i = 0; i < n; i += 1) {
        v[i] = copie[i] = rand() % nmax;
    }
}

void copiere() {
    int i;
    for (i = 0; i < n; i += 1)
        v[i] = copie[i];
}

int val(int nr, int putere) {
    return (nr >> putere) & (baza - 1);
}

void RadixSort() {
    long long nr;
    int i, maxi, *aparitii, *afis, putere = 0, d;
    maxi = v[0];
    for (i = 1; i < n; i += 1) {
        if (v[i] > maxi)
            maxi = v[i];
    }
    d = int(log2(baza));
    aparitii = new int[baza];
    afis = new int[n];
    for (nr = 1; maxi >= nr; nr *= baza) {
        for (i = 0; i < baza; i += 1) {
            aparitii[i] = 0;
        }
        for (i = 0; i < n; i += 1) {
            afis[i] = 0;
        }
        for (i = 0; i < n; i += 1) {
            aparitii[val(v[i], putere)] += 1;
        }
        for (i = 1; i < baza; i += 1) {
            aparitii[i] += aparitii[i - 1];
        }
        for (i = n - 1; i >= 0; i -= 1) {
            afis[--aparitii[val(v[i], putere)]] = v[i];
        }
        for (i = 0; i < n; i += 1)
            v[i] = afis[i];
        putere += d;
    }
}

void CountingSort() {
    int maxi, i, val_relativa, *aparitii, *sortat;
    maxi = -(1 << 30);
    for (i = 0; i < n; i += 1) {
        if (v[i] > maxi)
            maxi = v[i];
    }
    aparitii = new int[maxi + 1];
    sortat = new int[n];
    for (i = 0; i <= maxi; i += 1)
        aparitii[i] = 0;
    for (i = 0; i < n; i += 1)
        aparitii[v[i]]++;
    for (i = 1; i <= maxi; i += 1)
        aparitii[i] += aparitii[i - 1];
    for (i = 0; i < n; i += 1) {
        val_relativa = aparitii[v[i]] - 1;
        sortat[val_relativa] = v[i];
        aparitii[v[i]] -= 1;
    }
    for (i = 0; i < n; i += 1)
        v[i] = sortat[i];
}

void QuickSort(int st, int dr) {
    if (st < dr) {
        int pivot, i, j;
        pivot = v[dr];
        i = st - 1;
        j = st;
        while (j < dr) {
            if (v[j] <= pivot) {
                i++;
                if (i != j) {
                    v[i] = v[i] ^ v[j];
                    v[j] = v[i] ^ v[j];
                    v[i] = v[i] ^ v[j];
                }
            }
            j += 1;
        }
        if (i + 1 != dr) {
            v[i + 1] = v[i + 1] ^ v[dr];
            v[dr] = v[i + 1] ^ v[dr];
            v[i + 1] = v[i + 1] ^ v[dr];
        }
        QuickSort(st, i);
        QuickSort(i + 2, dr);
    }
}

void ShellSort() {
    int interval = n >> 1, sublista, pivot, i;
    while (interval) {
        for (sublista = interval; sublista < n; sublista += 1) {
            pivot = v[sublista];
            for (i = sublista; i >= interval; i -= interval) {
                if (v[i - interval] > pivot) {
                    v[i] = v[i - interval];
                } else break;
            }
            v[i] = pivot;
        }
        interval = interval >> 1;
    }
}

void Merge(int st, int mij, int dr) {
    int i, j, m = 0;
    i = st;
    j = mij + 1;
    while (i <= mij && j <= dr) {
        if (v[i] <= v[j])
            aux[m++] = v[i++];
        if (v[j] < v[i])
            aux[m++] = v[j++];
    }
    while (i <= mij)
        aux[m++] = v[i++];
    while (j <= dr)
        aux[m++] = v[j++];
    i = st;
    j = 0;
    while (i <= dr) {
        v[i++] = aux[j++];
    }
}

void MergeSort(int st, int dr) {
    int mij;
    if (st < dr) {
        mij = st + (dr - st) / 2;
        MergeSort(st, mij);
        MergeSort(mij + 1, dr);
        Merge(st, mij, dr);
    }
}

int main() {
    int i, T, x;
    fin >> T;
    for (i = 0; i < T; i += 1) {
        citire_elemente();
        auto inceput3 = std::chrono::steady_clock::now();
        ShellSort();
        auto sfarsit3 = std::chrono::steady_clock::now();
        std::chrono::duration<double> secunde3 = sfarsit3 - inceput3;
        std::cout << "Timpul pentru Shell Sort este de: " << secunde3.count() << "s\n";
        copiere();

        aux = new int[n];
        auto inceput2 = std::chrono::steady_clock::now();
        MergeSort(0, n - 1);
        auto sfarsit2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> secunde2 = sfarsit2 - inceput2;
        std::cout << "Timpul pentru Merge Sort este de: " << secunde2.count() << "s\n";
        copiere();

        auto inceput4 = std::chrono::steady_clock::now();
        CountingSort();
        auto sfarsit4 = std::chrono::steady_clock::now();
        std::chrono::duration<double> secunde4 = sfarsit4 - inceput4;
        std::cout << "Timpul pentru Counting Sort este de: " << secunde4.count() << "s\n";
        copiere();

        auto inceput5 = std::chrono::steady_clock::now();
        QuickSort(0, n - 1);
        auto sfarsit5 = std::chrono::steady_clock::now();
        std::chrono::duration<double> secunde5 = sfarsit5 - inceput5;
        std::cout << "Timpul pentru Quick Sort este de: " << secunde5.count() << "s\n";
        copiere();

        auto inceput6 = std::chrono::steady_clock::now();
        sort(v, v + n);
        auto sfarsit6 = std::chrono::steady_clock::now();
        std::chrono::duration<double> secunde6 = sfarsit6 - inceput6;
        std::cout << "Timpul pentru Sort este de: " << secunde6.count() << "s\n";
        copiere();


        auto inceput1 = std::chrono::steady_clock::now();
        RadixSort();
        auto sfarsit1 = std::chrono::steady_clock::now();
        std::chrono::duration<double> secunde1 = sfarsit1 - inceput1;
        std::cout << "Timpul pentru Radix Sort este de: " << secunde1.count() << "s\n";
        copiere();

        cout << endl;
    }
    return 0;
}