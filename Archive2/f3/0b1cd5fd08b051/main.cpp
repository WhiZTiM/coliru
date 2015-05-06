
#include <iostream>
#include <string>
#include <regex>
using namespace std;

std::string GetVal(const string& html, const string &sName)
{
    std::string ret = "";
	std::regex reg("<th>" + sName + "<\\/th>[^<>]*<td>([^<>]*)<\\/td>");

	std::smatch m;
	if (std::regex_search(html, m, reg)) {
		ret = m[1];
	}

	return ret;
}

int main()
{
	std::string html = R"(
		<table>
　		  <tr>
　　		   <th>이름</th>
　　		   <td>홍길동</td>
　		  </tr>
　		  <tr>
　　		   <th>전화번호</th>
　　		   <td>010-1234-5678</td>
　		  </tr>
		</table>
	)";

	cout << GetVal(html, "이름") << endl;
	cout << GetVal(html, "전화번호") << endl;

	return 0;
}

