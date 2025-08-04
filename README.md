# ChatRoom

ChatRoom中QT客户端部分的代码。编译过程中不使用QT Creator的qmake以及Visual Studio，而是使用CMake进行构建，以支持跨平台的编译。

项目原始代码：[llfc官方博客](https://llfc.club/)

更多的说明可以参考我的一篇博客[《CMake编译QT项目》](https://chrisnake11.github.io/blog/posts/coding/chatroom/cmake%E7%BC%96%E8%AF%91qt%E9%A1%B9%E7%9B%AE/)

**补充说明：**

`.vscode`目录下包含了VSCode的配置文件。
+ `c_cpp_properties.json`文件中包含了编译所需的头文件路径。
+ `settings.json`文件中包含了编译所需的CMake配置。