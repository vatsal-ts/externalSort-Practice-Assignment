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
int bufferSize;
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
    // int spaceOccupied();
    // int freeSpace();
    // page *prev;
    // page *next;
    int numRec;
    // int freeSpacePtr;
    // vector<pair<int, int>> records;
    vector<int> records;
};

page::page()
{
    // numRec = freeSpacePtr = 0;
    numRec = 0;
}

/*
int page::spaceOccupied()
{
    return (freeSpacePtr + 16 + numRec * 4); // real occupied space
}

int page::freeSpace()
{
    return (pageSize - spaceOccupied()); // real free space
}
*/
class file
{
public:
    file();
    vector<page *> heap;
    vi readHowManyPages(int);
    void insert(int);
    void status();
    pair<int, int> search(int);
    int numPages;
};

file::file()
{
    numPages = 0;
}

void file::insert(int rec)
{
    // if(recSize+4>pageSize){
    //     cout<<"overflow\n";
    //     return;
    // }
    /* //old
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
    */
    if (heap.size() == 0)
    {
        heap.push_back(new page);
        numPages++;
        heap[heap.size() - 1]->numRec++;
        heap[heap.size() - 1]->records.push_back(rec);
    }

    else if (heap[heap.size() - 1]->numRec == pageSize)
    {
        heap.push_back(new page);
        numPages++;
        heap[heap.size() - 1]->numRec++;
        heap[heap.size() - 1]->records.push_back(rec);
    }

    else
    {
        heap[heap.size() - 1]->numRec++;
        heap[heap.size() - 1]->records.push_back(rec);
    }
}

// vi file::readHowManyPages(int n){
//     vi a;
//     for(int i=0)
// }

void extSort(file fileToSort)
{
    int B = bufferSize;
    int n = fileToSort.numPages;
    int numPass = 0;
    // Let's make bufferSize page long runs-Pass 0
    numPass++;
    vvi prevPassOp;
    for (int i = 0; i <= (n - 1 / B); i++)
    {
        int start = i * B;
        int end = min(((i + 1) * B) - 1, n - 1);
        for (int i = start; i <= end; i++)
        {
            vi temp(all(((fileToSort.heap)[i])->records));
            sortall(temp);
            prevPassOp.pb(temp);
        }
    }
    // Subsequently we will execute a b-1 merge until one run is left
    while (prevPassOp.size() > 1)
    {
        vvi thisPassOp;
        for (int i = 0; i <= (n - 1 / (B - 1)); i++)
        {
            int start = i * (B - 1);
            int end = min(((i + 1) * (B - 1)) - 1, int(prevPassOp.size() - 1));
            for (int i = start; i <= end; i++)
            {
                vi temp(all(prevPassOp[i]));
                sortall(temp);
                thisPassOp.pb(temp);
            }
        }
        prevPassOp=thisPassOp;
    }
}
/*
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
*/

void file::status()
{
    // cout << "stat";
    cout << heap.size() << " ";
    for (auto pages : heap)
        cout << pages->numRec << " " /*<<pages->freeSpace()<<" "*/;
    cout /*<< "lol"*/ << "\n";
}

int main()
{
    fast;
    cin >> bufferSize >> pageSize;
    file myFile;
    int totalNumRec;
    cin >> totalNumRec;
    fo(i, totalNumRec)
    {
        int k;
        cin >> k;
        myFile.insert(k);
    }
    // cout<<myFile.numPages<<"\n";
    // for(auto x:myFile.heap){
    //     cout<<x->numRec<<"\n";
    // }
}