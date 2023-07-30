#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int N, cnt;
struct INFO {
    int pw, login;
};
unordered_map<string, INFO> hm;

int Register(string id, int pw) {
    if (hm.find(id) == hm.end()) {
        hm.insert({ id,{pw,0} });
        return 1;
    }
    return 0;
}

int Login(string id, int pw) {
    if (hm.find(id) != hm.end() && !hm[id].login && hm[id].pw == pw) {
        hm[id].login = 1;
        cnt++;
        return 1;
    }
    return 0;
}

int Change(string id, int pw, int npw) {
    if (hm.find(id) != hm.end() && hm[id].pw == pw) {
        hm[id].pw = npw;
        return 1;
    }
    return 0;
}

int Logout(string id) {
    if (hm.find(id) != hm.end() && hm[id].login) {
        hm[id].login = 0;
        cnt--;
        return 1;
    }
    return 0;
}

int Bye(string id) {
    if (hm.find(id) != hm.end() && hm[id].login) {
        hm.erase(id);
        cnt--;
        return 1;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    string cmd, id;
    int pw;
    for (int i = 0; i < N; i++) {
        cin >> cmd >> id;
        if (cmd == "reg") {
            cin >> pw;
            Register(id, pw) ? (cout << "welcome " << hm.size() << "\n") : (cout << "reg fail\n");
        }
        else if (cmd == "login") {
            cin >> pw;
            Login(id, pw) ? (cout << "login " << cnt << "\n") : (cout << "login fail\n");
        }
        else if (cmd == "change") {
            int npw;
            cin >> pw >> npw;
            Change(id, pw, npw) ? (cout << "success\n") : (cout << "change fail\n");
        }
        else if (cmd == "logout") {
            Logout(id) ? (cout << "logout " << cnt << "\n") : (cout << "logout fail\n");
        }
        else {
            Bye(id) ? (cout << "bye " << hm.size() << "\n") : (cout << "bye fail\n");
        }
    }
}
