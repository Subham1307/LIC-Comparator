#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// ----------------- LIC COVER DATA -----------------
struct AgeCover {
    int age;
    double normal_cover;
};

vector<AgeCover> covers = {
  {23,799500},{24,849000},{25,898500},{26,948000},{27,997500},{28,1047000},
  {29,1096500},{30,1146000},{31,1195500},{32,1245000},{33,1294500},
  {34,1344000},{35,1393500},{36,1443000},{37,1500000},{38,1526625},
  {39,1552500},{40,1579125},{41,1608750},{42,1640625},{43,1676250},
  {44,1719375},{45,1781250},{46,1843125},{47,1905000},{48,1966875},
  {49,2036250},{50,2105625},{51,2175000},{52,2270625},{53,2370000},
  {54,2488125},{55,2606250},{56,2724375},{57,2842500},{58,2960625},
  {59,3078750},{60,3196875},{61,3315000},{62,3433125},{63,3558750},
  {64,3688125},{65,3817500},{66,3961875},{67,4106250},{68,4250625},
  {69,4410000},{70,4569375},{71,4736250},{72,4903125},{73,5077500},
  {74,5259375},{75,5448750},{76,5638125},{77,5835000},{78,6031875},
  {79,6236250},{80,6440625},{81,6645000},{82,6856875},{83,7068750},
  {84,7288125},{85,7500000},{86,7719375},{87,7938750},{88,8150625},
  {89,8370000},{90,8581875},{91,8793750},{92,8998125},{93,9202500},
  {94,9406875},{95,9603750},{96,9793125},{97,9975000},{98,10149375},
  {99,10323750}
};

double getCover(int age) {
    for (auto &c : covers)
        if (c.age == age) return c.normal_cover;
    return -1; // not available
}

// ----------------- SIMULATOR -----------------
double simulateFund(int final_age, double rate) {
    int start_age = 23;
    int invest_years = 15;
    int retirement_age = start_age + invest_years; // 38

    double balance = 0.0;
    double invest = 61000.0;
    double withdraw = 60000.0;

    // phase 1 — investing
    for (int age = start_age; age < retirement_age; age++) {
        balance = balance + invest; // first invest at the year starts
        balance = balance + balance * rate; // then earn interest at the year end
    }
        
    // phase 2 — withdrawals
    for (int age = retirement_age; age <= final_age; age++) {
        balance = balance + balance * rate - withdraw; // withdraw at year end to maximize interest(i dont know how it works in real life)
        if (balance < 0) return -1;
    }
    return balance;
}

int main() {
    cout << fixed << setprecision(0);
    // int r;
    // cout<<"Enter the annual return rate (in %): ";
    // cin>>r;
    // double rate = r / 100.0; 
    for(double rate = 0.06; rate <= 0.068; rate += 0.001) {
        cout << "\n--- Comparing FUND vs LIC COVER at " << fixed << setprecision(4) << rate << " % return ---\n";
        for (int age = 39; age <= 100; age++) {

            double fund = simulateFund(age, rate);
            double cover = getCover(age);

            if (cover < 0) 
                break;

            cout << "Age " << age
                << " | Fund: " << fund
                << " | Cover: " << cover
                << " | Better: "
                << (fund > cover ? "FUND" : "LIC COVER")
                << endl;
        }
    }

    return 0;
}
