#include <iostream>
#include <vector>
using namespace std;

class SET
{
public:
    vector<int> set;

    void clear()
    {
        set.clear();
    }

    int Size()
    {
        return set.size();
    }

    bool belongsto(int d)
    {
        int left = 0;
        int right = set.size() - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (set[mid] == d)
                return true;
            if (set[mid] < d)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return false;
    }

    void print()
    {
        for (size_t i = 0; i < set.size(); ++i)
        {
            cout << set[i];
            if (i + 1 < set.size())
                cout << ",";
        }
        cout << endl;
    }

    int insert(int d)
    {
        if (belongsto(d))
        {
            return Size();
        }
        else
        {
            int left = 0;
            int right = set.size() - 1;
            int pos = -1;
            while (left <= right)
            {
                int mid = (left + right) / 2;
                if (set[mid] == d)
                {
                    pos = mid;
                    break;
                }
                else if (set[mid] < d)
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
            if (pos == -1)
            {
                pos = left;
            }
            set.insert(set.begin() + pos, d);
            return Size();
        }
    }

    int Delete(int d)
    {
        if (belongsto(d))
        {
            int left = 0;
            int right = set.size() - 1;
            int delpos = -1;
            while (left <= right)
            {
                int mid = (left + right) / 2;
                if (set[mid] == d)
                {
                    delpos = mid;
                    break;
                }
                else if (set[mid] < d)
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
            if (delpos != -1)
            {
                set.erase(set.begin() + delpos);
            }
        }
        return Size();
    }

    int Union(SET d)
    {
        for (int i = 0;i<d.Size();i++)
        {
            insert(d.set[i]);
        }
        return Size();
    }

    int Intersection(SET d)
    {
        SET finalSet;

        for (int i = 0;i<d.Size();i++)
        {
            if (belongsto(d.set[i]))
            {
                finalSet.insert(d.set[i]);
            }
        }

        set = finalSet.set;
        return Size();
    }

    int difference(SET d)
    {
        for (int i = 0;i<d.Size();i++)
        {
            Delete(d.set[i]);
        }
        return Size();
    }

    int Symmetric(SET d)
    {
        SET final;
        for(int i = 0;i<d.Size();i++)
        {
            final.insert(d.set[i]);
        }
        for(int j = 0;j<Size();j++)
        {
            final.insert(set[j]);
        }

        SET finalSet;

        for (int i = 0;i<d.Size();i++)
        {
            if (belongsto(d.set[i]))
            {
                finalSet.insert(d.set[i]);
            }
        }

        for (int k = 0; k < finalSet.Size(); k++)
        {
            final.Delete(finalSet.set[k]);
        }

        set = final.set;
        return Size();
    }
};

int main()
{
    int N;
    N = 210000;

    vector<SET> v(N + 1);

    int command;
    int setNum, data;

    while (cin >> command)
    {
        if (cin.eof())
            break;

        switch (command)
        {
        case 1: // Insert
            cin >> setNum >> data;
            if (setNum <= N)
                cout << v[setNum].insert(data) << endl;
            break;

        case 2: // Delete
            cin >> setNum >> data;
            if (setNum <= N)
                cout << v[setNum].Delete(data) << endl;
            break;

        case 3: // Belongs To
            cin >> setNum >> data;
            if (setNum <= N && v[setNum].belongsto(data))
                cout << 1 << endl;
            else
                cout << 0 << endl;
            break;

        case 4: // Union
            cin >> setNum >> data;
            if (setNum <= N && data <= N)
                cout << v[setNum].Union(v[data]) << endl;
            break;

        case 5: // Intersection
            cin >> setNum >> data;
            if (setNum <= N && data <= N)
                cout << v[setNum].Intersection(v[data]) << endl;
            break;

        case 6: // Size
            cin >> setNum;

            if (setNum <= N)
                cout << v[setNum].Size() << endl;
            else
                cout << 0 << endl;
            break;

        case 7: // Difference
            cin >> setNum >> data;
            if (setNum == data)
            {
                v[setNum].clear();
            }
            if (setNum <= N && data <= N)
                cout << v[setNum].difference(v[data]) << endl;
            break;

        case 8: // Symmetric Difference
            cin >> setNum >> data;
            if (setNum == data)
            {
                v[setNum].clear();
                // cout<<0<<endl;
            }
            if (setNum <= N && data <= N)
                cout << v[setNum].Symmetric(v[data]) << endl;
            break;

        case 9: // Print
            cin >> setNum;
            if (v[setNum].Size() == 0)
            {
                cout << endl;
                break;
            }
            if (setNum <= N)
                v[setNum].print();
            else
                cout << endl;
            break;

        default:
            break;
        }
    }

    return 0;
}