# Sonolus.js

适用于 Sonolus Server for C++ 的 Sonolus.js 开发插件。

## 链接

- [Sonolus Website](https://sonolus.com/)
- [Sonolus Wiki](https://wiki.sonolus.com/)

## 编译指令

```cpp
g++ plugins/libsonolusjs/libsonolusjs.cpp -o plugins/libsonolusjs.so -fPIC -shared -std=c++17 -DENABLE_MYSQL -DENABLE_SQLITE
```