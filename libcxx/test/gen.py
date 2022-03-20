#! /usr/bin/python3

import sys


cpp = '''
#include <optional>

int main()
{
    %s
}
'''


str = ''
for i in range(0, int(sys.argv[1])):
    str += '  std::optional<int> o_%d{};\n' %(i)


print(cpp %(str))



