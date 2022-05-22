#include <bits/stdc++.h>

using namespace std;

int n;
int a[100000];     //�����
int tree[400004];  //������ ������. � �������� ����������� ����

//�������� ������ �� ������.
//v - ����� ������� �������; tl, tr - ������� ���������� ������
void build_tree(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = a[tl];    //����� ������� �� ������ �������� ����� ����� ��������
    } else {
        //tm - ������� ������� �������
        //������ ���������� �� ��� ������� [tl; tm], [tm + 1; tr]
        int tm = (tl + tr) / 2;
        build_tree(v * 2, tl, tm);
        build_tree(v * 2 + 1, tm + 1, tr);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

//����
//l, r - ������� ������;
//v - ����� ������� �������; tl, tr - ������� ���������� ������
int get_sum(int l, int r, int v, int tl, int tr) {

    if (l <= tl && tr <= r) {
        return tree[v];
    }


    if (tr < l || r < tl) {
        return 0;
    }


    int tm = (tl + tr) / 2;
    return get_sum(l, r, v * 2, tl, tm) + get_sum(l, r, v * 2 + 1, tm + 1, tr);
}

//�������
//idx - ������ ��������, val - ���� ��������
//v - ����� ������� �������; tl, tr - ������� ���������� ������
void update(int idx, int val, int v, int tl, int tr) {

    if (idx <= tl && tr <= idx) {
        a[idx] = val;
        tree[v] = val;
        return;
    }


    if (tr < idx || idx < tl) {
        return;
    }


    int tm = (tl + tr) / 2;
    update(idx, val, v * 2,     tl,     tm);
    update(idx, val, v * 2 + 1, tm + 1, tr);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

int main() {
    //������ ������� n
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    build_tree(1, 0, n - 1);

    cout << get_sum(0, n-1, 1, 0, n - 1) << endl;
    update(2, 0, 1, 0, n - 1); //����� ������� ������� �� ����
    cout << get_sum(0, n-1, 1, 0, n - 1) << endl;

}
