# 简介

本文为 吴鸿毅（wuhongyi@qq.com） ROOT 使用的一些常用代码及总结。

ROOT 版本越高，其函数功能越多。随版本提升，不断修复以前版本的 bug，又增加了新功能。但是从 ROOT 6.03 开始，就要求 Python 版本大于 2.7（LLVM/Clang要求） ，但是在 Scientific Linux 6 下， 直接对系统的 Python 升级版本会造成桌面显示的问题，因为 Python 在版本提升中一些标准更改造成不兼容。一个好的方法就是在 /usr/local 下安装高版本的 Python，然后安装 ROOT 的时候给指定该 Python 的路径，还有一个偷懒的办法是直接更改 configure 文件中 Phyhon 版本的要求和 interpreter/llvm/src/configure 文件中 Python 版本的要求(检索"7",将其替换成"6")，这个会不会造成什么影响不清楚。
