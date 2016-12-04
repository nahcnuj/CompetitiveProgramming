#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
	string s,t,u;
	cin >> s >> t >> u;
	if (s.length() == 5 && t.length() == 7 && u.length() == 5) cout << "valid" << endl;
	else cout << "invalid" << endl;
	
    return 0;
}
