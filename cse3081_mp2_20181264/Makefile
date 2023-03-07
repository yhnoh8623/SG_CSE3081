cc = g++
target = mp2_20181264
objects = mp2_20181264.o

$(target) : $(objects)
	$(cc) -o $(target) $(objects)

%.o: %.c
	$(cc) -c -o $@ $<

.PHONY : clean
clean :
	rm *.o $(target)
