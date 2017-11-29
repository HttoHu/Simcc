# Simcc
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
## 其他
* 目前我在写0.2版本 现在master里并不是一个完整的解释器， 可以到发布里面找0.1 的版本(o.1 版本还有些bug（其实我已经修复了这些bug，但是没有高兴发布新版本），且速度缓慢）
* 示例在instance里有， 是一个一元二次方程解释器
* 如果有什么问题 请联系 [Email]huyuantao@outlook.com
