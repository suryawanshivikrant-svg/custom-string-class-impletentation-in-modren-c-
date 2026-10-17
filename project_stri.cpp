#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

class STRING
{
    char *p;

    int str_len(const char *s)
    {
        int i = 0;
        while(s[i] != '\0')
            i++;
        return i;
    }

public:
    STRING()
    {
        p = 0;
    }

    STRING(const char *s)
    {
        int len = str_len(s);
        p = new char[len + 1];

        int i = 0;
        while(s[i] != '\0')
        {
            p[i] = s[i];
            i++;
        }
        p[i] = '\0';
    }

    STRING(const STRING &s)
    {
        int len = str_len(s.p);
        p = new char[len + 1];

        int i = 0;
        while(s.p[i] != '\0')
        {
            p[i] = s.p[i];
            i++;
        }
        p[i] = '\0';
    }

    ~STRING()
    {
        delete[] p;
    }

    STRING& operator=(const STRING &s)
    {
        if(this != &s)
        {
            int len = str_len(s.p);
            char *temp = new char[len + 1];

            int i = 0;
            while(s.p[i] != '\0')
            {
                temp[i] = s.p[i];
                i++;
            }
            temp[i] = '\0';

            delete[] p;
            p = temp;
        }
        return *this;
    }

    STRING operator+(const STRING &s)
    {
        int len1 = str_len(p);
        int len2 = str_len(s.p);

        STRING temp;
        delete[] temp.p;

        temp.p = new char[len1 + len2 + 1];

        int i = 0;
        int j = 0;

        while(p[i] != '\0')
        {
            temp.p[i] = p[i];
            i++;
        }

        while(s.p[j] != '\0')
        {
            temp.p[i] = s.p[j];
            i++;
            j++;
        }

        temp.p[i] = '\0';
        return temp;
    }

    bool operator==(const STRING &s)
    {
        int i = 0;

        while(p[i] != '\0' || s.p[i] != '\0')
        {
            if(p[i] != s.p[i])
                return false;
            i++;
        }
        return true;
    }

    char& operator[](int i)
    {
        return p[i];
    }

    int length()
    {
        int i = 0;
        while(p[i] != '\0')
            i++;
        return i;
    }

    void display()
    {
        cout << p << endl;
    }

    friend STRING& my_strcpy(STRING&, const STRING&);
    friend STRING& my_strncpy(STRING&, const STRING&, int);
    friend int my_strcmp(const STRING&, const STRING&);
    friend int my_strncmp(const STRING&, const STRING&, int);
    friend STRING& my_strcat(STRING&, const STRING&);
    friend STRING& my_strncat(STRING&, const STRING&, int);
    friend STRING& my_strrev(STRING&);
    friend STRING& my_strupr(STRING&);
    friend STRING& my_strlwr(STRING&);
    friend char* my_strchr(STRING&, char);
    friend char* my_strrchr(STRING&, char);
    friend char* my_strstr(STRING&, char*);
    friend int my_strlen(STRING&);
    friend istream& operator>>(istream&, STRING&);
    friend ostream& operator<<(ostream&, const STRING&);
};

ostream& operator<<(ostream &fout, const STRING &s)
{
    fout << (s.p ? s.p : "");
    return fout;
}

istream& operator>>(istream &in, STRING &s)
{
    char ch;
    int len = 0;
    char *temp = new char[1];
    temp[0] = '\0';

    while(in.get(ch))
    {
        if(ch == ' ' || ch == '\n' || ch == '\t')
        {
            if(len > 0)
                break;
            continue;
        }

        char *temp1 = new char[len + 2];

        for(int i = 0; i < len; i++)
            temp1[i] = temp[i];

        temp1[len] = ch;
        temp1[len + 1] = '\0';

        delete[] temp;
        temp = temp1;
        len++;
    }

    delete[] s.p;
    s.p = temp;

    return in;
}

STRING& my_strcpy(STRING &s2, const STRING &s1)
{
    int len = 0;

    while(s1.p[len] != '\0')
        len++;

    delete[] s2.p;
    s2.p = new char[len + 1];

    int i = 0;
    while(s1.p[i] != '\0')
    {
        s2.p[i] = s1.p[i];
        i++;
    }

    s2.p[i] = '\0';
    return s2;
}

STRING& my_strncpy(STRING &t, const STRING &t1, int n)
{
    if(n < 0)
        n = 0;

    delete[] t.p;
    t.p = new char[n + 1];

    int i = 0;

    while(i < n && t1.p[i] != '\0')
    {
        t.p[i] = t1.p[i];
        i++;
    }

    t.p[i] = '\0';
    return t;
}

int my_strcmp(const STRING &t1, const STRING &t2)
{
    int i = 0;

    while(t1.p[i] != '\0' && t2.p[i] != '\0')
    {
        if(t1.p[i] != t2.p[i])
            return t1.p[i] - t2.p[i];

        i++;
    }

    return t1.p[i] - t2.p[i];
}

int my_strncmp(const STRING &t1, const STRING &t2, int n)
{
    int i = 0;

    while(i < n)
    {
        if(t1.p[i] != t2.p[i])
            return t1.p[i] - t2.p[i];

        if(t1.p[i] == '\0')
            return 0;

        i++;
    }

    return 0;
}

STRING& my_strcat(STRING &t, const STRING &t1)
{
    int len1 = 0;
    int len2 = 0;

    while(t.p[len1] != '\0')
        len1++;

    while(t1.p[len2] != '\0')
        len2++;

    char *temp = new char[len1 + len2 + 1];

    int i = 0;
    int j = 0;

    while(t.p[i] != '\0')
    {
        temp[i] = t.p[i];
        i++;
    }

    while(t1.p[j] != '\0')
    {
        temp[i] = t1.p[j];
        i++;
        j++;
    }

    temp[i] = '\0';

    delete[] t.p;
    t.p = temp;

    return t;
}

STRING& my_strncat(STRING &t, const STRING &t1, int n)
{
    if(n < 0)
        n = 0;

    int len1 = 0;
    int len2 = 0;

    while(t.p[len1] != '\0')
        len1++;

    while(t1.p[len2] != '\0')
        len2++;

    if(n > len2)
        n = len2;

    char *temp = new char[len1 + n + 1];

    int i = 0;
    int j = 0;

    while(t.p[i] != '\0')
    {
        temp[i] = t.p[i];
        i++;
    }

    while(j < n)
    {
        temp[i] = t1.p[j];
        i++;
        j++;
    }

    temp[i] = '\0';

    delete[] t.p;
    t.p = temp;

    return t;
}

STRING& my_strrev(STRING &t)
{
    int i = 0;

    while(t.p[i] != '\0')
        i++;

    i--;

    int j = 0;
    char temp;

    while(j < i)
    {
        temp = t.p[j];
        t.p[j] = t.p[i];
        t.p[i] = temp;

        j++;
        i--;
    }

    return t;
}

STRING& my_strupr(STRING &t)
{
    int i = 0;

    while(t.p[i] != '\0')
    {
        if(t.p[i] >= 'a' && t.p[i] <= 'z')
            t.p[i] -= 32;

        i++;
    }

    return t;
}

STRING& my_strlwr(STRING &t)
{
    int i = 0;

    while(t.p[i] != '\0')
    {
        if(t.p[i] >= 'A' && t.p[i] <= 'Z')
            t.p[i] += 32;

        i++;
    }

    return t;
}

char* my_strchr(STRING &t, char ch)
{
    int i = 0;

    while(t.p[i] != '\0')
    {
        if(t.p[i] == ch)
            return &t.p[i];

        i++;
    }

    return 0;
}

char* my_strrchr(STRING &t, char ch)
{
    int i = 0;

    while(t.p[i] != '\0')
        i++;

    i--;

    while(i >= 0)
    {
        if(t.p[i] == ch)
            return &t.p[i];

        i--;
    }

    return 0;
}

char* my_strstr(STRING &t, char *ch)
{
    int i, j;

    for(i = 0; t.p[i] != '\0'; i++)
    {
        for(j = 0; ch[j] != '\0'; j++)
        {
            if(t.p[i + j] != ch[j])
                break;
        }

        if(ch[j] == '\0')
            return &t.p[i];
    }

    return 0;
}

int my_strlen(STRING &t)
{
    int i = 0;

    while(t.p[i] != '\0')
        i++;

    return i;
}

int main()
{
    STRING s1;
    STRING s2;

    ifstream fin("temp.txt");

    if(!fin)
    {
        cout << "File not found" << endl;
        return 1;
    }

    fin >> s1;
    fin >> s2;

    cout << "S1 = " << s1 << endl;
    cout << "S2 = " << s2 << endl;

    STRING s3 = s1 + s2;
    cout << "S1 + S2 = " << s3 << endl;

    STRING s4 = s1;
    cout << "Copied string = " << s4 << endl;

    STRING s5;
    s5 = s2;
    cout << "Assigned string = " << s5 << endl;

    if(s1 == s2)
        cout << "Strings are equal" << endl;
    else
        cout << "Strings are not equal" << endl;

    cout << "s1[0] = " << s1[0] << endl;
    cout << "Length of s1 = " << s1.length() << endl;

    fin.close();

    STRING t;
    STRING a, b, c;

    cout << "Enter two strings for friend functions" << endl;

    string x, y;
    cin >> x >> y;

    a = STRING(x.c_str());
    b = STRING(y.c_str());

    t = my_strcpy(c, b);
    cout << "Copied string: " << t << endl;

    t = my_strncpy(c, b, 3);
    cout << "strncpy: " << t << endl;

    int n;

    n = my_strcmp(a, b);

    if(n < 0)
        cout << "String b is greater" << endl;
    else if(n > 0)
        cout << "String a is greater" << endl;
    else
        cout << "Strings are equal" << endl;

    n = my_strncmp(a, b, 4);

    if(n < 0)
        cout << "String b is greater" << endl;
    else if(n > 0)
        cout << "String a is greater" << endl;
    else
        cout << "First 4 characters are equal" << endl;

    t = my_strrev(b);
    cout << "Reversed string: " << t << endl;

    t = my_strupr(b);
    cout << "Lower to upper: " << t << endl;

    t = my_strlwr(a);
    cout << "Upper to lower: " << t << endl;

    t = my_strcat(a, b);
    cout << "Concatenated string: " << t << endl;

    t = my_strncat(a, b, 4);
    cout << "strncat string: " << t << endl;

    char ch;

    cout << "Enter character you want to check" << endl;
    cin >> ch;

    char *p = my_strchr(a, ch);

    if(p != 0)
        cout << *p << " character found" << endl;
    else
        cout << "Character not found" << endl;

    p = my_strrchr(a, ch);

    if(p != 0)
        cout << *p << " character found (strrchr)" << endl;
    else
        cout << "Not found (strrchr)" << endl;

    char *q = new char[20];

    cout << "Enter substring" << endl;
    cin >> q;

    char *z = my_strstr(b, q);

    if(z != 0)
        cout << z << " substring is present" << endl;
    else
        cout << "Substring not present" << endl;

    delete[] q;

    n = my_strlen(a);
    cout << "Length of string is " << n << endl;

    return 0;
}