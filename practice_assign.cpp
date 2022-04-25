#include <bits/stdc++.h>
using namespace std;

/* #region   */

#define gc getchar_unlocked
#define fo(i, n) for (auto i = 0; i < n; i++)
#define Fo(i, k, n) for (auto i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define si(x) scanf("%d", &x)
#define sl(x) scanf("%lld", &x)
#define ss(s) scanf("%s", s)
#define pi(x) printf("%d\n", x)
#define pl(x) printf("%lld\n", x)
#define ps(s) printf("%s\n", s)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<pll> vpll;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<vll> vvll;
#define lb lower_bound
#define ub upper_bound
#define PRESENT -1
#define FULL 0
#define SUCCESS 1
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
/* #endregion */

int pageSize;
/*
Later cosnider if record is too big to fit in a page alone
*/

bool comparePairSec(pair<int, int> a, pair<int, int> b)
{
    return (a.S < b.S);
}

class page
{
public:
    page();
    int spaceOccupied();
    int freeSpace();
    page *prev;
    page *next;
    int numRec;
    int freeSpacePtr;
    vector<pair<int, int>> records;
};

page::page()
{
    numRec = freeSpacePtr = 0;
}

int page::spaceOccupied()
{
    return (freeSpacePtr + 16 + numRec * 4); // real occupied space
}

int page::freeSpace()
{
    return (pageSize - spaceOccupied()); // real free space
}

class file
{
public:
    file();
    vector<page *> heap;
    void insert(int, int);
    void status();
    pair<int, int> search(int);
    int numPages;
};

file::file()
{
    numPages = 0;
}

void file::insert(int recSize, int primaryKey)
{
    // if(recSize+4>pageSize){
    //     cout<<"overflow\n";
    //     return;
    // }

    if (numPages == 0)
    {
        page *newPage = new page;
        numPages++;
        heap.push_back(newPage);
        newPage->prev = NULL;
        newPage->next = NULL;
        newPage->records.push_back({recSize, primaryKey});
        sort(all(newPage->records), comparePairSec);
        heap[numPages - 1]->freeSpacePtr += recSize;
        heap[numPages - 1]->numRec++;
        return;
    }
    else
    {
        pair<int, int> value = {-1, -1}; // freeSpace,Index
        for (int i = 0; i < numPages; i++)
        {
            if (((heap[i]->spaceOccupied() + recSize + 4) <= pageSize)) // less or equal to because freeSpacePtr points to next Free Location
            {
                // heap[i]->records.push_back({recSize, primaryKey});
                // sort(all(heap[i]->records),comparePairSec);
                // heap[i]->freeSpacePtr += recSize;
                // heap[i]->numRec++;
                // return;
                if (value.F < heap[i]->freeSpace())
                {
                    value.F = heap[i]->freeSpace();
                    value.S = i;
                }
            }
        }
        if (value.F != -1 && value.S != -1)
        {
            heap[value.S]->records.push_back({recSize, primaryKey});
            sort(all(heap[value.S]->records), comparePairSec);
            heap[value.S]->freeSpacePtr += recSize;
            heap[value.S]->numRec++;
            return;
        }
    }
    // new page Creation situation
    page *newPage = new page;
    numPages++;
    heap.push_back(newPage);
    heap[numPages - 2]->next = newPage;
    newPage->prev = heap[numPages - 2];
    newPage->next = NULL;
    newPage->records.push_back({recSize, primaryKey});
    sort(all(newPage->records), comparePairSec);
    heap[numPages - 1]->freeSpacePtr += recSize;
    heap[numPages - 1]->numRec++;
    // cout << heap[numPages - 1]->spaceOccupied() + recSize + 4 << "occupied.\n";
    // (heap[numPage - 1]->freeSpacePtr) += recSize;
    // (heap[numPage - 1]->numRec)++;
}

pair<int, int> file::search(int primaryKey)
{
    for (int i = 0; i < heap.size(); i++)
    {
        for (int j = 0; j < heap[i]->records.size(); j++)
        {
            if ((heap[i]->records[j]).second == primaryKey)
                return {i, j};
        }
    }
    return {-1, -1};
}

void file::status()
{
    // cout << "stat";
    cout << heap.size() << " ";
    for (auto pages : heap)
        cout << pages->numRec << " " /*<<pages->freeSpace()<<" "*/;
    cout /*<< "lol"*/ << "\n";
}