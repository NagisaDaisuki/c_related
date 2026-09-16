# GCC 编译常用选项与注意事项

> 环境参考:GCC 16.2.1 (Arch Linux)。以编译 C++ 为主线,兼带 C。

## 一、最常用的基本命令

```bash
# 最简编译(生成可执行文件 a.out)
g++ main.cpp

# 分步执行:源码 -> 预处理 -> 编译 -> 汇编 -> 链接
g++ -E main.cpp -o main.i   # 只预处理
g++ -S main.i -o main.s     # 只编译(生成汇编)
g++ -c main.s -o main.o     # 只汇编(生成目标文件)
g++ main.o other.o -o app   # 链接

# 一步到位 + 多文件
g++ -std=c++20 main.cpp utils.cpp -o app

# 一条命令等价写法:开警告、调试信息、优化
g++ -std=c++20 -Wall -Wextra -Wpedantic -g -O2 main.cpp -o app
```

## 二、语言标准选项(重点)

| 选项 | 含义 |
|---|---|
| `-std=c++11` / `c++14` / `c++17` / `c++20` / `c++23` | 指定 C++ 标准,推荐写明确的标准而不是默认值 |
| `-std=c++2a` / `2b` / `2c` | 旧写法,等价于 c++20/23/26,新代码别用 |
| `-std=gnu++17` 等 | GCC 默认风格,在标准之上附加 GNU 扩展(如 `typeof`),写移植代码时避免 |
| `-ansi` | 对 C++ 相当于 `-std=c++98` |

注意事项:

- **GCC 默认是 `gnu++xx`(带 GNU 扩展),不是 ISO 标准**。可用 `__cplusplus` 宏检查当前标准(见本目录 `What_language_standard_is_my_compiler_using.cpp`)。
  - 注意:GCC 对 `c++98` 的 `__cplusplus` 返回 `1`,需用其他方法区分。
- 查看编译器默认标准:`g++ -dM -E -x c++ /dev/null | grep __cplusplus`
- 老项目注意 GCC 15 起默认标准已升到 `gnu++17`(GCC 11~14 默认 `gnu++17`,GCC 15/16 仍为 17,但更早版本默认是 `gnu++14`)。

## 三、警告选项(强烈建议常开)

| 选项 | 含义 |
|---|---|
| `-Wall` | 开启大部分常用警告(名字有误导性,并非"所有") |
| `-Wextra` | 在 `-Wall` 之外的补充警告(如未使用参数、有符号/无符号比较) |
| `-Wpedantic` | 对标准之外的扩展用法发警告(配合 `-std=` 使用) |
| `-Werror` | 把所有警告当错误,强制干净代码 |
| `-Wshadow` | 局部变量遮蔽外层变量时警告 |
| `-Wconversion` | 可能丢失数据的隐式类型转换警告 |
| `-Wold-style-cast` | C 风格强转警告(C++ 推荐 `static_cast` 等) |
| `-Wnull-dereference`、`-Wdouble-promotion`、`-Wformat=2` | 进阶实用警告 |

```bash
# 学习/个人项目推荐组合
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror ...
```

注意事项:

- `-Wall` **不包含**所有警告,别被名字骗了。
- 第三方库的头文件可能触发大量警告,可用 `#pragma GCC diagnostic push/ignored` 局部关闭。

## 四、优化选项

| 选项 | 含义 |
|---|---|
| `-O0` | 不优化(默认),编译最快,配合 `-g` 调试体验最好 |
| `-O1` | 基本优化,编译时间适中 |
| `-O2` | 常用发布级别优化,不含空间换速度的激进手段 |
| `-O3` | 更激进(向量化、内联更积极),可能增大体积、不一定更快 |
| `-Os` | 针对代码体积优化 |
| `-Ofast` | `-O3` + 违反标准的浮点优化(如允许重排、假设无 NaN),**慎用** |
| `-Og` | 调试友好级优化,比 `-O0` 快一些且保留调试体验 |

注意事项:

- **调试必须用 `-O0 -g`**。`-O2` 及以上会内联、重排代码,断点会"乱跳",变量被优化掉。
- `-O2` 是发布构建的事实标准;未定义行为(UB)在高级别优化下可能表现为更诡异的现象。
- 优化级别只影响优化,**不含警告**,`-Wall -Wextra` 需要单独写。

## 五、调试与性能分析

| 选项 | 含义 |
|---|---|
| `-g` | 生成调试信息(gdb/lldb/valgrind 需要) |
| `-g3` | 附带宏定义等更多信息 |
| `-ggdb` | 为 GDB 定制格式 |
| `-pg` | 插入 gprof 性能分析代码 |
| `-fno-omit-frame-pointer` | 保留帧指针,perf 等分析工具调用栈更完整 |

## 六、头文件与库的搜索路径

| 选项 | 含义 |
|---|---|
| `-I<dir>` | 添加头文件搜索目录(大写 i) |
| `-iquote<dir>` | 仅对 `#include "..."` 生效的搜索目录 |
| `-L<dir>` | 添加库文件搜索目录(链接期) |
| `-l<name>` | 链接 `lib<name>.so` 或 `lib<name>.a`(如 `-l pthread` 链接 pthread) |
| `-static` | 静态链接(对 `-l` 找到的库优先用 `.a`) |
| `-static-libstdc++` | 只静态链接 libstdc++ |
| `-Wl,<option>` | 把选项直接传给链接器,如 `-Wl,-rpath,/opt/mylib/lib` |

注意事项(链接顺序很重要):

- **`-l` 选项的顺序有讲究**:被依赖的库要放在依赖它的文件**之后**。
  ```bash
  # 正确:main 用到 math 库
  g++ main.cpp -l m
  # 错误:g++ -l m main.cpp
  ```
- 循环依赖可用 `-Wl,--start-group ... -Wl,--end-group` 解决,或重复写库。
- 运行期找不到 `.so`:用 `LD_LIBRARY_PATH` 环境变量,或链接时加 `-Wl,-rpath,<dir>` 固化路径。

## 七、预处理与宏

| 选项 | 含义 |
|---|---|
| `-DNAME=value` | 定义宏(等价 `#define`),如 `-DNDEBUG`、`-DVERSION=2` |
| `-UNAME` | 取消宏定义 |
| `-DNDEBUG` | 关闭 `assert`(发布版应定义) |
| `-include <file>` | 强制先包含某头文件 |
| `-M` / `-MM` | 生成依赖关系(供 Makefile 使用) |
| `-dM -E` | 输出所有预定义宏,查看编译器内置宏 |

## 八、诊断与输出控制

| 选项 | 含义 |
|---|---|
| `-v` | 打印详细执行过程(驱动调用的命令、搜索路径) |
| `-###` | 只打印会执行的命令而不真正执行 |
| `-save-temps` | 保留中间文件(`.i/.s/.o`),查看预处理结果很有用 |
| `-fsyntax-only` | 只做语法检查,不生成文件 |
| `-fdiagnostics-color=always` | 强制彩色错误信息 |
| `-fmax-errors=N` | 限制最多显示 N 个错误 |
| `-H` | 打印每个头文件的包含路径 |

## 九、C++ 特有选项

| 选项 | 含义 |
|---|---|
| `-fno-exceptions` | 禁用异常(嵌入式/游戏引擎常用) |
| `-fno-rtti` | 禁用 RTTI(`typeid`/`dynamic_cast`) |
| `-fno-threadsafe-statics` | 关闭局部 static 初始化的线程安全保护 |
| `-fvisibility=hidden` | 默认隐藏符号,配合导出宏做动态库 |
| `-fconcepts-diagnostics-depth=N` | 概念(concepts)报错展开深度 |

## 十、常见注意事项汇总

1. **编译不开警告是最大坑**:养成 `-Wall -Wextra -Wpedantic` 起步的习惯。
2. **调试与优化冲突**:`-g` 配 `-O0`(或 `-Og`),发布配 `-O2`,不要配反了。
3. **默认标准不等于最新标准**:显式写 `-std=c++20` 等便于跨环境一致。
4. **链接顺序**:目标文件在前,库在后;库之间有依赖时被依赖者放后面。
5. **UB 与优化**:未定义行为在 `-O2/-O3` 下可能"消失"或表现异常,别拿调试结论套发布行为。
6. **头文件依赖**:改了头文件记得重新编译所有包含它的文件,Makefile 用 `-MMD -MP` 自动生成依赖。
7. **重定义/找不到符号**:检查是否重复定义全局符号、是否漏链接或链接了错误架构的库。
8. **`-I` 只影响编译期,`-L`/`-l` 只影响链接期**,运行期找库看 `rpath` / `LD_LIBRARY_PATH` / 系统路径。
9. **查看一切宏与定义**:`g++ -dM -E -x c++ /dev/null` 是排查标准兼容问题的利器。
10. **GCC 与 Clang 差异**:两个编译器都过一遍是检验代码可移植性的好习惯(`clang++` 选项大体兼容)。

## 十一、常用组合速查

```bash
# 日常学习/调试
g++ -std=c++20 -Wall -Wextra -Wpedantic -g -O0 main.cpp -o app

# 发布构建
g++ -std=c++20 -Wall -Wextra -O2 -DNDEBUG main.cpp -o app

# 生成静态库
g++ -c a.cpp b.cpp && ar rcs libmy.a a.o b.o

# 生成动态库
g++ -fPIC -shared a.cpp -o libmy.so

# 查看 .so/.o 导出符号
nm -C libmy.so | grep ' T '
ldd app          # 查看动态库依赖
```
