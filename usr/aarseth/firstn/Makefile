include $(NEMOLIB)/makedefs

#FFLAGS = -O2
#FC = f77

TIME = /usr/bin/time

SOURCE = \
firstn.f data.f energy.f force.f \
input.f intgrt.f output.f ran2.f scale.f

OBJECTS = $(SOURCE:.f=.o)

all:	firstn

firstn:	$(OBJECTS)
	$(FC) $(FFLAGS) $(OBJECTS) -o firstn

clean:
	rm -f *.o firstn core

N = 16 32 64 128 256

bench: firstn
	-@for i in $(N); do\
	(echo $$i 12.0 0.0 1.0 10.0 > input$$i;\
	 echo 1.0 1.0 1.0 0 >> input$$i;\
	 echo 0.5 0 >> input$$i;\
         $(TIME) ./firstn < input$$i > bench$$i.log); done
 
# Example 1 from the manybody guide
ex1:
	firstn < input
