#include<iostream>
int main(){
    using namespace std;
    unsigned long long guess{922337203685477580};
    unsigned long long start{0};
    unsigned long long end{18446744073709551615};
    int cnt{0};
    std::string command;
    cout << guess << endl;
    while (cin >> command){
        if (command == "TooSmall"){
            cnt++;
            start = guess;
            guess = guess/2+end/2+1;
        }else if(command == "TooBig"){
            end = guess;
            guess = guess/2+start/2;
        }else if(command == "Correct" || command == "GameOver"){
            break;
        }
        cout << guess << endl;
    }
    return 0;
}