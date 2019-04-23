# 基础知识： #
v3s提供一个非常小的C++ runtime 支持库(/system/lib/libstdc++)和头文件。
但此System C++库支持非常有限，不支持以下：

    - Standard C++ Library support (except a few trivial headers). 
    - C++ exceptions support 
    - RTTI support
但v3s也提供几个其它的选择。可以通过Camlinux.mk中APP_STL 作设置。
设置选项有如下选择：
	
	- system -> Use the default minimal system C++ runtime library. 
	- gabi++_static -> Use the GAbi++ runtime as a static library. 
	- gabi++_shared -> Use the GAbi++ runtime as a shared library. 
	- stlport_static -> Use the STLport runtime as a static library. 
	- stlport_shared -> Use the STLport runtime as a shared library. 
	- gnustl_static -> Use the GNU STL as a static library. 
	- gnustl_shared -> Use the GNU STL as a shared library.

当APP_STL没有设置时，则缺省使用system的这个。

以上几种C++库能力集对：C++ Exceptions ，C++ RTTI ，Standard Library支持分别如下：

| Library | C++ Exceptions | C++ RTTI | Standard Library |
| :------: | :------: | :------: | :------: |
| system | no | no | no |
| gabi++ | no | yes | no |
| stlport | no | yes | yes |
| gnustl | yes | yes | yes |

# 各Runtime简介： #
## System Runtime： ##
v3s提供的C++ Runtime，它只提供几个非常少的C++ 标准头文件。如果使用它，则应用程序二进制自动的链接此Android系统libstdc++。

提供的头文件只有以下这些：

	cassert cctype cerrno cfloat climits cmath csetjmp csignal cstddef cstdint cstdio cstdlib cstring ctime cwchar new stl_pair.h typeinfo utility

不支持：std::string or std::vector.

## GAbi++ runtime： ##
这是另一个小的C++ runtime, 与System C++ 提供同样多的头文件。但它支持RTTI。 现在已经很少用了。

## STLport runtime: ##
STLport(http://www.stlport.org)的Android 移植版。提供完整的C++ 标准库头文件，支持RTTI，但不支持EXCEPTIONS.（不支持异常很麻烦，就需要改不少代码）

静态动态均支持：

	APP_STL := stlport_shared 
	APP_STL := stlport_static

## GNU STL runtime： ##
GNU 标准的C++ library. 支持更多特性。库名叫：libgnustl_shared.so，而不是其它平台通常的：libstdc++.so

# 其它事项： #
## C++ Exceptions: ##
所有C++ 代码都缺省使用-fno-exceptions编译。

为了Enable C++ Exceptions,可以作如下动作：
在Camlinux.mk中：

	LOCAL_CPP_FEATURES += exceptions (推荐)
或者

	LOCAL_CPPFLAGS += -fexceptions

## RTTI support: ##
与异常类似，在缺省情况下都是用-fno-rtti来编译C++代码。
如果想Enable RTTI； 
在Camlinux.mk中：

	LOCAL_CPP_FEATURES += rtti (推荐)
或者

	LOCAL_CPPFLAGS += -frtti

## Static runtimes: ##
当工程只有一个动态库用到C++ library. 则其使用静态C++库没有问题。
但当工程中有多个动态库用到C++ library(或其它静态库)时，则问题来了，每个动态库会包含静态库进去。这就有问题了，因为在内存中，就有多份COPY,那全局变量等都会有问题。

所以，当工程中多个动态库链接C++ library时，不要使用静态C++库方式。

## Shared runtimes: ##
在使用动态库时，则需要确保C++ 动态库在其它库之前被Load到内存。


引用：
[https://blog.51cto.com/127825/1278413](https://blog.51cto.com/127825/1278413 "Android NDK 知识系列（五）")
