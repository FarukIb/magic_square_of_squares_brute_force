#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#define ll long long
#define pii pair<ll, ll>

using namespace std;


ll gcd(ll a, ll b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

bool isPerfectSquare(ll x) {
    ll root = sqrt(x);

    if (root * root == x)
        return true;
    return false;
}

struct triple {
    ll a, b, c;

    triple() { a = 0, b = 0, c = 0; }
    triple(ll A, ll B, ll C) { a = A, b = B, c = C; }

    bool isRelativelyPrime() {
        if (gcd(gcd(a, b), c) > 1)
            return false;
        return true;
    }

    bool isSquareTriple() {
        return isPerfectSquare(a) && isPerfectSquare(b) && isPerfectSquare(c);
    }

    bool operator<(const triple& x) const {
        if (a < x.a)
            return true;
        if (a > x.a)
            return false;

        if (b < x.b)
            return true;
        if (b > x.b)
            return false;

        return c < x.c;
    }
};

bool isGood(triple x, triple y, triple z) {
    return x.isSquareTriple() && y.isSquareTriple() && z.isSquareTriple();
}

set<triple> rpats;

int main()
{
    fstream reminder("powersOf10Reminder.txt");
    fstream solution("solution.txt");
    fstream RPAT("relatively_prime_arithmetic_triples_of_squares.txt");

    //sqrtE = 406166

    ll lastE = 0;
    for (ll sqrtE = 1; sqrtE * sqrtE * 3 < (1LL << 62); sqrtE++) {
        ll E = sqrtE * sqrtE;
        if (floor(log10(E)) > floor(log10(lastE)))
        {
            reminder << E << endl;
            //cout << E << endl;
        }
        lastE = E;


        // CODE TO FIND ALL ARITHMETIC TRIPLES WITH SUM 3E
        vector<triple> triples;
        for (ll sqrtX = 1; sqrtX * sqrtX <= 2 * E; sqrtX++) {
            ll x = sqrtX * sqrtX;
            ll z = 2 * E - x;
            if (z < x)
                break;

            if (!isPerfectSquare(z))
                continue;
            if (x == z)
                continue;

            triple curr(x, E, z);
            
            ll gcd_= gcd(gcd(curr.a, curr.b), curr.c);
            triple shortened(curr.a / gcd_, curr.b / gcd_, curr.c / gcd_);
            if (rpats.find(shortened) == rpats.end()) {
                rpats.insert(shortened);
                RPAT << shortened.a << " " << shortened.b << " " << shortened.c << endl;
            }

            triples.push_back(curr);
        }

        // CHECK ALL COMBINATION OF TRIPLES
        for (int i = 0; i < triples.size(); i++) {
            for (int j = i + 1; j < triples.size(); j++) {
                triple f = triples[i], s = triples[j];

                ll m = E - f.a, n = E - s.a;
                triple x(E - n,     E + n + m, E - m);
                triple y(E + n - m, E,         E + m - n);
                triple z(E + m,     E - n - m, E + n);

                if (isGood(x, y, z))
                {
                    //cout << x.a << " " << x.b << " " << x.c << endl;
                    //cout << y.a << " " << y.b << " " << y.c << endl;
                    //cout << z.a << " " << z.b << " " << z.c << endl;

                    solution << x.a << " " << x.b << " " << x.c << endl;
                    solution << y.a << " " << y.b << " " << y.c << endl;
                    solution << z.a << " " << z.b << " " << z.c << endl;
                }
            }      
        }
    }

    solution.close();
    RPAT.close();
    reminder.close();
}