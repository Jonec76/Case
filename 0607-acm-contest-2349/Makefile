CXX:=g++ -MMD
exe:=main
obj:=main.o

.PHONY:clean
all:$(obj) 
	$(CXX) -o $(exe) $(obj)  
%.o:%.cpp %.h
	$(CXX) -c $^ -o $@

clean:
	rm -rf $(obj) $(exe)
	rm -f *.d