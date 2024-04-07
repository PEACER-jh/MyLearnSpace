# ROS1 NOETIC
###### eiditor: [PEACER]()
[ROS官方文档链接](https://wiki.ros.org/cn/ROS/Tutorials)

[1. about ROS File System](#1)
[2. create a ROS Package](#2)
  - [2.1. 自定义package.xml](#2.1)
  - [2.2. 自定义CMakeLists.txt](#2.2)

[3. build the ROS Package](#3)
[4. learn about ROS Node](#4)
  - [4.1 ROS Topic](#4.1)
  - [4.2 ROS Service](#4.2)
  - [4.3 ROS Param](#4.3)

[5. rqt & roslaunch & rosed](#5)

[6. learn about ROS Interface](#5)
  - [6.1 ROS msg](#6.1)
  - [6.2 ROS srv](#6.2)
  - [6.3 ROS action](#6.3)

[7. create a Publisher & Subscriber Node](#7)
[8. create a Service & Client Node](#8)



## 1. about ROS File System
<p id=1></p>

- **软件包（Packages）**: 包是ROS代码的软件组织单元，每个软件包都可以包含程序库、可执行文件、脚本或其他构件。
- **Manifests (package.xml)**: 清单（Manifest）是对软件包的描述。它用于定义软件包之间的依赖关系，并记录有关软件包的元信息，如版本、维护者、许可证等。

##### ROS CLI
1. **rospack**:允许你获取软件包的有关信息
```cli
rospack list
rospack find [package_name]
```
2. **roscd**:允许你直接切换目录到某个软件包或者软件包集当中
```cli
roscd [package_name]
roscd log   #进入存储ROS日志文件的目录
echo $ROS_PACKAGE_PATH
```
3. **rosls**:列出当前目录下所有可用的软件包
```cli
rosls [package_name]
```

## 2. create a ROS Package
<p id=2></p>

catkin软件包组成:
- 一个符合catkin规范的package.xml文件(这个package.xml文件提供有关该软件包的元信息)
- 一个catkin版本的CMakeLists.txt文件 
- 有自己的目录,意味着在同一个目录下不能有嵌套的或者多个软件包存在

> workspace_folder/        -- WORKSPACE
  src/                   -- SOURCE SPACE
    CMakeLists.txt       -- 'Toplevel' CMake file, provided by catkin
    package_1/
      CMakeLists.txt     -- CMakeLists.txt file for package_1
      package.xml        -- Package manifest for package_1
    ...
    package_n/
      CMakeLists.txt     -- CMakeLists.txt file for package_n
      package.xml        -- Package manifest for package_n

创建catkin软件包:
```cli
# 创建的空白catkin工作空间中的源文件空间目录
# 使用catkin_create_pkg命令创建新软件包
catkin_create_pkg <package_name> [depend1] [depend2] [depend3]
# 构建一个catkin工作区并生效配置文件
catkin_make
# 将这个工作空间添加到ROS环境中
source devel/setup.bash
```
软件包依赖关系
```cli
rospack depends1 <package_name>     #一级依赖包
rospack depends <package_name>      #间接依赖包
```

#### 自定义软件包
<p id=2.1></p>

##### 1. 自定义package.xml(more have to learn)
- 描述description标签
> ```<description>The beginner_tutorials package</description>```
- 维护者maintainer标签
> ```<maintainer email="user@todo.todo">user</maintainer>```
- 许可证license标签
> ```<!--   BSD, MIT, Boost Software License, GPLv2, GPLv3, LGPLv2.1, LGPLv3 -->```
> ```<license>TODO</license>```
- 依赖项dependence标签
依赖项分为build_depend、buildtool_depend、run_depend、test_depend
> ```<buildtool_depend>catkin</buildtool_depend>``` 
> ```<build_depend>roscpp</build_depend>```
> ```<exec_depend>roscpp</exec_depend>```

<p id=2.2></p>

##### 2. 自定义CMakeLists.txt (more have to learn)
[ROS官方文档学习CMakeLists.txt](https://wiki.ros.org/catkin/CMakeLists.txt)
- **CMake Version版本**
> ```cmake_minimum_required(VERSION 3.0.2)```
- **Package name项目名称**
> ```project(<package_name>)```
在以后的CMake脚本中的任何位置引用项目名称: ${PROJECT_NAME}
- **Finding Dependent CMake Packages寻找依赖**
> ```find_package(catkin REQUIRED COMPONENTS roscpp)```
意味着roscpp导出的include路径、库等也被附加到catkin_变量中
- **CMake macro宏**
>```
>   catkin_package(INCLUDE_DIRS include 
>                  LIBRARIES beginner_tutorials
>                  CATKIN_DEPENDS roscpp rospy std_msgs
>                  DEPENDS system_lib)
>```
>- INCLUDE_DIRS 导出包的包含路径
>- LIBRARIES 导出包的库
>- CATKIN_DEPENDS 导出包所依赖的其他CATKIN项目
>- DEPENDS 导出包所依赖的其他非CATKIN项目
>- CFG_EXTRAS 其他配置选项
- **Specifying Build Targets(to be completed)**
    - Executable Target: 可以运行的程序
    - Library Target: 可执行目标在构建和/或运行时使用的库
1. **Target Naming**
> ```
> set_target_properties(beginner_tutorials 
>                          PROPERTIES OUTPUT_NAME "beginner"
>                          PREFIX "") 
>```
2. **Custom output director**y
>```
> set_target_properties(beginner_tutorials
>                          PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib") 
>```
3. **Include Paths and Library Paths**
    - Include Paths: 正在构建的代码的头文件的路径
    - Library Paths: 可执行目标构建所依据的库的路径
>```
>   include_directories(include ${catkin_INCLUDE_DIRS})
>   link_directories(${catkin_LIBRARY_DIRS})
>```
1. **Executable Targets**
>```add_executable(myProgram src/main.cpp)```
1. **Library Targets**
>```
>add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})
>target_link_libraries(<executableTargetName>, <lib1>, <lib2>, ... <libN>)
>```
- **Messages(.msg), Services(.srv), and Action(.action) Targets**
>```add_message_files()```
>```add_service_files()```
>```add_action_files()```

>```generate_messages()```
- **Specifying Installable Targets**
在构建时之后，目标被放置到catkin工作空间的devel空间中
希望能够对代码进行“make install”，则需要指定目标的最终位置
    - TARGETS 要安装的目标
    - ARCHIVE DESTINATION 静态库和DLL（Windows）.lib存根
    - LIBRARY DESTINATION 非DLL共享库和模块
    - RUNTIME DESTINATION 可执行目标和DLL（Windows）风格的共享库
>```
>install(TARGETS ${PROJECT_NAME}
>  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
>  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
>  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
>```
- Install header files
>```
>install(DIRECTORY include/${PROJECT_NAME}/
>  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
>  PATTERN ".svn" EXCLUDE)
>```
- Install launch files
>```
>install(DIRECTORY launch/
>  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
>  PATTERN ".svn" EXCLUDE)
>```

## 1. build the ROS Package
<p id=3></p>

```source /opt/ros/noetic/setup.bash    #设置环境```
简化了标准catkin工作流程:
```cli
catkin_make
catkin_make install 
```
- **build** 目录是构建空间的默认位置，同时cmake和make也是在这里被调用来配置和构建你的软件包
- **devel** 目录是开发空间的默认位置, 在安装软件包之前，这里可以存放可执行文件和库。

## 4. learn about ROS Node
<p id=4></p>

##### 图概念
计算图(**Computation Graph**)是一个由ROS进程组成的点对点网络，它们能够共同处理数据。ROS的基本计算图概念有节点(**Nodes**)、主节点(**Master**)、参数服务器(**Parameter Server**)、消息(**Messages**)、服务(**Services**)、话题(**Topics**)和袋(**Bags**)，它们都以不同的方式向图提供数据
  
  - 节点（Nodes）：节点是一个可执行文件，它可以通过ROS来与其他节点进行通信
  - 消息（Messages）：订阅或发布话题时所使用的ROS数据类型
  - 话题（Topics）：节点可以将消息发布到话题，或通过订阅话题来接收消息
  - 主节点（Master）：ROS的命名服务，例如帮助节点发现彼此

```roscore  #在运行所有ROS程序前首先要运行的命令```
```cli
rosnode list  #查看当前运行的节点
rosnode info </node_name>  #返回的是某个指定节点的信息
rosnode ping </node_name>  #返回的是某个指定节点与主节点的连接状态
rosnode kill </node_name>  #杀死某个指定节点
```
```rosrun [package_name] [node_name]  #运行软件包内的节点```

### 4.1 ROS Topic
<p id=4.1></p>

节点之间是通过一个ROS**话题**来相互通信的
```cli
rostopic list [-v]            #查看当前运行的话题节点
rostopic echo </topic_name>   #查看某个指定话题的消息
rostopic type </topic_name>   #查看某个指定话题的消息类型
rostopic pub [topic] [msg_type] [args]  #把数据发布到当前某个正在广播的话题上
rostopic hz </topic_name>     #查看某个指定话题的发布频率
rostopic find [topic_type]    #查找某个指定类型的所有话题
```

### 4.2 ROS Service
<p id=4.2></p>

服务允许节点发送一个**请求(request)** 并获得一个**响应(response)**
```cli
rosservice list         #输出活跃服务的信息
rosservice call </service_name> [args]          #用给定的参数调用服务
rosservice type </service_name> | rossrv show   #输出服务的类型
rosservice find         #按服务的类型查找服务
rosservice uri          #输出服务的ROSRPC uri
```

### 4.3 ROS Param
<p id=4.3></p>

在ROS **参数服务器(Parameter Server)** 上存储和操作数据,使用YAML标记语言的语法
-  整型(integer): 1
-  浮点型(float): 1.0
-  字符串(string): "one"
-  布尔型(boolean): true
-  列表(list): [1, 2, 3]
-  字典(dictionaries): {a: b, c: d}
```cli
rosparam list           #列出参数名
rosparam set </param_name>              #设置参数
rosparam get </param_name>              #获取参数
rosparam load [file_name] [namespace]   #从文件中加载参数
rosparam dump [file_name] [namespace]   #向文件中转储参数
rosparam delete         #删除参数
```

### 5 rqt & roslaunch & rosed
<p id=5></p>

#### rqt
[about ros rqt](https://wiki.ros.org/cn/ROS/Tutorials/UsingRqtconsoleRoslaunch)
- **rqt_console**: 连接到了ROS的日志框架，以显示节点的输出信息
- **rqt_logger_level**: 在节点运行时改变输出信息的详细级别(**Fatal**、**Debug**、**Warn**、**Info**、**Error**)

#### roslaunch
用来启动定义在launch(启动)文件中的节点
``` roslaunch [package] [filename.launch] ```
[a example for launch file](./catkin_ws/src/beginner_tutorials/launch/turtlemimic.launch)
```cli
#在创建和构建的软件包目录下创建一个launch目录
#创建一个***.launch的launch文件
```

#### rosed
通过软件包名编辑包中的文件，而无需键入完整路径
``` rosed [package] [filename] ```

## 6. learn about ROS Interface
<p id=6></p>

### 6.1 ROS msg
<p id=6.1></p>

**msg(消息)**: msg文件就是文本文件，用于描述ROS消息的字段。它们用于为不同编程语言编写的消息生成源代码。msg文件存放在软件包的msg目录下。
>- int8, int16, int32, int64, uint*
>- float32, float64
>- string
>- time, duration, Header
>- other msg file
>- variable-length array[] & fixed-length array[N] 

[创建示例:](./catkin_ws/src/beginner_tutorials/msg/Num.msg)
```cli
roscd beginner_tutorials
mkdir msg
echo "int64 num" > msg/Num.msg
```

### 6.2 ROS srv
<p id=6.1></p>

**srv(服务)**: srv文件用于描述ROS服务的请求(request)和响应(response)。它们用于为不同编程语言编写的服务生成源代码。srv文件存放在软件包的srv目录下。
>- 请求(request)
>- \---     
>- 响应(response)

[创建示例:](./catkin_ws/src/beginner_tutorials/srv/AddTwoInts.srv)

[修改package.xml](./catkin_ws/src/beginner_tutorials/package.xml)
```xml
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
```
[修改CMakeLists.txt](./catkin_ws/src/beginner_tutorials/CMakeLists.txt)
```CMakeLists.txt
# 调用添加message_generation依赖项
find_package(catkin REQUIRED COMPONENTS
    ...
    message_generation)
# 导出消息的运行时依赖关系
catkin_package(
  # ...
  CATKIN_DEPENDS message_runtime ...
  # ...)
# 生成msg文件
add_message_files(
  FILES
  Num.msg)
# 生成srv文件
add_service_files(
  FILES
  AddTwoInts.srv)
# 生成msg和srv的依赖项
generate_messages(
  DEPENDENCIES
  std_msgs)
```
```cli
roscp [package_name] [file_to_copy_path] [copy_path]
rosmsg show [message type]
rossrv show [service type]
```

### 6.3 ROS action
<p id=6.3></p>
<!-- TODO -->

## 7. create a Publisher & Subscriber Node
<p id=7></p>

1. [这是一个发布者的C++示例](./catkin_ws/src/beginner_tutorials/src/talker.cpp)
2. [这是一个订阅者的C++示例](./catkin_ws/src/beginner_tutorials/src/listener.cpp)
3. 修改CMakeLists.txt
```CMakeLists.txt
# publisher
add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
add_dependencies(talker beginner_tutorials_generate_messages_cpp)

# subscriber
add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener beginner_tutorials_generate_messages_cpp)
```
- 这将创建两个可执行文件talker和listener，默认情况下，它们将被放到软件包目录下的devel空间中,即```~/catkin_ws/devel/lib/<package name>```
- 必须为可执行目标添加依赖项到消息生成目标,确保了在使用此包之前生成了该包的消息头
4. 测试发布者和订阅者
```cli
# 第一个终端
catkin_make
roscore
# 第二个终端
cd ~/catkin_ws
source ./devel/setup.bash
rosrun beginner_tutorials talker
# 第三个终端
cd ~/catkin_ws
source ./devel/setup.bash
rosrun beginner_tutorials listener
```

## 8. create a Service & Client Node
<p id=8></p>

1. [这是一个服务端的C++示例](./catkin_ws/src/beginner_tutorials/src/server.cpp)
2. [这是一个客户端的C++示例](./catkin_ws//src/beginner_tutorials/src/client.cpp)
3. 修改CMakeLists.txt
```CMakeLists.txt
# server
add_executable(server src/server.cpp)
target_link_libraries(server ${catkin_LIBRARIES})
add_dependencies(server beginner_tutorials_gencpp)

# client
add_executable(client src/client.cpp)
target_link_libraries(client ${catkin_LIBRARIES})
add_dependencies(client beginner_tutorials_gencpp)
```
- 这将创建两个可执行文件server和client，默认情况下，它们将被放到软件包目录下的devel空间中,即```~/catkin_ws/devel/lib/<package name>```
- 
1. 测试服务端和客户端
```cli
# 第一个终端
catkin_make
roscore
# 第二个终端
cd ~/catkin_ws
source ./devel/setup.bash
rosrun beginner_tutorials server
# 第三个终端
cd ~/catkin_ws
source ./devel/setup.bash
rosrun beginner_tutorials client 1 3
```

