//A Bignum struct, supports currently only + and *(slow) and % operators


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



struct Bignum
{
    string Value;

    bool Negative;

    string Print()
    {
        string t = "";
        if(Negative)
        {
            t += "-";
        }
        t += Value;
        return t;
    }

    Bignum operator+(const Bignum& other)const
    {
        bool resultSign;

        if(Negative && other.Negative)
        {
            Bignum temp(Value, Negative);
            return temp - other;
        }else if(!Negative && other.Negative)
        {
            Bignum temp(Value, Negative);
            return temp - other;
        }else if(Negative && !other.Negative)
        {
            Bignum temp(Value, Negative);
            return other - temp;
        }else if(!Negative && !other.Negative)
        {
            resultSign = false;
        }



        //work with copies:
        string a = Value;
        string b = other.Value;
        //reverse the strings so they begin with last stelle

        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());

        string result;

        int temp = 0;

        //make sure, in a is the longer string:
        if(a.size() < b.size())
        {
            string c = b;
            b = a;
            a = c;
        }



        for(unsigned int i=0;i<a.size();i++)
        {
            if(i < b.size())
            {
                int first = a[i] - '0';
                int second = b[i] - '0';
                int res = first + second + temp;
                string r = to_string(res);

                //watch out, maybe .end() is enough
                result += r[r.size()-1];

                if(r.size() > 1)
                {
                    r = r.substr(0,r.size()-1);
                    temp = stoi(r);
                   // cout << temp << endl;
                }else
                {
                    temp = 0;
                }

            }else
            {
                int first =a[i] - '0';
                int res = first + temp;

                string r = to_string(res);
                result += r[r.size()-1];


                //cout << "here " << endl;


                if(r.size() > 1)
                {
                    r = r.substr(0,r.size()-1);
                    temp = stoi(r);
                   // cout << temp << endl;
                }else
                {
                    temp = 0;
                }
            }
        }
        if(temp != 0)
        {
            string r = to_string(temp);
            reverse(r.begin(),r.end());
            result += r;
        }
        reverse(result.begin(),result.end());

        return Bignum(result, resultSign);
    }

    //slow * operator O(n²)
    Bignum operator*(const Bignum& other)const
    {
        bool resultSign = false;

        if(Negative && other.Negative)
        {
            resultSign = false;
        }else if((!Negative && other.Negative) || (Negative && !other.Negative) )
        {
            resultSign = true;
        }


        string a = Value;
        string b = other.Value;

        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());

        vector<string> toAdd;

        for(unsigned int i=0;i<a.size();i++)
        {
            string currentResult = "";

            //Add zeros depending on i:
            for(unsigned int c = 0; c < i;c++)
            {
                currentResult += "0";
            }

            int temp = 0;

            for(unsigned int j = 0;j<b.size();j++)
            {

                int first = a[i] - '0';
                int second = b[j] - '0';
                int res = first * second + temp;
                string r = to_string(res);

                char add = r[r.size()-1];
                currentResult += add;

                r = r.substr(0,r.size()-1);
                //cout << "invalid " << endl;
                if(r.size() != 0)
                    temp = stoi(r);
                else
                    temp = 0;
            }

            if(temp!= 0)
            {
                string r = to_string(temp);
                reverse(r.begin(),r.end());
                currentResult += r;
            }

            reverse(currentResult.begin(),currentResult.end());
            toAdd.push_back(currentResult);

        }

    Bignum res(toAdd[0], resultSign);
   // cout << toAdd[0] << endl;
    for(unsigned int i =1;i<toAdd.size();i++)
    {
      //  cout << toAdd[i] << endl;
        Bignum q(toAdd[i], resultSign);
        res = res + q;
    }

    return res;
    }


    //only works if second parameter is lower or equal than a int
    //it will always give an unsigned result!
    Bignum operator%(const Bignum& other)const
    {
        string a = Value;
        string b = other.Value;

        long long int divisor = stoi(b);

        long long int rest = 0;

        while(a.size() != 0)
        {
            if(a.size() < b.size())
            {
                string res;
                if(rest != 0)
                    res = to_string(rest) + a;
                else
                    res = a;
                a = "";
                rest = stoi(res);
                break;
            }

            string next = to_string(rest) + a.substr(0,b.size());
            long long int n = stoi(next);
            if(n < divisor)
            {
                if(a.size() < b.size() +1)
                {
                    string res;
                    if(rest != 0)
                        res = to_string(rest) + a;
                    else
                        res = a;
                    a = "";
                    rest = stoi(res);
                    break;
                }
                next = a.substr(0, b.size()+1);
                a = a.substr(b.size() + 1, a.size());
                long long int n = stoi(next) ;
                rest = n % divisor;

            }else
            {
                rest = n % divisor;
                a = a.substr(b.size(), a.size());
            }

        }

        rest %= divisor;

        string res = to_string(rest);

        return  Bignum(res, false);

    }

    //doesnt work if first parameter is smaller than second
    Bignum operator-(const Bignum& other)const
    {
        string a = Value;
        string b = other.Value;

        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());

        //assuming a is larger than b:

        long long int rest = 0;

        int index;

        string result = "";

        for(unsigned int i=0;i<b.size();i++)
        {
            index = i;


            int res = 0;

            if(a[i] < b[i] + rest)
            {
                res = 10 + a[i] - '0' - '0' - b[i] + rest;
                string r = to_string(res);
                if(r.size() == 1)
                    rest = 0;
                else
                {
                    string re = r.substr(0,r.size()-2);
                    rest = stoi(re);
                }

            }else
            {
                res = a[i] - '0' - b[i] - '0' + rest;
                rest = 0;
            }

            result += to_string(res % 10);

        }

        int in = index;

        //not fertig!


    }


    Bignum(string value, bool negative)
    {
        Value = value;
        Negative = negative;
    }

    Bignum(string value)
    {
        string v = "";
        if(value[0] == '-')
        {
            v = value.substr(1,value.size()-1);
            Negative = true;
        }else
        {
            v = value;
            Negative = false;
        }
        Value = v;
    }

    Bignum()
    {

    }

};


int main()
{
    string a,b;
    cin >> a >> b;
    Bignum d(a);
    Bignum c(b);
    Bignum e = d + c;
    cout << e.Value << endl;
    Bignum r = d * c;
    cout << r.Value << endl;
    Bignum m = d % c;
    cout << m.Value << endl;
}
