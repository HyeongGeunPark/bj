/*

bj9466 �� ������Ʈ

���� ������ �ʴ� �л��� �� ���.

���ٹ�
1. �Է��� �޴´�.
2. 1�� �л�����, �� �л��� ���� ���� �� �ִ��� Ȯ���Ѵ�.
	2-1. ���ϴ� �л��� �������� ���󰡸� ����Ŭ�� �߻��ϴ��� Ȯ���Ѵ�.
	2-2. ����Ŭ�� ���̸�ŭ �л� ������ ����.

*/

#include<iostream>
#include<vector>
#include<stack>
#include<cstring>

constexpr int EVALUATED = 2;
constexpr int IN_STACK = 1;
constexpr int NOT_EVALUATED = 0;

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int preference[100001];
	char status[100001]; 

	int t, n;
	std::cin >> t;
	while (t--) {
		std::cin >> n;
		int result = n;
		std::memset(status, 0, sizeof(char) * (n + 1));
		std::stack<int> s;
		for (int i = 1; i <= n; ++i) {
			std::cin >> preference[i];
		}

		for (int i = 1; i <= n; ++i) {
			int cur = i;
			while (true) {
				if (status[cur] == NOT_EVALUATED) {
					s.push(cur);
					status[cur] = IN_STACK;
					cur = preference[cur];
				}
				else if (status[cur] == IN_STACK) {
					// cycle detected
					int cycle_end = cur;
					do {
						cur = s.top();
						--result;
						status[cur] = EVALUATED;
						s.pop(); 
					} while (cur != cycle_end);
				}
				else if (status[cur] == EVALUATED) {
					while (!s.empty()) {
						cur = s.top();
						status[cur] = EVALUATED;
						s.pop();
					}
					break;
				}
			} 
		}

		std::cout << result << '\n';


	}

}