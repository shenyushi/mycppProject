#include <iostream>
#include <string>
#include <cstdlib>
#include <deque>
#include <vector>
using namespace std;

class error
{
};
class Expression;

class Number
{
    friend Expression;

private:
    deque<int> data;
    bool minus;
    int dot; //after data[size-dot-1]

public:
    Number() : minus(false), dot(0) {}
    ~Number() {}
    friend ostream &operator<<(ostream &out, const Number &x)
    {
        if (x.minus)
            out << '-';
        for (int i = 0; i < int(x.data.size()); ++i)
        {
            out << x.data[i];
            if (i == int(x.data.size()) - x.dot - 1 && x.dot)
                out << '.';
        }
        return out;
    }
    bool operator<(const Number &x2) const //abs<
    {
        int dintN = (data.size() - dot) - (x2.data.size() - x2.dot);
        if (dintN < 0)
            return true;
        else if (dintN > 0)
            return false;
        int i = 0, j = 0;
        while (i < int(data.size()) && j < int(x2.data.size()))
        {
            int d = data[i++] - x2.data[j++];
            if (d < 0)
                return true;
            else if (d > 0)
                return false;
        }
        if (j < int(x2.data.size()))
            return true;
        return false;
    }
    bool simplify()
    {
        bool flag = false;
        int popNum = 0;
        for (int i = 0; i < int(data.size()) - dot - 1; ++i)
        {
            if (data[i])
                break;
            ++popNum;
            flag = true;
        }
        while (popNum--)
            data.pop_front();
        int dotMove = 0;
        for (int i = 0; i < dot; ++i)
        {
            int j = data.size() - 1 - i;
            if (data[j])
                break;
            dotMove++;
            flag = true;
        }
        for (int i = 0; i < dotMove; ++i)
            data.pop_back();
        dot -= dotMove;
        if (data.size() == 1 && data[0] == 0)
        {
            flag = true;
            minus = false;
        }
        return flag;
    }
};

class Expression
{
private:
    Number left, right;
    char operater;
    int maxN;

public:
    Expression(const string &str, int n = 128) : maxN(n)
    {
        int i = 0, j = 0;
        int dot1 = -1, dot2 = -1;
        while (str[i] != '<' && i < int(str.size()))
        {
            if (str[i] == '-')
                left.minus = true;
            else if (str[i] == '.')
            {
                dot1 = j;
                if (str[i - 1] - '0' < 0 || str[i - 1] - '0' > 9 || str[i + 1] - '0' < 0 || str[i + 1] - '0' > 9)
                    throw error();
            }
            else
            {
                int n = str[i] - '0';
                if (n < 0 || n > 9)
                    throw error();
                left.data.push_back(n);
                ++j;
            }
            ++i;
        }
        if (i == int(str.size()) || i > maxN || !i)
            throw error();
        if (dot1 >= 0)
            left.dot = j - dot1;
        operater = str[i + 1];
        if ((operater != '+' && operater != '-' && operater != '*' && operater != '/') || str[i + 2] != '>')
            throw error();
        i = i + 3;
        if (i == int(str.size()))
            throw error();
        int rightStart = i;
        j = 0;
        while (i < int(str.size()))
        {
            if (str[i] == '-')
                right.minus = true;
            else if (str[i] == '.')
            {
                dot2 = j;
                if (str[i - 1] - '0' < 0 || str[i - 1] - '0' > 9 || str[i + 1] - '0' < 0 || str[i + 1] - '0' > 9)
                    throw error();
            }
            else
            {
                int n = str[i] - '0';
                if (n < 0 || n > 9)
                    throw error();
                right.data.push_back(n);
                ++j;
            }
            ++i;
        }
        if (dot2 >= 0)
            right.dot = j - dot2;
        if (i - rightStart > maxN)
            throw error();
        if (left.simplify() || right.simplify())
            throw error();
    }
    ~Expression() {}
    void test()
    {
        cout << left << operater << right;
    }
    Number calculate() const;

private:
    void add(Number &result) const;
    void subtract(Number &result, bool isRev) const;
    void multiply(Number &result) const;
    void divide(Number &result) const;
};

Number Expression::calculate() const
{
    Number result;
    bool isDiff = left.minus ^ right.minus;
    switch (operater)
    {
    case '+':
        if (!isDiff)
        {
            add(result);
            result.minus = left.minus;
        }
        else if (left < right)
        {
            subtract(result, true);
            result.minus = right.minus;
        }
        else
        {
            subtract(result, false);
            result.minus = left.minus;
        }
        break;
    case '-':
        if (isDiff)
        {
            add(result);
            result.minus = left.minus;
        }
        else if (left < right)
        {
            subtract(result, true);
            result.minus = !left.minus;
        }
        else
        {
            subtract(result, false);
            result.minus = left.minus;
        }
        break;
    case '*':
        multiply(result);
        result.minus = isDiff ? true : false;
        break;
    default:
        if (left.dot || right.dot)
            throw error();
        divide(result);
        result.minus = isDiff ? true : false;
    }
    result.simplify();
    int n = result.minus ? 1 : 0, m = result.dot ? 1 : 0;
    if (int(result.data.size()) + n + m > maxN)
    {
        if (int(result.data.size()) + n - result.dot > maxN)
            throw error();
        if (int(result.data.size()) + n - result.dot < maxN)
            while (int(result.data.size()) + n + m > maxN)
            {
                result.data.pop_back();
                --result.dot;
            }
        else
            while (int(result.data.size()) + n + m > maxN + 1)
            {
                result.data.pop_back();
                --result.dot;
            }
        result.simplify();
    }
    return result;
}

void Expression::add(Number &result) const
{
    int i1 = left.data.size() - 1, i2 = right.data.size() - 1;
    int ddecN = left.dot - right.dot;
    if (ddecN > 0)
    {
        result.dot = left.dot;
        for (int i = 0; i < ddecN; ++i)
            result.data.push_front(left.data[i1--]);
    }
    else
    {
        result.dot = right.dot;
        for (int i = 0; i < -ddecN; ++i)
            result.data.push_front(right.data[i2--]);
    }
    int carry = 0;
    while (i1 >= 0 && i2 >= 0)
    {
        int tmp = left.data[i1--] + right.data[i2--] + carry;
        result.data.push_front(tmp % 10);
        carry = tmp / 10;
    }
    while (i1 >= 0 && carry)
    {
        int tmp = left.data[i1--] + carry;
        result.data.push_front(tmp % 10);
        carry = tmp / 10;
    }
    while (i1 >= 0)
        result.data.push_front(left.data[i1--]);
    while (i2 >= 0 && carry)
    {
        int tmp = right.data[i2--] + carry;
        result.data.push_front(tmp % 10);
        carry = tmp / 10;
    }
    while (i2 >= 0)
        result.data.push_front(right.data[i2--]);
    if (carry)
        result.data.push_front(1);
}

void Expression::subtract(Number &result, bool isRev) const
{
    const Number *n1, *n2;
    if (isRev)
    {
        n1 = &right;
        n2 = &left;
    }
    else
    {
        n1 = &left;
        n2 = &right;
    }
    int i1 = n1->data.size() - 1, i2 = n2->data.size() - 1;
    int carry = 0;
    int ddecN = n1->dot - n2->dot;
    if (ddecN > 0)
    {
        result.dot = n1->dot;
        for (int i = 0; i < ddecN; ++i)
            result.data.push_front(n1->data[i1--]);
    }
    else if (ddecN < 0)
    {
        carry = -1;
        result.dot = n2->dot;
        for (int i = 0; i < -ddecN; ++i)
        {
            if (!i)
                result.data.push_front((10 - n2->data[i2--]) % 10);
            else
                result.data.push_front(9 - n2->data[i2--]);
        }
    }
    else
        result.dot = n1->dot;
    while (i2 >= 0)
    {
        int tmp = n1->data[i1--] - n2->data[i2--] + carry;
        result.data.push_front((tmp + 10) % 10);
        carry = (tmp < 0) ? -1 : 0;
    }
    while (i1 >= 0 && carry)
    {
        int tmp = n1->data[i1--] + carry;
        result.data.push_front(tmp);
        carry = (tmp < 0) ? -1 : 0;
    }
    while (i1 >= 0)
        result.data.push_front(n1->data[i1--]);
}

void Expression::multiply(Number &result) const
{
    int l1, l2, i;
    for (i = 0; i < int(left.data.size()) && !left.data[i]; ++i)
        ;
    l1 = i;
    for (i = 0; i < int(right.data.size()) && !right.data[i]; ++i)
        ;
    l2 = i;
    if (l1 == int(left.data.size()) || l2 == int(right.data.size()))
    {
        result.data.push_front(0);
        return;
    }
    const Number *n1 = &left, *n2 = &right;
    int dL = (int(left.data.size()) - l1) - (int(right.data.size()) - l2);
    if (dL < 0)
    {
        n1 = &right;
        n2 = &left;
        swap(l1, l2);
    }
    int carry = 0;
    int start = 0;
    for (int i2 = int(n2->data.size()) - 1; i2 >= l2; --i2)
    {
        int key = n2->data[i2];
        if (!key)
        {
            result.data.push_front(0);
            ++start;
            continue;
        }
        vector<int> arr;
        for (int i1 = int(n1->data.size()) - 1; i1 >= l1; --i1)
            arr.push_back(n1->data[i1] * key);
        for (int i = 0; i < int(arr.size()); ++i)
        {
            int tmp = carry + arr[i];
            arr[i] = tmp % 10;
            carry = tmp / 10;
        }
        if (carry)
            arr.push_back(carry);
        carry = 0;
        for (int i = 0; i < int(arr.size()); ++i)
        {
            int j = int(result.data.size()) - 1 - start - i;
            if (j >= 0)
            {
                int tmp = arr[i] + result.data[j] + carry;
                result.data[j] = tmp % 10;
                carry = tmp / 10;
            }
            else if (carry)
            {
                int tmp = arr[i] + carry;
                result.data.push_front(tmp % 10);
                carry = tmp / 10;
            }
            else
                result.data.push_front(arr[i]);
        }
        if (carry)
            result.data.push_front(carry);
        ++start;
    }
    result.dot = left.dot + right.dot;
    while (result.dot >= int(result.data.size()))
        result.data.push_front(0);
}

void Expression::divide(Number &result) const
{
    if (int(right.data.size()) == 1 && right.data[0] == 0)
        throw error();
    if (int(left.data.size()) == 1 && left.data[0] == 0)
    {
        result.data.push_front(0);
        return;
    }
    deque<int> part;
    bool empty = false;
    int i1 = 0, i2 = 0, i3;
    for (; i1 < int(left.data.size()) && i2 < int(right.data.size()); ++i2)
        part.push_back(left.data[i1++]);
    if (i1 == int(left.data.size()))
        empty = true;
    for (; i2 < int(right.data.size()); ++i2)
    {
        part.push_back(0);
        result.data.push_front(0);
        ++result.dot;
    }
    int sum = 0;
    while (true)
    {
        bool isLess = false;
        if (part.size() < right.data.size())
            isLess = true;
        else if (part.size() == right.data.size())
        {
            for (int i = 0; i < int(part.size()); ++i)
            {
                if (part[i] < right.data[i])
                {
                    isLess = true;
                    break;
                }
                else if (part[i] > right.data[i])
                    break;
            }
        }
        if (isLess)
        {
            result.data.push_back(sum);
            if (int(result.data.size()) == maxN)
                return;
            sum = 0;
            if (empty)
            {
                if (part.empty())
                    return;
                part.push_back(0);
                ++result.dot;
            }
            else
            {
                part.push_back(left.data[i1++]);
                if (!part[0])
                    part.pop_front();
                if (i1 == int(left.data.size()))
                    empty = true;
            }
        }
        else
        {
            int carry = 0;
            i3 = int(part.size()) - 1;
            for (i2 = int(right.data.size()) - 1; i2 >= 0; --i2)
            {
                int tmp = part[i3] - right.data[i2] + carry;
                part[i3--] = (tmp + 10) % 10;
                carry = (tmp < 0) ? -1 : 0;
            }
            if (carry)
                --part[i3];
            int popN = 0;
            for (i3 = 0; !part[i3] && i3 < int(part.size()); ++i3)
                ++popN;
            while (popN--)
                part.pop_front();
            ++sum;
        }
    }
}

int main()
{
    string str;
    getline(cin, str);
    try
    {
        Expression e(str);
        Number result = e.calculate();
        cout << result;
    }
    catch (const error &e)
    {
        cerr << "error";
    }
    return 0;
}