#include <iostream>

/////////////////////////////////////////////////////////////////////////
//
// 可变参数模板
//
/////////////////////////////////////////////////////////////////////////
// typename... Ts，这是template parameter pack，表明这里有多种type；
// Ts... arg_left，这是function parameter pack，表明这里有多个参数；
// arg_left...，这是pack expansion，将参数名字展开为逗号分割的参数列表；

// C++的可变参数模板 - Gemfield的文章 - 知乎
// https://zhuanlan.zhihu.com/p/104450480

// void syszuxPrint() {
//     std::cout << std::endl;
// }

// template<typename T, typename... Ts>
// void syszuxPrint(T arg1, Ts... arg_left) {
//     std::cout << arg1 << ", ";
//     syszuxPrint(arg_left...);
// }

// int main(int argc, char **argv) {
//     syszuxPrint(719, 7030, "civilnet");
// }

template<typename T>
void syszuxPrint(T arg){std::cout<<arg<<", "<<std::endl;}

template<typename T, typename... Ts>
void syszuxPrint(T arg1, Ts... arg_left){
    std::cout<<arg1<<", ";
    syszuxPrint(arg_left...);
}

int main(int argc, char** argv)
{
    syszuxPrint(719,7030,"civilnet");
}