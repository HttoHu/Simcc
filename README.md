# Simcc
## 简介
Simcc 是一个简单的开源解释器，语法是简化的C
## 支持的语法
1. 基本类型 **int, long, double, string, char, bool**
2. 基本语句 **if / else / elif / while / for**
3. 支持函数调用 函数不需要写上返回类型如
```c++
sum (int x, int y)
{
  return x+y;
}
```
4. 基本的函数库  system::
**write|write_line|time|read**|
## 有关编译器
我使用的是Microsoft Visual Studio 2017 开发的，还没有在Linux/Mac OSX下进行编译。
**尝试使用Clang编译，编译成功但是当调用system::read方法时程序会崩溃。见clang-make.bat**
## BUG
* 估计一大堆内存泄露，没精力一个一个找了
* 在0.1版本中变量声明符都类似于var, 如
```cpp
int a=1.2;

``` 
a的类型将是double
## 其他
* 示例在instance里有， 是一个一元二次方程计算器和循环测试
* Simcc不再更新！请移步至[Merdog](https://www.github.com/HttoHu/Merdog)

