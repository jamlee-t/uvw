tcp: tcp.cc
	g++ $? -std=c++17 -Iinclude/uvw/uv/include -I../../src/ -Llib -Llib/uvw -luv_a -luvw -lpthread -ldl -o tcp

idle: idle.cc
	g++ $? -std=c++17 -Iinclude/uvw/uv/include -I../../src/ -Llib -Llib/uvw -luv_a -luvw -lpthread -ldl -o idle

demo001: demo001.cc
	g++ $? -o $@

clean:
	@rm -f tcp idle demo001