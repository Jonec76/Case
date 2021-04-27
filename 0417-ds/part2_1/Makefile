CC:=g++ -MMD
exe:=main
obj:=main.o 

.PHONY:clean
all:$(obj)
	$(CC) -o $(exe) $(obj)  
%.o:%.cpp %.h
	$(CC) -c $^ -o $@

clean:
	rm -rf $(obj) $(exe)
	rm -f *.d