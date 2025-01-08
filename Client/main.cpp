#include "client.h"

using namespace std;

int main() {
    string input;
    cout << "enter server ip or 0 for localhost" << endl;
    cin >> input;
    Client me(input);
    do {
        cin >> input;
        string answer = "";
        answer = me.TalkToServ(input);
        cout << answer << endl;
    } while (input != "quit");
}