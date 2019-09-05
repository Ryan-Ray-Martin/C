CC	= gcc
CFLAGS	= -Wall
LDFLAGS =
OBJFILES= a5_matrix.o a5_bits.o a5_list.o
TARGET	= stacktest

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
