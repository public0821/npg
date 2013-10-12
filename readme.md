<meta http-equiv="content-type" content="text/html; charset=UTF-8">
# NPG

Network packet generator(NPG) 是一个数据包生成和发送工具，主要用来供开发和测试人员构造和发送数据包，目前NPG支持多种常用的协议, 比如arp、rarp、icmp、raw udp、udp、tcp、netflow v5、dns、http等。通过编写配置文件，可以自定义想要的协议。

# 特点
- 可以通过xml配置文件定义新的协议*
- 支持IPV6
- 可以选择数据包的字符集
- 支持发送速度控制

# 截图

![screenshot1](https://github.com/public0821/npg/raw/master/wiki/screenshot1_zh.jpg)

# 安装

## Windows
- 先下载和安装 [WinPcap](http://www.winpcap.org/install/default.htm)
- 然后下载 [NPG](https://github.com/public0821/npg/raw/master/download/npg_win32_1.0.zip)
- 解压下载的zip包，然后进入解压后的目录，双击npg.exe即可运行

## Linux（以ubuntu为例）
- 先安装libqt4-dev 

    sudo apt-get install libqt4-dev
- 然后获取源代码

    git clone https://github.com/public0821/npg.git
- 编译

    cd npg/src

    qmake && make

# 使用

程序运行起来之后，双击左边栏里面的协议，即可打开相应协议的编辑和发送标签页，在打开的标签页中可以编辑并发送相应的数据包

# 自定义协议

如何编写自定义协议请参考conf目录下的配置文件，每个单独的xml对应一种协议，仿照相应的格式编写即可

根据当前语言环境，如果是中文环境，则将新建的xml配置文件放到conf/zh_CN目录下，否则放到conf目录下即可

xml文件内容的具体格式见格式[详细介绍(文档未完成)]()

# 问题?

如果有什么建议或者问题，欢迎发送邮件到我的邮箱 public0821@gmail.com
