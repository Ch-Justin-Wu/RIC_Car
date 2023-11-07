#ifndef __START_H_
#define __START_H_

#ifdef __cplusplus
extern "C"
{
#endif
  void startup(void);
  


  
  
  
  
#ifdef __cplusplus
}

#include <string>

class StringContainer {
public:
    std::string str1;
    std::string str2;
    std::string str3;

    // 构造函数，用于初始化字符串变量
    StringContainer(const std::string& s1, const std::string& s2, const std::string& s3) {
        str1 = s1;
        str2 = s2;
        str3 = s3;
    }
};
#endif

#endif

