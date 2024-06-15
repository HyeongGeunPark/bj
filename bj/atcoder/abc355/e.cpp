#include<iostream>
#include<vector>
#include<queue>


int result = 0;

void query(int l, int r) {
	int answer = 0;
	int sign = 1;
	if (l > r) {
		std::swap(l, r);
		sign = -1;
	}
	int temp = r - l - 1;
	int i = 0;
	while (temp) {
		++i;
		temp >>= 1;
	}
	int j = l / (1 << i);
	std::cout << "? " << i << ' ' << j << std::endl;
	std::cin >> answer;
	if (answer == -1) {
		throw std::exception();
	}
	result += answer * sign;
	result %= 100;
}

int main(void) {
	int n, l, r;
	std::cin >> n >> l >> r;

	int maxval = (1 << n) + 1;

	r++;

	std::vector<int> pred(maxval, -1);
	std::queue<int> q;

	q.push(l);
	pred[l] = l;

	int cur;
	while (q.size()) {
		cur = q.front();
		q.pop();
		if (cur == r) break;

		int width = 1;
		while (cur % width == 0 && width < maxval) {
			if (cur + width < maxval && pred[cur + width] == -1) {
				q.push(cur + width);
				pred[cur + width] = cur;
			}
			if (cur - width >= 0 && pred[cur - width] == -1) {
				q.push(cur - width);
				pred[cur - width] = cur;
			}
			width <<= 1;
		} 
	}

	std::vector<int> path;
	while (pred[cur] != cur) {
		path.push_back(cur);
		cur = pred[cur];
	} 

	cur = l;
	int next;

	for (int i = path.size() - 1; i >= 0; --i) {
		next = path[i];
		try {
			query(cur, next); 
		}
		catch (std::exception) {
			return 0;
		}
		cur = next; 
	} 
	std::cout << "! " << (result>=0?result:result+100);
	return 0;
}