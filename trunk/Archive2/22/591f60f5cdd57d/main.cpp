#include <iostream>
#include <string>
#include <sstream>
#include <string.h>

// 动漫类型
/*1-单幅 2-四格 3-故事 4-绘本 5-同人 6-连环画 7-条漫 8-轻小说 [100-300]-动画*/
enum EComicTypes
{
    EM_COMIC_TYPE_NONE = 0,
    EM_COMIC_TYPE_DAN_FU = 1,
    EM_COMIC_TYPE_SI_GE = 2,
    EM_COMIC_TYPE_GU_SHI = 3,
    EM_COMIC_TYPE_HUI_BEN = 4,
    EM_COMIC_TYPE_TONG_REN = 5,
    EM_COMIC_TYPE_LAN_HUAN_HUA = 6,
    EM_COMIC_TYPE_TIAO_MAN = 7,
    EM_COMIC_TYPE_QING_XIAO_SHUO = 8,
    EM_COMIC_TYPE_DONG_HUA = 100
};

// 已和IEG的同事确认漫画id和动画id不会出现一样的情况。
// 但是为了以后不出现冲突，我们从动画需求起，在id前面添加前缀(16位的无符号数字+下划线)。
// 其中16位的无符号数字是以16进制小写的方式表示（0000~ffff）并且与类型枚举值一一对应。动画的前缀是0064_
typedef struct _stComicTypePrefix {
    EComicTypes comicType;
    const char* prefix;
}SComicTypePrefix;

const SComicTypePrefix stComicTypePrefixArray[] =
{
    // 类型，前缀
    {EM_COMIC_TYPE_DAN_FU, "0001_"},
    {EM_COMIC_TYPE_SI_GE, "0002_"},
    {EM_COMIC_TYPE_GU_SHI, "0003_"},
    {EM_COMIC_TYPE_HUI_BEN, "0004_"},
    {EM_COMIC_TYPE_TONG_REN, "0005_"},
    {EM_COMIC_TYPE_LAN_HUAN_HUA, "0006_"},
    {EM_COMIC_TYPE_TIAO_MAN, "0007_"},
    {EM_COMIC_TYPE_QING_XIAO_SHUO, "0008_"},
    {EM_COMIC_TYPE_DONG_HUA, "0064_"},
};

const size_t stComicTypePrefixArrayNum = sizeof(stComicTypePrefixArray) / sizeof(SComicTypePrefix);

    ///GetComment给动漫id添加前缀
    ///@param [in] id: 原始动漫id
    ///@param [in] type: 动漫类型
    ///@retval 返回带前缀的id 成功
    ///@retval 返回空字符串 失败
    template<typename T>
    std::string addComicPrefix(T id, EComicTypes type) {
        std::stringstream ss;
        for(size_t i = 0; i < stComicTypePrefixArrayNum; i++) {
            if (stComicTypePrefixArray[i].comicType == type) {
                ss << stComicTypePrefixArray[i].prefix << id;
                break;
            }
        }
        return ss.str();
    }

    ///GetComment删除动漫id前缀
    ///@param [in] prefixAndId: 带前缀动漫id
    ///@param [in] type: 动漫类型
    ///@retval 返回原始动漫id 成功
    ///@retval 返回空字符串 失败
    std::string delComicPrefix(std::string prefixAndId, EComicTypes type) {
        std::stringstream ss;
        for(size_t i = 0; i < stComicTypePrefixArrayNum; i++) {
            if (stComicTypePrefixArray[i].comicType == type) {
                size_t found = prefixAndId.find(stComicTypePrefixArray[i].prefix);
                if (found == 0) { // 找到前缀
                    ss << prefixAndId.substr(strlen(stComicTypePrefixArray[i].prefix));
                }
                break;
            }
        }
        return ss.str();
    }

    ///GetComment 查询动漫id的类别
    ///@param [in] prefixAndId: 带前缀动漫id
    ///@param [in] type: 动漫类型
    ///@retval 返回特定的动漫类型 成功
    ///@retval 返回空动漫类型 失败
    EComicTypes getComicType(std::string prefixAndId) {
        for(size_t i = 0; i < stComicTypePrefixArrayNum; ++i) {
            size_t found = prefixAndId.find(stComicTypePrefixArray[i].prefix);
            if (found == 0) { // 找到前缀
                return stComicTypePrefixArray[i].comicType;
            }
        }
        return EM_COMIC_TYPE_NONE;
    }

int main ()
{
  std::string str="1234";
  std::cout << addComicPrefix(str,EM_COMIC_TYPE_DONG_HUA) << '\n';
  std::cout << delComicPrefix("0001_1234",EM_COMIC_TYPE_DAN_FU) << '\n';
  std::cout << getComicType("0001_1234") << '\n';

  return 0;
}