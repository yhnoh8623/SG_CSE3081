cc = g++
target = mp3_20181264
objects = mp3_20181264.o

$(target) : $(objects)
	$(cc) -o $(target) $(objects)

%.o : %.c
	$(cc) -c -o $@ $<

.PHONY : clean
clean :
	rm *.o $(target)