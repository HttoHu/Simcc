# Simcc
**若果想获得完整的解释器代码请在发布里面下载0.1**
## 简介
Simcc 是一个简单的开源解释器，语法是简化的C++. 
## 支持的语法
1. 基本类型 ** int, long, double, string, char, bool 
2. 基本语句 if / else / elif / while / for 
3. 支持函数调用 函数不需要写上返回类型如
```c++
sum (int x, int y)
{
  return x+y;
}
```
4. 基本的函数库  system::
**write|write_line|time|read**
## 有关编译器
我使用的是Microsoft Visual Studio 2017 开发的，还没有在Linux/Mac OSX下进行编译。
是否支持GCC及Clang还未知，我打算写完0.2版本后都编译一份发布。
## BUG
* 在0.1版本中请使用前置递增,使用后置递增会出现错误
* 在0.1版本中变量声明符都类似于var, 如```int a=1.2;``` a的类型将是double
## 其他
* **作者正忙于复习小高考，更新可能不那么频繁，见谅**
* 目前我在写0.2版本 现在master里并不是一个完整的解释器， 可以到发布里面找0.1 的版本(0.1 版本还有些bug（其实我已经修复了这些bug，但是没有高兴发布新版本），且速度缓慢）
* 示例在instance里有， 是一个一元二次方程计算器
* 如果有什么问题 请联系 [Email]huyuantao@outlook.com

