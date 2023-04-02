import <iostream>;
import <limits>;
import <format>;

using namespace std;

int main()	
{	
	// 获取数值极限信息
	cout << "int:\n";
	cout << format("Max int value: {}\n", numeric_limits<int>::max());  //最大值
	cout << format("Min int value: {}\n", numeric_limits<int>::min());  //最小值
	cout << format("Lowest int value: {}\n", numeric_limits<int>::lowest());  //最低值

	cout << "\ndouble:\n";
	cout << format("Max double value: {}\n", numeric_limits<double>::max());
	cout << format("Min double value: {}\n", numeric_limits<double>::min());
	cout << format("Lowest double value: {}\n", numeric_limits<double>::lowest()); //浮点最低值是-max()
}