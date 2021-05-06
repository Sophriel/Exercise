#include <string>
#include <vector>
#include <stack>
using namespace std;

int priority(char c)
{
	switch (c)
	{
	case '*':
	case '/':
		return 2;
		break;
	case '+':
	case '-':
		return 1;
		break;
	case '(':
	case ')':
		return 0;
		break;
	}

	return 0;
}

int calc(int l, int r, char op)
{
	switch (op)
	{
	case '*':
		return l * r;
		break;
	case '/':
		if (r == 0) return 0;
		return l / r;
		break;
	case '+':
		return l + r;
		break;
	case '-':
		return l - r;
		break;
	}

	return 0;
}

int solve(string s)
{
	int answer = 0;

	stack<int> nums;
	stack<char> ops;

	string n;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			n.push_back(s[i]);
		}

		//  2Áß °ıÈ£x
		else if (s[i] == '(')
			ops.push(s[i]);

		else if (s[i] == ')')
		{
			nums.push(stoi(n));
			n.clear();

			while (ops.top() != '(')
			{
				int r = nums.top();
				nums.pop();
				int l = nums.top();
				nums.pop();

				n = to_string(calc(l, r, ops.top()));
				ops.pop();
			}
			ops.pop();
		}


		else
		{
			nums.push(stoi(n));
			n.clear();

			while (!ops.empty() && priority(s[i]) <= priority(ops.top()))
			{
				int r = nums.top();
				nums.pop();
				int l = nums.top();
				nums.pop();
	
				nums.push(calc(l, r, ops.top()));
				ops.pop();
			}

			ops.push(s[i]);
		}
	}

	nums.push(stoi(n));
	while (!ops.empty())
	{
		int r = nums.top();
		nums.pop();
		int l = nums.top();
		nums.pop();

		nums.push(calc(l, r, ops.top()));
		ops.pop();
	}

	answer = nums.top();
	return answer;
}

int main()
{
	solve("((5+4)-((3*2)/1))");

	return 0;
}