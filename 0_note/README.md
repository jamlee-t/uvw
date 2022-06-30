# 编译安装命令

```
cmake --build . --target clean
cmake .. -DUSE_LIBCPP=OFF -DBUILD_UVW_LIBS=ON -DBUILD_TESTING=ON
cmake --build .

ctest -j4 -R uvw

cmake --install .

# 或者
ninja

# 安装到指定目录
cmake --install . --prefix /root/code/uvw/0_note/demo
```
编译自己写的 C++
```
g++ main.cc -Iinclude/uvw/uv/include -Iinclude -Llib -Llib/uvw -luv_a -luvw -lpthread  -ldl -std=c++17 -o main
```