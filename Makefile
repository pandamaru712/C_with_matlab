vpath %.c src
vpath %.h include

#CFLAGS = -I/Applications/MATLAB_R2014a.app/extern/include
OBJDIR = ./objects
LIBDIR = -L/Applications/MATLAB_R2014a.app/bin/maci64


PROG := C_with_matlab
SRCS := main.c
OBJS := $(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))
DEPS := $(SRCS:%.c=%.d)
LIBS := -leng -lmx

CC := gcc

all: $(PROG)

-include $(DEPS)

$(PROG): $(OBJS)
	$(CC) -Wall -g -O0 -o $@ $^ $(LIBDIR) $(LIBS)

$(OBJDIR)/%.o: %.c
	@[ -d $(OBJDIR) ]
	$(CC) -Iinclude -g -MMD -MP -o $@ -c $<

clean:
	rm -f $(OBJS) $(DEPS)
