#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;
int PageSize;

class Page
{
private:
public:
    Page *Prev;
    Page *Next;
    int start;
    int count;
    vector<int> DataArea;
    vector<int> BookArea;
    Page()
    {
        Prev = nullptr;
        Next = nullptr;
        start = 0;
        count = 0;
    }
    int SumRecordSize()
    {
        if (BookArea.size() == 0)
        {
            return 0;
        }
        int sum = 0;
        for (int i = 0; i < BookArea.size() - 1; i++)
        {
            sum += BookArea[i + 1] - BookArea[i];
        }
        sum += start - BookArea[BookArea.size() - 1];
        return sum;
    }
    int AvaliableSpace()
    {
        return PageSize - 16 - BookArea.size() * 4 - SumRecordSize();
    }
    void push(int RecordSize, int PrimaryKey)
    {
        // 4 IS REQUIRED FOR BOOK AREA
        if (AvaliableSpace() >= RecordSize + 4)
        {
            BookArea.push_back(start);
            start = start + RecordSize;
            DataArea.push_back(PrimaryKey);
            count++;
        }
        else
        {
            cout << "CAN'T INSERT" << endl;
        }
    }
};

class File
{
private:
public:
    Page *header;
    File()
    {
        header = nullptr;
    }
    void insert(int RecordSize, int PrimaryKey)
    {
        Page *ptr = header;
        // No PAGE
        if (ptr == nullptr)
        {
            ptr = new Page();
            header = ptr;
            ptr->push(RecordSize, PrimaryKey);
            return;
        }
        // 1ST PAGE AND INSERT IN THAT PAGE
        if (header != nullptr)
        {
            if (header->AvaliableSpace() >= RecordSize + 4)
            {
                header->push(RecordSize, PrimaryKey);
                return;
            }
            else
            {
                Page *ptr = header;
                while (ptr->Next != nullptr)
                {
                    if (ptr->AvaliableSpace() >= RecordSize + 4)
                    {
                        ptr->push(RecordSize, PrimaryKey);
                        return;
                    }
                    else
                    {
                        ptr = ptr->Next;
                    }
                }
                if (ptr->AvaliableSpace() >= RecordSize + 4)
                {
                    ptr->push(RecordSize, PrimaryKey);
                    return;
                }
                else
                {
                    Page *ptr2 = new Page();
                    ptr2->push(RecordSize, PrimaryKey);
                    ptr2->Prev = ptr;
                    ptr->Next = ptr2;
                    return;
                }
            }
        }
    }
    void search(int &pageid, int &slotid, int value)
    {
        Page *ptr = header;
        pageid = 0;
        slotid = 0;
        while (ptr != nullptr)
        {
            for (int i = 0; i < ptr->BookArea.size(); i++)
            {
                if (value == ptr->DataArea[i])
                {
                    slotid = i;
                    return;
                }
            }
            pageid++;
            ptr = ptr->Next;
        }
        pageid = -1;
        slotid = -1;
        return;
    }
    void printStatus()
    {
        Page *ptr = header;
        int noofpages = 0;
        while (ptr != nullptr)
        {
            noofpages++;
            ptr = ptr->Next;
        }
        cout << noofpages << " ";
        ptr = header;
        while (ptr != nullptr)
        {
            cout << ptr->count << " ";
            ptr = ptr->Next;
        }
        return;
    }
};
int main()
{
    cin >> PageSize;
    File *A = new File();
    int x;
    while (cin >> x)
    {
        if (x == 1)
        {
            int recordsize;
            int pkey;
            cin >> recordsize >> pkey;
            A->insert(recordsize, pkey);
        }
        else if (x == 2)
        {
            A->printStatus();
            cout << endl;
        }
        else if (x == 3)
        {
            int val;
            cin >> val;
            int pageid, recordno;
            A->search(pageid, recordno, val);
            cout << pageid << " " << recordno << endl;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}