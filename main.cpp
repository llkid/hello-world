#include <iostream>

using namespace std;

template <typename T>
class FreeArray
{
public:
    FreeArray(size_t t) : cap_(t)
    {
        if (ptr)
        {
            delete[] ptr;
            ptr = nullptr;
        }
        ptr = new T[t * sizeof(T)];
    }
    ~FreeArray()
    {
        if (ptr)
        {
            delete[] ptr;
            ptr = nullptr;
        }
        cout << "destructor\n";
    }
    size_t sizeArray() const
    {
        return cap_;
    }

    T &operator[](int index)
    {
        return ptr[index];
    }

private:
    T *ptr = nullptr;
    size_t cap_{};
};

//此模板继承自freearray
template <class T>
class SearchArray : public FreeArray<T>
{
public:
    //构造函数
    SearchArray(int s) : FreeArray<T>(s) {}
    //拷贝构造函数
    SearchArray(const SearchArray &);
    //查找特定元素
    size_t findItem(T);
};

template <class T>
SearchArray<T>::SearchArray(const SearchArray &obj)
{
    for (int n = 0; n < this->sizeArray(); n++)
        this->operator[](n) = obj[n];
}

template <class T>
size_t SearchArray<T>::findItem(T item)
{
    for (int n = 0; n <= this->sizeArray(); n++)
    {
        if (this->operator[](n) == item)
            return n;
    }
    return -1;
}

int main(int argc, char **argv)
{
    //模板类的继承测试
    SearchArray<int> arrInt(10);

    int x;
    for (x = 0; x < 10; x++)
        arrInt[x] = x + 3;
    cout << "the value of int array is:";
    for (x = 0; x < 10; x++)
        cout << arrInt[x] << " ";

    cout << "\n\nfind the item 6 in the int array:\n";
    auto result = arrInt.findItem(6);
    if (result == -1)
        cout << "not find item 6!\n\n";
    else
        cout << "the index of 6 is :" << result << endl;
    return 0;
}