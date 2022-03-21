# fcitx5-demo

## 简介
fcitx5-demo是一个fcitx5的输入法插件，里边实现了获取按键、设置候选词、修改候选词框等功能，为第三方开发基于fcitx5的输入法做一些参考

## 分支

该项目目前有两个分支，minimum分支和master分支。minimum是一个最精简的输入法，只实现了输入法的基本功能，master分支除了最精简的输入功能外，还实现了自定义候选词框、自定义状态栏（未完成）、托盘图标和右键菜单（未完成）

## 编译

该项目依赖fcitx5，fcitx5目前只在社区版上线，该项目目前只能在社区版运行

```
cd fcitx5-demo
sudo apt build-dep  .
mkdir build
cd build
cmake ..
make
```

## 目录结构
fcitx5-quwei目录下是区位输入法，里边包含了fcitx5输入法插件该有的所有信息

kimpanel-ui目录下是从kde-plasma里边摘取出来的kimpanel客户端，它接收kimpanel的dbus消息和输入法插件的dbus消息，显示候选词框、状态栏。