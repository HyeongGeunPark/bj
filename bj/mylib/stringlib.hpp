 /**
* @file stringlib.hpp
* @brief string related lib for competetive programming
* @author HyeongGeun Park
* @date 24-07-10
* @detail
* LCS: longest common sequence
*/
#pragma once

#include<vector>

std::vector<int> LCS(const std::vector<int>& a, const std::vector<int>& b)
{
	std::vector<std::vector<int>>
		buf(a.size() + 1, std::vector<int>(b.size() + 1, 0));

	for (int i = 1; i <= a.size(); ++i) {
		for (int j = 1; j <= b.size(); ++j) {
			if (a[i - 1] == b[j - 1]) buf[i][j] = buf[i - 1][j - 1] + 1;
			else {
				buf[i][j] = std::max(buf[i - 1][j], buf[i][j - 1]);
			}
		}
	}

	int i = a.size();
	int j = b.size();
	int n = buf[i][j];
	std::vector<int> result(n);
	while (n) {
		if (a[i - 1] == b[j - 1]) {
			result[n - 1] = a[i - 1];
			--i, --j, --n;
		}
		else if (n == buf[i - 1][j]) {
			--i;
		}
		else if (n == buf[i][j - 1]) {
			--j;
		}
	}
	return result;
}
