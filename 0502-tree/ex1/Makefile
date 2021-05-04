CC:=gcc 
exe:=main
obj:=main.o in2post.o
.PHONY:clean
all:$(obj)
	$(CC) -o $(exe) $(obj)  
%.o:%.c
	$(CC) -c $^ -o $@

clean:
	rm -rf $(obj) $(exe)
	rm -f *.d