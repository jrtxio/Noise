# CppNoise Tests

## 新增功能测试

本目录包含 CppNoise 新功能的测试程序。

### 测试文件

1. **FutureTest.cpp** - Future API 测试
   - 基本 resolve/reject
   - 取消机制
   - 超时等待
   - Map 链式操作
   - 工厂方法

2. **SerdeTest.cpp** - 序列化测试
   - 基本类型（bool, int16, uint16, int32, float32, string）
   - Varint 编码
   - Vector 序列化
   - Map 序列化
   - Optional 序列化

## 编译说明

### 使用 Visual Studio

1. 打开 Visual Studio
2. 文件 → 新建 → 项目
3. 选择 "Console App" (C++)
4. 添加测试文件到项目
5. 设置包含目录：项目属性 → C/C++ → 常规 → 附加包含目录
   - 添加: `d:\Codes\Noise\CppNoise\Sources`
6. 编译并运行

### 使用 CMake (推荐)

创建 `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.15)
project(CppNoiseTests)

set(CMAKE_CXX_STANDARD 17)

include_directories(../Sources)

# Future Test
add_executable(FutureTest FutureTest.cpp)

# Serde Test  
add_executable(SerdeTest SerdeTest.cpp)
```

编译:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

运行:
```bash
.\Debug\FutureTest.exe
.\Debug\SerdeTest.exe
```

### 使用命令行 (MSVC)

```bash
# Future Test
cl /EHsc /std:c++17 /I..\Sources FutureTest.cpp

# Serde Test
cl /EHsc /std:c++17 /I..\Sources SerdeTest.cpp
```

## 预期输出

### FutureTest

```
[10:33:05.123] [INFO ] === Starting Future Tests ===
[10:33:05.124] [INFO ] Testing basic future resolution...
[10:33:05.225] [INFO ] Result: 42
[10:33:05.225] [INFO ] ✓ Basic resolve test PASSED
[10:33:05.226] [INFO ] Testing future cancellation...
[10:33:05.327] [INFO ] ✓ Cancellation test PASSED
[10:33:05.328] [INFO ] Testing future timeout...
[10:33:05.429] [INFO ] ✓ Timeout test PASSED
[10:33:05.430] [INFO ] Testing future map...
[10:33:05.531] [INFO ] ✓ Map test PASSED
[10:33:05.532] [INFO ] Testing factory methods...
[10:33:05.532] [INFO ] ✓ Factory method test PASSED
[10:33:05.533] [INFO ] === All tests completed ===
```

### SerdeTest

```
[10:34:00.123] [INFO ] === Starting Serde Tests ===
[10:34:00.124] [INFO ] Testing basic type serialization...
[10:34:00.125] [INFO ] ✓ Basic types test PASSED
[10:34:00.126] [INFO ] Testing varint serialization...
[10:34:00.127] [INFO ] ✓ Varint test PASSED
[10:34:00.128] [INFO ] Testing vector serialization...
[10:34:00.129] [INFO ] ✓ Vector test PASSED
[10:34:00.130] [INFO ] Testing map serialization...
[10:34:00.131] [INFO ] ✓ Map test PASSED
[10:34:00.132] [INFO ] Testing optional serialization...
[10:34:00.133] [INFO ] ✓ Optional test PASSED
[10:34:00.134] [INFO ] === All Serde tests completed ===
```

## 要求

- C++17 或更高版本
- Windows (MSVC 或 Clang-CL)
- 标准库支持 `<optional>`, `<unordered_map>`

## 注意事项

- 所有测试都是独立的，可以单独运行
- 测试使用简单的 assert 进行验证
- 日志级别默认为 INFO，可以通过 `Logger::setLevel()` 修改
