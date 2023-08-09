# Sonolus.js

适用于 Sonolus Server for C++ 的 Sonolus.js 开发插件。

由于本人实在不会使用 TypeScript，无法继续维护针对 Sonolus.js 的开发插件，因此从 sonolus-server-cpp v1.5.0 起我们不再提供对 libsonolusjs 的支持。

## 链接

- [Sonolus Website](https://sonolus.com/)
- [Sonolus Wiki](https://wiki.sonolus.com/)

## 编译指令

```cpp
g++ plugins/libsonolusjs/libsonolusjs.cpp -o plugins/libsonolusjs.so -fPIC -shared -std=c++17 -DENABLE_MYSQL -DENABLE_SQLITE
```
