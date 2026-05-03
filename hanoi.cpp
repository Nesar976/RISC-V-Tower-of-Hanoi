#include <iostream>
#include <vector>
#include <string>
using namespace std;

int move_count = 0, total_disks = 4;
vector<int> pegA, pegB, pegC;

// ITERATIVE
void draw_state(const vector<int>& A, const vector<int>& B, const vector<int>& C, int move_num = 0) {
    int max_width = 2 * total_disks - 1;
    for (int i = total_disks - 1; i >= 0; --i) {
        auto draw_peg = [&](const vector<int>& peg) {
            if (i < peg.size()) {
                int width = 2 * peg[i] - 1, spaces = (max_width - width) / 2;
                cout << string(spaces, ' ') << string(width, '=') << string(spaces, ' ') << "  ";
            } else {
                cout << string(max_width / 2, ' ') << "|" << string(max_width / 2, ' ') << "  ";
            }
        };
        draw_peg(A); draw_peg(B); draw_peg(C); cout << "\n";
    }
    string base(max_width, '-');
    cout << base << "  " << base << "  " << base << "\n";
    string sp(max_width / 2, ' ');
    cout << sp << "A" << sp << "  " << sp << "B" << sp << "  " << sp << "C" << sp << "\n\n";
}

vector<int>& get_peg(char p) { return p == 'A' ? pegA : (p == 'B' ? pegB : pegC); }

// RECURSIVE
void hanoi(int n, char src, char dst, char aux) {
    if (n == 0) return;
    hanoi(n - 1, src, aux, dst);
    vector<int>& s = get_peg(src);
    vector<int>& d = get_peg(dst);
    int disk = s.back(); s.pop_back(); d.push_back(disk);
    move_count++;
    if (move_count == 1 || move_count == 8 || move_count == 15) {
        cout << "Move " << move_count << ": disk " << disk << " [" << src << "] -> [" << dst << "]\n";
        draw_state(pegA, pegB, pegC, move_count);
    }
    hanoi(n - 1, aux, dst, src);
}

int main() {
    for (int i = total_disks; i >= 1; --i) pegA.push_back(i);
    
    int min_moves = (1 << total_disks) - 1;
    cout << "Tower of Hanoi - " << total_disks << " disks\n";
    cout << "Minimum moves required: " << min_moves << "\n";
    cout << "\n";
    
    cout << "Initial state:\n";
    draw_state(pegA, pegB, pegC, 0);
    
    hanoi(total_disks, 'A', 'C', 'B');
    
    cout << "\n";
    cout << "Done! Total moves used: " << move_count << "\n";
    
    return 0;
}
