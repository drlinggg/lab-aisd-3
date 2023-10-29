#include <bits/stdc++.h>
#define fast std::cin.tie(0);std::ios_base::sync_with_stdio(0);
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const ll RBN = 1e9+7;
const ll RSN = -(1e9+7);
const double PI = 3.141592653589793;
//mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count()); ll gen(){return rnd()%100;}

ll lbs(ll a[], ll n, ll start) {
    ll l = 0;
    ll r = n - 1;
    while (l <= r) {
        ll mid = l + (r - l) / 2;
        if (a[mid] >= start) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return l;
}

ll rbs(ll a[], ll n, ll x) {
    ll l = 0;
    ll r = n - 1;
    while (l <= r) {
        ll mid = l + (r - l) / 2;
        if (a[mid] > x) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return r;
}

void count_sort(ll* count_array, string* sorted_names, ll* sorted_damage, ll damage[], string names[], ll n, ll max_value, ll* count_elem, ll* pref_count_elem) {
    for (ll i = 0; i < n; i++) {
        count_array[damage[i]] += 1;
        count_elem[damage[i]] += 1;
    }
    for (ll i = 1; i <= max_value; i++) {
        count_array[i] = count_array[i] + count_array[i-1];
    }
    for (ll i = 1; i <= max_value; i++) {
        pref_count_elem[i] = pref_count_elem[i-1] +  (count_array[i] - count_array[i-1]);
    }
    for (ll i = n - 1; i >= 0; i--) {
        count_array[damage[i]] -= 1;
        sorted_names[count_array[damage[i]]] = names[i];
        sorted_damage[count_array[damage[i]]] = damage[i];
    }
    return;
}


signed main() {
    fast;
    ll n;
    cin >> n;
    ll max_value = 0;
    ll array_of_damage[n];
    string array_of_names[n];
    ll sorted_array_damage[n];
    string sorted_array_names[n];

    //считывание
    for (ll i = 0; i < n; i++){
        ll temp;
        cin >> temp;
        max_value = max(max_value, temp);
        array_of_damage[i] = temp;
    }
    for (ll i = 0; i < n; i++) {
        string temp;
        cin >> temp;
        array_of_names[i] = temp;
    }

    ll array_of_counting_numbers[max_value+1];
    ll count_elem[max_value+1];
    ll pref_count_elem[max_value+1];
    pref_count_elem[0] = 0;
    for (ll i = 0; i <= max_value; i++) {
        array_of_counting_numbers[i] = 0;
        count_elem[i] = 0;
        pref_count_elem[i] = 0;
    }

    //сортировка
    count_sort(array_of_counting_numbers,sorted_array_names,sorted_array_damage,array_of_damage,array_of_names,n,max_value, count_elem, pref_count_elem);

    ll pref_sum[max_value+1];
    pref_sum[0] = 0;
    //префсумма
    for (ll i = 1; i <= n; i++) {
        pref_sum[i] = pref_sum[i-1] + sorted_array_damage[i-1];
    }

    //вывод
    for (ll i = 0; i < n; i++) {
        if (i == n - 1) {
            cout << sorted_array_damage[i] << '\n';
            break;
        }
        cout << sorted_array_damage[i] << " ";
    }
    for (ll i = 0; i < n; i++) {
        if (i == n - 1) {
            cout << sorted_array_names[i] << '\n';
            break;
        }
        cout << sorted_array_names[i] << " ";
    }

    //команды
    ll n1;
    cin >> n1;
    ll answer[n1];
    for (ll i = 0; i < n1; i++) {
        string temp;
        ll left, right;
        cin >> temp >> left >> right;
        ll left_index = lbs(sorted_array_damage,n,left);
        ll right_index = rbs(sorted_array_damage,n,right);
        if (left > max_value || right < sorted_array_damage[0]) {
            answer[i] = 0;
            continue;
        }
        if (temp == "Xor") {
            ll total = 0;
            for (ll j = left_index; j <= right_index; j++){
                total ^= sorted_array_damage[j];
            }
            answer[i] = total;
        }
        else if (temp == "Sum") {
            answer[i] = pref_sum[right_index+1] - pref_sum[left_index];
        }
        else if (temp == "Count") {
            answer[i] = right_index-left_index+1;
        }
    }

    for (ll i = 0; i < n1; i++) {
        cout << answer[i] << '\n';
    }
    return 0;
}
