GCC=g++ -g -Wall 
TARGET=main
TARGET2=func
EXT=cpp
$(TARGET): $(TARGET).$(EXT) $(TARGET2).$(EXT)
	$(GCC) $(TARGET).$(EXT) $(TARGET2).$(EXT) -lgmpxx -lgmp -lm -o $(TARGET) 
clean:
	rm -f *.o *~ $(TARGET) *.log
clean2:
	rm -f *.o *~ $(TARGET) *.log data*
